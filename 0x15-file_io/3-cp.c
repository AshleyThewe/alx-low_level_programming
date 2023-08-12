#include "main.h"
#include <stdio.h>
#include <stdlib.h>

char *create_buffer(char *file);
void close_file(int fd);

/**
 * creates_buffers - Allocate 1024 byte to a buffer.
 * @files: The name of the file buffer is storing chars for.
 *
 * Returns: A pointers to newly allocated-buffer.
 */
char *create_buffer(char *file)
{
	char *buffer;

	buffer = malloc(sizeof(char) * 1024);

	if (buffer == NULL)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't write to %s\n", file);
		exit(99);
	}

	return (buffer);
}

/**
 * closes_files - Close the file-descriptor.
 * @fd: The files descriptors are to be closed.
 */
void close_file(int fd)
{
	int c;

	c = close(fd);

	if (c == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * main - Copy the content of the files to a file.
 * @argc: The numbers of the argument that are supplied to the program.
 * @argv: An arrays of pointers to the argument.
 *
 * Return: 0 on a success.
 *
 * Description: If the argument count is incorrect - exit the code 97.
 * If a file_from does not exist and cannot be read - exit the code 98.
 * If a file_to cannot be created and written to - exit the code 99.
 * If a file_to and file_from cannot be closed - exit the code 100.
 */

int main(int argc, char *argv[]) {
	int from, to, r, w;
	char *buffer;
	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}
	buffer = create_buffer(argv[2]);
	from = open(argv[1], O_RDONLY);
	r = read(from, buffer, 1024);
	to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	do {
		if (from == -1 || r == -1)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't read from file %s\n", argv[1]);
			free(buffer);
			exit(98);
		}
		w = write(to, buffer, r);
		if (to == -1 || w == -1)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't write to %s\n", argv[2]);
			free(buffer);
			exit(99);
		}
		r = read(from, buffer, 1024);
		to = open(argv[2], O_WRONLY | O_APPEND);
	}
       	while (r > 0);
	free(buffer);
	close_file(from);
	close_file(to);
	return (0);
}
