#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include "../include/utils/get_current_time.h"

#define LOG_FOLDER "system-programming-assingment-logs"
#define LOG_FILE_INFO "system-programming-assingment-logs/info.log"
#define LOG_FILE_DEBUG "system-programming-assingment-logs/debug.log"

void get_home_path(char *buffer, size_t size, const char *sub_path) {
  const char *home = getenv("HOME");
  if (home == NULL) {
    fprintf(stderr, "Error: Could not get HOME environment variable\n");
    exit(EXIT_FAILURE);
  }

  // Construct the full path dynamically
  snprintf(buffer, size, "%s/%s", home, sub_path);
}

void ensure_folder_exists(const char *folder_path) {
  char path[256];
  snprintf(path, sizeof(path), "%s", folder_path);
  char *p = path;

  // Iterate through the path and create directories
  for (p = path + 1; *p; p++) {
    if (*p == '/') {
      *p = '\0'; // Temporarily terminate the string at the current level
      if (mkdir(path, 0755) == -1 && errno != EEXIST) {
        perror("Error creating folder");
        return;
      }
      *p = '/'; // Restore the slash
    }
  }

  // Create the final directory
  if (mkdir(path, 0755) == -1 && errno != EEXIST) {
    perror("Error creating folder");
  }
}

void logI(char *op_type, char *text) {
  char log_file_path[512];
  char log_folder_path[512];
  get_home_path(log_folder_path, sizeof(log_folder_path), LOG_FOLDER);
  get_home_path(log_file_path, sizeof(log_file_path), LOG_FILE_INFO);

  // Open the log file in append mode
  ensure_folder_exists(log_folder_path);
  int fd = open(log_file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
  if (fd == -1) {
    perror("Error opening log file");
    return;
  }

  // Prepare the log entry
  char log_entry[1024];
  char timestamp[64];
  get_current_time(timestamp, sizeof(timestamp));

  if (text == NULL) {
    snprintf(log_entry, sizeof(log_entry), "%s -INFO- [%s]\n", timestamp, op_type);
  } else {
    snprintf(log_entry, sizeof(log_entry), "%s -INFO- [%s] - %s", timestamp, op_type, text);
  }

  // Write the log entry to the file
  if (write(fd, log_entry, strlen(log_entry)) == -1) {
    perror("Error writing to log file");
  }
}

void logD(char *op_type, char *text) {
  char log_file_path[512];
  char log_folder_path[512];
  get_home_path(log_folder_path, sizeof(log_folder_path), LOG_FOLDER);
  get_home_path(log_file_path, sizeof(log_file_path), LOG_FILE_DEBUG);

  // Open the log file in append mode
  ensure_folder_exists(log_folder_path);
  int fd = open(log_file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
  if (fd == -1) {
    perror("Error opening log file");
    return;
  }

  // Prepare the log entry
  char log_entry[1024];
  char timestamp[64];
  get_current_time(timestamp, sizeof(timestamp));

  if (text == NULL) {
    snprintf(log_entry, sizeof(log_entry), "%s -DEBUG- [%s]\n", timestamp, op_type);
  } else {
    snprintf(log_entry, sizeof(log_entry), "%s -DEBUG- [%s] - %s", timestamp, op_type, text);
  }

  // Write the log entry to the file
  if (write(fd, log_entry, strlen(log_entry)) == -1) {
    perror("Error writing to log file");
  }
}

