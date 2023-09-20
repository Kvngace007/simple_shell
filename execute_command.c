#include "shell.h"

/**
 * execute_command - Execute a user command.
 * @command: The command to execute.
 */
void execute_command(const char* command)
{
    // Tokenize the command to separate the program name from arguments
    char* token = strtok((char*)command, " \t\n");
    if(token == NULL)
    {
        // Handle empty command
        fprintf(stderr, "Empty command\n");
        return;
    }

    // Create an array to store the program name and arguments
    char* args[MAX_ARGS]; // Adjust the size as needed

    // Initialize the first element with the program name
    args[0] = token;

    // Parse and store the remaining arguments
    int arg_index = 1;
    while((token = strtok(NULL, " \t\n")) != NULL)
    {
        args[arg_index] = token;
        arg_index++;
    }
    args[arg_index] = NULL; // Null-terminate the arguments array

    // Check if the command exists in the PATH
    char* path_env = getenv("PATH");
    if(path_env != NULL)
    {
        char* path = strtok(path_env, ":");
        while(path != NULL)
        {
            // Create a buffer to hold the full path to the command
            char command_path[MAX_PATH_LEN];
            snprintf(command_path, sizeof(command_path), "%s/%s", path, args[0]);

            // Check if the file exists
            if(access(command_path, F_OK) == 0)
            {
                // Check if the file is executable
                struct stat st;
                if(stat(command_path, &st) == 0 && (st.st_mode & S_IXUSR))
                {
                    // Command found in the current path, execute it
                    int child_pid = fork();
                    if(child_pid == -1)
                    {
                        perror("fork");
                        exit(EXIT_FAILURE);
                    }
                    if(child_pid == 0)
                    {
                        // This code is executed by the child process
                        execvp(command_path, args);
                        perror("execvp");
                        exit(EXIT_FAILURE);
                    } else
                    {
                        // This code is executed by the parent process
                        int status;
                        if(wait(&status) == -1)
                        {
                            perror("wait");
                            exit(EXIT_FAILURE);
                        }
                        if(WIFEXITED(status))
                        {
                            if(WEXITSTATUS(status) == 0)
                            {
                                printf("%s", COMMAND_EXECUTED);
                            } else
                            {
                                fprintf(stderr, "./shell: %s: command not found\n", args[0]);
                                fprintf(stderr, "%s", COMMAND_FAILED);
                            }
                        } else
                        {
                            // Handle other execution errors
                            perror("wait");
                            exit(EXIT_FAILURE);
                        }
                    }
                    return;
                }
            }
            path = strtok(NULL, ":");
        }
    }

    // Command not found in the PATH
    fprintf(stderr, "./shell: %s: command not found\n", args[0]);
    fprintf(stderr, "%s", COMMAND_FAILED);
}

