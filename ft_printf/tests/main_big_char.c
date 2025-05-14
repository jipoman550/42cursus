#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "ft_printf.h"

int main(void)
{
    const char *msg = "Hello42Gyeongsan!";
    int ret1, ret2;
    size_t i;

    // Print many times to potentially trigger write error
    for (i = 0; i < 10000000000; i++)
    {
        // Use libc printf
        ret1 = printf("%s\n", msg);
        if (ret1 < 0)
        {
            fprintf(stderr, "[libc printf] write error occurred at i=%zu\n", i);
            break;
        }

        // Use your own ft_printf
        ret2 = ft_printf("%s\n", msg);
        if (ret2 < 0)
        {
            write(2, "[ft_printf] write error occurred\n", 33);
            break;
        }
    }

    return 0;
}
