/*
 * Copyright (c) 2024 Vedant Mathur
 *
 * Linked List Structure Operations Implementation.
 */

#include <linked_list.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>

static int
insert_slist_common(slist_node_t **head, uint64_t key, bool tail)
{
    int error = 0;
    slist_node_t *temp = NULL;

    if (head == NULL) {
        error = EINVAL;
        goto done;
    }

    slist_node_t *new_node = (slist_node_t *)malloc(sizeof(slist_node_t));
    if (new_node == NULL) {
        *head = NULL;
        error = ENOMEM;
        goto done;
    }

    new_node->key_node.key = key;
    new_node->next = NULL;

    /* Empty List. */
    if (*head == NULL) {
        *head = new_node;
        goto done;
    }

    if (!tail) {
        /* Insert at Head. */
        new_node->next = *head;
        *head = new_node;
    } else {
        /* Insert at Tail. */
        temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }

done:
    return error;
}

int
insert_slist_head(slist_node_t **head, uint64_t key)
{
    return insert_slist_common(head, key, false);
}

int
insert_slist_tail(slist_node_t **head, uint64_t key)
{
    return insert_slist_common(head, key, true);
}

int
slist_remove(slist_node_t **head, uint64_t key)
{
    int error = 0;
    slist_node_t *temp = NULL;
    slist_node_t *prev = NULL;

    if (head == NULL) {
        error = EINVAL;
        goto done;
    }

    /* Empty list. */
    if (*head == NULL) {
        error = ENOENT;
        goto done;
    }

    /* Single Element. */
    if ((*head)->next == NULL) {
        if ((*head)->key_node.key == key) {
            free(*head);
            *head = NULL;
        } else {
            error = ENOENT;
        }
        goto done;
    }

    prev = *head;
    temp = (*head)->next;
    while (temp) {
        if (temp->key_node.key == key) {
            prev->next = temp->next;
            free(temp);
            goto done;
        }
        prev = temp;
        temp = temp->next;
    }

    /* Failed to find the element. */
    if (temp == NULL) {
        error = ENOENT;
    }

done:
    return error;
}


int
slist_foreach(slist_node_t *head, sll_traversalcb cb)
{
    int error = 0;
    slist_node_t *temp = NULL;

    if (head == NULL) {
        error = ENOENT;
        goto done;
    }

    temp = head;
    while (temp) {
        cb(temp);
        temp = temp->next;
    }

    /* Mark end of list. */
    error = ENOENT;

done:
    return error;
}

static int
insert_dlist_common(dlist_node_t **head, uint64_t key, bool tail)
{
   int error = 0;
   dlist_node_t *temp = NULL;

   if (head == NULL) {
       error = EINVAL;
       goto done;
   }

   dlist_node_t *new_node = (dlist_node_t*)malloc(sizeof(dlist_node_t));
   if (new_node == NULL) {
       error = ENOMEM;
       goto done;
   }

   new_node->key_node.key = key;
   new_node->prev = NULL;
   new_node->next = NULL;

   /* Empty List. */
   if (*head == NULL) {
       *head = new_node;
       goto done;
   }


   if (!tail) {
       /* Insert at Head. */
       new_node->next = *head;
       (*head)->prev = new_node;
       *head = new_node;
   } else {
       /* Insert at Tail. */
       temp = *head;
       while (temp->next != NULL) {
           temp = temp->next;
       }

       temp->next = new_node;
       new_node->prev = temp;
   }


done:
   return error;
}

int
insert_dlist_head(dlist_node_t **head, uint64_t key)
{
    return insert_dlist_common(head, key, false);
}

int
insert_dlist_tail(dlist_node_t **head, uint64_t key)
{
    return insert_dlist_common(head, key, true);
}


int
dlist_remove(dlist_node_t **head, uint64_t key)
{
    int error = 0;
    dlist_node_t *temp = NULL;

    if (head == NULL) {
        error = EINVAL;
        goto done;
    }

    /* Empty list. */
    if (*head == NULL) {
        error = ENOENT;
        goto done;
    }

    /* Single Element. */
    if ((*head)->next == NULL) {
        if ((*head)->key_node.key == key) {
            free(*head);
            *head = NULL;
        } else {
            error = ENOENT;
        }
        goto done;
    }

    temp = (*head)->next;
    while (temp) {
        if (temp->key_node.key == key) {
            temp->prev->next = temp->next;
            if (temp->next) {
                temp->next->prev = temp->prev;
            }
            free(temp);
            goto done;
        }
        temp = temp->next;
    }

    /* Failed to find the element. */
    if (temp == NULL) {
        error = ENOENT;
    }

done:
    return error;
}


int
dlist_foreach(dlist_node_t *head, dll_traversalcb cb)
{
    int error = 0;
    dlist_node_t *temp = NULL;

    if (head == NULL) {
        error = ENOENT;
        goto done;
    }

    temp = head;
    while (temp) {
        cb(temp);
        temp = temp->next;
    }

    /* Mark end of list. */
    error = ENOENT;

done:
    return error;}


