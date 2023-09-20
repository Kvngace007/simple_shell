#include "shell.h"

void allocate_buffer(Buffer* buffer);
void assign_lineptr(Buffer* buffer, char* line, size_t num_chars);


/**
 * allocate_buffer - Allocate memory for the buffer.
 * @buffer: A pointer to a Buffer structure.
 */
void allocate_buffer(Buffer* buffer)
{
    buffer->n = 128; // Initial buffer size
    buffer->lineptr = (char*)malloc(buffer->n);
    if(buffer->lineptr == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
}

/**
 * assign_lineptr - Assign the line pointer and its size.
 * @buffer: A pointer to a Buffer structure.
 * @line: The new line to assign.
 * @num_chars: The number of characters read.
 */
void assign_lineptr(Buffer* buffer, char* line, size_t num_chars)
{
    buffer->lineptr = line;
    buffer->n = num_chars;
}

/**
 * _getline - Read a line from a file stream.
 * @buffer: A pointer to a Buffer structure.
 * @stream: The input file stream.
 *
 * Return: The number of characters read, or (size_t)-1 on failure or end-of-file (EOF).
 */
size_t _getline(Buffer* buffer, FILE* stream)
{
    if(buffer == NULL || stream == NULL)
    {
        errno = EINVAL;
        return (size_t)-1; // Return a special value to indicate error
    }

    size_t num_chars = 0; // Number of characters read
    int ch;

    if(buffer->lineptr == NULL)
    {
        allocate_buffer(buffer);
    }

    char* line = buffer->lineptr;

    while((ch = fgetc(stream)) != EOF)
    {
        if(num_chars >= buffer->n - 1)
        {
            size_t bufsize = buffer->n * 2;
            char* new_buffer = (char*)realloc(line, bufsize);
            if(new_buffer == NULL)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
            line = new_buffer;
            assign_lineptr(buffer, line, bufsize);
        }

        line[num_chars++] = (char)ch;

        if(ch == '\n')
        {
            break;
        }
    }

    if(num_chars == 0)
    {
        return (size_t)-1; // Return a special value to indicate no data read
    }

    line[num_chars] = '\0';

    return num_chars;
}

