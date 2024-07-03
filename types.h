#ifndef TYPES_H
#define TYPES_H

// DATABASE
typedef struct Account
{
    int account_id;
    char account_holder[64];
    double balance;
} Account;

typedef struct Transaction
{
    int transaction_id;
    int account_number;
    char type[10];
    double amount;
    char date[20];
} Transaction;

// DICTIONNARY
typedef struct Entry
{
    char *key;
    struct Account *value;
    struct Entry *next;
} Entry;

typedef struct HashTable
{
    struct Entry **entries;
} HashTable;

#endif // TYPES_H