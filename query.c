#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include "header.h"

int main() {
    int i, search, sema_set;
    char found;

    /*Attach the shared memory segments and semaphore set*/
    getSharedMem();


    /*Get the id of the semaphore set created*/

    sema_set=semget(SEMA_KEY, 0,0);

      /*feature to include multiple attempts*/
    while (1) {

        /*Get the id of the student the user wants to query*/
        printf(" ENTER IN STUDENT ID: ");
        if (scanf("%d", &search) != 1) break;

        printf("\n Entering Critical Section...\n");

        Wait(sema_set, 1);

        /*increment read_count*/
        (*read_count)++;

        if (*read_count == 1)
            Wait(sema_set, 0);

        Signal(sema_set, 1);

        /*search the shared memory for the record of the student with the id, the user typed*/

        for (i = 0; (infoptr + i)->studentId[0] != '\0'; i++) {

            /*if found print the results to the screen*/
            if (atoi((infoptr + i)->studentId) == search) {
                printf("\n A MATCH WAS FOUND!\n\n");

                printf(" Name: %s\n StudentID: %s\n Phone Number: %s\n Address: %s\n Last Modified By: %s\n\n",
                       (infoptr + i)->name, (infoptr + i)->studentId, (infoptr + i)->telNumber,
                       (infoptr + i)->address, (infoptr + i)->whoModified);

                found = 1;
                break;
            }
        }
        /*if not print "record not found" to the screen*/
        if (found==0){
            search = 0;
            printf("\n RECORD NOT FOUND. TRY AGAIN \n");
            }

        printf("\n Going to sleep for 10 secs...... \n");

        sleep(SLEEPTIME);

        printf("\n Exiting Critical Section...\n");

        Wait(sema_set, 1);

        (*read_count)--;

        if (*read_count == 0)
            Signal(sema_set, 0);

        Signal(sema_set, 1);

        if (found == 1) break;
    }

    printf("\n THE END!\n\n");

    return 0;
}