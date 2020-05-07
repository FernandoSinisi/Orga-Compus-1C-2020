#include <stdio.h> 

#ifdef USE_REC_ATOI
#include "rec_atoi/my_atoi.h"
#else 
#include "loop_atoi/my_atoi.h"
#endif 

#ifndef USE_MIPS32
int my_atoi(char *);

int
my_atoi(char *s)
{
  char *start_at;
  int n;

  if (*s == '-' || *s == '+') {
      start_at = s + 1;
      #ifndef USE_REC_ATOI
      n = atoi_loop(start_at);
      #else
      n = ratoi(0, start_at);
      #endif

      return (*s == '-' ? -1 : 1) * n;
  }
  else {
      #ifndef USE_REC_ATOI
      return atoi_loop(s);
      #else
      return ratoi(0, s);
      #endif
  }
}
#else 
extern int my_atoi(char *);
#endif /* USE_MIPS32 */ 

int 
main(void) 
{
    printf("my_atoi(''):  %d\n", my_atoi(""));
    printf("my_atoi('1'):  %d\n", my_atoi("1"));
    printf("my_atoi('+1'):  %d\n", my_atoi("+1"));
    printf("my_atoi('-9'): %d\n", my_atoi("-9"));
    printf("my_atoi('1521'): %d\n", my_atoi("1521"));
    printf("my_atoi('-3501'): %d\n", my_atoi("-3501"));

    return 0;
}

