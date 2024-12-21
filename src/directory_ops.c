#include <stdio.h>
#include <dirent.h>

int dir_list() {
  // open the directory
  DIR *dir_ptr;
  dir_ptr = opendir(".");
  if (dir_ptr == NULL) {
    perror("Directory could not been opened.\n");
    return 1;
  }

  // list the folder
  struct dirent *read_dir;
  while ((read_dir = readdir(dir_ptr)) != NULL) {
    if (read_dir->d_type == DT_REG) {
      printf("FILE: %s\n", read_dir->d_name);
    } else if (read_dir->d_type == DT_DIR) {
      printf("DIR: %s\n", read_dir->d_name);
    }
  }

  // close the folder
  if (closedir(dir_ptr) == -1) {
    perror("Directory could not been closed.\n");
    return 2;
  }

  return 0;
}

int dir_create() {
  return 0;
}

int dir_delete() {
  return 0;
}

