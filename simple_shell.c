#include "shell.h"

/**
 * init_shell - Fuction to execute simple shell
 */

void init_shell(void)
{
	char **argv, *desired_prompt, *line;
	pid_t child_pid;
	ssize_t linelen;
	size_t aux;
	int status, exeresult;

	desired_prompt = "MiniShell>";
	argv = (char **)malloc(sizeof(char *) * 1024);
	if (argv == NULL)
		exit(0);
	while (1)
	{
		prompt(desired_prompt);
		line = (char *)malloc(sizeof(char) * 100);
		if (line  == NULL)
			exit(0);
		linelen = getline(&line, &aux, stdin);
		if (linelen == -1)
			break;
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
		if (isatty(0) != 1)
			break;
	}
}
