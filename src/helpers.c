#include "carpark.h"

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