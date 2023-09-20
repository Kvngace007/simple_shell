#include "shell.h"

/**
 * read_command - Read a command from the user.
 * @buffer: A pointer to a Buffer structure.
 *
 * Return: The number of characters read, or 0 on failure or end-of-file (EOF).
 */
size_t read_command(Buffer* buffer)
{
    size_t chars_read = _getline(buffer, stdin);
    return chars_read;
}

