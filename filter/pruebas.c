#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 4096

void    print_error(const char *msg)
{
    fprintf(stderr, "Error: %s\n", msg);
}

void    print_star_line(char *line, size_t len)
{
    while (len--)
        write(1, "*", 1);
}

int filter_line(char *line, char *filter, size_t filter_len)
{
    char    *ptr = line;
    int     found = 0;

    while (*ptr)
    {
        char *match = memmem(ptr, strlen(ptr), filter, filter_len);
        if (!match)
        {
            write(1, ptr, strlen(ptr));
            break;
        }
        write(1, ptr, match - ptr); // print before match
        print_star_line(match, filter_len);
        ptr = match + filter_len;
        found = 1;
    }
    return (found);
}

int process_input(char *filter)
{
    char    buf[BUF_SIZE + 1];
    ssize_t bytes_read;

    while ((bytes_read = read(0, buf, BUF_SIZE)) > 0)
    {
        buf[bytes_read] = '\0';
        if (strcmp(filter, "*") == 0)
            write(1, buf, bytes_read);
        else
            filter_line(buf, filter, strlen(filter));
    }
    if (bytes_read < 0)
    {
        print_error("read failed");
        return (1);
    }
    return (0);
}

int main(int argc, char **argv)
{
    if (argc != 2 || argv[1][0] == '\0')
        return (1);

    char *filter = strdup(argv[1]);
    if (!filter)
    {
        print_error("malloc failed");
        return (1);
    }
    int ret = process_input(filter);
    free(filter);
    return (ret);
}