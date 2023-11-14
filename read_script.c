#include "main.h"

int read_script(shdata_t *data)
{
	int fd, count;
	char *buf;
	char **cmd_arr;


	if (access(data->args[1], F_OK) == 0)
	{
		if (access(data->args[1], X_OK) == -1)
		{
			buf = malloc(sizeof(char) * 4096);
			if (!buf)
				return (-1);

			fd = open(data->args[1], O_RDONLY);

			read(fd, buf, 1024);

			cmd_arr = check_symbols(buf, data);
			count = 0;
			while (cmd_arr[count])
			{
				data->args = split_string(cmd_arr[count], "\n ");
				execute(data);
				count++;
				data->ps_count++;
			}
		}
	}
	return (0);
}
