#include "carpark.h"

node *new_node(void *arg)
{
	lock();
	node *n = malloc(sizeof(node));
	Car *c = arg;

	if (_ll.size == 0)
	{
		_ll.head = n;
		n->car = c;
		_ll.size = 1;
		
	} else {
		
	node *temp = _ll.head;
	printf("Crash zone C2\n");	
		while(temp->next != NULL)
		{
			printf("Crash zone C2.1\n");
			temp = temp->next;
		}
		
		temp->next = n;
		n->car = c;
	}
		
	_ll.size++;
	unlock();
	return n;
}


void delete_node(int n)
{
	lock();
	printf("Crash zone 1\n");
	node *p;
	int i = 0;
	if (_ll.size == 0)
	{
		printf("No nodes to delete\n");
	} else if (_ll.size < n)
	{
		printf("No such node exists\n");
	} else if (_ll.size == 1)
	{
		printf("Deleting the last node\n");
		free(_ll.head);
		_ll.head = NULL;
	} 
	else
	{
		printf("Crash zone B2, going until %d\n", n);
		while(i<n-1)
		{
			p = p->next;
			printf("%d\n", i);
			i++;
			
		}
	} //returns the 2nd last node
	printf("Crash zone B3\n");
	node *d = p;
	p->next = NULL;
	
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
		int i;
		while(n->next != NULL)
		{
			printf("Crash zone C2.1\n");
			n = n->next;
			printf("| %s |", get_car_id(n));
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

void quit() {
    puts("Quitting...");
    signal(SIGINT, force_quit);
    stop_running();
}

void force_quit() {
    exit_with_error("Hard shutdown...");
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