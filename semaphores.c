
/***********************************************************************************************
*
* FILE             : semaphores.c
* DESCRIPTION      : Explore, test and stress limits of semaphores
* AUTHOR           : Antonio NAVARRO
* DATE             : 22.11.10
* USAGE            : Explore, test and stress limits of semaphores
* CALL SYNTAXIS    : semaphores
* [NOTES]          : Checked on Solaris 8,9,10,11
*
***********************************************************************************************/


#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

int main (int argc, char * argv [])
{
        int sem1 ;
        key_t ipc_key;

        /*** Comprobamos ejecucion correcta del programa ***/
        if (argc != 4)
        {
            printf ("Ejecucion erronea del aplicativo !!!\n");
            printf ("semaforo <number of semaphores to raise> <time before free (minutes)> <free semaphores Y|N> \n\n");
            printf ("Semaforo,  Version 1, Dpto. BBDDs, Antonio NAVARRO, @2010.\n\n");
            exit (-1);
        }

        ipc_key = ftok(".", 'S');
        if (( sem1 = semget (ipc_key,  atoi (argv[1]), IPC_CREAT | 0666))==-1)
        {
                perror("semget: IPC_CREAT | 0666");
        }
        printf("identificator of semaphores %d\n", sem1);

        printf("Sleeping until free ...\n");
        sleep (60 * atoi (argv[2]));

        if (argv[3] == "Y" || argv[3] == "y" )
        {
           if (semctl(sem1, 0, IPC_RMID) == -1) {
               perror("semctl");
               exit(1);
           }
           printf("Semaphores realeased \n");
        }

        printf ("Semaforo,  Version 1, Dpto. BBDDs, Antonio NAVARRO, @2010.\n\n");
}






