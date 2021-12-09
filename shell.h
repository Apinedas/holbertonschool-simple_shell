#ifndef SHELL_H
#define SHELL_H
#define _GNU_SOURCE

/* libraries */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/* macros */

#define ISATTYOUT \
do {\
	if (isatty(0) == 0)\
		break;\
} while (0)

#define ISATTYPROMPT(PROMPT, LEN) \
do {\
	if (isatty(0) == 1)\
		write(STDOUT_FILENO, (PROMPT), (LEN));\
} while (0)

#define FREEWRITE(SH_COMMAND, LINE, ARGV) \
do {\
	perror(SH_COMMAND);\
	free(ARGV);\
	free(LINE);\
} while (0)

#define FREELAR(LINE, ARST, ARZ, AR) \
do {\
	free(LINE);\
	if (ARST == 1)\
		free(ARZ);\
	free(AR);\
} while (0)

#define ENVBUILTIN(ENV, I) \
do {\
	for (I = 0; ENV[I]; I++)\
	{\
		write(STDOUT_FILENO, ENV[I], _strlen(ENV[I]));\
		write(STDOUT_FILENO, "\n", 1);\
	} \
} while (0)

#define ISATTY(N)\
do {\
	if (isatty(0) != (N))\
		break;\
} while (0)

/* functions */

int init_shell(char *prompt, char *error, size_t aux);
int linetoargv(char *line, char **argv, ssize_t linelen);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int count_words(char *s);
void *_calloc(unsigned int nmemb, unsigned int size);
extern char **environ;



#endif
