# Terminal Based File Manager

A modular command-line file management system implementing basic file and directory operations.

## Project Description

This Terminal Based File Manager is a modular system programming project that provides common file and directory management operations through command-line interface. The project is designed with a focus on modularity, maintainability, and extensibility, separating different functionalities into distinct modules.

## Project Structure

The project is organized into several core modules:

- `main.c` - Main dispatcher that routes program execution
- `file_operations.c/.h` - File manipulation operations
- `directory_ops.c/.h` - Directory management operations
- `permissions.c/.h` - Permission management
- `logger.c/.h` - Logging functionality

## Features

### Directory Operations
- `mls` - List files in a directory
- `mmkdir` - Create a new directory
- `mrmdir` - Remove a directory

### File Operations
- `mtouch` - Create a new file
- `mrm` - Remove a file
- `mcp` - Copy a file
- `mmv` - Move/rename a file
- `mcat` - Display file contents
- `mgrep` - Search for patterns in files

### Permission Operations
- `mchmod` - Change file/directory permissions

### Logging
The system includes two types of logging:
- Info logging (`logI`)
- Debug logging (`logD`)

## Implementation Details

### Main Dispatcher
The program uses a single binary that can be invoked with different names through symbolic links. The `main.c` file acts as a dispatcher that determines the operation to perform based on the executable name (argv[0]).

### Core Components

#### Directory Operations
- Uses standard C library functions: `opendir()`, `readdir()`, `closedir()`, `mkdir()`, `rmdir()`
- Handles basic directory management tasks

#### File Operations
- Implements file manipulation using system calls: `open()`, `creat()`, `read()`, `write()`, `unlink()`, `rename()`
- Provides comprehensive file management capabilities

#### Permissions Management
- Uses `stat()` and `chmod()` for permission modifications
- Allows changing access rights for files and directories

#### Logger
- Implements two logging levels: Info and Debug
- Uses `open()` and `write()` system calls for log management

## Implementation Notes

The project uses a modular approach where each component is designed to handle specific tasks:
- All file operations are contained in `file_operations.c`
- Directory operations are handled in `directory_ops.c`
- Permission modifications are managed through `permissions.c`
- Logging functionality is provided via `logger.c`

This separation of concerns allows for easier maintenance and future extensions to the system.
