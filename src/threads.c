#include "carpark.h"

void *monitor(void *arg) {
    enable_terminal_flush();
    char c;
    
    while(should_keep_running()) {
        thread_sleep(25);
        
        if(kbhit()) {
            c = getchar();
            
            if(c=='Q'||c=='q') {
                printf("Quitting...\n");
                stop_running();
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
        thread_sleep_default();
    }
    
    return NULL;
}