#include <stdio.h>
#include <signal.h>

#include "helpers.h"
#include "quit.h"

void quit() {
    puts("Quitting...");
    signal(SIGINT, force_quit);
    stop_running();
}

void force_quit() {
    exit_with_error("Hard shutdown...");
}
