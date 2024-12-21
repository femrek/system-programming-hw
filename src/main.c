#include <stdio.h>
#include <dirent.h>
#include "directory_ops.c"
#include "file_operations.c"
#include "permissions.c"
#include "utils.c"

// the list for keep all the executable names. (comes from soft links to main executable).
char *executables[] = {
  "mls", // 0 -> ls
  "mmkdir", // 1 -> mkdir
  "mrmdir", // 2 -> rmdir
  "mtouch", // 3 -> touch
  "mrm", // 4 -> rm
  "mcp", // 5 -> cp
  "mmv", // 6 -> mv
  "mcat", // 7 -> cat
  "mgrep", // 8 -> grep
  "mchmod"  // 9 -> chmod
};

int main(int argc, char *argv[]) {
  if (argc < 1) {
    perror("No Argument\n");
    return -1;
  }

  // trigger the function according to called soft link file (dummy executable name).
  char *executable = argv[0];
  if (ends_with(executable, executables[0])) {
    return dir_ls(argc, argv);
  }
  if (ends_with(executable, executables[1])) {
    return dir_mkdir(argc, argv);
  }
  if (ends_with(executable, executables[2])) {
    return dir_rmdir(argc, argv);
  }
  if (ends_with(executable, executables[3])) {
    return file_touch(argc, argv);
  }
  if (ends_with(executable, executables[4])) {
    return file_rm(argc, argv);
  }
  if (ends_with(executable, executables[5])) {
    return file_cp(argc, argv);
  }
  if (ends_with(executable, executables[6])) {
    return file_mv(argc, argv);
  }
  if (ends_with(executable, executables[7])) {
    return file_cat(argc, argv);
  }
  if (ends_with(executable, executables[8])) {
    return file_grep(argc, argv);
  }
  if (ends_with(executable, executables[9])) {
    return permission_chmod(argc, argv);
  }

  perror("The program cannot be callded directly. Use soft links instead.\n");
  return -2;
}
