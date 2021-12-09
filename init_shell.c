#include "shell.h"

/**
 * execute - Execute function for simple_shell
 * @argv: Argument vector
 * Return: 0 on succes execution, -1 on exit
 */

int execute(char **argv)
{
	int i;

	if (_strcmp(argv[0], "env") == 0)
	{
		ENVBUILTIN(environ, i);
		return (0);
	}
	execve(argv[0], argv, environ);
	return (0);
}

/**
 * init_shell - Fuction to execute simple shell
 * @prompt: Prompt to print
 * @sh_command: command used to execute the shell
 * @aux: Auxiliar size_t to getline
 * Return: 0 on success execution, 1 on malloc failure
 */

int init_shell(char *prompt, char *sh_command __attribute__((unused)), size_t aux)
{
	char **argv, *line = NULL;
	pid_t child_pid;
	ssize_t linelen = 0;
	int status, argvst, argc = 0;

	while (1)
	{
		ISATTYPROMPT(prompt, _strlen(prompt));
		line = _calloc(100, sizeof(*line));
		if (line == NULL)
			return (1);
		linelen = getline(&line, &aux, stdin);
		argc = count_words(line);
		if (linelen == 1 || argc == linelen - 1)
		{
			free(line);
			continue;
		}
		if (linelen == -1 || _strcmp(line, "exit\n") == 0)
			break;
		argv = _calloc((argc + 2), sizeof(*argv));
		if (argv == NULL)
			break;
		argvst = linetoargv(line, argv, linelen);
		if (argvst >= 0)
		{
			child_pid = fork();
			if (child_pid == 0)
				execute(argv);
			else
				wait(&status);
			FREELAR(line, argvst, argv[0], argv);
		}
		else
			FREEWRITE(line, argv);
		ISATTYOUT;
	}
	free(line);
	return (0);
}
