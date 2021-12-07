#include "shell.h"

/**
 * main - Main function for shell
 * Return: Always 0
 */

int main(void)
{
	char *prompt, *error;
	size_t aux;

	prompt = "($)";
	error = "Error: Command not found\n";
	aux = 1;
	init_shell(prompt, error, aux);
	return (0);
}
