#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/bank.h"
#include "../include/config.h"
#include "../include/dictionnary.h"

int account_count = 0;
Account accounts[MAX_ACCOUNTS];

int transaction_count = 0;
Transaction transactions[MAX_TRANSACTIONS];

int initialize_bank_system(void)
{
    srand(time(NULL));

    // Initialiser les ressources nécessaires
    if (load_accounts(accounts, &account_count) != 0)
    {
        printf("Impossible de charger les comptes bancaires !\n");
        return 1;
    }
    if (load_transactions(transactions, &transaction_count) != 0)
    {
        printf("Impossible de charger les transactions !\n");
        return 1;
    }

    return 0;
}

int shutdown_bank_system(void)
{
    // Libérer les ressources allouées
    if (save_accounts(accounts, account_count) != 0)
    {
        printf("Impossible de sauvegarder les comptes bancaires !\n");
        return 1;
    }
    if (save_transactions(transactions, transaction_count) != 0)
    {
        printf("Impossible de sauvegarder les transactions !\n");
        return 1;
    }

    dict_free();
    return 0;
}

int create_account(const char *account_holder, double initial_balance)
{
    // Créer un compte bancaire
    Account acc;
    acc.account_id = (rand() % MAX_ACCOUNTS);
    strcpy(acc.account_holder, account_holder);
    acc.balance = initial_balance;

    dict_set(strdup(account_holder), &acc);
    return 0;
}

Account *get_account(const char *account_holder)
{
    return dict_get(strdup(account_holder));
}

Account *get_account_from_id(const int account_id)
{
    return dict_get_from_id(account_id);
}

int close_account(int account_number)
{
    // Fermer un compte bancaire
    Account *acc = dict_get_from_id(account_number);

    if (acc == NULL)
        return 0;

    dict_remove(acc->account_holder);

    return 1;
}

double get_balance(int account_number)
{
    // Retourner le solde du compte
    Account *acc = dict_get_from_id(account_number);

    if (acc == NULL)
        return 0;

    return acc->balance;
}

int deposit(int account_number, double amount)
{
    // Déposer de l'argent sur un compte
    return 0;
}

int withdraw(int account_number, double amount)
{
    // Retirer de l'argent d'un compte
    return 0;
}

int transfer(int from_account_number, int to_account_number, double amount)
{
    // Transférer de l'argent entre comptes
    return 0;
}

int get_transaction_history(int account_number, Transaction *transactions, int max_transactions)
{
    // Retourner l'historique des transactions
    return -1;
}