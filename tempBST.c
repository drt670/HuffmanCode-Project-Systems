#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include "bst.c"

static
void Merge(nodeBST **arr, int low, int mid, int high)
{
    int mergedSize = high - low + 1;
    nodeBST **temp = (nodeBST **)malloc(mergedSize * sizeof(nodeBST*));
    int mergePos = 0;
    int leftPos = low;
    int rightPos = mid + 1;

    //printf("-->> %s: lo = %d, md = %d, hi = %d, sz = %d\n", __func__, low, mid, high, mergedSize);

    //printf("L = %d, M = %d; R = %d, H = %d\n", leftPos, mid, rightPos, high);
    while (leftPos <= mid && rightPos <= high)      // Key change
    {
        //printf("a[%d].c = %d <=> a[%d].c = %d\n", leftPos, arr[leftPos].count,
        //       rightPos, arr[rightPos].count);
        if (arr[leftPos]->count < arr[rightPos]->count)
        {
            //printf("L1: a[%d].c = %d\n", leftPos, arr[leftPos].count);
            temp[mergePos++] = arr[leftPos++];
        }
        else
        {
            //printf("R1: a[%d].c = %d\n", rightPos, arr[rightPos].count);
            temp[mergePos++] = arr[rightPos++];
        }
        //printf("L = %d, M = %d; R = %d, H = %d\n", leftPos, mid, rightPos, high);
    }

    while (leftPos <= mid)
    {
        //printf("L2: a[%d].c = %d\n", leftPos, arr[leftPos].count);
        temp[mergePos++] = arr[leftPos++];
    }

    while (rightPos <= high)
    {
        //printf("R2: a[%d].c = %d\n", rightPos, arr[rightPos].count);
        temp[mergePos++] = arr[rightPos++];
    }

    assert(mergePos == mergedSize);

    //PrintArray("merged", mergedSize, temp);

    for (mergePos = 0; mergePos < mergedSize; ++mergePos)
        arr[low + mergePos] = temp[mergePos];

    free(temp);         // Key change
    //printf("<<-- %s: lo = %d, md = %d, hi = %d, sz = %d\n", __func__, low, mid, high, mergedSize);
}

static
void MergeSort(nodeBST **arr, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        //printf("-->> %s: lo = %d, md = %d, hi = %d\n", __func__, low, mid, high);

        MergeSort(arr, low, mid);
        MergeSort(arr, mid + 1, high);

        Merge(arr, low, mid, high);
        //printf("<<-- %s: lo = %d, md = %d, hi = %d\n", __func__, low, mid, high);
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
	struct nodeBST * a = (struct nodeBST**) p;    
    struct nodeBST * b = (struct nodeBST**) q;

   return a->count - b->count;
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

    struct nodeBST *words[1145];
    int z;
    for(z = 0; z < 1145; z++)
    {
        words[z]=malloc(sizeof(nodeBST));
    }
    

    printf("numTokens:%d words.\n", numTokens);
    int numTokensActual = AddToArray(root, words, 0);
    int i;

	MergeSort(words, 0, numTokensActual - 1);



/*
    for(i=0; i<numTokensActual; i++ ){
        
       printf("words[%d]:%s: \n", i, ((struct nodeBST*)words[i])->key);
    }

    qsort(*words,numTokensActual,sizeof(nodeBST), comparator); */
    for(i=0; i<numTokensActual; i++ ){
        
       printf("sorted words[%d]:%s: %d \n", i, ((struct nodeBST*)words[i])->key, ((struct nodeBST*)words[i])->count);
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
