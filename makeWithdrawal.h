
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


void makeWithdrawal(int bankGiro){
    system("cls");
    char fileName[100];
    char buffer[100];
    char transDate[20];
    char *temp;
    float answWithdrawal;
    float dataSaldo = 0;
    float newSaldo;


    snprintf(fileName, sizeof(fileName), "%d.csv", bankGiro);
    FILE *accountHistory = fopen(fileName, "a+");
    while(fgets(buffer, sizeof(buffer), accountHistory)){
                                
        temp = strtok(buffer,",");

        temp = strtok(NULL,",");
        temp = strtok(NULL,",");
        temp = strtok(NULL,",");
        temp = strtok(NULL,",");
        temp = strtok(NULL,",");

        if(temp !=""){
            sscanf(temp,"%f", &dataSaldo);
        }
        else{
            dataSaldo = 0;
        }
        
    };
    // DATUM, FROM, TO, MEDDELANDE, CHANGE, NEW SALDO
    time_t current_time = time(NULL);
    strftime(transDate, 20, "%Y-%m-%d", localtime(&current_time));


    printf("=========== MAKE A WITHDRAWAL ===========\n\n");
    printf("Amount: ");
    scanf("%f", &answWithdrawal);
    getchar();

    newSaldo = dataSaldo - answWithdrawal;
   
    fprintf(accountHistory, "%s, %d, 10000, WITHDRAWAL, -%.2f, %.2f \n", transDate, bankGiro, answWithdrawal, newSaldo);
    fclose(accountHistory);

    system("cls");

    printf("Withdrawal registered to your account.\n\n");

    printf("======== DETAILS ========\n");
    printf("Transaction date:      %s \n", transDate);
    printf("BankGiro:              %d \n", bankGiro);
    printf("Data saldo:         %.2f\n", dataSaldo);
    printf("Withdrawal:         %.2f \n", answWithdrawal);
    printf("New saldo:          %.2f\n", newSaldo);
    printf("=========================\n\n");

    printf("Returning...");


}
