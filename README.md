# Major-2
# Newshell

## Group Members:
- Subhash Galla (shell.c, shell.h)
- Murrali Sai (shell.h, makefile)

## Organization of the Project
- `shell.c`: Contains the main logic of the shell.
- `shell.h`: Header file defining function prototypes and global variables.
- `Makefile`: Automates compilation and cleanup.

## Design Overview
The code is a simple shell program that works in two ways: interactive mode and batch mode. 
It keeps track of custom paths (path_list) and user command history (history) using global variables.

## Modes of Operation
Interactive Mode: The shell displays a prompt where users can type commands, which are then executed in real-time.
Batch Mode: The shell reads commands from a file and runs them automatically, one at a time.

## Command Execution
The execute_command function handles all commands.
It runs built-in commands like cd, exit, path, and myhistory directly.
For external commands, it uses fork and execvp to create new processes. Input/output redirection is supported.

## Memory Management & Error Handling
The program ensures dynamic memory (e.g., for paths and history) is cleaned up using dedicated cleanup functions before exiting.
Errors like invalid commands or file issues are logged with helpful messages using perror and fprintf.

## GitHub Link: 
