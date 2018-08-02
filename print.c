#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include "header.h"

void main(int argc, char* argv[])
{
    int i, sema_set,sn;
    /*Attach the shared memory segments and semaphore set*/
    getSharedMem();

    /*Get the id of the semaphore set created*/

    sema_set=semget(SEMA_KEY, 0,0);

    printf(" The value of sema_set=%d\n", sema_set);

    
    printf("\n Entering Critical Section...\n");

    Wait(sema_set, 1);

    (*read_count)++;

    if(*read_count == 1) {
        Wait(sema_set, 0);
    }

    Signal(sema_set, 1);

    printf("\n");

    //print list of all student information
    printf(" %-2s %-14s\t %-10s\t %-12s\t %-40s\t %-12s\t\n\n\n"," ","Name","StudentID", "Phone Number", "Address","Last Modified By");


    for (i = 0; (infoptr + i)->studentId[0] != '\0' ; i++) {

        printf(" %-2d %-14s\t %-10s\t %-12s\t %-40s\t %-12s\t\n\n", i+1,
               (infoptr + i)->name, (infoptr + i)->studentId, (infoptr + i)->telNumber,
               (infoptr + i)->address, (infoptr + i)->whoModified);

    }

    printf(" Total count: %d\n", i);

    printf("\n Going to sleep for 10 secs...... \n");

    sleep(SLEEPTIME);

    printf("\n Exiting Critical Section...\n");

    Wait(sema_set, 1);

    /*deccrement read_count*/
    (*read_count)--;

    if (*read_count == 0)
        Signal(sema_set,0);

    Signal(sema_set, 1);

    printf("\n THE END!\n\n");
}