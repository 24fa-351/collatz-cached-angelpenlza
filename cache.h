#ifndef CACHE
#define CACHE

#include <stdlib.h>


//--------- cache implementation -----------------------

typedef struct var {
    unsigned long long num;
    unsigned long long steps;
    struct var* next;
} var;

typedef struct hash_table {
    var* head;
    var* curr;
    var* tail;
    int size;
} hash_table;

unsigned long long locate(unsigned long long num, hash_table* ty) {
    if(ty->size == 0)
        return -1;
    
    var* curr = ty->head;
    while(curr != NULL) 
        if(curr->num == num) 
            return curr->steps;
        else
            curr = curr->next;
        
    return -1;
    
}

void insert(unsigned long long num, unsigned long long steps, hash_table* ty, int cache_size) {

    var* new_var = (var*)malloc(sizeof(var));

    new_var->num = num;
    new_var->steps = steps;
    new_var->next = NULL;

    if(ty->size == 0) {
        ty->head = new_var;
        ty->tail = new_var;
        ty->curr = ty->head;
        ty->size++;

    } else if(ty->size <= cache_size) {
        ty->tail->next = new_var;
        ty->size++;

    } else { // FIFO
        ty->curr->num = num;
        ty->curr->steps = steps;
        ty->curr = ty->curr->next;
    }

}

void free_table(hash_table* ty) {
    var* curr = ty->head;
    while(curr != NULL) {
        var* temp = curr;
        curr = curr->next;
        free(temp);
    }
}

//------------------------------------------------------
#endif