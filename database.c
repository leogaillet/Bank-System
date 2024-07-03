#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "config.h"
#include "utils/directory.h"

int load_accounts(Account *accounts, int *account_count)
{
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
        fread(accounts, sizeof(Account), *account_count, f);

        fclose(f);
    }

    free(account_file);

    return 0;
}

int save_accounts(Account *accounts, int account_count)
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
    fread(accounts, sizeof(Account), account_count, f);

    fclose(f);
    free(account_file);

    return 0;
}

int load_transactions(Transaction *transactions, int *transaction_count)
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

int save_transactions(Transaction *transactions, int transaction_count)
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