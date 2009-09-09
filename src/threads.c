
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
			add_car();
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
        } else {
	//randomly remove a car from the car park
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
				Car c;
				c = new_car();
				printf("[A] Car Arrived with ID: %s\n", get_car_id(&c));
				
				lock();
				_cq.size++;
				_cq.index++;
				_cq.buffer[_cq.index] = &c;
				unlock();
				
			}
		
	
		}
        thread_sleep(500);
    }
    
    return NULL;
}