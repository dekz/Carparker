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

	if (_cp.head == NULL)
	{
		_cp.head = n;
		_cp.size = 1;
	} else
	{
		node *p = _cp.head;
		int i;
		for (i=1; i < _cp.size-1; i++)
		{
			p = p->next;
		}
		printf("SIZE IS %d, RETURNING NODE NUMBER %d\n", _cp.size, i);
		//p should now be the last node;
		p->next = n;
		_cp.size++;	
	}

    unlock();
	printf("ADDING NODE END\n");
    return n;
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
        for(int i = 1; i < n - 1; ++i) {
            previous = current;
            current = current->next;
        }
        
        previous->next = current->next;
    }
	printf("attempting to free current\n");
    free(current);
	printf("freeing current\n");
    _cp.size--;
	
    unlock();
}
