#include "main.h"

/**
  * execute - execute a functiong provided its
  * name and arguments.
  * @data: shell data.
  *
  * Return: 0 on success, 127 if file is not found.
  */
int execute(shdata_t *data)
{
	char *exe_path;
	int child_state;
	char **env_arr;

	if (!data->args[0])
		return (127);

	exe_path = check_exe(data->args[0], data->sh_env);
	env_arr = list_to_array(data->sh_env);

	if (!exe_path)
	{
		data->status = 127;
		print_errors(data);
		/*free(exe_path);*/
		free_aop(env_arr);
		return (127);
	}

	switch (fork())
	{
		case -1:
			perror("");
			exit(1);
		case 0:
			execve(exe_path, data->args, env_arr);
			perror("");
			_exit(1);
		default:
			wait(&child_state);
	}
	if (strcmp(exe_path, data->args[0]) != 0)
		free(exe_path);
	free_aop(env_arr);
	return (0);
}
