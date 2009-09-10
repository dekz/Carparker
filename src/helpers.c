#include "helpers.h"

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

void remove_carpark()
{
	int _rand = 0;
	_rand = RAND(0,_ll.size);
	printf("Trying to remove node %d ll size %d\n", _rand, _ll.size);
	delete_node(_rand);

}

void show_cars()
{
	printf("Total: %d \n", _ll.size);
	if (_ll.size > 0)
	{
		node *n = _ll.head;

		while(n->next != NULL)
		{
			printf("| %s |", get_car_id(n->car));
			n = n->next;
		}
    	
    	printf("\n");
	}
}

void add_car()
{
	if (_cq.size > 0)
    {
		if (_ll.size >= CAR_PARK_SIZE)
		{
			printf("car park is full\n");
		} else 
		{
			//get the car from the queue and add it to the linked list
			Car *_c = _cq.buffer[_cq.index];
			new_node(_c);
			printf("[C] Car Parked -> %s\n", get_car_id(_c));
			remove_car();
		}
	} else
	{
		printf("No cars in queue\n");
	}


}

void remove_car()
{
	lock();
	_cq.index += 1 & MAX_QUEUE_SIZE;
	_cq.size--;
	unlock();
}


bool is_carpark_full() {
    return (_ll.size >= CAR_PARK_SIZE);
}

bool is_carpark_empty() {
    return (_ll.size == 0);
}

void exit_with_error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

bool should_keep_running() {
    return _cp.keep_running;
}

void stop_running() {
    // Doubt the mutex locking is
    // needed as nothing else modifies
    // this flag, but we'll be safe
    lock();
    _cp.keep_running = FALSE;
    unlock();
}

char random_letter() {
    return (char)((rand() % 26)+65);
}

char *random_string(char *str) {
    int i, length = 1 + sizeof *str;
    for(i = 0; i < length; ++i) {
        str[i] = random_letter();
    }
    str[i] = '\0';
    return str;
}

void welcome_text() {
    printf("Welcome to the simulation of a Car Park Management System for %s.\n\n", CAR_PARK);
    puts("Press 'C/c' (followed by return) to show car park status.");
    puts("Press 'Q/q' (followed by return) to quit program.");
    puts("\n<--- Press return to continue --->\n");
    getchar();
}