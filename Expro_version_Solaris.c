/************************************************************************************************

  AUTHOR;      Antonio NAVARRO
  DATE;        22.11.2001

  Program that examines what a process does in kernel

NOTES: From doc

ru_maxrss 	This is the maximum resident set size measured in pages.
ru_idrss 	This is an "integral" value indicating the amount of memory
		in use by a process while it is running. This value is the sum
		of the resident set sizes of the process when a clock tick
		occurs. The value is given in pages multiplied by clock ticks.
		It does not take shared pages into account.
ru_minflt 	This is the number of minor page faults serviced. A minor
		page fault is one that does not require any physical I/O
		activity. An example of a minor page fault would be when a
		process starts up and refers to pages already in memory (e.g.,
		those in a shared library like libc.so).
ru_majflt 	This is the number of major page faults serviced. A major page
		fault is one that requires physical I/O activity. An example of
		a major page fault would be when a process starts up for the
		first time since the system was booted; the pages of the
		executable must be paged in from disk before the program
		can run.
ru_nswap 	This is the number of times the process was swapped out of
		physical memory.
ru_inblock 	This is the number of times the kernel had to perform input
		when servicing a read request.
ru_oublock 	This is the number of times the kernel had to perform output
		when servicing a write request.
ru_msgsnd 	This is the number of messages sent over sockets.
ru_msgrcv 	This is the number of messages received over sockets.
ru_nsignals 	This is the number of signals that have been delivered.
ru_nvcsw 	This is the number of voluntary context switches. A
		voluntary context switch occurs when a process gives up the
		CPU before its time slice has expired. This is usually because
		the process is awaiting the availability of a resource.
ru_nivcsw 	This is the number of involuntary context switches. An
		involuntary context switch occurs when a higher priority
		process has become runnable, or because the process has
		exceeded its time slice.

**********************************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#ifdef NEED_SNPRINTF
#include <sys/procfs.h>
#else
#include <sys/old_procfs.h>
#endif
#include <limits.h>
/*#include "ssp.h"*/

static int getprusage (pid_t pid, prusage_t *pr_usage);
static void print_rusage (pid_t pid, prusage_t *buf);


int main (int argc, char **argv)
{
  pid_t pid;
  prusage_t buf;
  int i;

  if (argc == 1) {
  
     printf ("Usage;\n\n");
     printf ("expro <pid from process to trace>\n\n");
  }
  else {
    for (i = 1; i < argc; i++) {
        pid = atoi (argv [i]);
        if (getprusage (pid, &buf) == -1)
           printf ("  ERROR >>>> \n");
        else
           print_rusage (pid, &buf);
    }
  }
  
  /*** Banner and exit ***/
  printf ("Dpt. of Databases, Antonio NAVARRO, Last review 2006.\n\n");
  return (0);
}


static int getprusage (pid_t pid, prusage_t *pr_usage)
{
  int fd;
  char name [PATH_MAX];
  
  if (pid == -1)
     snprintf (name, PATH_MAX, "/proc/%ld", (long) getpid ());
  else
     snprintf (name, PATH_MAX, "/proc/%ld", (long) pid);
  
  if ((fd = open (name, O_RDONLY)) == -1)
     return (-1);
  
  if (ioctl (fd, PIOCUSAGE, pr_usage) == -1) 
  {
     close (fd);
     return (-1);
  }
  else 
  {
     close (fd);
     return (0);
  }
}

static void print_rusage (pid_t pid, prusage_t *buf)
{
  printf ("Recursos usados por el PID %ld:\n", (long) pid);
  printf ("  LWP ID                       : %ld\n", (long) buf -> pr_lwpid);
  printf ("  Number of LWPs               : %d\n", (int) buf -> pr_count);
  printf ("  Timestamp                    : %ld.%ld\n", buf -> pr_tstamp.tv_sec,  buf -> pr_tstamp.tv_nsec);
  printf ("  Creation time                : %ld.%ld\n", buf -> pr_create.tv_sec,  buf -> pr_create.tv_nsec);
  printf ("  Termination time             : %ld.%ld\n", buf -> pr_term.tv_sec,  buf -> pr_term.tv_nsec);
  printf ("  Real (elapsed) time          : %ld.%ld\n", buf -> pr_rtime.tv_sec,  buf -> pr_rtime.tv_nsec);
  printf ("  User CPU time                : %ld.%ld\n", buf -> pr_utime.tv_sec,  buf -> pr_utime.tv_nsec);
  printf ("  System CPU time              : %ld.%ld\n", buf -> pr_stime.tv_sec,  buf -> pr_stime.tv_nsec);
  printf ("  System trap CPU time         : %ld.%ld\n", buf -> pr_ttime.tv_sec,  buf -> pr_ttime.tv_nsec);
  printf ("  Text page fault CPU time     : %ld.%ld\n", buf -> pr_tftime.tv_sec,  buf -> pr_tftime.tv_nsec);
  printf ("  Data page fault CPU time     : %ld.%ld\n", buf -> pr_dftime.tv_sec,  buf -> pr_dftime.tv_nsec);
  printf ("  Kernel page fault CPU time   : %ld.%ld\n", buf -> pr_kftime.tv_sec,  buf -> pr_kftime.tv_nsec);
  printf ("  User lock wait time          : %ld.%ld\n", buf -> pr_ltime.tv_sec,  buf -> pr_ltime.tv_nsec);
  printf ("  Other sleep time             : %ld.%ld\n", buf -> pr_slptime.tv_sec,  buf -> pr_slptime.tv_nsec);
  printf ("  CPU latency time ** grave ** : %ld.%ld\n", buf -> pr_wtime.tv_sec,  buf -> pr_wtime.tv_nsec);
  printf ("  Stopped time    (tienda a 0) : %ld.%ld\n", buf -> pr_stoptime.tv_sec,  buf -> pr_stoptime.tv_nsec);
  printf ("  Minor faults                 : %ld\n", buf -> pr_minf);
  printf ("  Major faults                 : %ld\n", buf -> pr_majf);
  printf ("  Number of swaps (tienda a 0) : %ld\n", buf -> pr_nswap);
  printf ("  Input blocks                 : %ld\n", buf -> pr_inblk);
  printf ("  Output blocks                : %ld\n", buf -> pr_oublk);
  printf ("  Messages sent                : %ld\n", buf -> pr_msnd);
  printf ("  Messages received            : %ld\n", buf -> pr_mrcv);
  printf ("  Signals received             : %ld\n", buf -> pr_sigs);
  printf ("  Voluntary context switches   : %ld\n", buf -> pr_vctx);
  printf ("  Involuntary context switches : %ld\n", buf -> pr_ictx);
  printf ("  System calls                 : %ld\n", buf -> pr_sysc);
  printf ("  Caracters leidos/escritos    : %ld\n\n", buf -> pr_ioch);
}




