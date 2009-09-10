#include "main.h"

Car *new_car() {
    Car *c = malloc(sizeof(Car));
    
    c->id  = RAND(CARID_NUMBER_MIN,CARID_NUMBER_MAX);
    random_string(c->str);

    return c;
}

char *get_car_id(Car *car) {
    // char *str = malloc(sizeof(*str) * 3);
    char str[11] = "          ";
    sprintf(str, "%s%8d", (*car).str, (*car).id);
    return str;
}
