#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "globals.h"
#include "helpers.h"

bool new_node(Car *car)
{
    if(car == NULL) return FALSE;
    

    node *new_node = malloc(sizeof(node));
    new_node->car  = car;
    new_node->next = NULL;
	
	lock();
	
    node *current = _cp.head;
    
    if(current == NULL) {
        _cp.head = new_node;
    } else {
        while(current->next != NULL) {
            current = current->next;
        }
        
        current->next = new_node;
    }
    
    _cp.size++;
    unlock();
    
    return TRUE;
}


void delete_node(int n)
{
	if(_cp.head == NULL) {
		puts("Trying to delete node from empty list, ignoring...");
		return;
	}
	
	if(n > _cp.size) {
        return;
	}
	
	lock();
    node *previous = _cp.head;
	node *current = _cp.head;
	
    if(n == 1) {
        _cp.head = current->next;
    } else {
        for(int i = 0; i < n - 1; ++i) {
            previous = current;
            current = current->next;
        }
        
        previous->next = current->next;
    }

    print_car_departure(current->car, n);

    free(current);

    _cp.size--;
	
    unlock();
}
