#include "carpark.h"

int main() {
    signal(SIGINT, quit);
    srand(time(0));
    
    printf("Welcome to the simulation of a Car Park Management System for %s.\n\n", CAR_PARK);
    puts("Press 'C/c' (followed by return) to show car park status.");
    puts("Press 'Q/q' (followed by return) to quit program.");
    puts("\n<--- Press return to continue --->\n");
    getchar();

    puts_example_car_id();
        
    start_threads();
    join_threads();
    exit(0);
}