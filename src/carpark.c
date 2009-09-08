#include "carpark.h"

int main() {
    printf("Welcome to %s!\n", CAR_PARK);
    signal(SIGINT, quit);
    start_threads();
    join_threads();
    exit(0);
}