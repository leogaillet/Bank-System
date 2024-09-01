#ifndef DATABASE_H
#define DATABASE_H

#include "types.h"
#include <stdio.h>

enum DB_STATUS
{
    OPENED,
    CLOSED,
    FAILED
};

enum DB_FUNCTION
{
    LOAD,
    SAVE,
    CREATE
};

struct Database
{
    char file_name[64];
    enum DB_STATUS status;
    void *contents;
};

struct AccountDatabase
{
    int account_count;
    Account **account_pointers;
};

typedef void (*DatabaseFunction)(struct Database *db, enum DB_FUNCTION db_operation, FILE *file_stream);
int database_load(struct Database *database, DatabaseFunction db_function);
int database_save(struct Database *database, DatabaseFunction db_function);

#endif // DATABASE_H