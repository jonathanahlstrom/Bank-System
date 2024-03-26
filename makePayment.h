
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



void makePayment(loginAccount loggedInAcc){
    

    loginAccount recAccount;

    int answBankGiro;
    float answSum;
    int dataBankGiro;
    int dataAccountNr;

    char firstName[15];
    char lastName[15];
    char creationDate[15];
    char creationTime[15];
    char message[25];
    char notes[25];
    char answConfirm;

    char transDate[15];
    float newSaldo;
    float recSaldo;

    char fileName[20];
    char buffer[100];
    int flag = 0;

    system("cls");

    printf("======== MAKE A PAYMENT OR TRANSFER ========\n\n");
    // To
    
   
    FILE *fp = fopen("bankAccounts.csv", "a+");

    while(true){
        printf("State BankGiro of recieving account (XXXXXX):         ");

        flag = 0;
        scanf("%d", &answBankGiro);
        getchar();

        rewind(fp);
        while(fgets(buffer, sizeof(buffer), fp)){
            sscanf(buffer, "%d,%d", &dataAccountNr, &dataBankGiro);

            // Check if the account exists
            if (answBankGiro == dataBankGiro)
            {
                sscanf(buffer, "%d,%d,%d,%d,%[^,],%[^,],%d,%f,%[^,],%[^\n]", &recAccount.accountNr,&recAccount.bankGiro,
                                                            &recAccount.personalNr,
                                                            &recAccount.lastDigits,
                                                            &firstName,
                                                            &lastName,
                                                            &recAccount.pin,
                                                            &recAccount.saldo,
                                                            &creationDate,
                                                            &creationTime);
                flag =1;
                break;
            }
            

        //sleep(3);
        }
        

        // If flag =1, the account exists and will exit the outer while loop.
        if (flag == 1)
        {
            break;
        }
        else
        {
            printf("The BankGiro is not connected to an account. Please provide a valid BankGiro.\n\n");
            
            continue;
        }
        
    }
    fclose(fp);     


    // Sum
    while(true){
        printf("Sum to transfer:                                      ");
        scanf("%f", &answSum);
        getchar();


        if(answSum > loggedInAcc.saldo){
            printf("Amount exceeds available account saldo.\n\n");
            continue;
        }
        else{
            break;
        }

    }


    printf("Transfer message or OCR:                              ");
    scanf("%s", &message);
    getchar();

    printf("Own notes:                                            ");
    scanf("%s", &notes);
    getchar();



    system("cls");
    printf("========== Transfer information ==========\n");
    printf("From account: %d             BankGiro: %d\n", loggedInAcc.accountNr, loggedInAcc.bankGiro);
    printf("To account: %d               BankGiro: %d\n\n", recAccount.accountNr, recAccount.bankGiro);
    printf("Amount to transfer:                    %10.2f\n", answSum);
    printf("Message:                                  %s\n", message);
    printf("Notes:                                    %s\n\n", notes);

    printf("Select an option: \n\n");
    printf("A) Approve transaction \n");
    printf("B) Cancel transaction \n\n");

    printf("Answer: ");
    scanf("%c", &answConfirm);




    

    time_t current_time = time(NULL);
    strftime(transDate, 20, "%Y-%m-%d", localtime(&current_time));


    newSaldo = loggedInAcc.saldo - answSum;
    recSaldo = recAccount.saldo + answSum;
   
    snprintf(fileName, sizeof(fileName), "%d.csv", loggedInAcc.bankGiro);
    FILE *transferAcc = fopen(fileName, "a+");
    fprintf(fp, "%s, %d, %d, %s, %10.2f, %10.2f \n", transDate, loggedInAcc.bankGiro, recAccount.bankGiro, message, -answSum, newSaldo);
    fclose(transferAcc);


    snprintf(fileName, sizeof(fileName), "%d.csv", recAccount.bankGiro);
    FILE *recAccFile = fopen(fileName, "a+");
    fprintf(recAccFile, "%s, %d, %d, %s, %10.2f, %10.2f \n", transDate, loggedInAcc.bankGiro, recAccount.bankGiro, message, answSum, recSaldo);
    fclose(recAccFile);


    updateSaldo(recAccount);
    

    printf("Transfer successful.\n");

}
