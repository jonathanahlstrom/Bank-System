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



void makeDeposit(int bankGiro){
    
    char fileName[100];
    char buffer[100];
    char transDate[20];
    char *temp;
    float answDeposit;
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

    system("cls");
    printf("=========== MAKE A DEPOSIT ===========\n\n");
    printf("Amount: ");
    scanf("%f", &answDeposit);
    getchar();

    newSaldo = dataSaldo + answDeposit;
   
    fprintf(accountHistory, "%s, 10000, %d, DEPOSIT, %10.2f, %10.2f \n", transDate, bankGiro, answDeposit, newSaldo);
    fclose(accountHistory);

    system("cls");

    printf("Deposit registered to your account.\n\n");

    printf("======== DETAILS ========\n");
    printf("Transaction date:      %s \n", transDate);
    printf("BankGiro:              %d \n", bankGiro);
    printf("Data saldo:         %10.2f\n", dataSaldo);
    printf("Deposit:            %10.2f \n", answDeposit);
    printf("New saldo:          %10.2f\n", newSaldo);
    printf("=========================\n\n");

}