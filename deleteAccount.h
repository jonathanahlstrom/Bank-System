
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <conio.h>
#define _OPEN_SYS_ITOA_EXT


loginAccount deleteAccount(){

    char fileName[100];
    char buffer[100];
    char *temp;
    float dataSaldo = 0;

    loggedInAcc.saldo = dataSaldo;
    int dataAccountNr;

    // Open old bankAccounts-file
    FILE *fp = fopen("bankAccounts.csv", "a+");
    if (!fp){
        printf("Error opening file.\n");
    }
    else{
        //printf("\nFile opened successfully.");
    }


    // Open new bankAccounts-file
    FILE *newFile = fopen("bankAccounts_copy.csv", "w");
    if (!fp){
        printf("Error opening file.\n");
    }
    else{
        //printf("\nFile opened successfully.");
    }

    // Loop through old bankAccounts, find account with correct bankGiro
    while(fgets(buffer, sizeof(buffer), fp)){                

        // Extract bankGiro from bankAccounts
        sscanf(buffer, "%d", &dataAccountNr);

        if(dataAccountNr == loggedInAcc.accountNr){
            printf("Did I get in her");
            continue;
        }
        else{
            fputs(buffer,newFile);
        }
    }
    
    fclose(fp);
    fclose(newFile);


    snprintf(fileName, sizeof(fileName), "%d.csv", loggedInAcc.bankGiro);
    remove(fileName);
    updateCopyFile();


    return loggedInAcc;


}