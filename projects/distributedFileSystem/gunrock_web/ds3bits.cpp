#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

#include "./include/LocalFileSystem.h"
#include "./include/Disk.h"
#include "./include/ufs.h"

using namespace std;

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    cerr << argv[0] << ": diskImageFile" << endl;
    return 1;
  }

  // Parse command line arguments
  Disk *disk = new Disk(argv[1], UFS_BLOCK_SIZE);
  LocalFileSystem *fileSystem = new LocalFileSystem(disk);

  // Implementation
  cout << "Super" << endl;

  // Read SuperBlock
  super_t super;
  fileSystem->readSuperBlock(&super);

  // Print out the super block information
  cout << "inode_region_addr " << super.inode_region_addr << endl;
  cout << "inode_region_len " << super.inode_region_len << endl;
  cout << "num_inodes " << super.num_inodes << endl;

  cout << "data_region_addr " << super.data_region_addr << endl;
  cout << "data_region_len " << super.data_region_len << endl;
  cout << "num_data " << super.num_data << endl;

  cout << endl;
  
  // Read and print the inode bitmap
  unsigned char buffer[UFS_BLOCK_SIZE];

  cout << "Inode bitmap" << endl;

  disk->readBlock(super.inode_bitmap_addr, buffer);

  int inodeBitmapSize = (super.num_inodes + 7) / 8;

  for(int idx = 0; idx < inodeBitmapSize; idx++)
  {
    cout << (unsigned int) buffer[idx] << " ";
  }

  cout << endl;
  cout << endl;

  // Read and print the data bitmap
  cout << "Data bitmap" << endl;

  disk->readBlock(super.data_bitmap_addr, buffer);

  int dataBitmapSize = (super.num_data + 7) / 8;

  for(int idx = 0; idx < dataBitmapSize; idx++)
  {
    cout << (unsigned int) buffer[idx] << " ";
  }

  cout << endl;

  delete fileSystem;
  delete disk;
  return 0;
}
