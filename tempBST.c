#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "avl.c"
//given a file, go word by word and add unique words and their frequencies into an avl tree
//to run : gcc -O -g -o tempBST tempBST.c
int main(int argc, char **argv)
{
    char *filename;
    filename = argv[1];
    printf("Filename:%s\n", filename);

    int fd = open(filename, O_RDONLY);

    if (fd == -1)
    {
        // we have an error
        printf("Error Number % d\n", errno);
    }
    char buffer[4096];
    int length;
    //int fd;

    /* Open the file, print error message if we fail */
    if ((fd = open(filename, O_RDONLY)) < 0)
    {
        perror("Unable to open data");
        exit(1);
    }

    /* Copy file contents to stdout, stop when read returns 0 (EOF) */
    while ((length = read(fd, buffer, 4096)) > 0)
        write(1, buffer, length);

    close(fd);
    // struct Node *root = NULL;
    // root = insert(root, 10);
    // root = insert(root, 20);
    // root = insert(root, 30);
    // root = insert(root, 40);
    // root = insert(root, 50);
    // root = insert(root, 25);
    // printf("Inorder traversal of the constructed AVL"
    //        " tree is \n");
    // inOrder(root);
    return 0;
}
