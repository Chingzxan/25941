#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
extern char *tzname[];
int main()
{
      time_t vrem;
     struct tm *sp;

     vrem=time(NULL );
	
     setenv("TZ","PST8PDT,M3.2.0,M11.1.0",1);
     tzset();

     sp = localtime(&vrem);
     printf("%d/%d/%02d %d:%02d %s\n",
         sp->tm_mon + 1, sp->tm_mday,
         sp->tm_year, sp->tm_hour,
         sp->tm_min, tzname[sp->tm_isdst]);
     exit(0);
}
