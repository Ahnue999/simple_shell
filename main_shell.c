#include "main.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/**
 * fill_shdata - fills the shdata_t structure.
 * @data: the empty structure.
 * @argv: main arguments.
 *
 * Return: a filled shdata structure.
 */
int fill_shdata(shdata *data, char **argv)
{
	int i;

	for (i = 0; environ[i]; i++)
		;

	data->sh_env = malloc(sizeof(char *) * i + 1);
	if (!sh_env)
		exit(1);

	i = 0;
	while (environ[i])
	{
		data->sh_env[i] = strdup(environ[i]);
		i++;
	}
	data->sh_env[i] = NULL;

	return (0);
}

/**
 * non_interactive : runs the shell in non-interactive mode.
 * @data: shell data.
 *
 * Return: void.
 */

void non_interactive(int argc, char **argv)
{
	exe_path = check_exe(argv[0]);

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
		execve(exe_path, argv, environ);
		perror("execve failed");
		_exit(1);
	}
	else
		wait(&child_state);
}

/**
 * main - entry point.
 * @argc: arguments count.
 * @argv: arguments vector.
 *
 * Return: always 0.
 */
int main(int argc, char **argv)
{
	shdata_t data;


	if (!isatty(STDIN_FILENO))
	{
		non_interactive(argv);
		return (0);
	}

	fill_shdata(&data, argv);
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
