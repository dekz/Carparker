#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"
#include "globals.h"
#include "linked_list.h"

void remove_carpark()
{
 	int _rand = 0;
    _rand = RAND(1,_cp.size);
    delete_node(_rand);

}

void show_cars()
{
	lock();
    printf("Current: %d Total: %d \n", _cp.size, CAR_PARK_SIZE);
    if (_cp.size > 0)
    {
        node *n = _cp.head;
		printf("Car Bay 1 | %s | arrived at %s\n", get_car_id(n->car), get_car_time(n->car));
		int i = 2;
         while(n->next != NULL)
        {
            n = n->next;
            printf("Car Bay %d | %s | arrived at %s\n", i, get_car_id(n->car), get_car_time(n->car));
            i++;
        }
        n = n->next;
        printf("Car Bay %d | %s | arrived at %s\n", i, get_car_id(n->car), get_car_time(n->car));
    }
	unlock();
}

void park_car_from_queue()
{
    if (_cq.size > 0)
    {
        if (_cp.size >= CAR_PARK_SIZE)
        {
            printf("car park is full\n");
        } else 
        {
			if(new_node(_cq.buffer[_cq.index])) {
    			Car *c = _cq.buffer[_cq.index];
    			c->cartime = time(NULL);
		
                // TODO: print out entrance number
                printf("[C] Car Parked -> %s at time %s\n", get_car_id(_cq.buffer[_cq.index]), get_car_time(c));
    			remove_car_from_queue();
			}
        }
    } else
    {
        printf("No cars in queue\n");
    }
}

void remove_car_from_queue()
{
	lock();
	_cq.index = ((_cq.index+1) % MAX_QUEUE_SIZE);
    _cq.size--;
    unlock();
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
    return g_keep_running;
}

void stop_running() {
    // Doubt the mutex locking is
    // needed as nothing else modifies
    // this flag, but we'll be safe
    lock();
    g_keep_running = FALSE;
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

void print_car_departure(Car *c, int n) {
    printf("[D] Car Departing from space #%d -> %s\n", n, get_car_id(c));  
}
