#include "shell.h"

int execute(char** args)
{
	int ret = 0, flag = 0;
	char *command = args[0];

	if(command[0] != '/' && command[0] != '.')
	{
		flag = 1;
	}

	if(!command || (access(command, F_OK) == -1))
	{
		if(errno == EACCES)
		{
			
		}
	}

	if(flag)
	{
		free(command);
	}
	return ret;
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(void)
{
    char* line;
    int read;
    size_t line_len = 0;
    while(1)
    {
        prompt();
        read = getline(&line, &line_len, stdin);

        if(read == -1)
        {
            if(feof(stdin))
            {
                printf("\n");
                free(line);
                exit_shell();
            }
            perror("getline");
            exit_shell();
        }

        if(read > 1)
        {
            if(line[read - 1] == '\n')
                line[read - 1] = '\0';

            execute_command(line);

            if(strcmp(line, "exit") == 0)
            {
                free(line);
                exit_shell();
            }
        }
    }

    return 0;
}

