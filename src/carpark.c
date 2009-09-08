#include "carpark.h"

int main() {
    printf("Welcome to %s!\n", CAR_PARK);
    signal(SIGINT, quit);
    
    // char str[81];
    // int i;

    srand(time(0));

    // for ( i = 0; i < 80; ++i )
    // {
    //    str[i] = RandomChar();
    // }
    
    // // Test car
    Car c = new_car();
    printf("%s\n", get_car_id(&c));
        
    start_threads();
    join_threads();
    exit(0);
}