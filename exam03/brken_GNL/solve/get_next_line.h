#ifndef GNL
# define GNL
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *get_next_line(int fd);
#endif
