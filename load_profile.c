
/***********************************************************************************************
*
* FILE             : load_profile.c
* DESCRIPTION      : Profile for last 1,5 and 15 minutes
* AUTHOR           : Antonio NAVARRO
* DATE             : 22.11.2001
* USAGE            : Retrive the last actived 
* CALL SYNTAXIS    : Load profile
* [NOTES]          : Checked on Solaris 8,9,10,11
*
***********************************************************************************************/

#include <stdio.h>
#include <sys/loadavg.h>

int main (void)
{
   double load_av [3];
   if (getloadavg (load_av, 3) == -1)
      printf (" ERROR >>> Fail when performing system call");

   printf ("Load over 1 minute ago: %.2f\n", load_av [LOADAVG_1MIN]);
   printf ("Load over 5 minutes ago: %.2f\n", load_av [LOADAVG_5MIN]);
   printf ("Load over 15 minutes ago: %.2f\n", load_av [LOADAVG_15MIN]);
   
   return (0);
}



