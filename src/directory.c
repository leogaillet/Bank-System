#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <strings.h>
#include <dirent.h>

int directory_exists(const char *dir_name)
{
    DIR *d = opendir(dir_name);
    if (d)
    {
        closedir(d);
        return 1;
    }
    else if (ENOENT == errno)
        return 0;
    else
        return 2;
}

// Fonction pour creer un dossier
int create_directory(const char *dir_name)
{
    if (directory_exists(dir_name))
        return 0;
    return mkdir(dir_name) == -1;
}

int file_exists(const char *file_name)
{
    return fopen(file_name, "r") == NULL ? 0 : 1;
}

void create_file_c_dc_dn(const char *file_name, const char *contents, const int dir_count, const char **dir_names)
{

    char file_path[256] = "";
    for (int i = 0; i < dir_count; i++)
    {
        strcat(file_path, *(dir_names + i));
        strcat(file_path, "/");
        if (directory_exists(file_path) == 0)
            create_directory(file_path);
    }

    strcat(file_path, file_name);

    FILE *file = fopen(file_path, "w");
    if (file == NULL)
    {
        printf("%s\n", file_path);
        perror("Erreur lors de la creation du fichier");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s\n", contents);
    fclose(file);
    printf("Fichier %s cree avec succes\n", file_path);
}

void create_file_c_dn(const char *file_name, const char *contents, const char *dir_name)
{
    const char *dir_names[40] = {dir_name};

    create_file_c_dc_dn(file_name, contents, 1, dir_names);
}

void create_file_dn(const char *file_name, const char *dir_name)
{
    const char *dir_names[40] = {dir_name};

    create_file_c_dc_dn(file_name, "contents", 1, dir_names);
}

void create_file_c(const char *file_name, const char *contents)
{
    const char *dir_names[40] = {""};

    create_file_c_dc_dn(file_name, contents, 0, dir_names);
}

void create_file(const char *file_name)
{
    create_file_c(file_name, "");
}
