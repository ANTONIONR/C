

/***********************************************************************************************                      
*                                                                                                                     
* FILE             : daemon_anr.c                                                                                                 
* DESCRIPTION      : Daemon for run process                                                                                                 
* AUTHOR           : /\/\/                                                                                 
* DATE             : 22.11.2001                                                                                       
* USAGE            : Daemon similar to nohup or crontab but controled by myself           
*                    execute a hardcode command                                                                                      
* CALL SYNTAXIS    : daemon_anr 10
* [NOTES]          : Checked on Solaris 8,9,10,11                                                                                                 
*                    create a new version with command to execute pass like parameter
*                                                                                                                     
***********************************************************************************************/                      
                                                                                                                      
                                                                              
                                                                              
#include <sys/types.h>  /* library (for types), here user for ID, PID processes */   
#include <unistd.h>     /* library (universal)  */                     
#include <stdio.h>      /* library (standard) */                               
#include <string.h>     /* library (strings) */                             
                                                                              
int main (int argc, char * argv [])                                           
{                                                                             
  pid_t pid;            /* id for the new process */                         
  char linea[100];      /* execution line */                              
                                                                              
                                                                              
  /*** Check parameters ***/                       
  if (argc != 2)                                                              
  {                                                                           
     printf ("Wrong execution !!!\n	");                     
     printf ("daemon_anr <execution interval in minutes> \n\n");                    
     exit (-1);                                                               
  }                                                                           
                                                                              
                                                                              
  /*** execution for daemon ***/                                            
  pid = fork ();                                                              
  if (pid != 0 ) /*** I am the father ***/                                   
  {                                                                           
     /*** Show information ***/                               
     system ("/sbin/date");                                                   
     printf (">>> Starting process... \n");                                 
     printf (">>> Started with PID %d \n",pid);                               
     printf (">>> Priority: %d\n", getpriority (0,pid));                     
                                                                              
     /*** get out ***/                                          
     exit (0);                                                                
  }                                                                           
  else /*** I am the child  ***/                                              
  {                                                                           
    sleep (2);                                                                
    setsid ();   /*** free and fit resident in memory ***/   
    for (;;)     /*** infinity loop ***/       
    {                                                                                 
        /*** execute direct or like wrapper ***/                                                                      
        strcpy (linea, "/anr/my_command.sh ");              
        system (linea);                                                       
                                                                              
        /*** waiting for ... ***/                                             
        sleep (60 * atoi (argv[1]));                                          
    }                                                                         
    exit (0);    /*** never will be executed ***/           
  }                                                                           
}                                                                             
                                                            
                                                            
                                                                              