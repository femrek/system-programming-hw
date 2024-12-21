#include <stdio.h>
#include <dirent.h>
#include "directory_ops.c"
#include "utils.c"

int main(int argc, char * argv[]) {
  if (argc < 1) {
    perror("No Argument\n");
    return -1;
  }

  char *executable = argv[0];
  if (ends_with(executable, "slist") == 1) {
    return dir_list();
  }

  perror("The program cannot be used directly.\n");
  return -2;
}
