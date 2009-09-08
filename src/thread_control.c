#include "carpark.h"

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