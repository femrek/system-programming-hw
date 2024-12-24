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
  return 0;
}

int file_cp(int argc, char *argv[]) {
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
