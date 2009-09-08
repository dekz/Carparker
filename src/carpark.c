#include "carpark.h"

int main() {
    printf("Welcome to %s!\n", CAR_PARK);

    _cp.keep_running = TRUE;

    start_threads();
    join_threads();
    exit(0);
}