#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if defined POSIX
  #define CLEARSCR system ( "clear" )
#elif defined MSDOS || defined WIN32
  #define CLEARSCR system ( "cls" )
#else
  #define CLEARSCR system ( "clear" )
#endif

void aspetta(double secondi){
    time_t tim = time(NULL);
    while(difftime(time(NULL),tim) < secondi);
}

void press_enter(){
    char enter = 0;
     while (enter != '\r' && enter != '\n') { enter = getchar(); }
}

void clear_screen(){
    CLEARSCR;
}
