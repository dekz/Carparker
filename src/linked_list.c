#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "globals.h"
#include "helpers.h"

node *new_node(void *arg)
{
   	printf("NEWNDOE START\n");
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
	printf("NEWNODE END POINTER OF CAR %d \n", c);
    unlock();
	printf("NEWNODE END\n");
    return n;
}


void delete_node(int n)
{
    printf("DELNODE START\n");
	lock();
    node *p = _ll.head;
    if (_ll.size == 0)
    {
        printf("Error: No Cars to Remove\n");
    } else if (n == _ll.size)
    {
        printf("[D] Car Departing -> %s\n", get_car_id(p->car));  
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
        printf("[D] Car Departing -> %s\n", get_car_id(d->car));
        free(d);
        _ll.size--;
    }
    unlock();
	printf("DELNODE END\n");
    
}
