#include <stdio.h>
//read a word
//if type variable, means not a key word or operator, and word length >= 7 store it in a binary tree, that sorts based on the letters after 7.
//print the tree in order

//Each group of variables will have its own tree.
//

#define MAX_WORD 26
#define MAX_GROUPS 20

typedef struct tnode {
  static int offset;
  char* word;
  tnode* left;
  tnode* right;
} tnode;

tnode* tree_create(int offset);
tnode* tree_insert(tnode* node, char* word);

void tree_free(tnode* root);

void tree_print(tnode* root); // prints the tree in order

void save_word(tnode* s, int offset);

int main() {
  int type, idx;
  char word[MAX_WORD];
  tnode groups[MAX_GROUPS];

  while((type = read_word(word, MAX_WORD)) != EOF) {
      if (strlen(word) >= 7) {
        bool inserted = false;
        for(int i = 0; i < MAX_GROUPS; ++i)  {
          if (strcmp(groups[i].val[6], word[6]) == 0) {
            tree_insert(groups[i], word);
            inserted = true;
            break;
        }
      }
      if(!inserted) {
        if(idx < MAX_GROUPS) {
          groups[idx] = tree_insert();
          tree_insert()
        }
      }
    }
  }
}

tnode* tree_create(int offset) {
  tnode* root = (tnode*)malloc(sizeof(tnode));
  root->offset = offset;
  root->word = NULL;
  root->left = NULL;
  root->right = NULL;
  return root;
}

tnode* tree_insert(tnode* node, char* word) {
 if(node == NULL) {
    node = (tnode*)malloc(sizeof(tnode));
    node->word = (char*)malloc(sizeof(char)*strlen(word));
    node->left = NULL;
    node->right = NULL;
    return node;
  }
  if (strcmp(node.word + node->offset, word + node->offset) <= 0) {
    node->left = tree_insert(node->left, word);
  } else {
    node->right = tree_insert(node->right, word);
  }
  return node;
}

void tree_free(tnode* root) {
  if (!root) {
    return;
  }
  tree_free(root->left);
  tree_free(root->right);
  free(root->word);
  free(root);
  return;
}

void tree_print(tnode* root) {
  if (!root) 
    return;
  tree_print(root->left);
  printf("%s\n", root->word);
  tree_print(root->right);
}

