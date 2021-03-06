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

    if (q == NULL)  // 如果q=NULL，代表malloc失敗，故回傳fales
    {
        return NULL;
    } else {
        q->tail = NULL;
    }

    q->head = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL) {
        return;
    }

    list_ele_t *t, *c;
    c = q->head;
    while (c != NULL) {
        t = c;
        c = c->next;
        free(t);
    }
    if (q != NULL) {
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
    /* What should you do if the q is NULL? */
    if (q == NULL) {
        return false;
    }

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));

    if (newh == NULL)  // 如果newh=NULL，代表malloc失敗，故回傳fales
    {
        return false;
    }

    newh->value = strdup(s);  // new 的 value 為你輸入的值
    newh->next = q->head;     // q 的 next = 原本的 head
    q->head = newh;           // newh = 新的 head

    if (q->size == 0)  // 如果 q 裡面沒有 node
    {
        q->tail =
            newh;  // q 的 head 就等於 q 的 tail ( 此時的 newh = q 的 head )
    }

    q->size += 1;  // 計算 q 裡面目前有幾個 node
    return true;

    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
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
    if (q == NULL) {
        return false;
    }
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));

    if (newh == NULL)  // 如果newh=NULL，代表malloc失敗，故回傳fales
    {
        return false;
    }
    newh->value = strdup(s);  // new 的 value 為你輸入的值
    newh->next = NULL;  // 因是從 tail 開始加，故新增加的 newh 的 next 要為 NULL

    if (q->size == 0)  // 如果 q 裡面沒有 node
    {
        q->head = newh;  // q 的 head 就為 newh
    } else {
        q->tail->next = newh;  // q 的 tail 的 next 指向 newh
    }
    q->tail = newh;  // newh 為新的 tail
    q->size += 1;
    return true;

    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
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

    if (q == NULL || q->size == 0) {
        return false;
    }
    list_ele_t *dummy;
    dummy = q->head;
    if (sp == NULL) {
        return false;
    }
    strncpy(sp, q->head->value, bufsize - 1);
    sp[bufsize - 1] = '\0';
    q->head = q->head->next;
    free(dummy);
    q->size -= 1;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL) {
        return 0;
    }
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

    if (q == NULL || q->size <= 1) {
        return;
    }

    /* list_ele_t *pre = NULL;
    list_ele_t *cur = q->head;
    list_ele_t *temp = q->head->next;

    q->tail = q->head;

    while (temp != 0) {
        pre = cur->next;
        pre = cur;
        cur = temp;
        temp = temp->next;
    }
    cur->next = pre;
    q->head = cur; */

    if (!q || q->size == 0)
        return;

    list_ele_t *pre = NULL, *temp, *cur = q->head;

    q->tail = q->head;

    while (cur != NULL) {
        temp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = temp;
    }

    q->head = pre;
}
