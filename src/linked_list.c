#include "linked_list.h"
#include "globals.h"

node *new_node(void *arg)
{
	lock();
	node *n = malloc(sizeof(node));
	Car *c = arg;
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
	if (_ll.size == 0)
	{
		printf("nothing to remove\n");
	} if (n == _ll.size)
	{
		printf("[D] Car Departing (LAST CAR)-> %s\n", get_car_id(p->car));	
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
		while(i < n-1)
		{
			//attempt to get the 2nd last node
			p = p->next;
			i++;
		}
		//p should be the 2nd last node
		node *d = p->next;
		printf("Crash point delete_node (1), next pointer is %d\n", p->next);
		//d is now the last node
		p->next = NULL;
		printf("attempting to remove node %s\n", get_car_id(d->car));
		printf("[D] Car Departing -> %s\n", get_car_id(d->car));
		free(d);
		_ll.size--;
	}
	unlock();
	
}
