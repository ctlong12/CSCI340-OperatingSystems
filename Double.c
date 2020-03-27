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
    //list lock
    pthread_mutex_t lock;
} list_t;

// Initialize the list

void List_Init(list_t *L) {

    // Add code here to initialize the list
    L->head = L->tail = NULL;
    pthread_mutex_init(&L->lock, NULL);
    
}

// Insert into the list (At the front)

void List_Insert(list_t *L,
                 int key) {
    
    // Add code here to safely insert a new node at the beginning of the list
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
        perror("malloc");
        return;
	pthread_mutex_unlock(&L->lock);
    }
    new->key = key;

// just lock critical section

    pthread_mutex_lock(&L->lock);
    new->next = L->head;
    L->head->prev = new;
    L->head = new;
    L->head->prev = NULL;
    pthread_mutex_unlock(&L->lock);
    
}

// Insert into the list (At the end)

void List_Append(list_t *L,
                 int key) {

    // Add code here to safely insert a new node at the end of the list
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
        perror("malloc");
        return;
    }
    new->key = key;
    pthread_mutex_lock(&L->lock);
    new->prev = L->tail;
    L->tail->next = new;
    L->tail = new;
    L->tail->next = NULL;
    pthread_mutex_unlock(&L->lock);
    
}

int List_Lookup(list_t *L,
                int key) {

    // Add code here to lookup an item in the list
    int rv = -1;
    pthread_mutex_lock(&L->lock);
    node_t *curr = L->head;
    while (curr) {
        if (curr->key == key) {
            rv = 0;
            break;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&L->lock);
    return rv; 
    
}

int main()
{

    // Add code here to test your list
    list_t *myList;
    List_Init(myList);
    //insert at head
    //case 1: empty list
    List_Insert(myList, 0);
    //case 2: non-empty list
    List_Insert(myList, 1); 
    //append to list
    List_Append(myList,2);
    //lookup item in list
    List_Lookup(myList, 2);
    return 0;

    
}
