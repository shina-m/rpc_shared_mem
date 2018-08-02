#include <stdio.h>
#include <stdlib.h>
#include "header.h"


int main ()
{
    int i;
    FILE *outfile;

    // open file for writing
    outfile = fopen ("person.dat", "w");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
        exit (1);
    }

    struct StudentInfo input[] = {
            {"Shina Madamori","12288524","Roselle","859-420-8765"},
            {"John Blakeman", "111223333", "560 Southbrook Dr. Lexington,  KY 40522", "8591112222"},
            {"Paul S Blair", "111223344","3197 Trinity Rd. Lexington,  KY 40533", "8591112234"},
            {"Dean Blair", "111223355", "925 Detroit Ave. Lexington,  KY 40523", "8591112235"},
            {"Michelle Boschert", "111223366", "453 South 3rd St. Lexington,  KY 40525", "8592223422"},
            {"Patricia Carey", "111223377", "320 Old Vine St. Lexington, KY 40506", "8592332534"},
            {"Kristen Carlson", "111224411","Grassy Creek Dr. Lexington, KY 40507","8592331111"},
            {"Angela Edward", "111224422", "323 Colorado Rd. Lexington, KY 40545", "8592442222"},
            {"Robert Gentry", "111224433", "345 Rose St. Lexington, KY 40506", "8592574444"},
            {"Barbara Smith", "111224444", "111 Twine Ridge Rd. Lexington KY 40513", "8592551111"},
            {"Greard Higgs", "111224455", "251 Nicholasville Rd. Lexington, KY 40513","8593551234"},
            {"Helen Higginbotham", "111224466", "345 South Hill Road, Lexington, KY 40533","8594002222"},
    };

    // write struct to file

    int numOfStudents= sizeof(input)/sizeof(struct StudentInfo);

    int er1=0;
    for(i=0;i<numOfStudents;i++) {
        fwrite(&input[i], sizeof(struct StudentInfo), 1, outfile);

        if (fwrite == 0)
            er1++;
    }
    if (er1 ==0)
        printf("\nContents to file written successfully !!\n");
    else
        printf("\n%d Errors occurred", er1);
    }
