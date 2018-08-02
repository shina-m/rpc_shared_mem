#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "header.h"

/* Lock the semaphore n of the semaphore set semaph */

void Wait(int semaph, int n)
{
    struct sembuf sop;
    sop.sem_num = n;
    sop.sem_op =  -1;
    sop.sem_flg = 0;
    semop(semaph,&sop,1);
}

/* Unlock the semaphore n of the semaphore set semaph */
void Signal(int semaph, int n)
{
    struct sembuf sop;
    sop.sem_num = n;
    sop.sem_op =  1;
    sop.sem_flg = 0;
    semop(semaph,&sop,1);
}

/* make an array of n semaphores with key k */
int GetSemaphs(key_t k, int n)
{
    int semid, i;

    /* get a set of n semaphores with the given key k */

    if ((semid=semget(k,n,IPC_CREAT|0666))!= -1){
        for (i=0;i<n;i++)
            Signal(semid,i); /* unlock all the semaphores */
    }
    return semid;
}

void getSharedMem() {

/* get the id of the  shared memory segment with key "KEY" */
/* note that this is the segment where the data is stored */

    id = shmget(KEY, SEGSIZE, 0);
    if (id < 0) {
        perror("change: shmget failed 1");
        exit(1);
    }

    shm_id = shmget(READ_KEY, RSEGSIZE, 0);
    if (shm_id < 0) {
        perror("change: shmget failed 2");
        exit(1);
    }

/* attach the already created shared memory segments to infoptr and read_count so the
   shared memory segment can be accessed through 'inforptr' and 'read_count' respectively
   */

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
}