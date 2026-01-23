#include <stdio.h>
#include <unistd.h> // For read, write, close and ft_popen prototype

// Declare ft_popen as it's defined in ft_popen.c
// Added const to argv for correctness as per typical conventions.
int ft_popen(const char *command, char *const argv[], char type);

int main() {
    // 'r' mode test
    // Corrected array initialization syntax
    char *args_ls[] = {"ls", "-l", NULL}; // Renamed to avoid conflict
    int fd_r = ft_popen("ls", args_ls, 'r'); // ls -l의 결과를 읽을 수 있는 FD를 받음

    if (fd_r == -1) {
        perror("ft_popen for 'ls' failed");
        return (1);
    }

    char buf[1024];
    int n;
    // Read from the file descriptor returned by ft_popen
    while ((n = read(fd_r, buf, sizeof(buf) - 1)) > 0) { // Use sizeof(buf)-1 for null termination
        buf[n] = '\0';
        printf("My program read: %s", buf);
    }
    close(fd_r); // Close the read file descriptor

    // 'w' mode test
    // Corrected array initialization syntax
    char *args_grep[] = {"grep", "hello", NULL}; // Renamed to avoid conflict
    int fd_w = ft_popen("grep", args_grep, 'w'); // grep의 입력으로 들어가는 FD를 받음

    if (fd_w == -1) {
        perror("ft_popen for 'grep' failed");
        return (1);
    }

    write(fd_w, "hello world\n", 12);
    write(fd_w, "this is test\n", 13); // 'hello'가 없으므로 출력되지 않아야 함
    close(fd_w); // Close the write file descriptor

    return (0);
}