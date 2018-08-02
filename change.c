#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <pwd.h>
#include "header.h"

int main()
{
    int i,search, sema_set;
    char password[25];
    char found = 0;
    char fname[25], lname[25];

    /*Attach the shared memory segments and semaphore set*/
    getSharedMem();

    /*Get the id of the semaphore set created*/

    sema_set = semget(SEMA_KEY, 0,0);

    printf(" The value of sema_set=%d\n", sema_set);

    /*Prompt the user for password*/
    printf("\n Password: ");
    scanf("%s", password);

    /*Validate the password*/
    if((strcmp("000",password) != 0))
    {
        printf("Password Incorrect!! \n");
        exit(1);
    }

    /*Get the id of the student the user wants to modify*/
    printf("\n Enter the StudentID: ");
    scanf("%d", &search);

    /*Get the new information about the student*/
    Wait(sema_set, 0);

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

    if (found==0)    {
        printf("No Match was found for: %d\n", search);
        exit(1);
    }

    /*Prompt for your to update student information 1 after the other*/
    printf("\n UPDATE THIS STUDENT'S INFORMATION BELOW:\n\n");

    /*update information in memory as it is entered*/
    printf(" First Name: ");
    scanf("%s", (infoptr + i)->name);

    printf(" Last Name: ");
    scanf("%s", lname);

    printf(" Phone: ");
    scanf("%s", (infoptr + i)->telNumber);

    printf(" Address: ");
    scanf("%s", (infoptr + i)->address);
    
    strcat((infoptr + i)->name, " ");
    strcat((infoptr + i)->name,lname);

    strcpy((infoptr + i)->whoModified, (getpwuid(getuid()))->pw_name);


    printf("\n Update Completed and Stored in Memory... \n");

    printf("\n Going to sleep for 10 secs...... \n");

    sleep(SLEEPTIME); // for debugging and testing

    printf("\n Exiting Critical Section...\n");

    Signal(sema_set, 0);

    return 0;
}