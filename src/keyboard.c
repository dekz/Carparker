#include "keyboard.h"

static struct termios previous_terminal_settings;

// Thanks to http://www.linuxquestions.org/questions/showthread.php?p=1060488#post1060488
void disable_terminal_flush() {
    tcsetattr(0, TCSANOW, &previous_terminal_settings);
}

/*
    In order to get pressing 'Q' or 'C' to perform actions 
    (without pressing ENTER), we need to change the terminal settings
    to flush characters straight away and not echo them so we
    can capture characters as they are pressed
*/
void enable_terminal_flush() {
    struct termios settings;

    // Previous settings are important (to restore)
    tcgetattr(0, &previous_terminal_settings);
    settings = previous_terminal_settings;
    
    // Change mode
    settings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &settings);
    
    // important!
    atexit(disable_terminal_flush);
}

/*
    Convenience method which lets us only call getc() when there is
    actually input, bypassing the blocking and letting us do something
    else (such as sleep)
    
    returns:
        1 if there is keyboard input waiting
        0 if there is no keyboard input or error
*/
int kbhit() {
    fd_set input;

    FD_ZERO (&input);
    FD_SET (0, &input);

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    if(select(1, &input, NULL, NULL, &timeout) == -1) return 0;
    
    if(FD_ISSET(0, &input)) return 1;
    else return 0;
}