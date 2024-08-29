#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "../include/directory.h"

void tload_accounts(struct Database *db, FILE *f)
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

    for (int i = 0; i < adb->account_count; i++)
    {
        Account *acc = adb->account_pointers[i];
        printf("%d: %s %s | %s %.3f$\n", acc->account_id, acc->account_name, acc->account_lastname, acc->password, acc->balance);
        printf("%p\n%p\n%p\n%p\n%p\n\n", &acc->account_id, &acc->account_name, &acc->account_lastname, &acc->password, &acc->balance);
    }

    db->contents = adb;
}

void tsave_accounts(struct Database *db, FILE *f)
{
    struct AccountDatabase *adb = (struct AccountDatabase *)db->contents;
    const int c = adb->account_count;
    Account **accounts = adb->account_pointers;

    fwrite(&c, sizeof(int), 1, f);

    printf("saved ----- \n");
    for (int i = 0; i < c; i++)
    {
        // Account *account = (Account *)malloc(sizeof(Account));
        Account *acc = accounts[i];
        fwrite(acc, sizeof(Account), 1, f);
        printf("%d: %s %s | %s %.3f$\n", acc->account_id, acc->account_name, acc->account_lastname, acc->password, acc->balance);
        free(acc);
    }

    free(accounts);
    free(adb);
}

int tload(struct Database *database, DatabaseFunction db_function)
{
    FILE *f = fopen(database->file_name, "rb");
    if (f == NULL)
    {
        save_accounts(NULL, 0);
    }

    db_function(database, f);

    fclose(f);

    database->status = OPENED;
    return 0;
}

int tsave(struct Database *database, DatabaseFunction db_function)
{
    FILE *f = fopen(database->file_name, "wb");
    if (f == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", database->file_name);
        database->status = FAILED;
        return 1;
    }

    db_function(database, f);

    fclose(f);

    database->status = OPENED;
    return 0;
}

int load_accounts(Account accounts[], int *account_count)
{
    /*
        *(*accounts)[] est un Account
        *(*accounts) est un tableau de Account
        (*accounts) est un pointeur de tableau de Account
        accounts est un pointeur de tableau de pointeurs de Account
    */
    char *account_file = (char *)malloc(255 * sizeof(char));
    sprintf(account_file, "%s/%s", DATABASE_FOLDER, ACCOUNT_FILE);

    if (file_exists(account_file) != 1)
    {
        create_file_dn(ACCOUNT_FILE, DATABASE_FOLDER);
        *account_count = 0;
    }
    else
    {
        FILE *f = fopen(account_file, "rb");
        if (f == NULL)
        {
            printf("Impossible d'ouvrir le fichier %s\n", account_file);
            return 1;
        }

        fread(account_count, sizeof(int), 1, f);

        Account **array_of_pointers = malloc(*account_count * sizeof(Account *));

        for (int i = 0; i < *account_count; i++)
        {
            array_of_pointers[i] = malloc(sizeof(Account));
            fread(array_of_pointers[i], sizeof(Account), *account_count, f);
        }

        fclose(f);

        // accounts = &array_of_pointers;
    }

    free(account_file);

    return 0;
}

int save_accounts(Account accounts[], int account_count)
{
    char *account_file = (char *)malloc(255 * sizeof(char));
    sprintf(account_file, "%s/%s", DATABASE_FOLDER, ACCOUNT_FILE);

    FILE *f = fopen(account_file, "wb");
    if (f == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", account_file);
        return 1;
    }

    fwrite(&account_count, sizeof(int), 1, f);
    fwrite(accounts, sizeof(Account), account_count, f);

    fclose(f);
    free(account_file);

    return 0;
}

int load_transactions(Transaction transactions[], int *transaction_count)
{
    char *transaction_file = (char *)malloc(255 * sizeof(char));
    sprintf(transaction_file, "%s/%s", DATABASE_FOLDER, TRANSACTION_FILE);

    if (file_exists(transaction_file) != 1)
    {
        create_file_dn(TRANSACTION_FILE, DATABASE_FOLDER);
        *transaction_count = 0;
    }
    else
    {

        FILE *f = fopen(transaction_file, "rb");
        if (f == NULL)
        {
            printf("Impossible d'ouvrir le fichier %s\n", transaction_file);
            return 1;
        }

        fread(transaction_count, sizeof(int), 1, f);
        fread(transactions, sizeof(Transaction), *transaction_count, f);

        fclose(f);
    }

    free(transaction_file);

    return 0;
}

int save_transactions(Transaction transactions[], int transaction_count)
{
    char *transaction_file = (char *)malloc(255 * sizeof(char));
    sprintf(transaction_file, "%s/%s", DATABASE_FOLDER, TRANSACTION_FILE);

    FILE *f = fopen(transaction_file, "wb");
    if (f == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", transaction_file);
        return 1;
    }

    fwrite(&transaction_count, sizeof(int), 1, f);
    fwrite(transactions, sizeof(Transaction), transaction_count, f);

    fclose(f);
    free(transaction_file);

    return 0;
}