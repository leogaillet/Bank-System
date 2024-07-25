#ifndef BANK_H
#define BANK_H
#include "database.h"
#include "types.h"

// Initialisation et finalisation
int initialize_bank_system(void);
int shutdown_bank_system(void);

// Gestion des comptes
int create_account(const char *account_name, const char *account_lastname, double initial_balance);
int close_account(unsigned int account_id);
Account *get_account(const char *account_name, char *account_lastname);
Account *get_account_from_id(const int account_id);

// Operations de transations
double get_balance(unsigned int account_id);
int deposit(unsigned int account_id, double amount);
int withdraw(unsigned int account_id, double amount);
int transfer(unsigned int from_account_id, unsigned int to_account_id, double amount);

// Historiques des transactions
int get_transaction_history(unsigned int account_id, Transaction *transactions, int max_transactions);

#endif // BANK_H
