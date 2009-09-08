#include "carpark.h"

int main() {
    printf("Welcome to %s!\n", CAR_PARK);
    signal(SIGINT, quit);
    srand(time(0));

    puts_example_car_id();
        
    start_threads();
    join_threads();
    exit(0);
}