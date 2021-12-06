#include "shell.h"

/**
 * init_shell - Fuction to execute simple shell
 * Return: 0 on success execution, 1 on malloc failure
 */

int init_shell(void)
{
	char **argv, *prompt, *line, *error;
	pid_t child_pid;
	ssize_t linelen;
	size_t aux;
	int status, argc, argvst, i;

	aux = 1;
	prompt = "($)";
	error = "Error: Command not foud\n";
	while (1)
	{
		line = malloc(sizeof(*line) * 100);
		if (line == NULL)
			return (1);
		ISATTYPROMPT(prompt, _strlen(prompt));
		linelen = getline(&line, &aux, stdin);
		if (linelen == 1)
		{
			free(line);
			continue;
		}
		else if (linelen == -1 || _strcmp(line, "exit\n") == 0)
		{
			free(line);
			return (0);
		}
		else if (_strcmp(line, "env\n") == 0)
		{
			ENVBUILTIN(environ, line, i);
			free(line);
			continue;
		}
		else if (linelen == -1 || _strcmp(line, "exit\n") == 0)
		{
			free(line);
			return (0);
		}
		argc = count_words(line);
		argv = malloc(sizeof(*argv) * (argc + 2));
		if (argv == NULL)
		{
			free(line);
			return (1);
		}
		argvst = linetoargv(line, argv, linelen);
		if (argvst >= 0)
		{
			child_pid = fork();
			if (child_pid == 0)
				execve(argv[0], argv, environ);
			else
				wait(&status);
			FREELAR(line, argvst, argv[0], argv);
		}
		else
		{
			write(STDOUT_FILENO, error, _strlen(error));
			free(line);
			free(argv);
		}
		ISATTYOUT;
	}
	return (0);
}
