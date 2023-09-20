#include "shell.h"

/**
 * exit_shell - Implement the "exit" built-in command without arguments.
 *
 * This function exits the shell gracefully.
 *
 * Return: 0 upon successful exit.
 */
int exit_shell(void)
{
    printf(SHELL_EXIT);
    exit(EXIT_SUCCESS);
    return 0;
}

/**
 * env_shell - Implement the "env" built-in command.
 *
 * This function prints the current environment variables.
 *
 * Return: 0 upon successful execution.
 */
int env_shell(void)
{
    extern char** environ;  // Access to the environment variables

    // Loop through and print each environment variable
    for(char** env = environ; *env; env++)
    {
        printf("%s\n", *env);
    }

    return 0;
}

/**
 * setenv_shell - Initialize or modify an environment variable.
 * @name: The name of the environment variable.
 * @value: The value to set for the environment variable.
 * @overwrite: If 1, overwrite the variable if it exists; if 0, don't overwrite.
 *
 * Return: 0 on success, -1 on failure.
 */
int setenv_shell(const char* name, const char* value, int overwrite)
{
    if(setenv(name, value, overwrite) != 0)
    {
        fprintf(stderr, "setenv: Error setting environment variable %s\n", name);
        return -1; // Return an error code
    }
    return 0; // Success
}

/**
 * unsetenv_shell - Remove an environment variable.
 * @name: The name of the environment variable to remove.
 *
 * Return: 0 on success, -1 on failure.
 */
int unsetenv_shell(const char* name)
{
    if(unsetenv(name) != 0)
    {
        fprintf(stderr, "unsetenv: Error unsetting environment variable %s\n", name);
        return -1; // Return an error code
    }
    return 0; // Success
}

/**
* cd_shell - Change the current directory of the process.
* @path: The directory to change to. If NULL or "-", go to the previous directory.
*
* Return: 0 on success, -1 on failure.
*/
int cd_shell(const char* path)
{
    char* previous_dir = NULL;

    // Get the current working directory
    char current_dir[1024];
    if(getcwd(current_dir, sizeof(current_dir)) == NULL)
    {
        perror("getcwd");
        return -1; // Return an error code
    }

    // If no path is provided or the path is "-", go to the previous directory
    if(path == NULL || strcmp(path, "-") == 0)
    {
        path = getenv("OLDPWD"); // Get the previous directory from the environment variable
        if(path == NULL)
        {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return -1; // Return an error code
        }
        printf("%s\n", path); // Print the directory we're changing to
    }

    // Change to the specified directory
    if(chdir(path) != 0)
    {
        perror("chdir");
        return -1; // Return an error code
    }

    // Update the environment variable PWD
    if(setenv("PWD", current_dir, 1) != 0)
    {
        perror("setenv");
        return -1; // Return an error code
    }

    // Update the environment variable OLDPWD
    if(setenv("OLDPWD", current_dir, 1) != 0)
    {
        perror("setenv");
        return -1; // Return an error code
    }

    return 0; // Success
}




