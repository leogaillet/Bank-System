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

    // Initialiser les ressources necessaires
    if (load_accounts(accounts, &account_count) != 0)
    {
        printf("Impossible de charger les comptes bancaires !\n");
        return 1;
    }
    for (int i = 0; i < account_count; i++)
    {
        printf("Acc n°%d\n", accounts[i].account_id);
    }
    parse_arr_to_dict(accounts, account_count, MAX_ACCOUNTS);

    if (load_transactions(transactions, &transaction_count) != 0)
    {
        printf("Impossible de charger les transactions !\n");
        return 1;
    }

    return 0;
}

int shutdown_bank_system(void)
{
    // Liberer les ressources allouees
    parse_dict_do_arr(&accounts, &account_count, MAX_ACCOUNTS, dict_get_node());
    for (int i = 0; i < account_count; i++)
    {
        printf("Acc n°%d\n", accounts[i].account_id);
    }
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
    // Creer un compte bancaire
    Account acc;
    acc.account_id = (rand() % MAX_ACCOUNTS);
    strcpy(acc.account_holder, account_holder);
    acc.balance = initial_balance;

    dict_set(strdup(account_holder), &acc);
    account_count++;
    return acc.account_id;
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
    account_count--;

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
    // Deposer de l'argent sur un compte
    return 0;
}

int withdraw(int account_number, double amount)
{
    // Retirer de l'argent d'un compte
    return 0;
}

int transfer(int from_account_number, int to_account_number, double amount)
{
    // Transferer de l'argent entre comptes
    return 0;
}

int get_transaction_history(int account_number, Transaction *transactions, int max_transactions)
{
    // Retourner l'historique des transactions
    return -1;
}
