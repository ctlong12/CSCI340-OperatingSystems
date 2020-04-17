// CSCI-340 - Homework #7

// Starter file for the double linked list


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


// basic node structure

typedef struct __node_t {
    
    int key;
    struct __node_t *next;
    struct __node_t *prev;

} node_t;

// basic list structure (one used per list)

typedef struct {
    
    node_t *head;
    node_t *tail;
    // Add the lock to the node structure
    pthread_mutex_t  lock;
    
} list_t;

// Initialize the list

void List_Init(list_t *L) {

    // Add code here to initialize the list
    L->head = NULL;
    L->tail = NULL;
    pthread_mutex_init(&L->lock, NULL);
    
}

// Insert into the list (At the front)

void List_Insert(list_t *L,
                 int key) {

    // Add code here to safely insert a new node at the beginning of the list
    pthread_mutex_lock(&L->lock); // Lock the thread for manipualation
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
 	perror("malloc");
	pthread_mutex_unlock(&L->lock); // Unlock the thread before failure
	return -1;  // Fail
    }

    // Create new node at head
    new->key = key;
    new->next = L->head;
    L->head = new;

    // Attach tail of linked list to the new node if list is empty
    if (L->head->next == NULL) {
 	L->tail = new;
    } else {
    // Otherwise, the attach the previous node's prev to the new node
	L->head->next->prev = new;
    }

    pthread_mutex_unlock(&L->lock); // Unlock the thread before exiting
    return 0;
    
}

// Insert into the list (At the end)

void List_Append(list_t *L,
                 int key) {

    // Add code here to safely insert a new node at the end of the list

    pthread_mutex_lock(&L->lock); // Lock the thread for data manipualation
    node_t *new = malloc(sizeof(node_t));

    if (new == NULL) {
 	perror("malloc");
	pthread_mutex_unlock(&L->lock); // Unlock the thread before failure
	return -1;  // Fail
    }

    // Create new node at tail
    new->key = key;
    new->prev = L->tail;
    L->tail = new;

    // Attach head of linked list to the new node if list is empty
    if (L->tail->prev == NULL) {
 	L->head = new;
    } else {
    // Otherwise, the attach the previous node's next to the new node
	L->tail->prev->next = new;
    }
    
    pthread_mutex_unlock(&L->lock); // Unlock the thread before exiting
    return 0;
    
}

int List_Lookup(list_t *L,
                int key) {

    // Add code here to lookup an item in the list
    pthread_mutex_lock(&L->lock);
    node_t *curr = L->head;
    while (curr) {
	if (curr->key == key) {
	    pthread_mutex_unlock(&L->lock); // Unlock the thread before exiting
  	    return 0; // Success
	}
	
	curr = curr->next;
    }

    pthread_mutex_unlock(&L->lock); // Unlock the thread before failure
    return -1; // Fail
    
}

int main()
{

    // Add code here to test your list
    list_t *myList;
    myList = malloc(sizeof(list_t));

    // Init Double Linked List
    List_Init(myList);
    
    // Add items to head
    List_Insert(myList, 2);
    List_Insert(myList, 4);
    List_Insert(myList, 6);

    // Add items to tail
    List_Insert(myList, 8);

   // Find item
   List_Lookup(myList, 6);
   List_Lookup(myList, 10);
    
   return 0;
    
}
