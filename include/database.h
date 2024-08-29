#ifndef DATABASE_H
#define DATABASE_H

#include "types.h"
#include <stdio.h>

enum DB_STATUS
{
    OPENED,
    CLOSED,
    FAILED
};

struct Database
{
    char file_name[64];
    enum DB_STATUS status;
    void *contents;
};

struct AccountDatabase
{
    int account_count;
    Account **account_pointers;
};

typedef void (*DatabaseFunction)(struct Database *db, FILE *file_stream);

void tload_accounts(struct Database *database, FILE *file_stream);
void tsave_accounts(struct Database *database, FILE *file_stream);
int tload(struct Database *database, DatabaseFunction db_function);
int tsave(struct Database *database, DatabaseFunction db_function);

int load_accounts(Account accounts[], int *account_count);
int save_accounts(Account accounts[], int account_count);
int load_transactions(Transaction transactions[], int *transaction_count);
int save_transactions(Transaction transactions[], int transaction_count);

#endif // DATABASE_H