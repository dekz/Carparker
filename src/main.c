#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include "quit.h"

int main() {
    signal(SIGINT, quit);
    srand(time(0));
    
    welcome_text();
        
    start_threads();
    join_threads();
    
    exit(0);
}
