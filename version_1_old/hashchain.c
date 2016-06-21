/*
Karl Toby Rosenberg
*/

#include "hashchain.h"

node_t* add_front(char* key, uint64_t value, node_t** head)
{
    if(!head)return NULL;
    
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    
    if(!new_node)return NULL;

    new_node->key = key;
    new_node->value = value;
    new_node->next = (*head);
    (*head) = new_node;

    print_chain(*head);

    //printf("%s\n", "Inside add_front function for the linked-list chains, item added successfully");
    
    return new_node;
}

node_t* remove_front(node_t** head)
{
    if(!head || !(*head))return NULL;

    node_t* to_remove = *head;
    *head = (*head)->next;

    to_remove->next = NULL;
    return to_remove;
}

void free_chain(node_t** head)
{
    node_t* to_free;
    while(head && (*head))
    {
        to_free = *head;
        *head = (*head)->next;
        free(to_free);
    }
}

void print_chain(node_t* head)
{
    while(head)
    {   
        printf("[KEY: %s, VALUE: %" PRIu64 "]", head->key, head->value);
        head = head->next; 
    }
}