#include <unistd.h>
#include "fromuni.h"
#include "keyboard.h"

// Defines
#define FALSE 0
#define TRUE !FALSE
#define bool int

bool is_carpark_full();
bool is_carpark_empty();
void start_threads();
void join_threads();
int thread_sleep_default();
void stop_running();
bool should_keep_running();
