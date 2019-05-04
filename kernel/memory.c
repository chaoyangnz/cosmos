#include <kernel/memory.h>
#include <stdio.h>

const char *humanize_size(uint64_t bytes_len)
{
    char *suffix[] = {"B", "KB", "MB", "GB", "TB"};
    char length = sizeof(suffix) / sizeof(suffix[0]);

    int i = 0;
    double dblBytes = bytes_len;

    if (bytes_len >= 1024) {
        for (i = 0; (bytes_len / 1024) > 0 && i<length-1; i++, bytes_len /= 1024)
            dblBytes = bytes_len / 1024.0;
    }

    static char buffer[5][50];
    static buffer_index = 0;
    buffer_index %= 5;

    char *output = buffer[buffer_index];
    sprintf(output, "%.0lf %s", dblBytes, suffix[i]);
    buffer_index++;
    return output;
}