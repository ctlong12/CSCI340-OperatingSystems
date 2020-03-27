
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct __node_t {
    
    int               value;
    struct __node_t * next;
    
} node_t;

typedef struct {
    
    node_t *        head;
    node_t *        tail;
    pthread_mutex_t head_lock;
    pthread_mutex_t tail_lock;

} queue_t;

void Queue_Init(queue_t *q) {
    
    node_t *tmp = malloc(sizeof(node_t));
    tmp->next = NULL;
    q->head = q->tail = tmp;
    
    pthread_mutex_init(&q->head_lock, NULL);
    pthread_mutex_init(&q->tail_lock, NULL);
    
}

void Queue_Enqueue(queue_t * q,
                   int       value) {
    
    pthread_mutex_lock(&q->tail_lock);
    node_t *tmp = malloc(sizeof(node_t));         /* Get a new node */
    if (tmp == NULL) {                            /* Did the allocation fail? */
        perror("malloc");
        return -1;
    }
/*problem 1) The assert statement creates a problem in concurrency because:
if the assert fails then the the program execution is aborted.
This results in the end of the current thread without unlocking the critical section.
Other threads trying to access this section will be in spin wait forever.
*/

//old:    assert(tmp != NULL);
//the correction is done by removing the assert and replacing it with logical if statement
    if(temp == NULL){
        tmp->value = value;                           /* Set the node's contents */
        tmp->next  = NULL;                            /* Show it's the tail */
        
        q->tail->next = tmp;                          /* Point old tail to new tail */
        q->tail = tmp;                                /* Point tail to new node */
    }
    
    
    pthread_mutex_unlock(&q->tail_lock);
    
}

int Queue_Dequeue(queue_t * q,
                  int *     value) {

    // Failure is always an option
    int rc = -1;
    
    
    if (q_head->next != NULL) {
        *value = q_head->next->value;             /* Return the value */
        pthread_mutex_lock(&q->head_lock);        /* Lock the list */
        node_t *tmp = q->head;                    /* Save the old head node pointer */
        q->head = q_head->next;                   /* Reset the head */
/*Problem 2: Premature unlocking. Thread is unlocked before the etire completion of the critical section.
This can be fixed by placing the unlock after the critical section.
*/
//old:        pthread_mutex_unlock(&q->head_lock);      /* Unlock the list */
        free(tmp);                                /* Free the old head node */
        rc = 0;
        pthread_mutex_unlock(&q->head_lock);      /*correction
    }
    
    
    return rc;
    
}
