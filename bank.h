#ifndef BANK_H
#define BANK_H
#include "database.h"

// Initialisation et finalisation
int initialize_bank_system(void);
int shutdown_bank_system(void);

// Gestion des comptes
int create_account(const char *account_holder, double initial_balance);
int close_account(int account_number);

// Opérations de transations
double get_balance(int account_number);
int deposit(int account_number, double amount);
int withdraw(int account_number, double amount);
int transfer(int from_account_number, int to_account_number, double amount);

// Historiques des transactions
int get_transaction_history(int account_number, Transaction *transactions, int max_transactions);

#endif // BANK_H
