#ifndef _MAIN_
#define _MAIN__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

typedef struct shdata_s
{
	char **argv;
	char **sh_env;
	int status;
	int pid;
} shdata_t;

typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

typedef struct builtin_func_s
{
	char *name;
	int (*func)(shdata_t *);
} builtin_funcs_t;

/* string functions */
int _strcmp(char *, char *);
char **split_string(const char *str, const char *delimiter);
int _atoi(char *s);

/* built-in functions */
int (*get_builtin(char *command))(shdata_t *);
int builtin_exit(shdata_t *data);
int builtin_env(shdata_t *data);

char *_getenv(const char *);
char *check_exe(char *);
void print_path(void);
void print_list(list_t *);
list_t *path_list();
list_t *add_node_end(list_t **, char *);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void shell_exit(int status, int args, char **argv);
void run_shell(shdata_t *);
void non_interactive(char **argv);
int fill_shdata(shdata_t *);

#endif
