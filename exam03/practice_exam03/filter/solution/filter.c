#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 2

int perror_and_free(char *stash, char *stars)
{
	perror("Error");
	free(stash);
	free(stars);
	return (1);
}

int main(int argc, char *argv[])
{
	if (argc != 2 || argv[1][0] == '\0')
		return (1);

	char buf[BUFFER_SIZE];
	char *stash = NULL;
	size_t stash_len = 0;
	char *pattern = argv[1];
	size_t pat_len = strlen(pattern);
	ssize_t r;

	char *stars = malloc(pat_len);
	if (!stars)
	{
		free(stash);
		return (1);
	}
	for (size_t i = 0; i < pat_len; ++i)
		stars[i] = '*';

	while ((r = read(STDIN_FILENO, buf, BUFFER_SIZE)) > 0)
	{
		char *tmp = realloc(stash, stash_len + r);
		if (!tmp)
			return perror_and_free(stash, stars);
		stash = tmp;
		memmove(stash + stash_len, buf, r);
		stash_len += r;

		size_t offset = 0;
		char *pos;
		while ((pos = memmem(stash + offset, stash_len - offset, pattern, pat_len)))
		{
			size_t prefix_len = pos - (stash + offset);

			if (prefix_len > 0)
			{
				if (write(STDOUT_FILENO, stash + offset, prefix_len) == -1)
					return (perror_and_free(stash, stars));
			}
			if (write(STDOUT_FILENO, stars, pat_len) == -1)
				return (perror_and_free(stash, stars));

			offset += prefix_len + pat_len;
		}

		size_t keep = (pat_len > 0) ? pat_len - 1 : 0;
		if (stash_len > offset)
		{
			size_t remaining = stash_len - offset;

			if (remaining > keep)
			{
				size_t write_len = remaining - keep;
				if (write(STDOUT_FILENO, stash + offset, write_len) == -1)
					return (perror_and_free(stash, stars));
				memmove(stash, stash + offset + write_len, keep);
				stash_len = keep;
			}
			else
			{
				memmove(stash, stash + offset, remaining);
				stash_len = remaining;
			}
		}
		else
		{
			stash_len = 0;
		}
	}
	if (r < 0)
		return (perror_and_free(stash, stars));

	if (stash_len > 0)
	{
		if (write(STDOUT_FILENO, stash, stash_len) == -1)
			return (perror_and_free(stash, stars));
	}

	free(stash);
	free(stars);
	return (0);
}
