#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "../include/utils/get_current_time.h"

#define LOG_FILE_INFO "logs/info.log"
#define LOG_FILE_DEBUG "logs/debug.log"

void logI(char *op_type, char *text) {
  // Open the log file in append mode
  int fd = open(LOG_FILE_INFO, O_WRONLY | O_CREAT | O_APPEND, 0644);
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
  // Open the log file in append mode
  int fd = open(LOG_FILE_DEBUG, O_WRONLY | O_CREAT | O_APPEND, 0644);
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

