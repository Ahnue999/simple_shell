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
	char *lineptr = NULL, *exe_path;
	size_t n = 0;
	int status = 1, child_state;
	pid_t child_pid;
	int (*func)(shdata_t *);
	char **env_arr;

	signal(SIGINT, signal_handler);

	while (1)
	{
		prompt();
		status = getline(&lineptr, &n, stdin);
		if (status == -1)
			break;
		if (*lineptr == '\n' && !*(lineptr + 1))
			continue;
		data->args = split_string(lineptr, "\n ");
		func = get_builtin(data);
		if (func != NULL)
		{
			data->status = 0;
			if (data->args[1])
				data->status = atoi(data->args[1]);
			func(data);
			continue;
		}
		exe_path = check_exe(data->args[0]);

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
			env_arr = list_to_array(data->sh_env);
			execve(exe_path, data->args, env_arr);
			perror("");
			_exit(1);
		}
		else
			wait(&child_state);
	}

	free(lineptr);
}
