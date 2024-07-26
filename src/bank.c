#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include "../include/bank.h"
#include "../include/config.h"
#include "../include/linkedlist.h"

#define ACCOUNT_NOT_FOUND -1

Account accounts[MAX_ACCOUNTS];
int account_index;
Transaction transactions[MAX_TRANSACTIONS];
int transaction_index;

NodeHead *account_list = NULL;
NodeHead *transaction_list = NULL;

int initialize_bank_system(void)
{
    srand(time(NULL));

    account_index = 0;
    // Initialiser les ressources necessaires pour les comptes
    if (load_accounts(accounts, &account_index) != 0)
    {
        printf("Impossible de charger les comptes bancaires !\n");
        return 1;
    }

    printf("%d\n", account_index);
    init_generic_table(&account_list, accounts, account_index, sizeof(Account), init_account_node);

    transaction_index = 0;
    // Initialiser les ressources necessaires pour les transactions
    if (load_transactions(transactions, &transaction_index) != 0)
    {
        printf("Impossible de charger les transactions !\n");
        return 1;
    }

    init_generic_table(&transaction_list, transactions, transaction_index, sizeof(Transaction), init_transaction_node);

    return 0;
}

int shutdown_bank_system(void)
{

    int account_count = get_account_nodehead()->total_node;
    Account saved_acc[account_count];
    table_to_array(account_list, saved_acc, account_count, sizeof(Account));

    if (save_accounts(saved_acc, account_count) != 0)
    {
        printf("Impossible de sauvegarder les comptes bancaires !\n");
        return 1;
    }
    // Liberer les ressources allouees
    free_generic_table(account_list);

    int transaction_count = get_transaction_nodehead()->total_node;
    Transaction saved_tra[transaction_count];
    table_to_array(transaction_list, saved_tra, transaction_count, sizeof(Transaction));

    if (save_transactions(saved_tra, transaction_count) != 0)
    {
        printf("Impossible de sauvegarder les transactions !\n");
        return 1;
    }
    // Liberer les ressources allouees
    free_generic_table(transaction_list);

    return 0;
}

NodeHead *get_account_nodehead()
{
    return account_list;
}
Account *get_accounts()
{
    return accounts;
}

NodeHead *get_transaction_nodehead()
{
    return transaction_list;
}

// Operation avec les comptes
Account *create_account(const char *account_name, const char *account_lastname, const char *password, double initial_balance)
{
    // Récuperer la derniere position du tableau des comptes
    Account *account_ptr = &accounts[account_index];

    // Créer un nouveau compte
    Account account;
    account.account_id = rand() % MAX_ACCOUNTS;
    strcpy_s(account.account_name, 32, account_name);
    strcpy_s(account.account_lastname, 32, account_lastname);
    strcpy_s(account.password, 64, password);
    account.balance = initial_balance;

    memcpy(account_ptr, &account, sizeof(Account));

    add_node(account_list, account_ptr, &init_account_node);

    account_index++;
    return account_ptr;
}

int close_account(unsigned int account_id)
{
    // Fermer un compte bancaire
    if (get_account_from_id(account_id) == NULL)
        return -1;

    delete_node(account_list, &account_id, compare_account_id);
    return 0;
}

Account *get_account(const char *account_name, const char *account_lastname)
{
    char account_name_lastname[64];
    strcpy(account_name_lastname, account_name);
    strcat(account_name_lastname, account_lastname);
    // Récupérer un compte
    return find_node(account_list, account_name_lastname, &compare_account_name);
}

Account *get_account_from_id(unsigned int account_id)
{
    // Récupérer un compte par rapport à un identifiant
    return (Account *)find_node(account_list, &account_id, &compare_account_id);
}

double get_balance(unsigned int account_id)
{
    // Récupérer l'argent sur le compte
    Account *account = (Account *)find_node(account_list, &account_id, &compare_account_id);
    if (account == NULL)
        return DBL_MIN;
    return account->balance;
}

// Operations de transaction

int deposit(unsigned int account_id, double amount)
{
    // Deposer de l'argent sur un compte
    Account *account = (Account *)find_node(account_list, &account_id, &compare_account_id);
    if (account == NULL)
        return ACCOUNT_NOT_FOUND;

    double positive_amount = amount > 0 ? amount : -amount;
    account->balance += positive_amount;
    return 0;
}

int withdraw(unsigned int account_id, double amount)
{
    // Retirer de l'argent d'un compte
    Account *account = (Account *)find_node(account_list, &account_id, &compare_account_id);
    if (account == NULL)
        return ACCOUNT_NOT_FOUND;

    double positive_amount = amount > 0 ? amount : -amount;
    account->balance -= positive_amount;
    return 0;
}

int transfer(unsigned int from_account_id, unsigned int to_account_id, double amount)
{
    // Transferer de l'argent entre comptes
    Account *from_account = (Account *)find_node(account_list, &from_account_id, &compare_account_id);
    Account *to_account = (Account *)find_node(account_list, &to_account_id, &compare_account_id);

    if (from_account == NULL || to_account == NULL)
        return ACCOUNT_NOT_FOUND;

    double positive_amount = amount > 0 ? amount : -amount;
    from_account->balance -= positive_amount;
    to_account->balance += positive_amount;

    return 0;
}

int get_transaction_history(unsigned int account_id, Transaction *transactions, int max_transactions)
{
    // Retourner l'historique des transactions
    return -1;
}
