#include <stddef.h>
#include <stdio.h>

#define LIMIT 1000

char secondary[LIMIT];
size_t i = 0;

size_t get_line(char *line, const size_t lim, const size_t n);

int main()
{
    char line[LIMIT];
    size_t len = 0;
    size_t n = 50;
    while ((len = get_line(line, LIMIT, n)) > 0)
    {
        printf("%s", line);
    }
    return 0;
}


size_t get_line(char *line, const size_t lim, const size_t n)
{
    if (!line || lim == 0)
        return 0;
    if (n == 0 || lim < n)
        return 0;


    size_t j = 0;
    while (i > 0)
    {
        line[j] = secondary[j];
        ++j;
        --i;
    }

    int c;
    for (; j < n - 1; ++j)
    {
        c = getchar();
        if (c == EOF) {
            break;
        }
        if (c == '\n') {
            break;
        }
        line[j] = c;
    }

    if (j > 0)
    {
        for (; i < LIMIT - 1 && (line[j] == ' ' || line[j] == '\t'); ++i, --j)
        {
            secondary[i] = line[j];
        }
        secondary[i] = '\0';
        if (j < n - 2)
        {
            line[++j] = '\n';
            line[j] = '\0';
        }
        else
        {
            line[j] = '\0';
        }
    }
    return j;
}

/*
While working on this i observed that i am not translating logic to code. I am
not deliberatly practicing, the code design that i wrote is false because i did
not think like i was programing.
The code sections i dont write as a translation of a responsibility.
I am not activly writing the code i am just rushing to finish the exercise.
 */
