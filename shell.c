#include "shell.h"

// Global Variables
char command_history[MAX_HISTORY][MAX_INPUT_LEN];
int history_size = 0;

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        fprintf(stderr, "Usage: %s [batchFile]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 2)
    {
        run_batch_mode(argv[1]);
    }
    else
    {
        run_interactive_mode();
    }

    return 0;
}

void run_interactive_mode()
{
    char user_input[MAX_INPUT_LEN];
    printf("StudentShell> ");
    while (fgets(user_input, MAX_INPUT_LEN, stdin) != NULL)
    {
        user_input[strcspn(user_input, "\n")] = '\0'; // Remove newline character
        if (strlen(user_input) > 0)
        {
            add_to_cmd_history(user_input);
            process_command(user_input);
        }
        printf("StudentShell> ");
    }
}

void run_batch_mode(const char *filename)
{
    FILE *batch_file = fopen(filename, "r");
    if (!batch_file)
    {
        perror("Error opening batch file");
        exit(EXIT_FAILURE);
    }

    char batch_line[MAX_INPUT_LEN];
    while (fgets(batch_line, MAX_INPUT_LEN, batch_file) != NULL)
    {
        batch_line[strcspn(batch_line, "\n")] = '\0'; // Remove newline character
        if (strlen(batch_line) > 0)
        {
            printf("%s\n", batch_line); // Echo the command
            add_to_cmd_history(batch_line);
            process_command(batch_line);
        }
    }
    fclose(batch_file);
}

void process_command(char *input)
{
    char *cmd_args[MAX_INPUT_LEN / 2 + 1]; // Command arguments
    int cmd_arg_count = 0;

    char *token = strtok(input, " ");
    while (token)
    {
        cmd_args[cmd_arg_count++] = token;
        token = strtok(NULL, " ");
    }
    cmd_args[cmd_arg_count] = NULL;

    // Check for built-in commands
    if (strcmp(cmd_args[0], "exit") == 0)
    {
        exit(EXIT_SUCCESS);
    }
    else if (strcmp(cmd_args[0], "myhistory") == 0)
    {
        if (cmd_arg_count > 1 && strcmp(cmd_args[1], "-c") == 0)
        {
            clear_command_history();
        }
        else if (cmd_arg_count > 2 && strcmp(cmd_args[1], "-e") == 0)
        {
            int history_index = atoi(cmd_args[2]);
            execute_from_history(history_index);
        }
        else
        {
            show_command_history();
        }
        return;
    }

    // Fork and execute
    pid_t process_id = fork();
    if (process_id == 0)
    {
        // Child process
        if (execvp(cmd_args[0], cmd_args) == -1)
        {
            perror("Error executing command");
        }
        exit(EXIT_FAILURE);
    }
    else if (process_id > 0)
    {
        // Parent process
        wait(NULL);
    }
    else
    {
        perror("Error during fork");
    }
}

void handle_builtin_cmd(char *input)
{
    // Placeholder for additional built-in commands
}

void add_to_cmd_history(const char *input)
{
    if (history_size == MAX_HISTORY)
    {
        // Shift history to make space for new command
        for (int i = 1; i < MAX_HISTORY; i++)
        {
            strcpy(command_history[i - 1], command_history[i]);
        }
        history_size--;
    }
    strcpy(command_history[history_size++], input);
}

void show_command_history()
{
    for (int i = 0; i < history_size; i++)
    {
        printf("%d: %s\n", i + 1, command_history[i]);
    }
}

void clear_command_history()
{
    history_size = 0;
    printf("Command history cleared.\n");
}

void execute_from_history(int history_index)
{
    if (history_index < 1 || history_index > history_size)
    {
        fprintf(stderr, "Invalid history index.\n");
        return;
    }
    process_command(command_history[history_index - 1]);
}
