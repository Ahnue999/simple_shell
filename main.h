#ifndef _MAIN_
#define _MAIN__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct shdata_s
{
	char **argvec;
	char **sh_env;
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
	void (*func)(shdata_t *);
} builtin_funcs_t;

/* string functions */
int _strcmp(char *, char *);
char **split_string(const char *str, const char *delimiter);

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

#endif
