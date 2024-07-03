#ifndef DATABASE_H
#define DATABASE_H

typedef struct
{
    int account_id;
    char *account_holder;
    double balance;
} Account;

typedef struct
{
    int transaction_id;
    int account_number;
    char type[10];
    double amount;
    char date[20];
} Transaction;

int load_accounts(Account *accounts, int *account_count);
int save_accounts(Account *accounts, int account_count);
int load_transactions(Transaction *transactions, int *transaction_count);
int save_transactions(Transaction *transactions, int transaction_count);

#endif // DATABASE_H