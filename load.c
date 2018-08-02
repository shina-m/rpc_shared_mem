#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "header.h"

void main(int argc, char* argv[])
{
    int id, shm_id, x = 0;
    struct StudentInfo *infoptr = NULL;
    int *read_count = NULL;
    int sema_set;

    // Create a shared memory segment to store the students records

    id = shmget(KEY, SEGSIZE,IPC_CREAT|0666);/* get shared memory to store data*/
    if (id <0){
        perror("create: shmget failed");
        exit(1);
    }

    // Create a shared memory segment to store the shared variable read_count;

    shm_id = shmget(READ_KEY,RSEGSIZE,IPC_CREAT|0666); /* get shared memory to store read_count*/
    if (shm_id <0){
        perror("create: shmget failed");
        exit(1);
    }

    printf("\n Shared Memory Created\n");

    /*attach the shared memory segments to the process's address space */
    infoptr=(struct StudentInfo *)shmat(id,0,0);
    read_count = (int *)shmat(shm_id,0,0);

    if (infoptr <= (struct StudentInfo *) (0)) {
        perror("create: shmat failed");
        exit(2);
    }

    if (read_count <= (int *) (0)) {
        perror("create: shmat failed");
        exit(2);
    }

    /*Create a semaphore set*/

    sema_set = GetSemaphs(SEMA_KEY, NUM_SEMAPHS); /* get a set of NUM_SEMAPHS
 * semaphores*/
    if ((sema_set < 0) ){
        perror("create: semget failed");
        exit(2);
    }

    printf("\n Semaphore Set Created (sema_set=%d)\n", sema_set);

    printf("\n Entering Critical Section...\n");

    Wait(sema_set, 0);

    /*Initialize read_count to 0 */
    *read_count = 0;

    /* store data in the shared memory segment */
    FILE *infile;
    struct StudentInfo input;

    // Open person.dat for reading
    infile = fopen ("person.dat", "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    // read file contents and load into shared memory

    while(fread(&input, sizeof(struct StudentInfo), 1, infile))
    {
        strcpy((infoptr+x)->name,input.name);
        strcpy((infoptr+x)->telNumber, input.telNumber);
        strcpy((infoptr+x)->studentId, input.studentId);
        strcpy((infoptr+x)->address, input.address);
        strcpy((infoptr+x)->whoModified, input.whoModified);

        x++;
    }

    printf("\n Student Data Successfully loaded into Memory\n");

    printf("\n Going to sleep for 10 secs...... \n");

    sleep(SLEEPTIME); // for debugging and testing

    printf("\n THE END!\n\n");

    Signal(sema_set, 0);
}
