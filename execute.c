#include "main.h"

int execute(shdata_t *data)
{
	char *exe_path;
	int child_state;
	pid_t child_pid;

	exe_path = check_exe(data->args[0], data->sh_env);

	printf("entered execute!\n\n");

	if (!exe_path)
	{
		data->status = 127;
		perror("");
		data->ps_count++;
		return (127);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("");
		exit(1);
	}

	if (child_pid == 0)
	{
		execve(exe_path, data->args, list_to_array(data->sh_env));
		perror("");
		_exit(1);
	}
	else
		wait(&child_state);
	return (0);
}
