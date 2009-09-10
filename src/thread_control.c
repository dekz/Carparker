#include "carpark.h"

/*
    Start all the process threads and init the mutex
*/
void start_threads() {
    _cp.keep_running = TRUE;
	_cq.keep_running = TRUE;
	_cp.size = 0;
	_cq.size = 0;
	_cq.index = 0;
    
	_nullcar.id = 0;
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
    t.tv_sec = ms / 1000;
    t.tv_nsec = (ms % 1000) * 1000000;
    int ret = nanosleep(&t, NULL);
    return ret;
}

/*
    Most of the time we want to sleep for the same amount of time,
    defined in a constant, so we'll create a convenience function f
    or it.
*/
int thread_sleep_default() {
    return thread_sleep(TIME_OUT_SLEEP);
}

void lock() {
    pthread_mutex_lock(&mutex);
}

void unlock() {
    pthread_mutex_unlock(&mutex);
}