#include <stdio.h>
#include <stdlib.h>
#include "avl2.c"
struct nodeBST
{
    char *key;
    int count;
    struct nodeBST *left;
    struct nodeBST *right;
};

struct nodeBST *newNodeBST(char *key)
{
    struct nodeBST *n = (struct nodeBST *)malloc(sizeof(struct nodeBST));
    n->key = key;
    n->count = 1;
    n->left = NULL;
    n->right = NULL;
    return n;
}

struct nodeBST *insertBST(struct nodeBST *root, char *key)
{
    if (root == NULL)
    {
        return newNodeBST(key);
    }
    int bal = strcmp(key, root->key);
    if (bal == 0)
    {
        (root->count)++;
        return root;
    }
    if (bal < 0)
    {
        root->left = insertBST(root->left, key);
    }
    else
    {
        root->right = insertBST(root->right, key);
    }
    return root;
}

void inOrder(struct nodeBST *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%s:%d\n", root->key, root->count);
        inOrder(root->right);
    }
}
void insertIntoAVL(struct nodeBST *root){
     if (root != NULL)
    {
        insertIntoAVL(root->left);
        printf("inserting %s:%d\n", root->key, root->count);
        insert(root, root->key, root->count);
        insertIntoAVL(root->right);
    }
}