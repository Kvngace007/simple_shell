#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#ifndef F_OK
#define F_OK 0
#endif

#ifndef X_OK
#define X_OK 1
#endif

#ifndef S_IXUSR
#define S_IXUSR 0100
#endif

#define END_OF_FILE -2
#define EXIT -3

typedef struct list_s
{
		char *value;
		struct list_s *next;
} list_t;


/**
 * struct Buffer - Structure to hold the line buffer and its size.
 * @lineptr: A pointer to the buffer storing the line.
 * @n: The size of the buffer.
 */
typedef struct Buffer
{
	char* lineptr;
	size_t n;
} Buffer;

#define COMMAND_EXECUTED "Command executed successfully\n"
#define COMMAND_FAILED "Command failed\n"
#define SHELL_EXIT "Exiting the shell...\n"
#define MAX_ARGS 1024
#define MAX_PATH_LEN 1024


char* GLOBAL_NAME;
extern char** environ;

size_t _getline(Buffer* buffer, FILE* stream);
void prompt(void);
size_t read_command(Buffer* buffer);
void execute_command(char* command);


char** copy_environment(void);
void free_environment(void);
char** get_environment_variable(const char* name);


int _strlen(const char* s);
char* _strcpy(char* dest, const char* src);
char* _strcat(char* dest, const char* src);
char* _strncat(char* dest, const char* src, size_t n);
char* _strchr(char* s, char c);
int _strspn(char* s, char* accept);
int _strcmp(char* s1, char* s2);
int _strncmp(const char* s1, const char* s2, size_t n);


int exit_shell(void);
int env_shell(void);
int setenv_shell(const char* name, const char* value, int overwrite);
int unsetenv_shell(const char* name);
int cd_shell(const char* path);

#endif
