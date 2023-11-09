#include "main.h"

/**
 * non_interactive : runs the shell in non-interactive mode.
 * argv: arguments vector.
 *
 * Return: void.
 */
void non_interactive(char **argv)
{
	char *exe_path;
	int child_state;
	pid_t child_pid;

	argv++;
	exe_path = check_exe(argv[0]);

	if (!exe_path)
	{
		perror("");
		exit(1);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("");
		exit(1);
	}

	if (child_pid == 0)
	{
		execve(exe_path, argv, environ);
		perror("");
		_exit(1);
	}
	else
		wait(&child_state);
}


/**
 * run_shell - runs the prompt loop.
 * shdata: data of the shell.
 *
 * Return: void.
 */
void run_shell(shdata_t *data)
{
	char *lineptr = NULL, *exe_path, *cwd = NULL;
	size_t n = 0;
	int status = 1, child_state, length;
	pid_t child_pid;
	char **args;
	int (*func)(shdata_t *);

	signal(SIGINT, SIG_IGN);

	while (1)
	{
		cwd = getcwd(NULL, 4096);
		length = 0;
		while (cwd[length])
			length++;
		write(STDOUT_FILENO, cwd, length);
		write(STDOUT_FILENO, "  \\(^~^)/ ", 11);
		fflush(stdout);
		status = getline(&lineptr, &n, stdin);
		if (status == -1)
			break;
		args = split_string(lineptr, "\n ");
		func = get_builtin(args[0]);
		if (func != NULL)
		{
			data->status = 0;
			if (args[1])
				data->status = atoi(args[1]);
			func(data);
			continue;
		}
		exe_path = check_exe(args[0]);

		if (!exe_path)
		{
			perror("");
			continue;
		}

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("");
			exit(1);
		}

		if (child_pid == 0)
		{
			execve(exe_path, args, data->sh_env);
			perror("");
			_exit(1);
		}
		else
			wait(&child_state);
	}

	free(lineptr);
}
