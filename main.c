#include "shell.h"

int execute(char** args, char** front)
{
	int ret = 0, flag = 0, status;
	char *command = args[0];

	//set flag  = 1, when args[0] is not / or .
	if(command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		//command = get_location(command);
	}

	if(!command || (access(command, F_OK) == -1))
	{
		if(errno == EACCES)
		{
			//ret = create_error(args, 126);
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
    size_t line_len = 0;
    int status = 0;

    while(1)
    {
        prompt(); // Display the shell prompt
        size_t read = getline(&line, &line_len, stdin);

        if(read == -1)
        {
            if(feof(stdin)) // End of file (Ctrl+D)
            {
                printf("\n");
                free(line);
                exit_shell(EXIT_SUCCESS);
            }
            perror("getline");
            exit_shell(EXIT_FAILURE);
        }

        if(read > 1)
        {
            if(line[read - 1] == '\n')
                line[read - 1] = '\0';

            execute_command(line);

            if(strcmp(line, "exit") == 0)
            {
                free(line);
                exit_shell(EXIT_SUCCESS);
            }
        }
    }

    return 0;
}

