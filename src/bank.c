#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/bank.h"
#include "../include/config.h"
#include "../include/linkedlist.h"

int account_count = 0;
Account accounts[MAX_ACCOUNTS];

int transaction_count = 0;
Transaction transactions[MAX_TRANSACTIONS];

NodeHead *account_list = NULL;
NodeHead *transaction_list = NULL;

int initialize_bank_system(void)
{
    srand(time(NULL));

    // Initialiser les ressources necessaires
    if (load_accounts(accounts, &account_count) != 0)
    {
        printf("Impossible de charger les comptes bancaires !\n");
        return 1;
    }

    init_generic_table(accounts, account_count, sizeof(Account), init_account_node, &account_list);

    if (load_transactions(transactions, &transaction_count) != 0)
    {
        printf("Impossible de charger les transactions !\n");
        return 1;
    }

    init_generic_table(transactions, transaction_count, sizeof(Transaction), init_transaction_node, &transaction_list);

    return 0;
}

int shutdown_bank_system(void)
{
    // Liberer les ressources allouees
    if (save_accounts(accounts, account_count) != 0)
    {
        printf("Impossible de sauvegarder les comptes bancaires !\n");
        return 1;
    }

    free_generic_table(account_list);

    if (save_transactions(transactions, transaction_count) != 0)
    {
        printf("Impossible de sauvegarder les transactions !\n");
        return 1;
    }

    free_generic_table(transaction_list);

    return 0;
}

int create_account(const char *account_name, const char *account_lastname, double initial_balance)
{
    // Créer un nouveau compte
    return 0;
}

Account *get_account(const char *account_name, char *account_lastname)
{
    // Récupérer un compte
    return NULL;
}

Account *get_account_from_id(const int account_id)
{
    // Récupérer un compte par rapport à un identifiant
    return NULL;
}

int close_account(unsigned int account_id)
{
    // Fermer un compte bancaire
    return 1;
}

double get_balance(unsigned int account_id)
{
    // Récupérer l'argent sur le compte
    return 0;
}

int deposit(unsigned int account_id, double amount)
{
    // Deposer de l'argent sur un compte
    return 0;
}

int withdraw(unsigned int account_id, double amount)
{
    // Retirer de l'argent d'un compte
    return 0;
}

int transfer(unsigned int from_account_id, unsigned int to_account_id, double amount)
{
    // Transferer de l'argent entre comptes
    return 0;
}

int get_transaction_history(unsigned int account_id, Transaction *transactions, int max_transactions)
{
    // Retourner l'historique des transactions
    return -1;
}
