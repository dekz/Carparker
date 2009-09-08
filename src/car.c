#include "car.h"
#include "carpark.h"

Car new_car() {
    Car c;
    
    c.id = RAND(CARID_NUMBER_MIN,CARID_NUMBER_MAX);
    c.str[0] = random_letter();
    c.str[1] = random_letter();
    
    return c;
}

char *get_car_id(Car *car) {
    char *str = malloc(sizeof(*str) * 3);
    sprintf(str, "%s%8d", (*car).str, (*car).id);
    return str;
}
