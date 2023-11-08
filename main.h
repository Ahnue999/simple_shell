#ifndef _MAIN_
#define _MAIN__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

char **split_string(const char *str, const char *delimiter);
char *_getenv(const char *);
char *check_exe(char *);
void print_path(void);
void print_list(list_t *);
list_t *path_list();
list_t *add_node_end(list_t **, char *);

#endif
