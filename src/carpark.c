#include "carpark.h"

// Threads
pthread_mutex_t mutex;
pthread_t t_arrival_queue;
pthread_t t_enter_carpark;
pthread_t t_departure;
pthread_t t_monitor;

int main() {
    printf("Welcome to %s!\n", CAR_PARK);
    start_threads();
    join_threads();
    exit(0);
}

void *monitor(void *arg) {
    char c;
    
    while(TRUE) {
        if(kbhit()) {
            c = getch();
            
            if(c=='Q'||c=='q') {
                printf("Quitting...\n");

                pthread_cancel(t_enter_carpark);
                pthread_cancel(t_departure);
                pthread_cancel(t_arrival_queue);

                break;
            } else if(c=='C'||c=='c') {
                printf("Printing summary...\n");
            } else {
                printf("Invalid key. Use either Q or C\n");
            }
        }
        
        thread_sleep(25);
    }
    
    return NULL;
}

void *enter_carpark(void *arg) {
    
    puts("I am enter_carpark");
    // while(TRUE) {
    //     if(is_carpark_full()) {
    //         printf("No parking bays available. Arrival blocked\n");
    //     } else {
    //     }
    //     
    //     thread_sleep(500);
    // }
    return NULL;
}

void *departure(void *arg) {
    thread_sleep_default();
    
    puts("I am departure");
    
    // while(TRUE) {
    //     if(is_carpark_empty()) {
    //         printf("Car park empty.  Departure blocked");
    //     } else {
    //     }
    //     
    //     thread_sleep(500);
    // }
    return NULL;
}

void *arrival_queue(void *arg) {
    puts("I am arrival_queue");
    int i = 1;

    while(i++) {
        printf("%d\n", i);
        thread_sleep_default();
    }
    
    // puts("I am no longer arrival_queue");
    return NULL;
}


int is_carpark_full() {
    return FALSE;
}

int is_carpark_empty() {
    return FALSE;
}

void exit_with_error(char *message) {
    fprintf(stderr, "%s", message);
    exit(1);
}



/////////////////////// Thread Control /////////////////////////

void start_threads() {
    pthread_mutex_init(&mutex, NULL);
    
    pthread_create(&t_arrival_queue, NULL, arrival_queue, NULL);
    pthread_create(&t_enter_carpark, NULL, enter_carpark, NULL);
    pthread_create(&t_departure,     NULL, departure,     NULL);
    pthread_create(&t_monitor,       NULL, monitor,       NULL);
}

void join_threads() {
    pthread_join(t_arrival_queue, NULL);
    pthread_join(t_enter_carpark, NULL);
    pthread_join(t_departure,     NULL);
    pthread_join(t_monitor,       NULL);

    pthread_mutex_destroy(&mutex);
}

int thread_sleep(int ms) {
    struct timespec t;
    t.tv_sec = 0;
    t.tv_nsec = ms * 1000000;
    return nanosleep(&t, NULL);
}

int thread_sleep_default() {
    return thread_sleep(TIME_OUT_SLEEP);
}