#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#define _OPEN_SYS_ITOA_EXT


//#include "updateCopyFile.h"
//#include "loginAccount.h"

//loginAccount loggedInAcc;

loginAccount updateSaldo(loginAccount loggedInAcc){
    char fileName[100];
    char buffer[100];
    char *temp;
    float dataSaldo = 0;

    snprintf(fileName, sizeof(fileName), "%d.csv", loggedInAcc.bankGiro);
    FILE *accountHistory = fopen(fileName, "a+");
    while(fgets(buffer, sizeof(buffer), accountHistory)){
                                
        temp = strtok(buffer,",");

        temp = strtok(NULL,",");
        temp = strtok(NULL,",");
        temp = strtok(NULL,",");
        temp = strtok(NULL,",");
        temp = strtok(NULL,",");

        sscanf(temp,"%f", &dataSaldo);
        
    };

    fclose(accountHistory);



    loggedInAcc.saldo = dataSaldo;
    int dataBankGiro;
    int dataAccountNr;
    char creationDate[15];
    char creationTime[15];
    char firstName[15];
    char lastName[15];
    
    // Create a temporary account struct
    loginAccount newAccountFile;

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
        sscanf(buffer, "%d,%d", &dataAccountNr, &dataBankGiro);

        if(dataBankGiro == loggedInAcc.bankGiro){
            
            // If a match is found, extract the information from the row
            sscanf(buffer, "%d,%d,%d,%d,%[^,],%[^,],%d,%f,%[^,],%[^\n]", &newAccountFile.accountNr,&newAccountFile.bankGiro,
                                                            &newAccountFile.personalNr,
                                                            &newAccountFile.lastDigits,
                                                            &firstName,
                                                            &lastName,
                                                            &newAccountFile.pin,
                                                            &newAccountFile.saldo,
                                                            &creationDate,
                                                            &creationTime);
            
          

            /*printf("============== TESTING =============================\n");
            printf("\nAccount Number: %i\n", newAccountFile.accountNr);
            printf("Bank giro: %i\n", newAccountFile.bankGiro);                  
            printf("Personal Number: %i\n", newAccountFile.personalNr);
            printf("Last digits: %i\n", newAccountFile.lastDigits);  
            printf("First name: %s\n", firstName);
            printf("Last name: %s\n", lastName);  
            printf("Pin: %d\n", loggedInAcc.pin);  
            printf("Current saldo: %f\n", newAccountFile.saldo);
            printf("Creation date: %s \n", creationDate);
            printf("Creation time: %s \n", creationTime);
            printf("============== TESTING =============================\n");*/

            // Set the new saldo to the temporary struct
            newAccountFile.saldo = dataSaldo;
            

            // Print the information to the new file
            fprintf(newFile, "%i,%i,%i,%i,%s,%s,%d,%f,%s,%s\n", newAccountFile.accountNr, 
                                                                newAccountFile.bankGiro, 
                                                                newAccountFile.personalNr, 
                                                                newAccountFile.lastDigits, 
                                                                firstName, 
                                                                lastName, 
                                                                newAccountFile.pin, 
                                                                newAccountFile.saldo, 
                                                                creationDate, 
                                                                creationTime);

        }
        else{
            fputs(buffer,newFile);
        }
    }
    
    fclose(fp);
    fclose(newFile);



    updateCopyFile();


    return loggedInAcc;
}