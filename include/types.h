#ifndef TYPES_H
#define TYPES_H

// DATABASE
// #pragma pack(push, 1)
typedef struct Account
{
    int account_id;
    char account_holder[32];
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

// Structure de nœud pour la liste chaînee
typedef struct Node
{
    Account *account;
    struct Node *next;
} Node;

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