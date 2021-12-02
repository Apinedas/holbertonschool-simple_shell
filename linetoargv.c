#include "shell.h"

/**
 * _getenv - Extracts an env variable from environ
 * @name: Variable name
 * Return: Pointer to variable name, or NULL if variable hasn't be found
 */

char *_getenv(char *name)
{
	extern char **environ;
	char *extractenv;
	int difference, i, envlen;

	for (i = 0; environ[i]; i++)
	{
		envlen = _strlen(environ[i]);
		extractenv = (char *)malloc(sizeof(char) * envlen);
		if (extractenv == NULL)
			return (NULL);
		extractenv = _strcpy(extractenv, environ[i]);
		extractenv = strtok(extractenv, "=");
		difference = _strcmp(name, extractenv);
		if (difference == 0)
		{
			free(extractenv);
			return (environ[i]);
		}
		else
			free(extractenv);
	}
	return (NULL);
}

/**
 * manage_path - Search for a file in the PATH
 * @file: String to file to search
 * Return: Path to file if found, or NULL if not found in any path
 */

char *manage_path(char *file)
{
	char *path, *direction;
	struct stat st;
	int pathlen, filelen, filestatus;

	path = _getenv("PATH");
	path = strtok(path, "=");
	path = strtok(path, ":");
	pathlen = _strlen(path);
	filelen = _strlen(file);
	while (path)
	{
		direction = (char *)malloc(sizeof(char) * (pathlen + filelen));
		if (direction == NULL)
			return (NULL);
		direction = _strcpy(direction, path);
		direction = _strcat(direction, file);
		filestatus = stat(direction, &st);
		if (filestatus == 0)
			return (direction);
		free(direction);
		path = strtok(NULL, ":");
	}
	return (NULL);
}

/**
 * linetoargv - transforms a read line in an argv array
 * @line: Line to transform into argv
 * @argv: Array to put line into
 * @linelen: length of line to transform
 * Return: Argv filled with Modified line
 */

char **linetoargv(char *line, char **argv, ssize_t linelen)
{
	char *auxline;
	struct stat st;
	int i, filestatus;

	line[linelen - 1] = '\0';
	auxline = strtok(line, " ");
	for (i = 0; auxline; i++)
	{
		argv[i] = auxline;
		auxline = strtok(NULL, " ");
	}
	argv[i] = NULL;
	filestatus = stat(argv[0], &st);
	if (filestatus == -1)
	{
		auxline = manage_path(argv[0]);
		if (auxline != NULL)
			argv[0] = auxline;
	}
	return (argv);
}
