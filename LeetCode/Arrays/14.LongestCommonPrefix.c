#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    if(strsSize == 1) {
        return strs[0];
    }

    if(strsSize == 0) {
        return "";
    }

    size_t min_len = 200;
    for (int i = 0; i < strsSize; i++) {
        size_t len = strlen(strs[i]);
        if (min_len > len) {
            min_len = len;
        }
    }
    char* prefix = malloc(min_len + 1);
    if (!prefix) {
        return NULL;
    }
    prefix[0] = '\0';
    for(int i = 0; i < min_len; i++) {
        for(int j = 1; j < strsSize; j++) {
            if (strs[j][i] != strs[j - 1][i]) {
               return prefix;
            }
        }
        prefix[i] = strs[0][i];
        prefix[i + 1] = '\0';
    } 
    return prefix;
}
