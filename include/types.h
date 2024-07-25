#ifndef TYPES_H
#define TYPES_H

typedef struct Transaction Transaction;

// DATABASE
// #pragma pack(push, 1)
typedef struct Account
{
    unsigned int account_id;
    char account_name[32];
    char account_lastname[32];
    char password[32];
    double balance;
} Account;
// #pragma pack(pop)

typedef struct Transaction
{
    unsigned int transaction_id;
    unsigned int account_id;
    unsigned char type[16];
    double amount;
    unsigned char date[24];
} Transaction;

// // DICTIONNARY
// typedef struct Entry
// {
//     char *key;
//     struct Account value;
//     struct Entry next;
// } Entry;

// typedef struct HashTable
// {
//     struct Entry *entries;
// } HashTable;

#endif // TYPES_H