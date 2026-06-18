#include "../include/list.h"
#include "../include/string.h"
#include <stdio.h>

int main()
{
    String* str = create_str(8);
    List *list = create_list();
    char line[] = "Hello, world!";
    for(int i =0; line[i]; ++i)
    {
        str_append(str, line[i]);
    }
    printf("%s\n", get_text(str));
    list_append(list, str);
    list_print(list);
}
