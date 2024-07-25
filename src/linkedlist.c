#include "../include/linkedlist.h"
#include <string.h>
#include <stdio.h>

/*
ACCOUNT PART
*/

void init_account_node(void *node, void *data)
{
    GenericNode *gnode = (GenericNode *)node;
    Account *account = (Account *)data;
    gnode->data = account;
}

int compare_account_id(void *data, void *account_id)
{
    int *id = (int *)account_id;
    Account *acc = (Account *)data;
    return *id - acc->account_id;
}

int compare_account_name(void *data1, void *account_name_lastname)
{
    Account *acc1 = (Account *)data1;
    char account1[64];
    strcpy(account1, acc1->account_name);
    strcat(account1, acc1->account_lastname);
    char *account2 = (char *)account_name_lastname;
    return strcmp(account1, account2);
}

int compare_account(void *data1, void *data2)
{
    Account *acc1 = (Account *)data1;
    Account *acc2 = (Account *)data2;
    return acc1->account_id - acc2->account_id;
}

void print_account_id(void *data)
{
    Account *account = (Account *)data;
    printf("%d", account->account_id);
}

/*
TRANSACTION PART
*/

void init_transaction_node(void *node, void *data)
{
    GenericNode *gnode = (GenericNode *)node;
    Transaction *transaction = (Transaction *)data;
    gnode->data = transaction;
}

int compare_transaction_id(void *data, void *transaction_id)
{
    int *id = (int *)transaction_id;
    Transaction *acc = (Transaction *)data;
    return *id - acc->transaction_id;
}

int compare_transaction(void *data1, void *data2)
{
    Transaction *tr1 = (Transaction *)data1;
    Transaction *tr2 = (Transaction *)data2;
    return tr1->transaction_id - tr2->transaction_id;
}

void print_transaction_id(void *data)
{
    Transaction *transaction = (Transaction *)data;
    printf("%d", transaction->transaction_id);
}

/*
MAIN EXAMPLE PART
*/

// int main()
// {
//     Account accounts[] = {
//         {1, "Alice", "Dupont", "password", 5000.0},
//         {2, "Bob", "Bricoleur", "password", 3000.0}};
//     Transaction transactions[] = {
//         {1001, 1, "withdraw", -200.0, "2023-07-25"},
//         {1002, 2, "deposit", 500.0, "2023-07-26"}};

//     NodeHead *account_list;
//     NodeHead *transaction_list;

//     init_generic_table(accounts, 2, sizeof(Account), init_account_node, account_list);
//     init_generic_table(transactions, 2, sizeof(Transaction), init_transaction_node, transaction_list);

//     Transaction *transaction = (Transaction *)find_node_by_id(transaction_list, 1001, compare_transaction_id);
//     Account *account1 = (Account *)find_node_by_id(account_list, 1, compare_account_id);
//     Account *account2 = (Account *)find_node_by_id(account_list, 2, compare_account_id);

//     Account account3 = {3, "Jean", "Marc", "password", -1223.32};
//     Account account4 = {4, "Edouard", "Duc", "bonsoir", 123456.0};

//     add_node(account_list, &account3, init_account_node);
//     add_node(account_list, &account4, init_account_node);

//     Account *ac = find_node(account_list, &account3, compare_account_id);

//     showgraph(account_list->head, print_account_id);

//     delete_node(account_list, &account3, compare_account);

//     int accountid = 2;
//     delete_node(account_list, &accountid, compare_account_id);

//     Account account9 = {1822, "E2ridc", "Md2oretti", "assd222emblee", -12.32};
//     add_node(account_list, &account9, init_account_node);

//     showgraph(account_list->head, print_account_id);

//     return 0;
// }