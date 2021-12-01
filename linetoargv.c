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
 * linetoargv - transforms a read line in an argv array
 * @line: Line to transform into argv
 * @argv: Array to put line into
 * @linelen: length of line to transform
 * Return: Argv filled with Modified line
 */

char **linetoargv(char *line, char **argv, ssize_t linelen)
{
	char *auxline/*, *path*/;
	/*struct stat st;*/
	int i/*, filestatus, pathlen*/;

	line[linelen - 1] = '\0';
	auxline = strtok(line, " ");
	for (i = 0; auxline; i++)
	{
		argv[i] = auxline;
		auxline = strtok(NULL, " ");
	}
	argv[i] = NULL;
	/*filestatus = stat(argv[0], &st);
	if (filestatus == -1)
	{
		path = _getenv("PATH");
		pathlen = _strlen(path);
		auxline = (char *)malloc(sizeof(char) * pathlen);
		if (auxline == NULL)
			return (NULL);
		auxline = _strcpy(auxline, path);
		auxline = strtok(auxline, "=");
		auxline = strtok(auxline, ":");
		while (auxline)
		{
			_strcat(auxline, argv[0]);
			filestatus = stat(auxline, &st);
			if (filestatus == 0)
			{
				argv[0] = auxline;
				break;
			}
			else
				auxline = strtok(NULL, ":");
		}
		free(auxline);
	}*/
	return (argv);
}
