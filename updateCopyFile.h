#include <stdio.h>

void updateCopyFile(){


    FILE *fp = fopen("bankAccounts.csv", "w");
    FILE *newFile = fopen("bankAccounts_copy.csv", "a+");

    char copy[100];
    while(fgets(copy, sizeof(copy), newFile) != NULL){
        fputs(copy, fp);
    }

    fclose(fp);
    fclose(newFile);

}