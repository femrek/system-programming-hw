#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "../include/logger.h"

int permission_chmod(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "permission and file name must be given.\n");
    return 1;
  }

  char *permission = argv[argc - 2];
  char *file_name = argv[argc - 1];

  // check if file exists
  struct stat st;
  if (stat(file_name, &st) == -1) {
    fprintf(stderr, "file does not exist.\n");
    return 1;
  }

  // check if permission is valid
  if (strlen(permission) != 3) {
    fprintf(stderr, "permission must be 3 digits.\n");
    return 1;
  }
  if (permission[0] < '0' || permission[0] > '7' ||
      permission[1] < '0' || permission[1] > '7' ||
      permission[2] < '0' || permission[2] > '7') {
    fprintf(stderr, "permission must be in octal format.\n");
    return 1;
  }

  // convert permission string to integer
  int permission_code = strtol(permission, NULL, 8);

  // change the permission with chmod call
  if (chmod(file_name, permission_code) == -1) {
    perror("permission change failed");
    return 1;
  }

  char text[512];
  snprintf(text, sizeof(text), "permission changed successfully. File: %s, new permissions: %s\n", file_name, permission);
  printf("%s", text);
  logD("mchmod", text);
  return 0;
}
