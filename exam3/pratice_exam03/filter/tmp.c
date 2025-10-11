#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

extern int errno;

int main(int, char* argv[])
{
    printf("errno: %d\n", errno);
    int fd = open("./thisfiledoesnotexist", O_RDONLY);
    printf("errno: %d\n", errno);
    perror(argv[0]);
    fd = open("./thisfiledoesnotexist", O_RDONLY);
    char buf[1024];
    size_t size = read(fd, buf, 1024);
    printf("errno: %d\n", errno);
    perror(argv[0]);
    //for(int i=0;i<255;i++)
    //    printf("%s\n", strerror(i));
}