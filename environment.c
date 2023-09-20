#include "shell.h"


/**
 * copy_environment - Create a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a double pointer to the new copy.
 */
char** copy_environment(void)
{
    char** new_environment;
    size_t environment_size;
    int index;

    for(environment_size = 0; environ[environment_size]; environment_size++)
        ;

    new_environment = malloc(sizeof(char*) * (environment_size + 1));
    if(!new_environment)
        return (NULL);

    for(index = 0; environ[index]; index++)
    {
        new_environment[index] = malloc(_strlen(environ[index]) + 1);

        if(!new_environment[index])
        {
            for(index--; index >= 0; index--)
                free(new_environment[index]);
            free(new_environment);
            return (NULL);
        }
        _strcpy(new_environment[index], environ[index]);
    }
    new_environment[index] = NULL;

    return (new_environment);
}

/**
 * free_environment - Free the environment copy.
 */
void free_environment(void)
{
    int index;

    for(index = 0; environ[index]; index++)
        free(environ[index]);
    free(environ);
}

/**
 * get_environment_variable - Get an environmental variable by name.
 * @name: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char** get_environment_variable(const char* name)
{
    int index, name_length;

    name_length = _strlen(name);

    for(index = 0; environ[index]; index++)
    {
        if(_strncmp(name, environ[index], name_length) == 0)
            return (&environ[index]);
    }

    return (NULL);
}

