#include <stdio.h>
#include <stdlib.h>
#include <bst.c>
#include <tempBST.c>

typedef struct Node 
{ 
	struct Node *left
	struct Node *right;
	char *data;
	int frequency; 


}Node; 

struct Node* llNode(char * key, int frequency) {

	struct Node* node = (struct mhNode*) malloc(sizeof(struct mhNode));
	Node->frequency = key;
	Node->left = NULL;
	Node->right = NULL;
	Node->data = frequency;
	return (node);
}
  
// Utility function for allocating node for BST 
Node* newNode(int frequency, char* data)
{ 
	struct Node* node = (struct Node*) malloc(sizeof(struct Node));
	node->frequency = frequency; 
	node->data = data;
	node->left = node->right = NULL; 
	return node; 
} 

struct qNode { 
	int key; 
	struct qNode *next; 
}; 
  
// Front stores the front node of the linked list and rear stores the last node of the linked list
typedef struct Queue { 
	struct qNode *front, *rear;
}; 
  
// Create a new linked list node for queue
struct qNode* newQ(int k, char *data) { 
	
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
	struct QNode *temp = llNode(k, data); 
  
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

Node* flattenToLL(Node* root) {
    
	Node *list1 = (root->left) ? flattenToLL(root->left) : NULL;
	Node *list2 = (root->right) ? flattenToLL(root->right) : NULL;
	Node *list3 = newNode(root->frequency);
	
	// The "middle" list3 cannot be NULL; append list2 to list3
	list3->right = list2; // If list2 is NULL, it's OK
    
	if (!list1) return list3; // Nothing to prepend
		Node *last = list1;
    
	while (last->right) last=last->right; // Go to the end of list1
		last->right = list3; // Append list3+list2 to the end of list1
    
	return list1;
}

void SortedLLToMinHeap(Node* &root, Node* head) { 
	
	// Base Case 
	if (head == NULL) 
		return; 
  
	// create empty queue to store parent nodes
	struct Queue *q = newQ(); 
  
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
	Node *parent = root;
	dequeue(q);
  
        /* Take next two nodes from the linked list and 
       	   Add them as children of the current parent node. 
           Also, push them into the queue so that 
           they will be parents to the future nodes 
	*/	

	Node *leftChild = head; 
	head = head->right;        // advance linked list to next node 
	leftChild->right = NULL; // set its right child to NULL 
	enqueue(leftChild, head->frequency, head->data); 
  
        // Assign the left child of parent 
	parent->left = leftChild; 
  
	if (head) 
	{ 
		Node *rightChild = head; 
		head = head->right; // advance linked list to next node 
		rightChild->right = NULL; // set its right child to NULL 
		enqueue(rightChild, head->frequency, head->data); 
  
            // Assign the right child of parent 
		parent->right = rightChild; 
        } 
    } 
} 

int main() 
{ 

	Node *list1 = flattenToLL(root);
	
	root = NULL;

	sortedLLToMinHeap(root, list1);
  
	return 0; 
} 
