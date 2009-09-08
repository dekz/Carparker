#include <sys/types.h>
#include <sys/time.h>
#include <termios.h>

// Documentation in the implementation file

static struct termios previous_terminal_settings;

void disable_terminal_flush();
void enable_terminal_flush();
int kbhit();
char getch();