#include <stdlib.h> // For exit
#include <unistd.h> // For pipe, fork, close, dup2, execvp

// Corrected function name and added necessary includes
int ft_popen(const char *file, char *const argv[], char type)
{
	int fds[2];

	if (type != 'r' && type != 'w')
		return (-1);
	if (pipe(fds) < 0)
		return (-1);

	int pid = fork();
	if (pid < 0) {
		close(fds[0]);
		close(fds[1]);
		return (-1);
	}

	if (pid == 0) // Child process
	{
		if (type == 'r') {
			// Redirect stdout of the command to the pipe's write end
			dup2(fds[1], STDOUT_FILENO); // Use STDOUT_FILENO for clarity
		} else {                       // type == 'w'
			// Redirect stdin of the command from the pipe's read end
			dup2(fds[0], STDIN_FILENO); // Use STDIN_FILENO for clarity
		}
		close(fds[0]);
		close(fds[1]);
		execvp(file, argv);
		// If execvp fails, exit with an error
		exit(EXIT_FAILURE); // Use EXIT_FAILURE for standard practice
	}
	else                // Parent process
	{
		if (type == 'r') {
			close(fds[1]); // Close the write end, parent doesn't need it for reading
			return (fds[0]); // Return the read end of the pipe
		}
		else             // type == 'w'
		{
			close(fds[0]);   // Close the read end, parent doesn't need it for writing
			return (fds[1]); // Return the write end of the pipe
		}
	}
}
