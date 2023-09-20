#include "shell.h"

/**
 * execute_command - Execute a user command.
 * @command: The command to execute.
 */
void execute_command(char* command)
{
    char* args[MAX_ARGS];
    int arg_index = 0;
    char* token = strtok((char*)command, " \t\n");
    char* path_env = getenv("PATH");
    if(token == NULL)
    {
        fprintf(stderr, "Empty command\n");
        return;
    }


    args[arg_index] = token;
    arg_index = 1;
    while((token = strtok(NULL, " \t\n")) != NULL)
    {
        args[arg_index] = token;
        arg_index++;
    }

    if(path_env != NULL)
    {
        char* path = strtok(path_env, ":");
        while(path != NULL)
        {
            char command_path[MAX_PATH_LEN];
            snprintf(command_path, sizeof(command_path), "%s/%s", path, args[0]);

            if(access(command_path, F_OK) == 0)
            {
                struct stat st;
                if(stat(command_path, &st) == 0 && (st.st_mode & S_IXUSR))
                {
                    int child_pid = fork();
                    if(child_pid == -1)
                    {
                        perror("fork");
                        exit(EXIT_FAILURE);
                    }
                    if(child_pid == 0)
                    {
                        execvp(command_path, args);
                        perror("execvp");
                        exit(EXIT_FAILURE);
                    } else
                    {
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

    fprintf(stderr, "./shell: %s: command not found\n", args[0]);
    fprintf(stderr, "%s", COMMAND_FAILED);
}

