#include <iostream>
#include <string>
#include <vector>

#include "./include/LocalFileSystem.h"
#include "./include/Disk.h"
#include "./include/ufs.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 4) {
    cerr << argv[0] << ": diskImageFile parentInode directory" << endl;
    cerr << "For example:" << endl;
    cerr << "    $ " << argv[0] << " a.img 0 a" << endl;
    return 1;
  }

  // Parse command line arguments
  
  Disk *disk = new Disk(argv[1], UFS_BLOCK_SIZE);
  LocalFileSystem *fileSystem = new LocalFileSystem(disk);
  int parentInode = stoi(argv[2]);
  string directory = string(argv[3]);
  
  int result = fileSystem->create(parentInode, UFS_DIRECTORY, directory);

  if (result < 0) {
    delete fileSystem;
    delete disk;

    cerr << "Error creating directory" << endl;
    return 1;
  }

  delete fileSystem;
  delete disk;
  return 0;
}
