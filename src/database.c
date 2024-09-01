#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "../include/directory.h"

int database_create(struct Database *database, DatabaseFunction db_function)
{
    FILE *f = fopen(database->file_name, "rb");
    if (f == NULL)
    {
        db_function(database, CREATE, f);
        database->status = OPENED;
        return 0;
    }

    fclose(f);
    printf("le fichier %s est déjà existant !\n", database->file_name);
    database->status = FAILED;
    return 1;
}

int database_load(struct Database *database, DatabaseFunction db_function)
{
    FILE *f = fopen(database->file_name, "rb");
    if (f == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", database->file_name);
        database->status = FAILED;
        return 1;
    }

    db_function(database, LOAD, f);

    fclose(f);

    database->status = OPENED;
    return 0;
}

int database_save(struct Database *database, DatabaseFunction db_function)
{
    FILE *f = fopen(database->file_name, "wb");
    if (f == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", database->file_name);
        database->status = FAILED;
        return 1;
    }

    db_function(database, SAVE, f);

    fclose(f);

    database->status = OPENED;
    return 0;
}