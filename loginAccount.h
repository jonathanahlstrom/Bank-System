typedef struct{
    int accountNr;
    int bankGiro;
    int personalNr;
    int lastDigits;
    char *firstName;
    char *lastName;
    int pin;
    float saldo;
    int loginFlag;

} loginAccount;

loginAccount loggedInAcc;