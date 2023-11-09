#include "main.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/**
 * main - entry point.
 * Return: always 0.
 */
int main(int argc, char **argv)
{
	shdata data;
	char **av;
	fill_shdata(

	run_shell(&data);
}

/**
 * run_shell - runs the prompt loop.
 * shdata: data of the shell.
 *
 * Return: void.
 */
void run_shell(shdata_t *data)
{
	char *lineptr = NULL, *exe_path;
	size_t n = 0;
	int status = 1, child_state;
	pid_t child_pid;
	char **args;

	signal(SIGINT, SIG_IGN);

	while (1)
	{
		write(STDOUT_FILENO, "\\(*_*)/ ", 9);
		fflush(stdout);
		status = getline(&lineptr, &n, stdin);
		if (status == -1)
			break;
		args = split_string(lineptr, "\n ");
		exe_path = check_exe(args[0]);

		if (!exe_path)
		{
			perror("");
			continue;
		}

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork failed");
			return (1);
		}

		if (child_pid == 0)
		{
			execve(exe_path, args, environ);
			perror("execve failed");
			_exit(1);
		}
		else
			wait(&child_state);
	}

	free(lineptr);
	return (0);
}
