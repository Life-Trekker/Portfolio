#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

#include "./include/LocalFileSystem.h"
#include "./include/Disk.h"
#include "./include/ufs.h"

using namespace std;


int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << argv[0] << ": diskImageFile inodeNumber" << endl;
    return 1;
  }

  // Parse command line arguments

  Disk *disk = new Disk(argv[1], UFS_BLOCK_SIZE);
  LocalFileSystem *fileSystem = new LocalFileSystem(disk);
  int inodeNumber = stoi(argv[2]);

  // Implementation

  // Read the inode's type and size
  inode_t inodeToRead;
  fileSystem->stat(inodeNumber, &inodeToRead);

  if(inodeToRead.type != UFS_REGULAR_FILE)
  {
    delete fileSystem;
    delete disk;
    
    cerr << "Error reading file" << endl;
    return 1;
  }
  
  // Print the block numbers of the file's data blocks
  cout << "File blocks" << endl;

  int numDirectBlocks =  (inodeToRead.size + UFS_BLOCK_SIZE - 1) / UFS_BLOCK_SIZE;
  
  for(int i = 0; i < numDirectBlocks; i++)
  {
    
    cout << inodeToRead.direct[i] << endl;
    
  }
  

  cout << endl;

  // Read the file's data and print it
  cout << "File data" << endl;

  unsigned char buffer[inodeToRead.size];
  int bytesRead = fileSystem->read(inodeNumber, buffer, inodeToRead.size);

  for (int i = 0; i < bytesRead; i++)
  {
    cout << buffer[i];
  }


  delete fileSystem;
  delete disk;
  return 0;
}
