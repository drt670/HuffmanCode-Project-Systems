#include <stdio.h>
#include <stdlib.h>
typedef struct nodeBST
{
    char *key;
    int count;
    struct nodeBST *left;
    struct nodeBST *right;
}nodeBST;

struct nodeBST *newNodeBST(char *key)
{
    struct nodeBST *n = (struct nodeBST *)malloc(sizeof(struct nodeBST));
    n->key = malloc(sizeof(char)*100);
strcpy(n->key, key);
    n->count = 1;
    n->left = NULL;
    n->right = NULL;
    return n;
}
struct nodeBST *newNodeBST2(char *key, int count)
{
    struct nodeBST *n = (struct nodeBST *)malloc(sizeof(struct nodeBST));
    n->key = malloc(sizeof(char)*1000);
strcpy(n->key, key);
    n->count = count;
    n->left = NULL;
    n->right = NULL;
    return n;
}
int AddToArray( nodeBST *node,  nodeBST **arr, int i)
{
    if (node == NULL)
        return i;

    if (node->left != NULL)
        i = AddToArray(node->left, arr, i);
    //printf("Adding To Array[%d]: %s:%d\n",i, node->key, node->count);
    //arr[i] = node;
    arr[i] = newNodeBST2(node->key, node->count);
    //printf("added array[%d]: %s\n", i, arr[i]->key);
    i++;
    if (node->right != NULL)
        i = AddToArray(node->right, arr, i);

    return i;
}


struct nodeBST *insertBST(struct nodeBST *root, char *key)
{
    if (root == NULL)
    {
        return newNodeBST(key);
    }
    int bal = strcmp(key, (root)->key);
    if (bal == 0)
    {
        ((root)->count)++;
        return root;
    }
    if (bal < 0)
    {
        (root)->left = insertBST((root)->left, key);
    }
    else
    {
        (root)->right = insertBST((root)->right, key);
    }
    return root;
}
struct nodeBST *insertBSTbyCount(struct nodeBST *root, struct nodeBST *unsorted)
{
    int decider =0;
    if (root == NULL)
    {
        return newNodeBST2(unsorted->key, unsorted->count);
    }
    int bal = unsorted->count -
              root->count;
    if (bal == 0)
    {
        //(root->count)++;
        //return newNodeBST2(unsorted->key, unsorted->count);
         root->left = insertBSTbyCount(root->left, unsorted);
        //return root;
    }
    if (bal < 0)
    {
        root->left = insertBSTbyCount(root->left, unsorted);
    }
    else
    {
        root->right = insertBSTbyCount(root->right, unsorted);
    }
    return root;
}

void inOrderBST(struct nodeBST *root)
{
    if (root != NULL)
    {
        inOrderBST(root->left);
        printf("inOrderBST:token %s count%d\n", root->key, root->count);
        inOrderBST(root->right);
    }
    //printf("inOrderBST: root is null\n");
}
struct nodeBST *inOrderBSTsort(struct nodeBST *root, struct nodeBST *unsorted)
{ //printf("inOrderBSTsort: root is null\n");

    if (root != NULL)
    {
        inOrderBSTsort(root->left, unsorted);
        insertBSTbyCount(root, unsorted);
        printf("inOrderBSTsort: %s:%d\n", root->key, root->count);
        inOrderBSTsort(root->right, unsorted);
        return root;
    }
}
/*
void inOrderAVL(struct node *root)
{
    if (root != NULL)
    {
        inOrderAVL(root->left);
        printf("%s:%d\n", root->key, root->count);
        inOrderAVL(root->right);
    }
}
/*
int minValue(struct nodeBST *node)
{
    struct nodeBST *current = node;

    
    while (current->left != NULL)
    {
        current = current->left;
    }
    return (current->key);
}  


void insertIntoAVL(struct nodeBST *root, struct node **avl)
{
    if (root == NULL)
    {
        return;
    }

    insertIntoAVL(root->left, *(&avl));
    printf("inserting %s:%d\n", root->key, root->count);

    *avl = insert(*avl, root->key, root->count);
    inOrderAVL(*avl);
    return;
    insertIntoAVL(root->right, *(&avl));
}
*/
