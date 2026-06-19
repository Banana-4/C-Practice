#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct Bucket
{
    char *entries;
    size_t len;
    size_t size;
};

typedef struct Set
{
    struct Bucket **buckets;
    size_t len;
    size_t size;
    float load;
}Set;

Set *create_set();
bool set_insert(Set *set, char key);
bool in_set(const Set *set, char key);
void set_delete(Set *set);
