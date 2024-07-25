#ifndef DATABASE_H
#define DATABASE_H

#include "types.h"

int load_accounts(Account accounts[], int *account_count);
int save_accounts(Account accounts[], int account_count);
int load_transactions(Transaction transactions[], int *transaction_count);
int save_transactions(Transaction transactions[], int transaction_count);

#endif // DATABASE_H