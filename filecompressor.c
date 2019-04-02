#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include "sortedToHuffman.c"
static int numTokens = 0;
nodeBST *compressFile(char *, nodeBST **);
static void Merge(nodeBST **arr, int low, int mid, int high)
{
    int mergedSize = high - low + 1;
    nodeBST **temp = (nodeBST **)malloc(mergedSize * sizeof(nodeBST *));
    int mergePos = 0;
    int leftPos = low;
    int rightPos = mid + 1;

    while (leftPos <= mid && rightPos <= high) // Key change
    {
        if (arr[leftPos]->count < arr[rightPos]->count)
        {
            temp[mergePos++] = arr[leftPos++];
        }
        else
        {
            temp[mergePos++] = arr[rightPos++];
        }
    }

    while (leftPos <= mid)
    {
        temp[mergePos++] = arr[leftPos++];
    }

    while (rightPos <= high)
    {
        temp[mergePos++] = arr[rightPos++];
    }

    assert(mergePos == mergedSize);

    for (mergePos = 0; mergePos < mergedSize; ++mergePos)
        arr[low + mergePos] = temp[mergePos];

    free(temp);
}

static void MergeSort(nodeBST **arr, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        MergeSort(arr, low, mid);
        MergeSort(arr, mid + 1, high);
        Merge(arr, low, mid, high);
    }
}

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
    //printf("number of chars in file:%d\n", size);
    buffer[0][size] = '\0';

    close(fd);
    return buffer[0];
}

int main(int argc, char **argv)
{
    char *filename;
    filename = argv[1];
    int x;
    char *string;

    //char path[100] = ".";
    //listFilesRecursively(path);
    struct nodeBST *root = NULL;
    root = compressFile("test2.txt", &root);
    inOrderBST(root);
    root = compressFile("test2.txt", &root);
    inOrderBST(root);

    //huffmanEncode(&root, numTokens);

    //string = getStringFromFile(filename);

    //struct Node *avlRoot = addToAVL(string);
    //generateHuffmanTree(avlRoot);
    //printf("%s", string);

    return 0;
}

nodeBST *compressFile(char *path, nodeBST **rootc)
{
    struct nodeBST *root = NULL;
    root = *rootc;
    char *text = getStringFromFile(path);
    // printf("%s", text);
    char delimit[] = "  \t\r\n\v\f";
    //int i = 0, j = 0;
    char *token;
    int i, z;

    //     start with a pointer to the begining of the string
    // iterate character by character, looking for your delimiter
    // each time you find one, you have a string from the last position of the length in difference - do what you want with that
    // set the new start position to the delimiter + 1, and the go to step 2.
    i = 0;
    int start = 0;
    while (text[i] != '\0')
    {
        if (!strchr(delimit, (char)text[i]))
        {
            //delimitor found
            char subbuff[1];
            subbuff[0] = text[i];

            subbuff[1] = '\0';
            root = insertBST(root, subbuff);
            if (start != i)
            {
                //insert prev string
                char subbuff[i - start + 1];
                memcpy(subbuff, &text[start], i - start);
                subbuff[i - start] = '\0';
                root = insertBST(root, subbuff);
            }
            i++;
            start = i;
        }
        else
        {

            i++;
        }
    }
    token = 'a';
    if (numTokens == 0 || numTokens == 16)
    {
        token = strtok(text, delimit);
        root = insertBST(root, token);
        numTokens++;
    }
    while (token != NULL)
    {
        //printf("found token:%s\n", token);
        token = strtok(NULL, delimit);
        if (token != NULL)
        {
            root = insertBST(root, token);
            numTokens++;
        }
    }
    printf("string has been tokenized.\n");
    return root;
    //prints inorder of bst sorted alphabetically
    inOrderBST(root);
    // printf("tempBST: inorder of alphabetical has been printed.\n");
}
void huffmanEncode(nodeBST ***rootz, int numTokens)
{
    nodeBST **root = NULL;
    root = *rootz;
    int z, i;
    struct nodeBST *words[numTokens];
    for (z = 0; z < numTokens; z++)
    {
        words[z] = malloc(sizeof(nodeBST));
    }

    printf("numTokens:%d words.\n", numTokens);
    int numTokensActual = AddToArray(root, words, 0);

    root = *root;

    MergeSort(words, 0, numTokensActual - 1);

    for (i = 0; i < numTokensActual; i++)
    {

        // printf("sorted words[%d]:%s: %d \n", i, ((struct nodeBST*)words[i])->key, ((struct nodeBST*)words[i])->count);
    }
    int huffmanCodeBookFD = open("HuffmanCodebook", O_RDWR | O_CREAT | O_TRUNC, 0666);

    if (huffmanCodeBookFD < 0)
    {
        return -1;
    }

    HuffmanCodes(words, numTokensActual, huffmanCodeBookFD);
}