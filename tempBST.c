#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "bst.c"

//Given a filepath, this function will return a null terminated string of the file.
char *getStringFromFile(char *path)
{
    int bufSize = 100;
    int elementSize = 131072;
    unsigned char **buffer = malloc(sizeof(unsigned char *) * bufSize);
    int z;
    for (z = 0; z < bufSize; z++)
    {
        buffer[z] = malloc(sizeof(unsigned char) * elementSize);
    }
    int length;

    int fd;
    /* Open the file, print error message if we fail */
    if ((fd = open(path, O_RDONLY)) < 0)
    {
        perror("Unable to open data");
        exit(1);
    }
    printf("Filename:%s\n", path);
    int i = 0;
    int size = 0;
    while ((length = read(fd, buffer[0] + i, 1)) > 0)
    {

        //printf("i=%d\tbuffer:%c\t", i, buffer[0][i]);
        //printf("ascii:%d\n", buffer[0][i]);
        size++;
        i++;
    }
    printf("number of chars in file:%d\n", size);
    buffer[0][size] = '\0';

    close(fd);
    return buffer[0];
}

// void generateHuffmanTree(struct Node *n)
// {
// }
int main(int argc, char **argv)
{
    char *filename;
    filename = argv[1];
    int x;
    char *string;
    compressFile(filename);
    //string = getStringFromFile(filename);

    //struct Node *avlRoot = addToAVL(string);
    //generateHuffmanTree(avlRoot);
    //printf("%s", string);

    return 0;
}
int comparator(const void *p, const void *q)  
{ 
    int l = ((struct nodeBST *)p)->count; 
    int r = ((struct nodeBST *)q)->count;  
    return (l - r); 
} 
void compressFile(char *path)
{
    struct nodeBST *root = NULL;
    struct nodeBST *rootCopy = NULL;
    char *text = getStringFromFile(path);
    // printf("%s", text);
    char delimit[] = " \t\r\n\v\f";
    //int i = 0, j = 0;
    char *token;
    token = strtok(text, delimit);

    root = insertBST(root, token);
    rootCopy = root;
    int numTokens=1;
    while (token != NULL)
    {
        printf("found token:%s\n", token);
        token = strtok(NULL, delimit);
        if (token != NULL){
            root = insertBST(root, token);
            numTokens++;
        }
    }
    printf("string has been tokenized.\n");
    //prints inorder of bst sorted alphabetically
    inOrderBST(root);
    printf("tempBST: inorder of alphabetical has been printed.\n");
    if (root == NULL)
    {
        printf("tempBST: root is null.\n");
    }

    struct nodeBST *words[numTokens];

    printf("numTokens:%d words.\n", numTokens);
    int numTokensActual = AddToArray(root, &words, 0);
    int i;
    for(i=0; i<numTokensActual; i++ ){
        
       printf("words[%d]:%s: \n", i, ((struct nodeBST*)words[i])->key);
    }
    qsort(words,sizeof(words)/sizeof(words[0]), sizeof(words[0]), comparator );
    for(i=0; i<numTokensActual; i++ ){
        
       printf("sorted words[%d]:%s: \n", i, ((struct nodeBST*)words[i])->key);
    }
   // words[1000] = root->right;
   // printf("words[1000]: %s\n", (&words)[1000]->key );
    // add inorder of sorted alphabetically list to stack

    //insert into sorted bst
    //struct nodeBST *sorted = NULL;
   // inOrder(root, &sorted);
   // printf("tempBST: list has been sorted by frequency.\n");

// if (sorted == NULL)
//     {
//         printf("tempBST: sorted is null.\n");
//     }
    //prints inorder of bst sorted by word frequency
    //inOrderBST(sorted);

    // insertIntoAVL(root,&avl);
    //inOrderAVL(avl);
}
