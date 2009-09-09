#include "carpark.h"

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
            printf("Car park empty.  Departure blocked");
        } else {
	//randomly remove a car from the car park
        }
        
        thread_sleep(500);
    }
    return NULL;
}

void *arrival_queue(void *arg) {
    puts("I am arrival_queue");
    
    int i = 1;

    while(should_keep_running() && i++) {
        printf("%d\n", i);
		//work out probability of arrival
		//create a car and add it to the structure
        thread_sleep_default();
    }
    
    return NULL;
}