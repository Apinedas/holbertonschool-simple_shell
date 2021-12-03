#include "shell.h"

/**
 * init_shell - Fuction to execute simple shell
 */

int init_shell(void)
{
	char **argv, *prompt, *line;
	pid_t child_pid;
	ssize_t linelen;
	size_t aux;
	int status, exeresult, argc;

	aux = 1;
	linelen = 0;
	argc = 0;
	prompt = "($)";
	while (1)
	{
		line = malloc(sizeof(*line) * 100);
		if (line == NULL)
			return (1);
		write(STDOUT_FILENO, prompt, _strlen(prompt));
		linelen = getline(&line, &aux, stdin);
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
		child_pid = fork();
		if (child_pid == 0)
		{
			exeresult = execve(argv[0], argv, NULL);
			if (exeresult == -1)
				printf("Error: Command or file not found\n");
		}
		else
			wait(&status);
		free(line);
		free(argv);
		if (isatty(0) != 1)
			break;
	}
	return (0);
}
