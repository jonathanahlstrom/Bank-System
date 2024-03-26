
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

#include "Functions/loginAccount.h"

#include "Functions/updateCopyFile.h"
#include "Functions/updateSaldo.h"
#include "Functions/login.h"
#include "Functions/makeDeposit.h"
#include "Functions/makePayment.h"
#include "Functions/makeWithdrawal.h"
#include "Functions/deleteAccount.h"
#include "Functions/createAccount.h"

//Global variables
int loggedIn = 0;
int loggingOut = 0;


int main(){
 

    int start = 1;
    do{
        system("cls");
        printf("============================================\n");
        printf("======== WELCOME TO BIG BANKING INC ========\n");
        printf("============================================\n");

        printf("\nWhat you wish to do? \n");
        printf("A. Create an account\n");
        printf("B. Login to my account\n");
        printf("C. Exit application\n");

        char answer;
        int cancelLogin;
        printf("\n\nAnswer: ");
        scanf("%c", &answer);
        getchar();



        if(answer == 'A')
        {
            
            createAccount();
            
        }
        else if (answer == 'B')
        {
                loggedIn == 0;
                loggingOut = 0;
            while(loggedIn==0 && loggingOut ==0){
                loggedInAcc = login(&cancelLogin);
                //loginAccount loggedInAcc = login(&cancelLogin);
                char firstName[15];
                char lastName[15];
                //printf("First name: %s\n", loggedInAcc.firstName);
                //printf("Last name 2: %s\n", loggedInAcc.lastName);
                if(loggedInAcc.loginFlag == 1)
                {

                    //printf("Last name 2: %s\n", loggedInAcc.lastName);
                    char buffer[100];
                    printf("\nLOGIN SUCCESSFUL \n");
                    sleep(1);
                    
                    strcpy(firstName,loggedInAcc.firstName);
                    strcpy(lastName,loggedInAcc.lastName);

                    while(loggedInAcc.loginFlag == 1){    
                        
                        system("cls");

                        
                        printf("===========================================\n");
                        printf("\nAccount Number: %d\n", loggedInAcc.accountNr);
                        printf("Bank giro: %d\n", loggedInAcc.bankGiro);                  
                        printf("Personal Number: %d\n", loggedInAcc.personalNr);
                        printf("Last digits: %d\n", loggedInAcc.lastDigits);  
                        printf("First name: %s\n", firstName);
                        printf("Last name: %s\n", lastName);  
                        printf("Pin: ****\n");  
                        printf("Current saldo: %f\n", loggedInAcc.saldo);
                        printf("===========================================\n");

                        printf("\nOptions: \n");
                        printf("A. Make a deposit\n");
                        printf("B. Make a payment\n");
                        printf("C. Withdraw from your account\n");
                        printf("D. Delete your account\n");
                        printf("E. Log out\n\n");
                    
                        printf("Answer: ");
                        scanf("%s", &answer);
                        getchar();



                        char buffer[100];
                        char n = '\0';
                        

                        if (answer == 'A')
                        {

                            makeDeposit(loggedInAcc.bankGiro);
                            loggedInAcc = updateSaldo(loggedInAcc);

                            sleep(2);
                            

                        }
                        else if (answer == 'B')
                        {
                            makePayment(loggedInAcc);
                            loggedInAcc = updateSaldo(loggedInAcc);

                            system("cls");
                        }
                        else if (answer == 'C')
                        {
                            makeWithdrawal(loggedInAcc.bankGiro);
                            loggedInAcc = updateSaldo(loggedInAcc);

                            sleep(2);

                          
                        }
                        else if (answer == 'D')
                        {
                            char answDelete;
                            printf("Are you sure you wish to delete your account? Deleting your account cannot be reversed.\n");
                            printf("A) Yes\n");
                            printf("B) No\n");



                            while (true)
                            {
                                printf("Answer: ");
                                scanf("%s", &answDelete);
                                getchar();


                                if (answDelete == 'A')
                                {
                                    deleteAccount(loggedInAcc);
                                    printf("Logging out...");
                                    loggingOut == 1;
                                    loggedInAcc.loginFlag = 0;
                                    loggedIn =0;
                                    strcpy(&answer,"E");
                                    sleep(1);
                                    break;
                                }
                                else if (answDelete == 'B')
                                {
                                    break;
                                }
                                else{
                                    printf("Option not available. Please answer A or B.\n\n");
                                    continue;
                                }
                            }
                            

                        }
                        if (answer == 'E')
                        {
                            loggedInAcc.loginFlag = 0;
                            loggedIn = 0;
                            loggingOut = 1;
                            printf("\nYou are logged out.\n");
                            sleep(2);
                            break;
                            
                        }

                    }

                    

                }

            }

        
        }
        else if (answer == 'C')
        {
            system("cls");
            printf("Exiting application...");
            start = 0;
            break;
            
            
        }
        else
        {
            printf("Please enter a valid option.\n\n");
        }

        
    } while(true);



}

