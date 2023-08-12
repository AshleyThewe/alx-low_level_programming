#include "main.h"

/**
 * appends_texts_to_files - Append texts at end of file.
 * @filenames: A pointers to names of the files.
 * @texts_contents: The strings to be  added to the ends of the files.
 *
 * Returns: If function fail and the filename is NULL then  - -1.
 *         If the files are not existing the users lack the write-permissions then - -1.
 *         Or-otherwise - 1.
 */

int append_text_to_file(const char *filename, char *text_content) {
	int o, w, len = 0;
	if (filename == NULL)
		return (-1);
	if (text_content != NULL)
	{
		for (len = 0; text_content[len];)
			len++;
	}
	o = open(filename, O_WRONLY | O_APPEND);
	w = write(o, text_content, len);

	if (o == -1 || w == -1)
		return (-1);
	close(o);
	return (1);
}
