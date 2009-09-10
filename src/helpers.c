#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"
#include "globals.h"
#include "linked_list.h"

void remove_carpark()
{
 	int _rand = 0;
    _rand = RAND(1,_ll.size);
    delete_node(_rand);

}

void show_cars()
{
    printf("Total: %d \n", _ll.size);
    if (_ll.size > 0)
    {
        node *n = _ll.head;
		printf("| %s |", get_car_id(n->car));
        while(n->next != NULL)
        {
			n = n->next;
            printf("| %s |", get_car_id(n->car));
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
			if (_cq.buffer[_cq.index] != NULL)
			{
			time_t now;
			new_node(_cq.buffer[_cq.index]);
			Car *c = _cq.buffer[_cq.index];
			c->cartime = time(NULL);
            printf("[C] Car Parked -> %s at time %s", get_car_id(_cq.buffer[_cq.index]), ctime(&c->cartime));
			remove_car();
			}
			else {
				printf("WHY IS THERE A NULL, removing broken car\n");
				remove_car();
			}

        }
    } else
    {
        printf("No cars in queue\n");
    }


}

void remove_car()
{
	lock();
	_cq.index = ((_cq.index+1) % MAX_QUEUE_SIZE);
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