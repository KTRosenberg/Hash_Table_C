/*
Karl Toby Rosenberg
*/

#include "hashchain.h"

record_t* add_front(char* key, uint64_t value, record_t** head)
{
    if(!head)return NULL;
    
    record_t* new_record = (record_t*)malloc(sizeof(record_t));
    
    if(!new_record)return NULL;

    new_record->key = key;
    new_record->value = value;
    new_record->next_link= *head;
    *head = new_record;
    
    return new_record;
}

record_t* remove_front(record_t** head)
{
    if(!head || !(*head))return NULL;

    record_t* to_remove = *head;
    *head = (*head)->next_link;

    to_remove->next_link = NULL;
    return to_remove;
}

void print_list(record_t* head)
{
    while(head)
    {   
        printf("[KEY: %s, VALUE: %" PRIu64 "]", head->key, head->value);
        head = head->next_link; 
    }
}

void del_list(record_t** head)
{
    record_t* to_free;
    while(head && (*head))
    {
        to_free = *head;
        *head = (*head)->next_link;
        free(to_free);
        to_free = NULL;
    }
}