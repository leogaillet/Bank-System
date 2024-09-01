#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include "../include/bank.h"
#include "../include/config.h"
#include "../include/linkedlist.h"

NodeHead *account_list = NULL;

struct Database adb = {
    "storage/accounts.dat",
    CLOSED,
    NULL};

int initialize_bank_system(void)
{
    srand(time(NULL));

    database_load(&adb, database_account_function);

    struct AccountDatabase *accDb = (struct AccountDatabase *)adb.contents;
    int account_index = accDb->account_count;
    Account **accounts_pointers = accDb->account_pointers;

    if (adb.status == FAILED)
    {
        printf("Impossible de charger les comptes bancaires !\n");
        return 1;
    }

    const long long int padding = 16 - (sizeof(Account) % 16);
    init_generic_table(&account_list, accounts_pointers[0], account_index, sizeof(Account) + padding, init_account_node);

    return 0;
}

int shutdown_bank_system(void)
{
    const int account_count = get_account_nodehead()->total_node;

    Account **saved_acc = (Account **)malloc(account_count * sizeof(Account *));
    table_to_array(account_list, saved_acc, account_count, sizeof(Account *));

    struct AccountDatabase *accdb = (struct AccountDatabase *)adb.contents;
    accdb->account_pointers = saved_acc;
    accdb->account_count = account_count;

    if (database_save(&adb, database_account_function) != 0)
    {
        printf("Impossible de sauvegarder les comptes bancaires !\n");
        return 1;
    }

    // Liberer les ressources allouees
    free_generic_table(account_list);

    return 0;
}

NodeHead *get_account_nodehead()
{
    return account_list;
}

// Operation avec les comptes
Account *create_account(const char *account_name, const char *account_lastname, const char *password, double initial_balance)
{
    // Créer un nouveau compte
    Account account;
    account.account_id = rand() % MAX_ACCOUNTS;
    strcpy_s(account.account_name, 32, account_name);
    strcpy_s(account.account_lastname, 32, account_lastname);
    strcpy_s(account.password, 64, password);
    account.balance = initial_balance;

    Account *account_ptr = malloc(sizeof(Account));
    memcpy(account_ptr, &account, sizeof(Account));

    add_node(account_list, account_ptr, &init_account_node);

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
        return -1;

    double positive_amount = amount > 0 ? amount : -amount;
    account->balance += positive_amount;
    return 0;
}

int withdraw(unsigned int account_id, double amount)
{
    // Retirer de l'argent d'un compte
    Account *account = (Account *)find_node(account_list, &account_id, &compare_account_id);
    if (account == NULL)
        return -1;

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
        return -1;

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

void database_account_function(struct Database *db, enum DB_FUNCTION db_operation, FILE *f)
{
    if (db_operation == CREATE)
    {
        int c = 0;
        fwrite(&c, sizeof(int), 1, f);
    }
    else if (db_operation == LOAD)
    {

        int c = 0;
        fread(&c, sizeof(int), 1, f);

        Account **accounts = (Account **)malloc(c * sizeof(Account *));

        for (int i = 0; i < c; i++)
        {
            Account *account = (Account *)malloc(sizeof(Account));
            fread(account, sizeof(Account), 1, f);
            accounts[i] = account;
        }

        struct AccountDatabase *adb = (struct AccountDatabase *)malloc(sizeof(struct AccountDatabase));
        adb->account_count = c;
        adb->account_pointers = accounts;

        db->contents = adb;
    }
    else if (db_operation == SAVE)
    {

        struct AccountDatabase *adb = (struct AccountDatabase *)db->contents;
        const int c = adb->account_count;
        Account **accounts = adb->account_pointers;

        fwrite(&c, sizeof(int), 1, f);

        for (int i = 0; i < c; i++)
        {
            Account *acc = accounts[i];
            fwrite(acc, sizeof(Account), 1, f);
            free(acc);
        }

        free(accounts);
        free(adb);
    }
    return;
}
