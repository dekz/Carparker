#include <stdio.h>
#include "keyboard.h"
#include "threads.h"
#include "thread_control.h"
#include "helpers.h"
#include "globals.h"
#include "quit.h"
#include "time.h"

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
                show_cars();
            } else {
                printf("[!]\tInvalid key. Use either Q or C\n");
            }
        }
    }
    
    disable_terminal_flush();
    return NULL;
}

void *enter_carpark(void *arg) {
    while(should_keep_running()) {
        if(is_carpark_full()) {
            printf("[C]\tNo parking bays available. Parking blocked\n");
            thread_sleep_default();
        } else {
            //grab the first car in the queue
    		if (_cq.size > 0)
    		{
    			park_car_from_queue();
    		} else 
    		{
    			printf("[C]\tNo Cars in the queue\n");
    		}
        }
        
        thread_sleep_default();
    }
    return NULL;
}

void *departure(void *arg) {
    while(should_keep_running()) {
        if(is_carpark_empty()) {
            printf("[D]\tCar park empty. Departure blocked\n");
            thread_sleep_default();
        } else 
        {
            int _rand = RAND(0,100);
            if (_rand <= DEPARTURE_PERCENT_ACTION)
            {
				remove_carpark();
            }
   
        }
        
        thread_sleep_default();
    }
    return NULL;
}

void *arrival_queue(void *arg) {
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
				printf("[A] Car %s Queued at %s\n", get_car_id(c), get_car_time(c));
                
                lock();
                _cq.size++;

                _cq.buffer[_cq.index] = c;

                unlock();
				}
                
            }
        
    
        }
        thread_sleep_default();
    }
    
    return NULL;
}