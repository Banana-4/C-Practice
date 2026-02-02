#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 50

#define LETTER 'a'
#define NUMBER '0'

struct lnode {
    int val;
    struct lnode* next;
};

typedef struct lnode LinkedList;


struct tnode {
    char* word;
    int count;
    struct tnode* left;
    struct tnode* right;
};

typedef struct tnode BinaryTree;

BinaryTree *tree(struct tnode *node, const char* word);

struct ttnode {
    struct tnode* words;
    struct ttnode* left;
    struct ttnode* right;
};

typedef struct ttnode TokenTree;

TokenTree* ttree(struct ttnode* node, const char* word, unsigned len);
void print_ttree(TokenTree* root);

char type(char word);
char get_word(char* word, unsigned limit);
void print_tree(BinaryTree* root);
char* save_word(char* word);

int main() {
    //get word
    //check if letter
    // yes, add it to the tree
    //print binary tree in order
    char t, word[MAX];
    TokenTree* root = NULL;
    while((t = get_word(word, MAX)) != EOF) {
        if (t == LETTER) {
         root = ttree(root, word, 7);
        }
    }
    print_ttree(root);
}



BinaryTree *tree(struct tnode *node, const char* word) {
    if (!node) {
        node = (struct tnode*)malloc(sizeof(struct tnode));
        if (!node) {
            return NULL;
        }
        node->word = save_word(word);
        node->count = 1;
        node->left = NULL;
        node->right = NULL;
    } else {
        int cond = strcmp(node->word, word);
        if (cond == 0) {
            node->count++;
        }
        else if (cond > 0) {
            node->left = tree(node->left, word);
        }
        else {
             node->right = tree(node->right, word);
        }
    }
    return node;
}

char *save_word(char* word) {
    unsigned l = strlen(word) + 1;
    char*  s = (char*)malloc(sizeof(char) * l);
    if(!s )
        return NULL;
    memcpy(s, word, l);
    return s;
}


void print_tree(BinaryTree* root) {
    if (root == NULL)
        return;
    print_tree(root->left);
    printf("Word: %s, Count: %d\n", root->word, root->count);
    print_tree(root->right);
}

TokenTree* ttree(struct ttnode* node, const char* word, unsigned len) {
    if (!node) {
        node = (struct ttnode*)malloc(sizeof(struct ttnode));
        if (!node) {
            return NULL;
        }
        node->words = tree(NULL, word);
        node->left = NULL;
        node->right = NULL;
    } else {
        if (!node->words) {
            node->words = tree(node->words, word);
        } else {
            int i = 0;
            int cond;
            unsigned l = len;
            while (l-- && node->words->word[i] && word[i]) {
                if (node->words->word[i] != word[i++])
                    break;
            }

            cond = (unsigned char)node->words->word[i] - (unsigned char)word[i];

            if (cond == 0) {
                node->words = tree(node->words, word);
            }
            else if (cond > 0) {
                node->left = ttree(node->left, word, len);
            }
            else {
                node->right = ttree(node->right, word,len);
            }
        }

    }
    return node;
}

void print_ttree(TokenTree* root) {
    if(!root)
        return;
    print_ttree(root->left);
    print_tree(root->words);
    print_ttree(root->right);
}
