/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)
        return NULL;  // if malloc fail return NULL
    q->head = NULL;   // if malloc success do init
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q != NULL) {
        list_ele_t *removePtr;
        while (q->head != NULL) {
            removePtr = q->head;
            q->head = q->head->next;
            free(removePtr);
        }  // free from the head of queue
        free(q);
    }
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q != NULL) {
        list_ele_t *newh;
        /* What should you do if the q is NULL? */
        newh = malloc(sizeof(list_ele_t));
        /* Don't forget to allocate space for the string and copy it */
        /* What if either call to malloc returns NULL? */
        if (newh != NULL) {
            newh->value = strdup(s);
            if (q->head == NULL && q->tail == NULL) {  // insert first node
                newh->next = NULL;
                q->head = newh;
                q->tail = newh;
            } else {
                newh->next = q->head;
                q->head = newh;
            }
            q->size++;
            return true;
        }
    }
    return false;  // if malloc fail or q is NULL return false
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q != NULL) {
        list_ele_t *newh;
        newh = malloc(sizeof(list_ele_t));
        if (newh != NULL) {
            newh->value = strdup(s);
            if (q->head == NULL && q->tail == NULL) {  // insert first node
                newh->next = NULL;
                q->head = newh;
                q->tail = newh;
            } else {
                q->tail->next = newh;
                newh->next = NULL;
                q->tail = newh;
            }
            q->size++;
            return true;
        }
    }
    return false;  // if malloc fail or q is NULL return false
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q != NULL && q->head != NULL) {
        list_ele_t *removePtr = q->head;
        if (sp != NULL) {
            memcpy(sp, removePtr->value,
                   bufsize);         // copy the removed string to *sp
            sp[bufsize - 1] = '\0';  // plus a null terminator
        }

        q->size--;
        q->head = q->head->next;  // move head to next node
        free(removePtr);          // free remove node
        return true;
    }
    return false;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
        return 0;

    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q != NULL && q->size != 0) {
        list_ele_t *cur = q->head;        // current ptr point to queue head
        list_ele_t *nxt = q->head->next;  // next ptr point to queue head->next
        list_ele_t *temp;
        temp = q->tail;        // store the address of tail
        q->tail = q->head;     // let tail pointer to head
        q->head = temp;        // let head pointer to temp(tail)
        while (nxt != NULL) {  // reverse middle node from orignal head
            temp = cur;
            cur = nxt;
            nxt = nxt->next;
            cur->next = temp;
        }
        q->tail->next = NULL;
    }
}
