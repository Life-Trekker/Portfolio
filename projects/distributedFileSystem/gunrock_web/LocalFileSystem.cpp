#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <cstring>

#include "./include/LocalFileSystem.h"
#include "./include/Disk.h"

using namespace std;

LocalFileSystem::LocalFileSystem(Disk *disk)
{
  this->disk = disk;
}

void LocalFileSystem::readSuperBlock(super_t *super)
{
  unsigned char buffer[UFS_BLOCK_SIZE];
  disk->readBlock(0, buffer);

  *super = *(super_t *)buffer;
}

void LocalFileSystem::readInodeBitmap(super_t *super, unsigned char *inodeBitmap)
{
  for (int i = 0; i < super->inode_bitmap_len; i++)
  {
    disk->readBlock(super->inode_bitmap_addr + i, inodeBitmap + (i * UFS_BLOCK_SIZE));
  }

}

void LocalFileSystem::writeInodeBitmap(super_t *super, unsigned char *inodeBitmap)
{
  for (int i = 0; i < super->inode_bitmap_len; i++)
  {
    disk->writeBlock(super->inode_bitmap_addr + i, inodeBitmap + (i * UFS_BLOCK_SIZE));
  }
}

void LocalFileSystem::readDataBitmap(super_t *super, unsigned char *dataBitmap)
{
  for (int i = 0; i < super->data_bitmap_len; i++)
  {
    disk->readBlock(super->data_bitmap_addr + i, dataBitmap + (i * UFS_BLOCK_SIZE));
  }

}

void LocalFileSystem::writeDataBitmap(super_t *super, unsigned char *dataBitmap)
{
  for (int i = 0; i < super->data_bitmap_len; i++)
  {
    disk->writeBlock(super->data_bitmap_addr + i, dataBitmap + (i * UFS_BLOCK_SIZE));
  }

}

void LocalFileSystem::readInodeRegion(super_t *super, inode_t *inodes)
{
  for (int i = 0; i < super->inode_region_len; i++)
  {
    disk->readBlock(super->inode_region_addr + i, (char*)inodes + (i * UFS_BLOCK_SIZE));
  }

}

void LocalFileSystem::writeInodeRegion(super_t *super, inode_t *inodes)
{
  for (int i = 0; i < super->inode_region_len; i++)
  {
    disk->writeBlock(super->inode_region_addr + i, (char*)inodes + (i * UFS_BLOCK_SIZE));
  }

}

int LocalFileSystem::lookup(int parentInodeNumber, string name)
{
  super_t super;
  readSuperBlock(&super);

  // determine if the parent is valid
  if (parentInodeNumber < 0 || parentInodeNumber >= super.num_inodes)
  {
    return -EINVALIDINODE;
  }

  inode_t parentInode;
  stat(parentInodeNumber, &parentInode);
  
  int numEntries = parentInode.size / sizeof(dir_ent_t);

  dir_ent_t *entries;  
  dir_ent_t entry;
  int blockIndex = 0;
  int entryIndex = 0;

  unsigned char buffer[UFS_BLOCK_SIZE];
  
  int entriesPerBlock = UFS_BLOCK_SIZE / sizeof(dir_ent_t);

  // search all the entries in the parent directory for the name, and return the inode number if found
  for (int i = 0; i < numEntries; i++)
  {
    blockIndex = i / entriesPerBlock;
    entryIndex = i % entriesPerBlock;

    disk->readBlock(parentInode.direct[blockIndex], buffer);

    entries = (dir_ent_t *)buffer;
    entry = entries[entryIndex];


    if (name == string(entry.name))
    {
      return entry.inum;
    }

  }
  
  // if the name is not found, return error
  return -ENOTFOUND;

}

int LocalFileSystem::stat(int inodeNumber, inode_t *inode)
{

  super_t super;
  readSuperBlock(&super);

  // check if the inode number is valid
  if (inodeNumber < 0 || inodeNumber >= super.num_inodes)
  {
    return -EINVALIDINODE;
  }

  int numInodesPerBlock = UFS_BLOCK_SIZE / sizeof(inode_t);

  int addressOffset = inodeNumber / numInodesPerBlock;
  int blockIndex = inodeNumber % numInodesPerBlock;

  unsigned char buffer[UFS_BLOCK_SIZE];

  disk->readBlock(super.inode_region_addr + addressOffset, buffer);

  // copy the type and size of the inode
  inode_t *block = (inode_t *)buffer;

  inode->type = block[blockIndex].type;
  inode->size = block[blockIndex].size;

  // copy the direct block pointers
  int numDirectBlocks =  (inode->size + UFS_BLOCK_SIZE - 1) / UFS_BLOCK_SIZE;

  for (int i = 0; i < numDirectBlocks; i++)
  { 
    inode->direct[i] = block[blockIndex].direct[i];
  }



  return 0;
}

int LocalFileSystem::read(int inodeNumber, void *buffer, int size)
{
  
  super_t super;
  readSuperBlock(&super);

  // check if the inode number is valid
  if (inodeNumber < 0 || inodeNumber >= super.num_inodes)
  {
    return -EINVALIDINODE;
  }

  // read the inode to determine the type and size of the entry
  inode_t inodeToRead;
  stat(inodeNumber, &inodeToRead);

  if (size < 0 || size > inodeToRead.size)
  {
    return -EINVALIDSIZE;
  }

  unsigned char readBuffer[UFS_BLOCK_SIZE];
  int bytesRead = 0;
  int blockIndex = 0;

  if(inodeToRead.type == UFS_REGULAR_FILE)
  {
    // for regular files, we can read the data in chunks of UFS_BLOCK_SIZE and copy them into the output buffer
    char *output = (char *)buffer;

    while (bytesRead < size)
    {

      disk->readBlock(inodeToRead.direct[blockIndex], readBuffer);

      int bytesToCopy = min(UFS_BLOCK_SIZE, size - bytesRead);

      for (int i = 0; i < bytesToCopy; i++)
      {
        output[bytesRead + i] = readBuffer[i];
      }

      bytesRead += bytesToCopy;
      blockIndex++;

    }
    
    return bytesRead;
  }
  else if (inodeToRead.type == UFS_DIRECTORY)
  {

    // for directories, we need to read the data in chunks of dir_ent_t and copy them into the output buffer
    dir_ent_t* output = (dir_ent_t *)buffer;
    

    int numEntries =  size / sizeof(dir_ent_t);

    int numEntriesPerBlock = UFS_BLOCK_SIZE / sizeof(dir_ent_t);
    int idx = 0;
    int entryIndex = 0;

    while(idx < numEntries)
    {

      blockIndex = idx / numEntriesPerBlock;
      entryIndex = idx % numEntriesPerBlock;

      disk->readBlock(inodeToRead.direct[blockIndex], readBuffer);

      dir_ent_t *blockEntries = (dir_ent_t *)readBuffer;

      output[idx] = blockEntries[entryIndex];

      idx++;
      bytesRead += sizeof(dir_ent_t);
    }


    return bytesRead;
  }

  return -EINVALIDTYPE;
}

int LocalFileSystem::create(int parentInodeNumber, int type, string name)
{
  super_t super;
  readSuperBlock(&super);

  inode_t parentInode;
  int rc = stat(parentInodeNumber, &parentInode);

  if(rc != 0)
  {
    return -EINVALIDINODE;
  }

  if(parentInode.type != UFS_DIRECTORY)
  {
    return -EINVALIDINODE;
  }

  if(name.size() == 0 || name.size() >= DIR_ENT_NAME_SIZE)
  {
    return -EINVALIDNAME;
  }

  // search for the name in the parent directory, and if it already exists, return success if the type matches or error if it doesn't match
  unsigned char buffer[UFS_BLOCK_SIZE];
  int parentBytesRead = read(parentInodeNumber, buffer, parentInode.size);

  int numEntriesOfParent = parentBytesRead / sizeof(dir_ent_t);
  dir_ent_t *entries = (dir_ent_t *)buffer;

  for (int i = 0; i < numEntriesOfParent; i++)
  {
    if(name == string(entries[i].name))
    {
      inode_t existingInode;
      stat(entries[i].inum, &existingInode);

      if(type == existingInode.type)
      {
        return entries[i].inum;
      }
      else
      {
        return -EINVALIDNAME;
      }
    }
  }

  // write the new inode to the inode region, and add an entry to the parent directory with the new inode number and name.
  unsigned char inodeBitmap[super.inode_bitmap_len * UFS_BLOCK_SIZE];
  readInodeBitmap(&super, inodeBitmap);

  int newInodeNumber;
  bool isNewNumberAllocated = false;

  disk->beginTransaction();

  for (int i = 0; i < super.num_inodes; i++)
  {
    int byteIndex = i / 8;
    int bitIndex  = i % 8;

    if (!(inodeBitmap[byteIndex] & (1 << bitIndex)))
    {
      inodeBitmap[byteIndex] |= (1 << bitIndex);

      newInodeNumber = i;
      isNewNumberAllocated = true;

      break;
    }
  }

  if(!isNewNumberAllocated)
  {
    disk->rollback();

    return -ENOTENOUGHSPACE;
  }
  


  inode_t newInodeRegion[super.inode_region_len * UFS_BLOCK_SIZE / sizeof(inode_t)];
  readInodeRegion(&super, newInodeRegion);   

  newInodeRegion[newInodeNumber].type = type;
  newInodeRegion[newInodeNumber].size = 0;
  for(int i = 0; i < DIRECT_PTRS; i++)
  {
    newInodeRegion[newInodeNumber].direct[i] = 0;
  }
  
  // if creating a directory, we need to allocate a data block for it and write the '.' and '..' entries
  if(type == UFS_DIRECTORY)
  {
    unsigned char dataBitmap[super.data_bitmap_len * UFS_BLOCK_SIZE];
    readDataBitmap(&super, dataBitmap);

    int dataBlock;
    bool dataBlockFound = false;

    for (int i = 0; i < super.num_data; i++)
    {

      int byteIndex = i / 8;
      int bitIndex  = i % 8;

      if (!(dataBitmap[byteIndex] & (1 << bitIndex)))
      {
        dataBitmap[byteIndex] |= (1 << bitIndex);
        dataBlock = i;
        dataBlockFound = true;
        break;
      }
    }

    if (dataBlockFound == false)
    {
      return -ENOTENOUGHSPACE;
    }

    dir_ent_t entries[UFS_BLOCK_SIZE / sizeof(dir_ent_t)];
    memset(entries, 0, UFS_BLOCK_SIZE);

    strcpy(entries[0].name, ".");
    entries[0].inum = newInodeNumber;

    strcpy(entries[1].name, "..");
    entries[1].inum = parentInodeNumber;

    disk->writeBlock(super.data_region_addr + dataBlock, entries);
    writeDataBitmap(&super, dataBitmap);

    newInodeRegion[newInodeNumber].direct[0] = super.data_region_addr + dataBlock;
    newInodeRegion[newInodeNumber].size = 2 * sizeof(dir_ent_t);
  }

  int numEntries = parentInode.size / sizeof(dir_ent_t);
  dir_ent_t *parentEntries = new dir_ent_t[numEntries + 1];
  read(parentInodeNumber, parentEntries, parentInode.size);

  strcpy(parentEntries[numEntries].name, name.c_str());
  parentEntries[numEntries].inum = newInodeNumber;

  // allocate more blocks if needed
  int newNumberOfBlocks = ((numEntries + 1) * sizeof(dir_ent_t) + UFS_BLOCK_SIZE - 1) / UFS_BLOCK_SIZE;
  int oldNumberOfBlocks = (parentInode.size + UFS_BLOCK_SIZE - 1) / UFS_BLOCK_SIZE;

  unsigned char newDataBitmap[super.data_bitmap_len * UFS_BLOCK_SIZE];
  readDataBitmap(&super, newDataBitmap);

  if(newNumberOfBlocks > oldNumberOfBlocks)
  {
    if(oldNumberOfBlocks >= DIRECT_PTRS)
    {
      disk->rollback();
      delete[] parentEntries;
      return -ENOTENOUGHSPACE;
    }

    bool isNewBlockAllocated = false;
    int allocatedBlockNumber;

    for (int j = 0; j < super.num_data; j++)
    {

      int byteIndex = j / 8;
      int bitIndex  = j % 8;

      if (!(newDataBitmap[byteIndex] & (1 << bitIndex)))
      {
        newDataBitmap[byteIndex] |= (1 << bitIndex);

        allocatedBlockNumber = j;
        isNewBlockAllocated = true;

        break;
      }
    }

    if(isNewBlockAllocated == false)
    {
        disk->rollback();
        delete[] parentEntries;
        return -ENOTENOUGHSPACE;
    }

    parentInode.direct[oldNumberOfBlocks] = super.data_region_addr + allocatedBlockNumber;

    writeDataBitmap(&super, newDataBitmap);
  }
  
  // write the updated parent directory entries to disk
  int bytesWritten = 0;
  int newSize = (numEntries + 1) * sizeof(dir_ent_t);
  
  for(int i = 0; i < newNumberOfBlocks; i++)
  {
    unsigned char blockBuffer[UFS_BLOCK_SIZE];
    memset(blockBuffer, 0, UFS_BLOCK_SIZE);

    int bytesToCopy = min(UFS_BLOCK_SIZE, newSize - bytesWritten);
    memcpy(blockBuffer, (char*)parentEntries + bytesWritten, bytesToCopy);

    disk->writeBlock(parentInode.direct[i], blockBuffer);

    bytesWritten += bytesToCopy;
  }

  parentInode.size = newSize;
  memcpy(&newInodeRegion[parentInodeNumber], &parentInode, sizeof(inode_t));
 


  writeInodeBitmap(&super, inodeBitmap);
  writeInodeRegion(&super, newInodeRegion);

  disk->commit();

  delete[] parentEntries;

  return newInodeNumber;

}

int LocalFileSystem::write(int inodeNumber, const void *buffer, int size)
{
  inode_t inodeToWrite;
  int rc = stat(inodeNumber, &inodeToWrite);

  if(rc < 0)
  {
    return -EINVALIDINODE;
  }

  if(inodeToWrite.type == UFS_DIRECTORY)
  {
    return -EWRITETODIR;
  }

  if(inodeToWrite.type != UFS_REGULAR_FILE)
  {
    return -EINVALIDTYPE;
  }

  if(size < 0 || size > MAX_FILE_SIZE)
  {
    return -EINVALIDSIZE;
  }

  super_t super;
  readSuperBlock(&super);

  unsigned char dataBitmap[super.data_bitmap_len * UFS_BLOCK_SIZE];
  readDataBitmap(&super, dataBitmap);

  int newNumberOfBlocks = (size + UFS_BLOCK_SIZE - 1) / UFS_BLOCK_SIZE;
  int oldNumberOfBlocks = (inodeToWrite.size + UFS_BLOCK_SIZE - 1) / UFS_BLOCK_SIZE;

  disk->beginTransaction();

  // allocate more blocks if needed
  if(newNumberOfBlocks > oldNumberOfBlocks)
  {
    bool isNewBlockAllocated = false;
    int allocatedBlockNumber;

    for (int i = oldNumberOfBlocks; i < newNumberOfBlocks; i++)
    {
      isNewBlockAllocated = false;

      for (int j = 0; j < super.num_data; j++)
      {

        int byteIndex = j / 8;
        int bitIndex  = j % 8;

        if (!(dataBitmap[byteIndex] & (1 << bitIndex)))
        {
          dataBitmap[byteIndex] |= (1 << bitIndex);

          allocatedBlockNumber = j;
          isNewBlockAllocated = true;

          break;
        }
      }

      if(isNewBlockAllocated == false)
      {
        disk->rollback();
        size = i * UFS_BLOCK_SIZE;
        newNumberOfBlocks = i;

        break;
      }

      inodeToWrite.direct[i] = super.data_region_addr + allocatedBlockNumber;
    }

    writeDataBitmap(&super, dataBitmap);
  }
  else if (newNumberOfBlocks < oldNumberOfBlocks)
  {

    // free blocks that are no longer needed
    for (int i = oldNumberOfBlocks - 1; i >= newNumberOfBlocks; i--)
    {
      if (inodeToWrite.direct[i] == 0) 
      {
        continue;
      }

      int bitmapIndex = inodeToWrite.direct[i] - super.data_region_addr;

      int byteIndex = bitmapIndex / 8;
      int bitIndex  = bitmapIndex % 8;

      dataBitmap[byteIndex] &= ~(1 << bitIndex);

      inodeToWrite.direct[i] = 0;
    }

    writeDataBitmap(&super, dataBitmap);
  }


  unsigned char writeBuffer[UFS_BLOCK_SIZE];
  int bytesWritten = 0;
  int blockIndex = 0;

  while (bytesWritten < size)
  {

    memset(writeBuffer, 0, UFS_BLOCK_SIZE);

    int bytesToCopy = min(UFS_BLOCK_SIZE, size - bytesWritten);
    memcpy(writeBuffer, (char*)buffer + bytesWritten, bytesToCopy);

    disk->writeBlock(inodeToWrite.direct[blockIndex], writeBuffer);

    bytesWritten += bytesToCopy;
    blockIndex++;

  }


  //add the inode to the inode region
  inodeToWrite.size = size;
  inode_t newInodeRegion[super.inode_region_len * UFS_BLOCK_SIZE / sizeof(inode_t)];
  readInodeRegion(&super, newInodeRegion);
  memcpy(&newInodeRegion[inodeNumber], &inodeToWrite, sizeof(inode_t));

  writeInodeRegion(&super, newInodeRegion);

  disk->commit();


  return size;
  
}

int LocalFileSystem::unlink(int parentInodeNumber, string name)
{
  inode_t parentInode;
  int rc = stat(parentInodeNumber, &parentInode);

  if(rc != 0)
  {
    return -EINVALIDINODE;
  }

  if(parentInode.type != UFS_DIRECTORY)
  {
    return -EINVALIDINODE;
  }

  if(name == "." || name == "..")
  {
    return  -EUNLINKNOTALLOWED;
  }

  if(name.size() == 0 || name.size() >= DIR_ENT_NAME_SIZE)
  {
    return -EINVALIDNAME;
  }

  int inodeNumberToUnlink = lookup(parentInodeNumber, name);
  if (inodeNumberToUnlink < 0) {
    if (inodeNumberToUnlink == -ENOTFOUND) 
    {
      return 0;
    }
    else
    {
      return inodeNumberToUnlink;
    }

  }

  inode_t inodeToUnlink;
  stat(inodeNumberToUnlink, &inodeToUnlink);



  if(inodeToUnlink.type == UFS_DIRECTORY)
  {

    int numEntries = inodeToUnlink.size / sizeof(dir_ent_t);
    dir_ent_t *dirEntries = new dir_ent_t[numEntries];
    read(inodeNumberToUnlink, dirEntries, inodeToUnlink.size);

    for (int i = 0; i < numEntries; i++)
    {
      if(string(dirEntries[i].name) != "." && string(dirEntries[i].name) != "..")
      {
        delete[] dirEntries;
        return -EDIRNOTEMPTY;
      }
      
    }

    delete[] dirEntries;
  }

  super_t super;
  readSuperBlock(&super);

  // update the inode bitmap
  unsigned char newInodeBitmap[super.inode_bitmap_len * UFS_BLOCK_SIZE];

  readInodeBitmap(&super, newInodeBitmap);

  int byteIndex = inodeNumberToUnlink / 8;
  int bitIndex  = inodeNumberToUnlink % 8;

  newInodeBitmap[byteIndex] &= ~(1 << bitIndex);

  disk->beginTransaction();
  writeInodeBitmap(&super, newInodeBitmap);
  disk->commit();


  // update the data bitmap
  unsigned char newDataBitmap[super.data_bitmap_len * UFS_BLOCK_SIZE];
  readDataBitmap(&super, newDataBitmap);


  int numDirectBlocks =  (inodeToUnlink.size + UFS_BLOCK_SIZE - 1) / UFS_BLOCK_SIZE;
  
  for(int i = 0; i < numDirectBlocks; i++)
  {

    int dataIndex = inodeToUnlink.direct[i] - super.data_region_addr;

    int byteIndex = dataIndex / 8;
    int bitIndex  = dataIndex % 8;

    newDataBitmap[byteIndex] &=  ~(1 << bitIndex);
    
  }

  disk->beginTransaction();
  writeDataBitmap(&super, newDataBitmap);
  disk->commit();

  // find the index of the entry to remove from the parent
  int numParentEntries = parentInode.size / sizeof(dir_ent_t);
  dir_ent_t *parentEntries = new dir_ent_t[numParentEntries];
  read(parentInodeNumber, parentEntries, parentInode.size);

  int indexToRemove;
  bool found = false;
  for (int i = 0; i < numParentEntries; i++)
  {
    if (string(parentEntries[i].name) == name)
    {
      indexToRemove = i;
      found = true;
      break;
    }
  }

  if(found == false)
  {
    delete[] parentEntries;
    return 0;
  }

  // if the entry to remove is found, shift all entries after it back by one
  for (int i = indexToRemove + 1; i < numParentEntries; i++) {
    parentEntries[i - 1] = parentEntries[i];
  }
    
  int newSize = (numParentEntries - 1) * sizeof(dir_ent_t);
  int newBlocks = (newSize + UFS_BLOCK_SIZE - 1) / UFS_BLOCK_SIZE;
  int numParentBlocks = (parentInode.size + UFS_BLOCK_SIZE - 1) / UFS_BLOCK_SIZE;

  int bytesWritten = 0;
  for (int i = 0; i < newBlocks; i++) {
    if (inodeToUnlink.direct[i] == 0) 
    {
      continue;
    }

    unsigned char blockBuffer[UFS_BLOCK_SIZE];
    memset(blockBuffer, 0, UFS_BLOCK_SIZE);
        
    int bytesToCopy = (newSize - bytesWritten > UFS_BLOCK_SIZE) ? UFS_BLOCK_SIZE : (newSize - bytesWritten);
    memcpy(blockBuffer, (char*)parentEntries + bytesWritten, bytesToCopy);

    disk->writeBlock(parentInode.direct[i], blockBuffer);

    bytesWritten += bytesToCopy;
  }

  if (newBlocks < numParentBlocks) {

    readDataBitmap(&super, newDataBitmap);

    for(int i = newBlocks; i < numParentBlocks; i++) {

      if (parentInode.direct[i] != 0) {

        int blockIdx = parentInode.direct[i] - super.data_region_addr;
        int byteIndex = blockIdx / 8;
        int bitIndex  = blockIdx % 8;

        newDataBitmap[byteIndex] &= ~(1 << bitIndex);
        parentInode.direct[i] = 0;
      }
    }

    disk->beginTransaction();
    writeDataBitmap(&super, newDataBitmap);
    disk->commit();
  }
    
  parentInode.size = newSize;

  inode_t newInodeRegion[super.inode_region_len * UFS_BLOCK_SIZE / sizeof(inode_t)];

  readInodeRegion(&super, newInodeRegion);
  memcpy(&newInodeRegion[parentInodeNumber], &parentInode, sizeof(inode_t));

  disk->beginTransaction();
  writeInodeRegion(&super, newInodeRegion);
  disk->commit();


  delete[] parentEntries;
  return 0;
}
