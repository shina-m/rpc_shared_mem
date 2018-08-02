#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include "header.h"


void main() {

    int j, sema_set;
    
    /*Attach the shared memory segments and semaphore set*/
    getSharedMem();

    /*Get the id of the semaphore set created*/

    sema_set=semget(SEMA_KEY, 0,0);

    printf(" The value of sema_set=%d\n", sema_set);

    printf("\n Entering Critical Section...\n");

    Wait(sema_set,0);

    FILE *outfile;

    // open file for writing
    outfile = fopen ("person.dat", "w");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }
    
    /*Update file based on what is in the shared memory*/

    int er1 = 0;
    for(j=0;(infoptr + j)->studentId[0] != '\0';j++) {
        fwrite((infoptr + j), sizeof(struct StudentInfo), 1, outfile);

        if (fwrite == 0)
            er1++;
    }
    if (er1 ==0)
        printf("\n Contents to file written successfully !!\n");
    else
        printf(" %d Errors occurred", er1);

    
    /* destroy the shared memory segment*/
    shmctl(id, IPC_RMID, (struct shmid_ds *) 0);
    shmctl(shm_id, IPC_RMID, (struct shmid_ds *) 0);

    /*Remove the semaphore set */
    semctl(sema_set, 0, IPC_RMID);

    printf("\n Shared Memory Destroyed !!\n");

    printf("\n Going to sleep for 10 secs...... \n");
    
    sleep(SLEEPTIME);

    Signal(sema_set, 0);

    printf("\n THE END!\n\n");

    exit(0);
}

