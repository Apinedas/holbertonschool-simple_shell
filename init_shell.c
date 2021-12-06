#include "shell.h"

/**
 * init_shell - Fuction to execute simple shell
 */

int init_shell(void)
{
	char **argv, *prompt, *line, *error;
	pid_t child_pid;
	ssize_t linelen;
	size_t aux;
	int status, argc = 0;

	aux = 1;
	linelen = 0;
	prompt = "($)";
	error = "Error: Command not foud\n";
	while (1)
	{
		line = malloc(sizeof(*line) * 100);
		if (line == NULL)
			return (1);
		if (isatty(0) == 1)
			write(STDOUT_FILENO, prompt, _strlen(prompt));
		linelen = getline(&line, &aux, stdin);
		if (linelen == 1)
		{
			free(line);
			continue;
		}
		if (linelen == -1)
		{
			free(line);
			return (2);
		}
		argc = count_words(line);
		argv = malloc(sizeof(*argv) * (argc + 2));
		if (argv == NULL)
		{
			free(line);
			return (1);
		}
		argv = linetoargv(line, argv, linelen);
		if (argv[0] != NULL)
		{
			child_pid = fork();
			if (child_pid == 0)
				execve(argv[0], argv, NULL);
			else
				wait(&status);
			free(line);
			if (argv[0] != line)
				free(argv[0]);
			free(argv);
		}
		else
		{
			write(STDOUT_FILENO, error, _strlen(error));
			free(line);
			free(argv);
		}
		ISATTY(1);
	}
	return (0);
}
