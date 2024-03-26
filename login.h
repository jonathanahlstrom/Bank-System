
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>


loginAccount loggedInAcc;

loginAccount login(int *cancelLogin){
    
    //loginAccount loggedInAcc;
    loggedInAcc.loginFlag =0;

    int answPersonalNr;
    int answLastDigits;
    int answPin;
    
    int dataAccountNr;
    int dataBankGiro;
    char *dataFirstName;
    char *dataLastName;
    int dataPersonalNr;
    int dataLastDigits;
    int dataPin;
    float dataSaldo;
    char *temp;
    int flag =1;

    char buffer[1000];

    FILE* fp =fopen("bankAccounts.csv","a+");

    if (!fp){
        printf("Error logging in.\n");
    }
    else{
        //printf("\nFile opened successfully.");
    }

    while (true){

        do{
            system("cls");
            printf("===========LOGIN TO YOUR ACCOUNT===========\n");
            printf("\nEnter your personal number (YYYYMMDD):    ");
            scanf("%d", &answPersonalNr);
            getchar();

            if(answPersonalNr > 10000000 && 21000000 > answPersonalNr){
                break;
            }
            else
            {
                printf("Incorrect format.\n");
                printf("Please enter your 10-digit personal number in the format YYYYMMDD. \n\n");
                sleep(1.5);
                continue;
            }

        } while(true);
            

        do{
            printf("Enter your 4 last digits: (NNNN):         ");
            scanf("%d", &answLastDigits);
            getchar();


            if(answLastDigits > 1000 && 9999 > answLastDigits){
                break;
            }
            else
            {
                printf("Incorrect format. \n");
                printf("Please enter your four last digits in the format NNNN.\n\n");
                continue;
            }
        } while(true);
        

        do{
            printf("Enter PIN-code:                           ");
            scanf("%d", &answPin);
            getchar();


            if(answPin > 1000 && 9999 > answPin){
                break;
            }
            else
            {
                printf("Incorrect format. \n");
                printf("Plase enter your PIN-code in the format NNNN. \n\n");
                continue;
            }
        } while(true);
        
        
        do{
            fgets(buffer, sizeof(buffer), fp);

            temp = strtok(buffer,",");
            sscanf(temp,"%d", &dataAccountNr);
            
            
            temp = strtok(NULL,",");
            sscanf(temp,"%d", &dataBankGiro);

            temp = strtok(NULL,",");
            sscanf(temp,"%d", &dataPersonalNr);
                            
            // Check the last 4-digits
            temp = strtok(NULL,",");
            sscanf(temp,"%d", &dataLastDigits);

            dataFirstName = strtok(NULL,",");

            dataLastName = strtok(NULL,",");   

            temp = strtok(NULL,",");
            sscanf(temp,"%d", &dataPin);

            temp = strtok(NULL,",");
            sscanf(temp,"%f", &dataSaldo);

            if(dataPersonalNr == answPersonalNr && dataLastDigits == answLastDigits && dataPin == answPin){

                    

                        loggedInAcc.accountNr = dataAccountNr;
                        //printf("\nAccount Number: %d\n", loggedInAcc.accountNr);

                        loggedInAcc.bankGiro = dataBankGiro;
                        //printf("Bank giro: %d\n", loggedInAcc.bankGiro);  

                        loggedInAcc.personalNr = dataPersonalNr;
                        //printf("Personal Number: %d\n", loggedInAcc.personalNr);

                        loggedInAcc.lastDigits = dataLastDigits;
                        //printf("Last digits: %d\n", loggedInAcc.lastDigits);  

                        loggedInAcc.firstName = dataFirstName;
                        //printf("First name: %s\n", loggedInAcc.firstName);

                        loggedInAcc.lastName = dataLastName;
                        //printf("Last name: %s\n", loggedInAcc.lastName);  

                        loggedInAcc.pin = dataPin;
                        //printf("Pin: ****\n");  

                        loggedInAcc.saldo = dataSaldo;
                        //printf("Saldo: %f\n", loggedInAcc.saldo);  

                        loggedInAcc.loginFlag = 1;
                        flag = 0;
                        return loggedInAcc;
            }        


            if (flag == 0)
            {
                
                rewind(fp);
                break;
            }
            else if(flag == 1){

                rewind(fp);
                break;

            }




        } while(true);

        if (flag == 0)
        {
            break;
        }
        else if(flag == 1){
            printf("\nPersonal number or PIN-code is incorrect. Please try again.\n\n");
            sleep(1.5);
        }
        

    }
    

    *cancelLogin = 1;
}