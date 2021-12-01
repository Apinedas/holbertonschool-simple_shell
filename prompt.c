#include "shell.h"

/**
 * prompt - Displays the shell prompt
 * @desired_prompt: Prompt to display
 */

void prompt(char *desired_prompt)
{
	write(STDOUT_FILENO, desired_prompt, _strlen(desired_prompt));
}
