#include "shell.h"

/**
 * main- First version of simple shell
 * Return: Always 0
 */

int main()
{
	char **argv, *input_line, *line, *prompt, *linetoargv;
	pid_t child_pid;
	size_t linelen, aux;
	int status, exeresult, i;

	prompt = "MiniShell>";
	while (1)
	{
		write(STDOUT_FILENO, prompt, _strlen(prompt));
		linelen = getline(&input_line, &aux, stdin);
		line = (char *)malloc((sizeof(char) * linelen) + 1);
		if (line  == NULL)
			write(STDOUT_FILENO, "Error on malloc\n", 17);
		_strcpy(line, input_line);
		linetoargv = strtok(line, " ");
		for (i = 0; linetoargv; i++)
		{
			argv[i] = linetoargv;
			linetoargv = strtok(NULL, " ");
		}
		argv[i] = NULL;
		child_pid = fork();
		if (child_pid == 0)
		{
			exeresult = execve(argv[0], argv, NULL);
			if (exeresult == -1)
				printf("Error :(\n");
		}
		else
			wait(&status);
		if (isatty(0) != 1)
			break;
	}
	return (0);
}
