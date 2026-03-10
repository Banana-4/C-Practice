#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lnode {
    char *_text;
    struct lnode *_next;
} lnode;

typedef struct pylist {
    lnode *_head;
    lnode *_tail;
    size_t _len;

}pylist;

pylist *pylist_new() {
    pylist *l = (pylist*)malloc(sizeof(pylist));
    if (!l)
        return NULL;
    l->_head = l->_tail = NULL;
    l->_len = 0;
    return l;
}

void pylist_del(pylist *l) {
    if (!l)
        return;
    lnode *cur = l->_head;

    while (cur) {
        lnode *n = cur->_next;
        free(cur->_text);
        free(cur);
        cur = n;
    }
    free(l);
}

void pylist_append(pylist *l, char *str) {
    if (!l || !str)
        return;
    lnode *n = (lnode*)malloc(sizeof(lnode));
    if (!n)
        return;
    n->_text = malloc(strlen(str) + 1);
    if (!n->_text) {
        free(n);
        return;
    }
    strcpy(n->_text, str);
    n->_next = NULL;
    if(l->_head) {
        l->_tail->_next = n;
        l->_tail = n;
    } else
        l->_head = l->_tail = n;
    ++l->_len;
}

int pylist_index(pylist *l, char *str) {
    if (!l || !str)
        return -1;
    lnode *c = l->_head;
    int p = 0;
    while (c) {
      if  (strcmp(c->_text, str) == 0)
            return p;
        p++;
        c = c->_next;
    }
    return -1;
}

size_t pylist_len(pylist *l) {
    return l ? l->_len : -1;
}

void pylist_print(pylist *l) {
    if (!l)
        return;
    lnode *c = l->_head;
    printf("[");
    while (c) {
        printf("'%s'", c->_text);
        c = c->_next;
        if (c)
            printf(", ");
    }
    printf("]\n");
}


int main() {
    pylist *l = pylist_new();
    pylist_print(l);
    pylist_append(l, "Hello world!");
    pylist_print(l);
    pylist_append(l, "Catch phrase");
    pylist_print(l);
    pylist_append(l, "Brian");
    pylist_print(l);
    printf("pylist len: %zu\n", pylist_len(l));
    printf("Brian? %d\n", pylist_index(l, "Brian"));
    printf("Bob? %d \n", pylist_index(l, "Bob"));
    pylist_del(l);
}
