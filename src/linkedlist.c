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
