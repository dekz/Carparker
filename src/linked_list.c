#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "globals.h"
#include "helpers.h"

node *new_node(void *arg)
{
	printf("ADDING NODE START\n");
	
	lock();
    node *n = malloc(sizeof(node));
    Car *c = arg;
	if (c == NULL)
	{
		printf("why is there a null?\n");
	}
	n->car = c;
	n->next = NULL;

	if (_ll.head == NULL)
	{
		_ll.head = n;
		_ll.size = 1;
	} else
	{
		node *p = _ll.head;
		int i;
		for (i=1; i < _ll.size-1; i++)
		{
			p = p->next;
		}
		printf("SIZE IS %d, RETURNING NODE NUMBER %d\n", _ll.size, i);
		//p should now be the last node;
		p->next = n;
		_ll.size++;	
	}

    unlock();
	printf("ADDING NODE END\n");
    return n;
}


void delete_node(int n)
{
	if(_ll.head == NULL) {
		puts("Trying to delete node from empty list, ignoring...");
		return;
	}
	
	if(n > _ll.size) {
        return;
	}
	
	lock();
    node *previous, *current = _ll.head;
	
    if(n == 1) {
        _ll.head = current->next;
    } else {
        for(int i = 0; i < n - 1; ++i) {
            previous = current;
            current = current->next;
        }
        
        previous->next = current->next;
    }
    
    free(current);
    _ll.size--;
	
    unlock();
}
