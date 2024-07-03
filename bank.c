#include "bank.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

int account_count = 0;
Account *accounts;

int transaction_count = 0;
Transaction *transactions;

int initialize_bank_system(void)
{
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
    return 0;
}

int create_account(const char *account_holder, double initial_balance)
{
    // Créer un compte bancaire
    return 0;
}

int close_account(int account_number)
{
    // Fermer un compte bancaire
    return 0;
}

double get_balance(int account_number)
{
    // Retourner le solde du compte
    return 0;
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
