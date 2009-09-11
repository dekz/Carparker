#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "globals.h"
#include "helpers.h"

node *new_node(void *arg)
{
 	lock();
    node *n = malloc(sizeof(node));
    Car *c = arg;
	if (c == NULL)
		{
			printf("trying to add a null car what \n");
		}
    n->car = c;
    n->next = NULL;
    
    if (_ll.size == 0)
    {
        _ll.head = n;
        _ll.size = 1;
    } else
    {
        node *temp = _ll.head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        
        temp->next = n;
        _ll.size++; 
    }
    unlock();
    return n;
}


void delete_node(int n)
{

	lock();
    node *p = _ll.head;
<<<<<<< HEAD:src/linked_list.c
    if (_ll.size == 0)
    {
        printf("Error: No Cars to Remove\n");
    } else if (n == _ll.size)
    {
        print_car_departure(p->car, n);
        int i = 1;
        for (i=1; i < _ll.size-1; i++)
        {
            p = p->next;
        }
        node *d = p->next;
        p->next = NULL;
        _ll.size--;
        free(d);
    } else if (n == 0)
    {
        //remove first
        node *d = p;
        _ll.head = p->next;
        _ll.size--;
        free(d);
    }
    else
    {
        int i=1;
        for (i=1; i < _ll.size-1; i++)
        {
            p = p->next;
        }
        
        //p should be the 2nd last node
        node *d = p->next;
        //d is now the last node
        p->next = NULL;
        print_car_departure(d->car, n);
        free(d);
        _ll.size--;
    }
=======
    
	if (n == 1)
	{
		//remove first node
		_ll.head = NULL;
		_ll.size--;
		printf("[D] Car Departing -> %s\n", get_car_id(p->car));
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
		printf("[D] Car Departing -> %s\n", get_car_id(d->car));
		free(d);
		
	}
	

>>>>>>> rewrote delete_node:src/linked_list.c
    unlock();
    
}
