// C program for Huffman Coding
#include <stdio.h>
#include <stdlib.h>
#include "bst.c"

// This constant can be avoided by explicitly
// calculating height of Huffman Tree
#define MAX_TREE_HT 20000

// A Huffman tree node
struct MinHeapNode
{

    // One of the input characters
    char *data;

    // Frequency of the character
    unsigned freq;

    // Left and right child of this node
    struct MinHeapNode *left, *right;
};

// A Min Heap:  Collection of
// min heap (or Hufmman tree) nodes
struct MinHeap
{

    // Current size of min heap
    unsigned size;

    // capacity of min heap
    unsigned capacity;

    // Attay of minheap node pointers
    struct MinHeapNode **array;
};

// A utility function allocate a new
// min heap node with given character
// and frequency of the character
struct MinHeapNode *newHeapNode(nodeBST *words)
{
    struct MinHeapNode *temp = (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));

    temp->left = temp->right = NULL;
    temp->data = words->key;
    temp->freq = words->count;

    return temp;
}

// A utility function to create
// a min heap of given capacity
struct MinHeap *createMinHeap(unsigned capacity)

{

    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));

    // current size is 0
    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array = (struct MinHeapNode **)malloc(minHeap->capacity * sizeof(struct MinHeapNode *));
    return minHeap;
}

// A utility function to
// swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode **a,
                     struct MinHeapNode **b)

{

    struct MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

// The standard minHeapify function.
void minHeapify(struct MinHeap *minHeap, int idx)

{

    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx)
    {
        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// A utility function to check
// if size of heap is 1 or not
int isSizeOne(struct MinHeap *minHeap)
{

    return (minHeap->size == 1);
}

// A standard function to extract
// minimum value node from heap
struct MinHeapNode *extractMin(struct MinHeap *minHeap)

{

    struct MinHeapNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

// A utility function to insert
// a new node to Min Heap
void insertMinHeap(struct MinHeap *minHeap,
                   struct MinHeapNode *minHeapNode)

{

    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
    {

        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

// A standard funvtion to build min heap
void buildMinHeap(struct MinHeap *minHeap)

{

    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// A utility function to print an array of size n
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);

    printf("\n");
}

// Utility function to check if this node is leaf
int isLeaf(struct MinHeapNode *root)

{

    return !(root->left) && !(root->right);
}

// Creates a min heap of capacity
// equal to size and inserts all character of
// data[] in min heap. Initially size of
// min heap is equal to capacity
struct MinHeap *createAndBuildMinHeap(nodeBST **data, int size)

{
    int i;

    struct MinHeap *minHeap = createMinHeap(size);

    for (i = 0; i < size; ++i)
        minHeap->array[i] = newHeapNode(data[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}
void print2DUtil(struct MinHeapNode *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    int i;
    for (i = 2; i < space; i++)
        printf(" ");
    printf("%s:%d\n", root->data, root->freq);

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(struct MinHeapNode *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

// The main function that builds Huffman tree
struct MinHeapNode *buildHuffmanTree(nodeBST **data, int size)

{
    struct MinHeapNode *left, *right, *top;

    // Step 1: Create a min heap of capacity
    // equal to size.  Initially, there are
    // modes equal to size.
    struct MinHeap *minHeap = createAndBuildMinHeap(data, size);

    // Iterate while size of heap doesn't become 1
    while (!isSizeOne(minHeap))
    {

        // Step 2: Extract the two minimum
        // freq items from min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Step 3:  Create a new internal
        // node with frequency equal to the
        // sum of the two nodes frequencies.
        // Make the two extracted node as
        // left and right children of this new node.
        // Add this node to the min heap
        // '$' is a special value for internal nodes, not used
        nodeBST *temp = newNodeBST2("$", left->freq + right->freq);
        top = newHeapNode(temp);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    // Step 4: The remaining node is the
    // root node and the tree is complete.
    return extractMin(minHeap);
}

// Prints huffman codes from the root of Huffman Tree.
// It uses arr[] to store codes
void printCodes(struct MinHeapNode *root, int *arr, int top)

{

    if (root->left)
    {

        arr[top] = 0;

        printCodes(root->left, arr, top + 1);
    }

    if (root->right)
    {

        arr[top] = 1;

        printCodes(root->right, arr, top + 1);
    }

    if (isLeaf(root))
    {

        printf("%s: ", root->data);
        printArr(arr, top);
    }
}

// The main function that builds a
// Huffman Tree and print codes by traversing
// the built Huffman Tree
void HuffmanCodes(nodeBST **words, int size, int fd)

{
    // Construct Huffman Tree
    struct MinHeapNode *root = buildHuffmanTree(words, size);

    // Print Huffman codes using
    // the Huffman tree built above
    int arr[MAX_TREE_HT], top = 0;
    //print2D(root);
    printCodes(root, arr, top);
    //write first escape character
    if (write(fd, "\\\n", 2) != 2)
    {
        write(2, "There was an error writing to file\n", 35);
        return -1;
    }
    generateCodeBook(root, arr, top, fd);
    printf("codebook generated\n");
    
}
void generateCodeBook(struct MinHeapNode *root, int *arr, int top, int fd)
{

    if (root->left)
    {

        arr[top] = 0;

        generateCodeBook(root->left, arr, top + 1, fd);
    }

    if (root->right)
    {

        arr[top] = 1;

        generateCodeBook(root->right, arr, top + 1, fd);
    }

    if (isLeaf(root))
    {

       // printf("%s: ", root->data);
        writeToCodeBook(root->data, arr, top, fd);
        //printArr(arr, top);
    }
}
void append(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}
void writeToCodeBook(char *word, int *code, int n, int filedesc)
{
    if (filedesc < 0)
    {
        return -1;
    }
    char *line = malloc(strlen(word) + n + 3);
    
    strcat(line, word);
    strcat(line, "\t");

    int i;
    for(i=0;i<n;i++){
        append(line, (char)(code[i]+'0'));
    }
    append(line, '\n');

    if (write(filedesc, line, strlen(line)) != strlen(line))
    {
        write(2, "There was an error writing to testfile.txt\n", 43);
        return -1;
    }
}
