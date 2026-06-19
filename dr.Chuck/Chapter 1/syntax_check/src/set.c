#include "../include/set.h"
#include <stdio.h>

struct Bucket *create_bucket()
{
    const size_t CAP = 8;
    struct Bucket *b = (struct Bucket*) malloc(sizeof(struct Bucket));
    if(!b)
        return NULL;
    b->entries = malloc(CAP);
    if(!b->entries)
    {
        free(b);
        return NULL;
    }
    b->len = 0;
    b->size = CAP;
    return b;
}

bool bucket_grow(struct Bucket *b)
{
    if(!b)
        return false;
    const size_t F = 2;
    char *entries = malloc(F * b->size);
    if(!entries)
        return NULL;
    memcpy(entries, b->entries, b->len);
    free(b->entries);
    b->entries = entries;
    return true;
}

bool bucket_append(struct Bucket *b, char key)
{
    if (!b)
        return false;

    if (b->len + 1 == b->size)
        if(!bucket_grow(b))
            return false;

    b->entries[b->len++] = key;

    return true;
}

void bucket_delete(struct Bucket *b)
{
    if(!b)
        return;
    free(b->entries);
    b->len = 0;
    b->size = 0;
    free(b);
}

Set *create_set()
{
    Set *set = (Set*) malloc(sizeof(Set));
    if(!set)
        return NULL;
    const size_t CAP = 8;
    set->len = 0;
    set->size = CAP;
    set->load = 0.6;
    set->buckets = calloc(set->size, sizeof(struct Bucket*));
    if(!set->buckets)
    {
        free(set);
        return NULL;
    }
    return set;
}

bool set_grow(Set* set)
{
    if(!set)
        return false;
    const size_t F = 2;
    struct Bucket **buckets = calloc(set->size * F, sizeof(struct Bucket*));
    if (!buckets)
        return false;
    size_t old_size = set->size;
    struct Bucket **old_entries = set->buckets;
    set->buckets = buckets;
    set->size = set->size * F;
    set->len = 0;
    for(size_t i = 0; i < old_size; ++i)
    {
        struct Bucket *b = old_entries[i];
        if (b == NULL)
            continue;
        for(size_t j = 0; j < b->len; ++j)
        {
            set_insert(set, b->entries[j]);
        }
    }
    return true;
}

bool set_insert(Set *set, char key)
{
    if(!set)
        return false;
    int idx = (unsigned)key % set->size;

    if (set->buckets[idx] == NULL)
    {

        set->buckets[idx] = create_bucket();
    }

    char* k = set->buckets[idx]->entries;
    size_t len = set->buckets[idx]->len;
    for(size_t i = 0; i < len; ++i)
    {
        if(k[i] == key)
            return true;
    }
    if ((double)set->len / set->size >= set->load)
        if(!set_grow(set))
            return false;
    bucket_append(set->buckets[idx], key);
    ++set->len;
    return true;
}

bool in_set(const Set *set, char key)
{
    if(!set)
        return false;
    int idx = (unsigned)key % set->size;
    if (set->buckets[idx] == NULL)
        return false;
    char* k = set->buckets[idx]->entries;
    size_t len = set->buckets[idx]->len;
    for(size_t i = 0; i < len; ++i)
    {
            if(k[i] == key)
                return true;
    }
    return false;
}

void set_delete(Set *set)
{
    if (!set)
        return;
    for (size_t i = 0; i < set->size; ++i)
    {
        if (set->buckets[i] != NULL)
        {
            bucket_delete(set->buckets[i]);
        }
    }
    set->len = 0;
    set->size = 0;
    free(set);
}
