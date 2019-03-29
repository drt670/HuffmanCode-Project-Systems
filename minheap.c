#include <stdio.h>
#include <stdlib.h>
#include <"avl.c">

/* Basically I am traversing through the BST recursively and storing them into a Linked List, then I am converting that Linked List into a Min-Heap*/

// Node for BST/Min-Heap
struct mhNode {

	struct mhNode *left;
	struct mhNode *right;
	char *data;
	int frequency;
};

// Helper function to create new node for linked list
struct mhNode* llNode(char * key) {

	struct mhNode* node = (struct mhNode*) malloc(sizeof(struct mhNode));
	mhNode->frequency = node->key;
	mhNode->left = NULL;
	mhNode->right = NULL;
	mhNode->data = node->count;
	return (mhNode);
}

// A linked list node to store a queue entry 
struct qNode { 
	int key; 
	struct qNode *next; 
}; 
  
// Front stores the front node of the linked list and rear stores the last node of the linked list
struct Queue { 
	struct qNode *front, *rear, *leftChild, *rightChild; 
}; 
  
// Create a new linked list node 
struct qNode* newNode(int k, char *data) { 
	
	struct qNode *temp = (struct QNode*)malloc(sizeof(struct qNode)); 
	temp->key = k;
	temp->data = data;
	temp->next = NULL; 
	
	return temp;  
} 
  
// Create an empty queue
struct Queue *newQueue() { 
	
	struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue)); 
	q->front = q->rear = NULL; 
    
	return q; 
} 

// Function to add a key k to q
void enQueue(struct Queue *q, int k, char *data) { 
    
	// Create new linked list node
	struct QNode *temp = newNode(k); 
  
	// If queue is empty, then new node is front and rear
	if (q->rear == NULL) {
		printf("Sorry queue is empty"); 
		q->front = q->rear = temp; 
       
		return; 
	} 
  
	// Add new node to the front and change rear 
	q->rear->next = temp; 
	q->rear = temp; 
} 
  
// Function to remove a key from q
struct QNode *deQueue(struct Queue *q) { 
	
	// If queue is empty return 0. 
	if (q->front == NULL) {
		printf("Sorry queue is empty"); 
		return 0; 
	}

	// store the prev front and move front node one ahead
	struct QNode *temp = q->front; 
	q->front = q->front->next;
  
	// If front is NULL, make rear NULL as well
	if (q->front == NULL) 
		q->rear = NULL; 

	return temp; 
} 

void BSTToSortedLL(mhNode* root, mhNode** head_ref) { 
    
	// If root is empty return 0 
	if(root == NULL) 
		return 0; 
  
	// Recursively convert the right subtree
	BSTToSortedLL(root->right, head_ref); 
  
	// Place root inside of linked list
	root->right = *head_ref; 
  
	// Change left pointer of previous head to point to NULL
	if (*head_ref != NULL) 
		(*head_ref)->left = NULL; 
  
	// Change head of linked list 
	*head_ref = root; 
  
	// Recursively convert left subtree 
	BSTToSortedLL(root->left, head_ref); 
} 

void SortedLLToMinHeap(mhNode* &root, mhNode* head) { 
	
	// Base Case 
	if (head == NULL) 
		return; 
  
	// create empty queue to store parent nodes
	struct Queue *q = newQueue(); 
  
	// The first node is always the root node 
	root = head; 
  
	// advance the pointer to the next node 
	head = head->right; 
  
	// set right child to NULL 
	root->right = NULL; 
  
	// add first node to the queue 
	enqueue(q, root->frequency, root->data); 
  
	// run until the end of linked list is reached 
	while (head) { 
        
	// Take the parent node from the q and remove it from q 
	dequeue(q);
  
        // Take next two nodes from the linked list and 
        // Add them as children of the current parent node 
        // Also in push them into the queue so that 
        // they will be parents to the future nodes 
	mhNode *leftChild = head; 
	head = head->right;        // advance linked list to next node 
	leftChild->right = NULL; // set its right child to NULL 
	enqueue(leftChild, FREQUENCY); 
  
        // Assign the left child of parent 
	parent->left = leftChild; 
  
	if (head) 
	{ 
		mhNode *rightChild = head; 
		head = head->right; // advance linked list to next node 
		rightChild->right = NULL; // set its right child to NULL 
		enqueue(rightChild, FREQUENCY); 
  
            // Assign the right child of parent 
		parent->right = rightChild; 
        } 
    } 
} 

// Function to convert BST into a Min-Heap 
mhNode* convertMin(mhNode* &root) { 
    
	// head of Linked List 
	mhNode *head = llNode(root); 
  
	// Convert a given BST to Sorted Linked List 
	BSTToSortedLL(root, &head); 
  
	// set root as NULL 
	root = NULL; 
  
	// Convert Sorted Linked List to Min-Heap 
	SortedLLToMinHeap(root, head); 
} 

int main() {

	convertMin(root);

	
	
}
