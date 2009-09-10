#include <stdio.h>
#include "keyboard.h"
#include "threads.h"
#include "thread_control.h"
#include "helpers.h"
#include "globals.h"
#include "quit.h"

void *monitor(void *arg) {
    enable_terminal_flush();
    char c;
    
    while(should_keep_running()) {
        thread_sleep(25);
        
        if(kbhit()) {
            c = getchar();
            
            if(c=='Q'||c=='q') {
                quit();
            } else if(c=='C'||c=='c') {
                printf("Printing summary...\n");
                show_cars();
            } else {
                printf("Invalid key. Use either Q or C\n");
            }
        }
    }
    
    disable_terminal_flush();
    return NULL;
}

void *enter_carpark(void *arg) {

    puts("I am enter_carpark");
    while(should_keep_running()) {
        if(is_carpark_full()) {
            printf("No parking bays available. Arrival blocked\n");
        } else {
        //grab the first car in the queue
		if (_cq.size > 0)
		{
			printf("CP THREAD START\n");
			add_car();
			printf("CP THREAD END\n");
		} else 
		{
			printf("No Cars in the queue\n");
		}
        //add it to the car park where a space is available
        //print out a message, depending on entrance
        }
        
        thread_sleep(500);
    }
    return NULL;
}

void *departure(void *arg) {

    puts("I am departure");
    
    while(should_keep_running()) {
        if(is_carpark_empty()) {
            printf("Car park empty.  Departure blocked\n");
        } else 
        {
            int _rand = RAND(0,100);
            if (_rand <= DEPARTURE_PERCENT_ACTION)
            {
				remove_carpark();
            }
    
    //randomly remove a car from the car park
    //DEALLOC
        }
        
        thread_sleep(500);
    }
    return NULL;
}

void *arrival_queue(void *arg) {
    
    puts("I am arrival_queue");

    while(should_keep_running()) {
        if (_cq.size  < MAX_QUEUE_SIZE)
        {

            //work out the probability of arrival
            int _rand = RAND(0,100);
            if (_rand <= ARRIVAL_PERCENT_ACTION)
            {
				Car *c;
                c = new_car();
                if (c != NULL)
				{
				printf("[A] Car Arrived with ID: %s Queue index %d\n", get_car_id(c), _cq.index);
                
                lock();
                _cq.size++;
				printf("ARRIVAL QUEUE INDEX(1) %d\n", _cq.index);
                _cq.buffer[_cq.index] = c;
				printf("ARRIVAL QUEUE INDEX(2) %d\n", _cq.index);
                unlock();
				}
                
            }
        
    
        }
        thread_sleep(500);
    }
    
    return NULL;
}