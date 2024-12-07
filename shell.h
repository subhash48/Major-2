#ifndef STUDENT_SHELL_H
#define STUDENT_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_INPUT_LEN 512
#define MAX_HISTORY 20

// Function Declarations
void run_interactive_mode();
void run_batch_mode(const char *filename);
void process_command(char *input);
void handle_builtin_cmd(char *input);
void add_to_cmd_history(const char *input);
void show_command_history();
void clear_command_history();
void execute_from_history(int history_index);

#endif // STUDENT_SHELL_H
