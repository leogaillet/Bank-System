#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include "../include/bank.h"
#include "../include/config.h"
#include "../include/linkedlist.h"

NodeHead *account_list = NULL;
NodeHead *transaction_list = NULL;

struct Database adb = {
    "storage/accounts.dat",
    CLOSED,
    NULL};

int initialize_bank_system(void)
{
    srand(time(NULL));

    tload(&adb, tload_accounts);

    struct AccountDatabase *accDb = (struct AccountDatabase *)adb.contents;
    int account_index = accDb->account_count;
    Account **accounts_pointers = accDb->account_pointers;

    // accounts -> tableau de pointeurs -> (*Account)[]

    // Initialiser les ressources necessaires pour les comptes
    // if (load_accounts(&accounts, &account_index) !   = 0)
    if (adb.status == FAILED)
    {
        printf("Impossible de charger les comptes bancaires !\n");
        return 1;
    }

    for (int i = 0; i < account_index; i++)
    {
        printf("id %d | %p\n", accounts_pointers[i]->account_id, accounts_pointers[i]);
    }

    const long long int padding = 16 - (sizeof(Account) % 16);
    init_generic_table(&account_list, accounts_pointers[0], account_index, sizeof(Account) + padding, init_account_node);
    print_graph(account_list, print_account_id);

    /*

    int transaction_index = 0;
    Transaction transactions[MAX_TRANSACTIONS];
    // Initialiser les ressources necessaires pour les transactions
    if (load_transactions(transactions, &transaction_index) != 0)
    {
        printf("Impossible de charger les transactions !\n");
        return 1;
    }

    init_generic_table(&transaction_list, transactions, transaction_index, sizeof(Transaction), init_transaction_node);

    */

    return 0;
}

int shutdown_bank_system(void)
{

    if (1)
    {
        const int account_count = get_account_nodehead()->total_node;
        print_graph(account_list, print_address);
        print_graph(account_list, print_account_id);

        printf("%d addresses ---\n", account_count);

        for (struct Node *current = account_list->head; current != NULL; current = current->next)
        {
            GenericNode *gnode = (GenericNode *)current;
            Account *account = (Account *)gnode->data;

            printf("%p %d\n", account, account->account_id);
        }

        Account **saved_acc = (Account **)malloc(account_count * sizeof(Account *));
        // const long long int padding = 16 - (sizeof(Account *) % 16);
        table_to_array(account_list, saved_acc, account_count, sizeof(Account *));

        printf("%d saved_acc ---\n", account_count);
        for (int i = 0; i < account_count; i++)
        {
            Account *acc = saved_acc[i];
            printf("%d %p\n", acc->account_id, acc);
        }

        struct AccountDatabase *accdb = (struct AccountDatabase *)adb.contents;
        accdb->account_pointers = saved_acc;
        accdb->account_count = account_count;

        if (tsave(&adb, tsave_accounts) != 0)
        {
            printf("Impossible de sauvegarder les comptes bancaires !\n");
            return 1;
        }
    }
    else
    {
        const long long int padding = 16 - (sizeof(Account) % 16);
        Account saved_acc[] = {
            {123, "a", "b", "c", 999.9},
            {456, "d", "e", "f", 111.1},
            {138712731, "ediuzhudized", "zfuiezfgyurezgfiuezrf", "boisiehfuieghfuerfuref", 1231231.1},
            {789, "g", "h", "i", 888.8}};
        const int account_count = 4;
        table_to_array(account_list, &saved_acc, account_count, sizeof(Account) + padding);

        if (save_accounts(saved_acc, account_count) != 0)
        {
            printf("Impossible de sauvegarder les comptes bancaires !\n");
            return 1;
        }
    }

    // Liberer les ressources allouees
    printf("a");
    free_generic_table(account_list);

    printf("a");
    /*
        const int transaction_count = get_transaction_nodehead()->total_node;
    Transaction saved_tra[transaction_count];
    table_to_array(transaction_list, saved_tra, transaction_count, sizeof(Transaction));

    if (save_transactions(saved_tra, transaction_count) != 0)
    {
        printf("Impossible de sauvegarder les transactions !\n");
        return 1;
    }
    // Liberer les ressources allouees
    free_generic_table(transaction_list);
    */

    return 0;
}

NodeHead *get_account_nodehead()
{
    return account_list;
}

NodeHead *get_transaction_nodehead()
{
    return transaction_list;
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
