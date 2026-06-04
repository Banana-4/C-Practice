#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
// Author: Banana-4
// Date: 04-06-2026

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} StringList;

//list interface
bool list_init(StringList *list);
bool list_append(StringList *list, char *value);
void list_iterate(const StringList *list); // iterates over the list while printing node values
void list_free(StringList *list);

size_t get_line(char *line, const size_t lim);
size_t remove_comments(char *line, const size_t len);
char *save_line(char *line, size_t len);

int main()
{
    const size_t LIMIT = 10000;
    char line[LIMIT];
    size_t len;
    StringList list;
    if (!list_init(&list))
        return -1;

    while ((len = get_line(line, LIMIT)))
    {
        len = remove_comments(line, len);
        if (len > 0)
        {
            char *l = save_line(line, len);
            if (l)
            {
                list_append(&list, l);
            }
        }
    }

    list_iterate(&list);
    list_free(&list);
    return 0;
}

bool list_init(StringList *list)
{
    if (!list)
    {
      return false;
    }

    list->head = NULL;
    list->tail = NULL;

    return true;
}

bool list_append(StringList *list, char *value)
{
    Node *node = malloc(sizeof(Node));
    if (!node) {
        return false;
    }

    node->value = value;
    node->next = NULL;

    if (list->tail) {
        list->tail->next = node;
    } else {
        list->head = node;
    }

    list->tail = node;
    return true;
}

void list_iterate(const StringList *list)
{
    if (!list)
        return;
    for (Node *n = list->head; n != NULL; n = n->next) {
        printf("%s", n->value);
    }
}

void list_free(StringList *list)
{
    if (!list)
    {
        return;
    }
    Node *n = list->head;

    while (n) {
        Node *next = n->next;
        free(n->value);
        free(n);
        n = next;
    }

    list->head = NULL;
    list->tail = NULL;
}

size_t get_line(char *line, const size_t lim) {

    if (!line || lim == 0)
        return 0;
    int c;
    size_t i = 0;

    for (; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
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

size_t remove_comments(char *line, const size_t len)
{
    if (!line || len == 0)
        return 0;
    size_t i = 0;
    while( i < len - 1)
    {
        if (line[i] == '\'' || line[i] == '"')
        {
            char d = line[i];
            while (i < len - 1)
            {
                ++i;
                if (line[i] == d)
                    break;
            }
        }
        else if (line[i] == '/' && line[i + 1] == '/')
        {
                if (i != 0)
                    line[i++] = '\n';
                line[i] = '\0';
                return i;
        }
        ++i;
    }
    return i;
}

char *save_line(char *line, size_t len) {
  if (!line || len == 0) {
      return NULL;
  }
  char *l = malloc(len + 1);
  if (!l)
      return NULL;
  memcpy(l, line, len + 1);
  return l;
}
