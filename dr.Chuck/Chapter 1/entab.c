#include <stdio.h>

size_t get_line(char *line, size_t limit)
{
    char c;
    size_t i = 0;
    for (; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        line[i] = c;
    }

    if (c == '\n')
    {
        line[i++] = c;
    }

    line[i] = '\0';

    return i;
}

size_t entab(char *buf, const char *line, const size_t LIMIT, const size_t TABSTOP)
{
    if (!buf || !line || LIMIT == 0 || TABSTOP == 0)
    {
        return 0;
    }

    size_t i = 0;
    size_t j = 0;
    while ( j < LIMIT - 1 && line[i] != '\0')
    {

        if (line[i] == ' ')
        {
            size_t start = i;
            size_t end;
            while (line[++i] == ' ');
            end = i;
            int tabs = 0;
            int spaces = 0;
            size_t next_tab = start + (TABSTOP - (start % TABSTOP));
            while (next_tab <= end)
            {
                ++tabs;
                next_tab += TABSTOP;
            }
            spaces = end - start - (tabs * TABSTOP);
            while (tabs--)
            {
                buf[j++] = '\t';
            }
            while (spaces--)
            {
                buf[j++] = ' ';
            }
        }
        else
        {
            buf[j++] = line[i++];
        }
    }
    buf[j] = '\0';
    return j;
}

int main()
{
    const size_t LIMIT = 1000;
    const size_t TABSTOP = 4;
    char line[LIMIT];

    size_t len = 0;
    while ((len = get_line(line, LIMIT)))
    {
        char entab_line[LIMIT];
        len = entab(entab_line, line, LIMIT, TABSTOP);
        if (len == 0)
        {
            fprintf(stderr, "Error: entab failed.\n");
            return 1;
        }
        printf("%s", entab_line);
    }
    return 0;

}
