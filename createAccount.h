
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





void createAccount(){

    int personalNr;
    int lastDigits;
    char firstName[15];
    char lastName[15];
    int *check = 0;
    //int *checkAcc = 0;
    int bankGiro;
    int accountNr;
    float saldo = 0;
    char pin[5];
    char creationDate[20];
    char creationTime[20];

    char pinTry1[5];
    char pinTry2[5];
    char buffer[1000];
    char *temp;
    char answer;


    FILE* fp =fopen("bankAccounts.csv","a+");

    if (!fp){
        printf("Error opening file.\n");
    }
    else{
        //printf("\nFile opened successfully.");
    }
    printf("============= CREATING ACCOUNT =============\n");



    do{
    
            do{
                printf("Input your personal number in the format (YYYYMMDD): ");
                scanf("%d", &personalNr);
                getchar();

                printf("Input your last four digits:                         ");
                scanf("%d", &lastDigits);
                getchar();

                int flagAcc = 0;


                if(personalNr > 10000000 && 21000000 > personalNr && lastDigits > 1000 && 9999 > lastDigits) 
                {
                    
                    int dataPersonalNr;
                    int dataLastDigits;
                    int checkPersonalNr;
                    flagAcc = 0;
                    //printf("Flag: %d \n", flagAcc);
                    while(fgets(buffer, sizeof(buffer), fp)){

                        // Check the 6-digit personal number (birthday)
                        temp = strtok(buffer,",");
                        temp = strtok(NULL,",");
                        temp = strtok(NULL,",");
                        sscanf(temp,"%d", &dataPersonalNr);
                        
                        // Check the last 4-digits
                        temp = strtok(NULL,",");
                        sscanf(temp,"%d", &dataLastDigits);
                        
                        // If the strings match, the account exists and flagAcc goes from 0 to 1.
                        if(dataPersonalNr == personalNr && dataLastDigits == lastDigits){
                            flagAcc = 1;
                        }
                                
                    }
                    
                    rewind(fp);
                }
                else
                {
                    printf("\nIncorrect number of characters.\n");
                    printf("Please input your 10-digit personal number.\n\n");

                    continue;
                }

                // Decide if the while-loop should break or not
                if(flagAcc==1){
                            // If flagged  (account exists), continue for another iteration
                            printf("Account already exists\n");
                            continue;
                }   
                else if(flagAcc==0){
                            // If not flagged (account does not exist), break while-loop
                            break;
                }       

            } while(!check);

        
        printf("Input your first name:                               ");
        scanf("%s", &firstName);
        getchar();

        printf("Input your last name:                                ");
        scanf("%s", &lastName);
        getchar();


        // Set the PIN-code
        do{    

            printf("Input your new PIN-code:                             ");
            scanf("%s", &pinTry1);
            getchar();


            printf("Repeat your new PIN-code:                            ");
            scanf("%s", &pinTry2);
            getchar();


            int comp = strcmp(pinTry1, pinTry2);

            if(comp == 0){
                    strcpy(pin, pinTry1);
                    break;
            }
            else if(pinTry1 != pinTry2){
                printf("\nPIN-codes not matching. Try again.\n");

            }

        } while(true);
        

        // Add account number
        srand(time(NULL)*time(NULL)*time(NULL)*time(NULL));


        int dataAccountNr;
        int flag =0;
        do{
            fgets(buffer, sizeof(buffer), fp);
            accountNr = rand() % 50000 + 10000;

            temp = strtok(buffer,",");


            if(temp != NULL){
                sscanf(temp,"%d", &dataAccountNr);

                //printf("accountNr: %d   dataAccountNr:  %d", accountNr, dataAccountNr);
                if(accountNr == dataAccountNr){
                    continue;
                }
                else if(accountNr != dataAccountNr){
                    break;
                }
            }
            else{
                rewind(fp);
                break;
            }
        } while(true);
        
    
        // Add bankgiro

        int dataBankGiro;
        do{
            fgets(buffer, sizeof(buffer), fp);
            bankGiro = rand() % 50000 + 10000;

            temp = strtok(buffer,",");

            if(temp != NULL){
                sscanf(temp,"%d", &dataBankGiro);

                //printf("accountNr: %d   dataAccountNr:  %d", accountNr, dataBankGiro);
                if(bankGiro == dataBankGiro){
                    continue;
                }
                else if(bankGiro != dataBankGiro){
                    rewind(fp);
                    break;
                }
            }
            else{
                break;
            }
        } while(true);

        // Add creationDate and creationTime to account info
        time_t current_time = time(NULL);
        strftime(creationDate, 20, "%Y-%m-%d", localtime(&current_time));
        strftime(creationTime, 20, "%H:%M:%S", localtime(&current_time));


        //printf("Date: %s    Time: %s \n", creationDate, creationTime);

        // Add saldo
        sleep(2);
        //printf("Saldo: %s \n", saldo);
        system("cls");
        printf("===========================================\n\n");
        printf("\n\nThe following account will be created: \n\n");
        printf("Account number:     %i\n", accountNr);
        printf("BankGiro:           %i\n", bankGiro);
        printf("Personal number:    %i-%i\n", personalNr, lastDigits);
        printf("First name:         %s\n", firstName);
        printf("Last name:          %s\n", lastName);
        printf("PIN-code:           ****\n", pin);
        printf("Current saldo:      %f\n", saldo);
        printf("Creation date:      %s\n", creationDate);
        printf("Creation time:      %s\n", creationTime);
        printf("\n\n===========================================");


        printf("\nSelect an option: \n");
        printf("A) Confirm information and create account \n");
        printf("B) Edit my information\n");

        printf("\nAnswer: ");
        scanf("%s", &answer);
        getchar();

    } while(answer == 'B');

    // Check to see if first line
    fgets(buffer, sizeof(buffer), fp);
    temp = strtok(buffer,",");
    rewind(fp);
    if(answer == 'A'){
        if(temp != NULL){
            fprintf(fp,"\n");
        }
        fprintf(fp, "%i,%i,%i,%i,%s,%s,%s,%f,%s,%s", accountNr, bankGiro, personalNr, lastDigits, firstName, lastName, pin, saldo,creationDate, creationTime);

        
        printf("\nAccount created.\n");
        printf("Welcome to Big Banking.\n");
        sleep(2);
    }


    // Print to document
    

    fclose(fp);
}