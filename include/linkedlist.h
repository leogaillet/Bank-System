#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "generic_linkedlist.h"

/*
ACCOUNT PART
*/

void init_account_node(void *node, void *data);

int compare_account(void *data1, void *data2);

int compare_account_id(void *data, void *account_id);

int compare_account_name(void *data1, void *account_name_lastname);

int compare_account(void *data1, void *data2);

void print_account_id(void *data);

/*
TRANSACTION PART
*/

void init_transaction_node(void *node, void *data);

int compare_transaction_id(void *data, void *transaction_id);

int compare_transaction(void *data1, void *data2);

void print_transaction_id(void *data);

#endif // LINKEDLIST_H