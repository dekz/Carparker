#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <termios.h>

// Documentation in the implementation file
void disable_terminal_flush();
void enable_terminal_flush();
int kbhit();