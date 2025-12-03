#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# include <unistd.h>
# include <stdlib.h>

char    *get_next_line(int fd);

#endif