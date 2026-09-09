#include <iostream>
#include <string>

#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "./include/LocalFileSystem.h"
#include "./include/Disk.h"
#include "./include/ufs.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 4) {
    cerr << argv[0] << ": diskImageFile src_file dst_inode" << endl;
    cerr << "For example:" << endl;
    cerr << "    $ " << argv[0] << " tests/disk_images/a.img dthread.cpp 3" << endl;
    return 1;
  }

  // Parse command line arguments
  Disk *disk = new Disk(argv[1], UFS_BLOCK_SIZE);
  LocalFileSystem *fileSystem = new LocalFileSystem(disk);
  string srcFile = string(argv[2]);
  int dstInode = stoi(argv[3]);

  int fileDescriptor = open(argv[2], O_RDONLY);

  if (fileDescriptor < 0)
  {
    delete fileSystem;
    delete disk;

    cerr << "Could not open source file" << endl;
    return 1;
  }


  unsigned char bufferToFile[MAX_FILE_SIZE];

  char buffer[4096];
  int ret;
  int fileSize = 0;

  while ((ret = read(fileDescriptor, buffer, 4096)) > 0)
  {

    for(int i = 0; i < ret; i++)
    {
      bufferToFile[i + fileSize] = buffer[i];
    }

    fileSize += ret;
  }    



  int rc = fileSystem->write(dstInode, bufferToFile, fileSize);

  if (rc < 0) {
    delete fileSystem;
    delete disk;

    cerr << "Could not write to dst_file" << endl;
    return 1;
  }
  
  delete fileSystem;
  delete disk;
  return 0;
}
