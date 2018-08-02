#ifndef UNTITLED_HEADER_H
#define UNTITLED_HEADER_H

#include <sys/shm.h>

#define KEY  ((key_t)(88524)) /*change it to last five digits of your SID*/
#define READ_KEY   ((key_t)(524)) //for the read_count variable
#define SEGSIZE  sizeof(&students)
#define RSEGSIZE sizeof(int)

#define SLEEPTIME 10
#define STUDENT_NUM 20

#define NUM_SEMAPHS 5
#define SEMA_KEY   ((key_t)(8524)) /* change this to last four digits of SID */

int id, shm_id;
struct StudentInfo *infoptr;
int *read_count;


struct StudentInfo{
    char name[50];
    char studentId[10];
    char address[100];
    char telNumber[15];
    char whoModified[10];
};

/*
struct StudentInfo{
    char name[50] = { NULL };
    char studentId[10] = { NULL };
    char telNumber[15] = { NULL };
    char address[100] = { NULL };
    char whoModified[10] = { NULL };
};
*/

struct StudentInfo students[STUDENT_NUM];

void Wait(int semaph, int n);
void Signal(int semaph, int n);
int GetSemaphs(key_t k, int n);
void getSharedMem();

#endif //UNTITLED_HEADER_H
