#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "avl.c"

//Given a filepath, this function will return a null terminated string of the file.
char *getStringFromFile(char *path)
{
    int bufSize = 1000;
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

struct Node* addToAVL(char * c){
    return NULL;
}
void generateHuffmanTree(struct Node* n){
}
int main(int argc, char **argv)
{
    char *filename;
    filename = argv[1];
    int x;
    char * string;
    string =getStringFromFile(filename);
    
    struct Node* avlRoot = addToAVL(string);
    generateHuffmanTree(avlRoot);
    //printf("%s", string);
    struct node* root = NULL;
    for (x = 0; string[x]!='\0'; x++)
    {
        printf("%c", string[x]);
        root = insert(root, string[x]);
       
    }
    printf("\n");
    

    printf("Inorder traversal of the constructed AVL"
           " tree is \n");
    inOrder(root);
    return 0;
}
