#include "main.h"

int main() {
    signal(SIGINT, quit);
    srand(time(0));
    
    welcome_text();
        
    start_threads();
    join_threads();
    
    exit(0);
}

void quit() {
    puts("Quitting...");
    signal(SIGINT, force_quit);
    stop_running();
}

void force_quit() {
    exit_with_error("Hard shutdown...");
}