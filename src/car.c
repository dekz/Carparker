#include "car.h"
#include "carpark.h"

Car *new_car() {
    Car *c = malloc(sizeof(Car));

    
    c->id  = RAND(CARID_NUMBER_MIN,CARID_NUMBER_MAX);
    random_string(c->str);
	printf("new car pointer %d\n", c);
    return c;
}

char *get_car_id(Car *car) {
    char *str = malloc(sizeof(*str) * 3);
    sprintf(str, "%s%8d", (*car).str, (*car).id);
    return str;
}

/*void puts_example_car_id() {
    puts("Example car ID generation:");
    
    int i;
    Car c;
    
    for ( i = 0; i < 10; ++i )
    {
        c = new_car();
        printf("%s\n", get_car_id(&c));
    }
}*/