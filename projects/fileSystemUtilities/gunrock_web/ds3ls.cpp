#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

#include "./shared/include/StringUtils.h"
#include "./include/LocalFileSystem.h"
#include "./include/Disk.h"
#include "./include/ufs.h"

using namespace std;

/*
  Use this function with std::sort for directory entries
bool compareByName(const dir_ent_t& a, const dir_ent_t& b) {
    return std::strcmp(a.name, b.name) < 0;
}
*/

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << argv[0] << ": diskImageFile directory" << endl;
    cerr << "For example:" << endl;
    cerr << "    $ " << argv[0] << " tests/disk_images/a.img /a/b" << endl;
    return 1;
  }

  // parse command line arguments
  Disk *disk = new Disk(argv[1], UFS_BLOCK_SIZE);
  LocalFileSystem *fileSystem = new LocalFileSystem(disk);
  string directory = string(argv[2]);

  // Implementation

  // Parse the directory into its components
  vector<string> directories;
  string currentDirectory = "";
  for(long unsigned int i = 1; i < directory.length(); i++)
  {    
    if(directory[i] == '/')
    {
      directories.push_back(currentDirectory);
      currentDirectory = "";
    }
    else
    {
      currentDirectory += directory[i];
    }

  }
  
  if(currentDirectory != "")
  {
    directories.push_back(currentDirectory);
  }

  // Traverse the directory structure to find the inode number of the final directory
  int parent = UFS_ROOT_DIRECTORY_INODE_NUMBER;

  for(long unsigned int i = 0; i < directories.size(); i++)
  {

    int inodeNumber = fileSystem->lookup(parent, directories[i]);

    if(inodeNumber < 0)
    {
      delete fileSystem;
      delete disk;

      cerr << "Directory not found" << endl;
      return 1;
    }

    parent = inodeNumber;
  }


  // Read the inode of the final directory and print out its contents
  inode_t inode;
  fileSystem->stat(parent, &inode);

  if (inode.type == UFS_REGULAR_FILE)
  {
    cout << parent << "\t" << directories.back() << endl;
  }
  else if (inode.type == UFS_DIRECTORY)
  {
    unsigned char buffer[UFS_BLOCK_SIZE * DIRECT_PTRS];
    int bytesRead = fileSystem->read(parent, buffer, inode.size);

    int numEntries = bytesRead / sizeof(dir_ent_t);

    dir_ent_t *entries = (dir_ent_t *)buffer;

    // Sort the entries by name using std::sort and a custom comparator
    vector<dir_ent_t> entryVector;

    for (int i = 0; i < numEntries; i++)
    {
      entryVector.push_back(entries[i]);
    }

    sort(entryVector.begin(), entryVector.end(), [](const dir_ent_t& a, const dir_ent_t& b) {
        return strcmp(a.name, b.name) < 0;
    });

    for (int i = 0; i < numEntries; i++)
    {
      cout << entryVector[i].inum << "\t" << entryVector[i].name << endl;
    }
  }
  else
  {
    delete fileSystem;
    delete disk;

    cerr << "Invalid inode type" << endl;
    return 1;
  }
  


  delete fileSystem;
  delete disk;
  return 0;
}
