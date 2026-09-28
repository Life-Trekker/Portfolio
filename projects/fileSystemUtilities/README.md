# Description:

For this project, I implemented a Unix-style file system in C++. The core LocalFileSystem class manages inodes, directory entries and data blocks on a disk image.  It can handle essential operations such as reading, writing, creating and deleting files/ directories.  

I also built seven command-line utilities that mirror familiar Unix commands, which let me exercise and validate the file system from the terminal.\
ds3bits - outputs the metadata for a file system\
ds3cat - outputs the contents of a file\
ds3ls - outputs the contents of a directory\
ds3mkdir - creates a new directory\
ds3touch - creates a new file\
ds3cp - copies a file from the computer onto the disk image\
ds3rm - removes a file or empty directory\

This project involved on-disk data structures, block allocation, bitmap management and path resolution.  It also required careful error handling for unique cases like invalid paths, full disks or missing files.