#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "../include/logger.h"

int dir_ls(int argc, char *argv[]) {
  // open the directory
  DIR *dir_ptr;
  dir_ptr = opendir(".");
  if (dir_ptr == NULL) {
    perror("Directory could not been opened.\n");
    return 1;
  }

  // list the folder
  struct dirent *read_dir;
  char result[256];
  while ((read_dir = readdir(dir_ptr)) != NULL) {
    if (read_dir->d_type == DT_REG) {
      snprintf(result, sizeof(result), "FILE: %s\n", read_dir->d_name);
    } else if (read_dir->d_type == DT_DIR) {
      snprintf(result, sizeof(result), "DIR: %s\n", read_dir->d_name);
    }
    printf("%s", result);
    logD("mls", result);
  }

  // close the folder
  if (closedir(dir_ptr) == -1) {
    perror("Directory could not been closed.\n");
    return 2;
  }

  return 0;
}

int dir_mkdir(int argc, char *argv[]) {
  return 0;
}

int dir_rmdir(int argc, char *argv[]) {
  return 0;
}

