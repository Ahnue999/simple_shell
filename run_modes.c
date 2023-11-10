#include "main.h"

void non_interactive(char **argv, shdata_t *data);
/**
 * non_interactive - runs the shell in non-interactive mode.
 * @argv: arguments vector.
 * @data: data
 * Return: void.
 */
void non_interactive(char **argv, shdata_t *data)
{
	char *exe_path;
	int child_state;
	pid_t child_pid;

	argv++;
	exe_path = check_exe(argv[0], data->sh_env);

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
 * @data: data of the shell.
 *
 * Return: void.
 */
void run_shell(shdata_t *data)
{
	char *lineptr = NULL, *exe_path;
	size_t n = 0;
	int status = 1, child_state, count;
	pid_t child_pid;
	int (*func)(shdata_t *);
	char **env_arr, **cmd_arr;

	signal(SIGINT, signal_handler);

	while (1)
	{
		prompt();
		status = _getline(&lineptr, &n, stdin);
		if (status == -1)
			break;
		if (*lineptr == '\n' && !*(lineptr + 1))
			continue;
		cmd_arr = check_symbols(lineptr);
		count = 0;
		while (cmd_arr[count])
		{
			data->args = split_string(cmd_arr[count], "\n ");
			func = get_builtin(data);
			if (func != NULL)
			{
				data->status = 0;
				if (data->args[1])
					data->status = atoi(data->args[1]);
				func(data);
				count++;
				continue;
			}
			exe_path = check_exe(data->args[0], data->sh_env);

			if (!exe_path)
			{
				perror("");
				count++;
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
			count++;
		}
	}

	data->ps_count++;
	free(lineptr);
}
