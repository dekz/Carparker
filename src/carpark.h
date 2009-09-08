#include <unistd.h>
#include "fromuni.h"
#include "keyboard.h"

// Defines
#define FALSE 0
#define TRUE !FALSE

int is_carpark_full();
int is_carpark_empty();
void start_threads();
void join_threads();
int thread_sleep_default();