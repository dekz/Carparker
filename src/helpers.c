#include "carpark.h"

node *new_node(void *arg)
{
	lock();
	node *n = malloc(sizeof(node));
	Car *c = arg;
	
	
	n->next = 0;
	n->car = c;
	if (_ll.size == 0)
	{
		_ll.head = n;
		_ll.tail = n;
		n->prev = 0;
	} else
	{
		node *p = _ll.tail;
		p->next = n;
		n->prev = p;
		_ll.tail = n;
	}
	_ll.size++;
	unlock();
	return n;
}

void remove_node(void *arg)
{
	lock();
	node *n = arg;
	node *_previous = n->prev;
	node *_next = n->next;
	printf("attempting to remove node %s", get_car_id(n));
	_previous->next = _next;
	_next->prev = _previous;
	_ll.size--;
	free(n);
	unlock();
}

void show_cars()
{
	printf("Total: %d \n", _ll.size);
	if (_ll.size > 0)
	{
		node *n = _ll.head;
		int j;
		int _t = 0;
    	for (j=0; j < _ll.size; j++)
    	{
		//	printf("pointer is %d", n->next);
			printf("| %s |\n", get_car_id(n->car));
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

void remove_carpark()
{
	int _rand = 0;
	_rand = RAND(0,_ll.size-1);
	remove_node(get_node(_rand));
}

node *get_node(int num)
{
	node *n = _ll.tail; //just incase
	if (!(_ll.size <= num))
	{
		printf("Error: linked list too small\n");
	} else
	{
		int i;
		for (i=0; i < num; i++)
		{
			n = n->next;
		}
	}
	return n;
}

void clean_carpark()
{
	
	//find old cars and dealloc them also?
/*
	int i = 0;
	int j = 0;

	if ((!is_carpark_empty()) && (!is_carpark_full()))
	{
		for (i=0; i < _cp.size; i++)
		{
			
			if (_cp.buffer[i]->id == 0)
			{
				printf("Found a NULL CAR\n");
				//dealloc the pointer to the structure
				for (j=i; j < _cp.size; j++)
				{
					//i is blank, move j to i and more the rest down
					printf("[C_P] Swapping %s", get_car_id(_cp.buffer[j]));
					printf(" and %s \n", get_car_id(_cp.buffer[j+1]));
					lock();
					_cp.buffer[j] = _cp.buffer[j+1];
					unlock();
				
				}
				
			}
		}
	}
	*/
}

bool is_carpark_full() {
    return (_cp.size >= CAR_PARK_SIZE);
}

bool is_carpark_empty() {
    return (_cp.size == 0);
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

/*
    successfully prints out random characters with:

        int i;
        for(i = 0; i <= 20; i++) {
            printf("%c\n",random_letter());
        }
*/
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