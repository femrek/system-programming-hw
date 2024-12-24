#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../include/logger.h"

#define SIZE_SUFFIXES {"B", "KB", "MB", "GB", "TB"}

// return name string for file type by its code comes from derent.
// #define DT_UNKNOWN       0
// #define DT_FIFO          1
// #define DT_CHR           2
// #define DT_DIR           4
// #define DT_BLK           6
// #define DT_REG           8
// #define DT_LNK          10
// #define DT_SOCK         12
// #define DT_WHT          14
char *get_file_type_name_by_code(int code) {
  switch(code) {
    case DT_UNKNOWN:
      return "Unknown  ";
    case DT_FIFO   :
      return "Fifo     ";
    case DT_CHR    :
      return "Chr      ";
    case DT_DIR    :
      return "Directory";
    case DT_BLK    :
      return "Blk      ";
    case DT_REG    :
      return "File     ";
    case DT_LNK    :
      return "Link     ";
    case DT_SOCK   :
      return "Sock     ";
    case DT_WHT    :
      return "Wht      ";
    default:
      fprintf(stderr, "Unkown File Type Code: %d\n", code);
      return "";
  }
}

// turns byte size into presentable string. (e.g. 32B, 123.25KB)
char *get_size_by_byte_value(int byte) {
  int sizeOfResult = sizeof(char) * 12;
  char *result = malloc(sizeOfResult);

  int tmp = byte;
  int dec = 0;
  int dept = 0;

  // determine integer and decimal part of the result
  while (tmp > 1024) {
    dec = tmp % 1024;
    tmp /= 1024;
    dept++;
  }

  // create the result text according to integer and decimal part.
  const char *a[] = SIZE_SUFFIXES;
  if (dec == 0) {
    snprintf(result, sizeOfResult, "%d%3s", byte, a[dept]);
  } else {
    snprintf(result, sizeOfResult, "%d.%d%3s", tmp, dec, a[dept]);
  }

  // make the result right aligned
  char resultTemp[12];
  strcpy(resultTemp, result);
  snprintf(result, sizeOfResult, "%11s", resultTemp);

  return result;
}

// turns the permission code from stat call into presentable text. (e.g. rwxrwxrwx, rwxrw-r--)
char *get_permission_by_code(int code) {
  char *result = malloc(sizeof(char) * 10);
  strcpy(result, "");
  if (code & S_IRUSR) strcat(result, "r"); else strcat(result, "-");
  if (code & S_IWUSR) strcat(result, "w"); else strcat(result, "-");
  if (code & S_IXUSR) strcat(result, "x"); else strcat(result, "-");
  if (code & S_IRGRP) strcat(result, "r"); else strcat(result, "-");
  if (code & S_IWGRP) strcat(result, "w"); else strcat(result, "-");
  if (code & S_IXGRP) strcat(result, "x"); else strcat(result, "-");
  if (code & S_IROTH) strcat(result, "r"); else strcat(result, "-");
  if (code & S_IWOTH) strcat(result, "w"); else strcat(result, "-");
  if (code & S_IXOTH) strcat(result, "x"); else strcat(result, "-");
  return result;
}

int dir_ls(int argc, char *argv[]) {
  // determine the listing directory
  char *dir_name;
  if (argc > 1) {
    dir_name = argv[1];

    if (dir_name == NULL) {
      perror("Directory name could not been read");
      return 1;
    }
  } else {
    // current directory by default
    dir_name = ".";
  }

  // open the directory
  DIR *dir_ptr;
  dir_ptr = opendir(dir_name);
  if (dir_ptr == NULL) {
    perror("Directory could not been opened.\n");
    return 1;
  }

  // list the folder
  struct dirent *read_dir;
  char result[512];
  char file_path_buffer[512] = "";
  struct stat *stat_buffer = malloc(sizeof(struct stat));
  char *permission_buffer;
  while ((read_dir = readdir(dir_ptr)) != NULL) {
    // get full path of the file
    strcpy(file_path_buffer, "");
    strcat(file_path_buffer, dir_name);
    strcat(file_path_buffer, "/");
    strcat(file_path_buffer, read_dir->d_name);

    // get the information about the file
    stat(file_path_buffer, stat_buffer);
    char *file_type = get_file_type_name_by_code(read_dir->d_type);
    char *size = get_size_by_byte_value(stat_buffer->st_size);
    permission_buffer = get_permission_by_code(stat_buffer->st_mode);

    // prepare the result
    snprintf(result, sizeof(result), "%s %s %s %s\n",
        file_type,
        permission_buffer,
        size,
        read_dir->d_name);

    // print standard output and log
    printf("%s", result);
    logD("mls", result);
  }

  // close the folder
  if (closedir(dir_ptr) == -1) {
    perror("Directory could not been closed.\n");
    return 1;
  }

  // release the sources
  free(stat_buffer);
  free(permission_buffer);

  return 0;
}

int dir_mkdir(int argc, char *argv[]) {
  if (argc < 2) {
    perror("folder name must be given.");
    return 1;
  }

  char *folder_name = argv[argc - 1];

  if (mkdir(folder_name, 0755) == -1) {
    if (errno == EEXIST) {
      // Folder already exists
      printf("Folder '%s' already exists.\n", folder_name);
    } else {
      // Error occurred while creating the folder
      perror("Error creating folder");
      return EXIT_FAILURE;
    }
  } else {
    // Folder successfully created
    printf("Folder '%s' created successfully.\n", folder_name);
  }

  return 0;
}

int dir_rmdir(int argc, char *argv[]) {
  if (argc < 2) {
    perror("folder name must be given.");
    return 1;
  }

  char *folder_name = argv[argc - 1];

  // Attempt to remove the directory
  if (rmdir(folder_name) == -1) {
    if (errno == ENOENT) {
      // Directory does not exist
      printf("Directory '%s' does not exist.\n", folder_name);
    } else if (errno == ENOTDIR) {
      // The path is not a directory
      printf("'%s' is not a directory.\n", folder_name);
    } else {
      // Other error
      perror("Error removing folder");
      exit(EXIT_FAILURE);
    }
  } else {
    // Directory successfully removed
    printf("Directory '%s' removed successfully.\n", folder_name);
  }

  return 0;
}

