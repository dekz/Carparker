#include "linked_list.h"
#include "globals.h"

node *new_node(void *arg)
{
	lock();
	node *n = malloc(sizeof(node));
	Car *c = arg;

	if (_ll.size == 0)
	{
		_ll.head = n;
		n->car = c;
		n->next = NULL;
		
	} else if (_ll.size == 1)
	{
		node *head = _ll.head;
		n->car = c;
		head->next = n;
		n->next = NULL;
	} 
	else {
		
	node *temp = _ll.head;
	printf("Crash zone C2\n");	
		while(temp->next != NULL)
		{
			printf("Crash zone C2.1\n");
			temp = temp->next;
		}
		
		temp->next = n;
		n->car = c;
		n->next = NULL;
	}
		
	_ll.size++;
	unlock();
	return n;
}


void delete_node(int n)
{
	lock();
	printf("Crash zone 1\n");
	
	node *p = _ll.head;
	
	if (_ll.size == 0)
	{
		printf("No nodes to delete\n");
	} else if (_ll.size < n)
	{
		printf("No such node exists\n");
	} else if (_ll.size == 1)
	{
		printf("Deleting the last node\n");
		printf("[D] Car Departing -> %s\n", get_car_id(_ll.head->car));
		free(_ll.head);
		_ll.head = NULL;
	} 
	else
	{
		int i = 0;
		printf("Crash zone B2, trying to remove %d size of list is %d\n", n, _ll.size);
		while(i<n-1)
		{
			printf("%d\n", i);
			if(p->next == NULL)
				{
					printf("freak the fuck out\n");
				}
			p = p->next;
			i++;
			
		}
	} //returns the 2nd last node
	printf("Crash zone B3. 2nd last node has pointer of %d\n", p->next);
	node *d = p->next;
	p->next = NULL;
	printf("[D] Car Departing -> %s\n", get_car_id(d->car));
	printf("Crash zone B4\n");
	
	_ll.size--;
	free(d);
	unlock();
	
}
