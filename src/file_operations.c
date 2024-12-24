#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "../include/logger.h"

int file_touch(int argc, char *argv[]) {
  if (argc < 2) {
    perror("folder name must be given.");
    return 1;
  }

  char *file_name = argv[argc - 1];

  // check if file already exists
  struct stat st;
  if (stat(file_name, &st) == 0) {
    perror("file already exists.");
    return 1;
  }

  // create file with creat call
  int fd = creat(file_name, 0644);
  if (fd == -1) {
    perror("file creation failed.");
    return 1;
  }

  char *text = "file created successfully.\n";
  printf("%s", text);
  logD("mtouch", text);
  close(fd);
  return 0;
}

int file_rm(int argc, char *argv[]) {
  if (argc < 2) {
    perror("file name must be given.");
    return 1;
  }

  char *file_name = argv[argc - 1];

  // remove the file with unlink call
  if (unlink(file_name) == -1) {
    perror("file removal failed.");
    return 1;
  }

  char *text = "file removed successfully.\n";
  printf("%s", text);
  logD("mrm", text);
  return 0;
}

int file_cp(int argc, char *argv[]) {
  if (argc < 3) {
    perror("source and destination file names must be given.");
    return 1;
  }

  char *source_file = argv[argc - 2];
  char *destination_file = argv[argc - 1];

  // open source file
  int src_fd = open(source_file, O_RDONLY);
  if (src_fd == -1) {
    perror("source file open failed.");
    return 1;
  }

  // open destination file
  int dest_fd = creat(destination_file, 0644);
  if (dest_fd == -1) {
    perror("destination file creation failed.");
    return 1;
  }

  // copy source file to destination file
  char buffer[1024];
  int read_bytes;
  while ((read_bytes = read(src_fd, buffer, sizeof(buffer))) > 0) {
    if (write(dest_fd, buffer, read_bytes) == -1) {
      perror("file copy failed.");
      return 1;
    }
  }

  char *text = "file copied successfully.\n";
  printf("%s", text);
  logD("mcp", text);
  close(src_fd);
  close(dest_fd);
  return 0;
}

int file_mv(int argc, char *argv[]) {
  return 0;
}

int file_cat(int argc, char *argv[]) {
  return 0;
}

int file_grep(int argc, char *argv[]) {
  return 0;
}
