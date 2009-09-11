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

	if (_ll.size == 0)
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

	lock();
    node *p = _ll.head;
    
	if (n == 1)
	{
		//remove first node
		_ll.head = NULL;
		_ll.size--;
        print_car_departure(p->car, n);
		free(p);
	} else 
	{
		int i=0;
		//return the 2nd last node
		for(i=0; i < _ll.size-1; i++)
		{
			p = p->next;
		}
		node *d = p->next;
		p->next = NULL;
		_ll.size--;
        print_car_departure(d->car, n);
		free(d);
		
	}
	
    unlock();
    
}
