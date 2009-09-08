#include "carpark.h"

// Threads
pthread_mutex_t mutex;
pthread_t t_arrival_queue;
pthread_t t_enter_carpark;
pthread_t t_departure;
pthread_t t_monitor;

CarPark _cp;

int main() {
    printf("Welcome to %s!\n", CAR_PARK);

    _cp.keep_running = TRUE;

    start_threads();
    join_threads();
    exit(0);
}

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


bool is_carpark_full() {
    return FALSE;
}

bool is_carpark_empty() {
    return FALSE;
}

void exit_with_error(char *message) {
    fprintf(stderr, "%s", message);
    exit(1);
}

bool should_keep_running() {
    return _cp.keep_running;
}

void stop_running() {
    // Doubt the mutex locking is
    // needed as nothing else modifies
    // this flag, but we'll be safe
    pthread_mutex_lock(&mutex);
    _cp.keep_running = FALSE;
    pthread_mutex_unlock(&mutex);
}


/////////////////////// Thread Control /////////////////////////

/*
    Start all the process threads and init the mutex
*/
void start_threads() {
    pthread_mutex_init(&mutex, NULL);
    
    pthread_create(&t_arrival_queue, NULL, arrival_queue, NULL);
    pthread_create(&t_enter_carpark, NULL, enter_carpark, NULL);
    pthread_create(&t_departure,     NULL, departure,     NULL);
    pthread_create(&t_monitor,       NULL, monitor,       NULL);
}

/*
    Wait for all the process threads to gracefully join 
    (when stop_running() is called), then destroy the mutex
*/
void join_threads() {
    pthread_join(t_arrival_queue, NULL);
    pthread_join(t_enter_carpark, NULL);
    pthread_join(t_departure,     NULL);
    pthread_join(t_monitor,       NULL);

    pthread_mutex_destroy(&mutex);
}

/*
    Nice wrapper for sleeping the current thread based just on
    milliseconds to sleep
*/
int thread_sleep(int ms) {
    struct timespec t;
    t.tv_sec = 0;
    t.tv_nsec = ms * 1000000;
    return nanosleep(&t, NULL);
}

/*
    Most of the time we want to sleep for the same amount of time,
    defined in a constant, so we'll create a convenience function f
    or it.
*/
int thread_sleep_default() {
    return thread_sleep(TIME_OUT_SLEEP);
}