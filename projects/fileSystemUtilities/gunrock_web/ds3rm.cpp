#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

#include "./include/LocalFileSystem.h"
#include "./include/Disk.h"
#include "./include/ufs.h"

using namespace std;


int main(int argc, char *argv[]) {
  if (argc != 4) {
    cerr << argv[0] << ": diskImageFile parentInode entryName" << endl;
    return 1;
  }

  // Parse command line arguments
  Disk *disk = new Disk(argv[1], UFS_BLOCK_SIZE);
  LocalFileSystem *fileSystem = new LocalFileSystem(disk);
  int parentInode = stoi(argv[2]);
  string entryName = string(argv[3]);


  // Implementation  

  int rc = fileSystem->unlink(parentInode, entryName);

  if(rc != 0)
  {
    delete fileSystem;
    delete disk;

    cerr << "Error removing entry" << endl;
    return 1;
  }

  // inode_t parent;
  // fileSystem->stat(parentInode, &parent);

  // cout << "size: " << parent.size << endl;
  // cout << "type: " << parent.type << endl;
  
  // unsigned char buffer[UFS_BLOCK_SIZE * DIRECT_PTRS];
  // int bytesRead = fileSystem->read(parentInode, buffer, parent.size);


  // int numEntriesOfParent = bytesRead / sizeof(dir_ent_t);
  // dir_ent_t *entries = (dir_ent_t *)buffer;

  // bool found = false;

  // for (int i = 0; i < numEntriesOfParent; i++)
  // {

  //   cout << "direct[" << i << "]: " << endl;
  //   cout << "   name: " << entries[i].name << endl;
  //   cout << "   inum: " << entries[i].inum << endl;
    
  // }

  delete fileSystem;
  delete disk;
  return 0;
}
