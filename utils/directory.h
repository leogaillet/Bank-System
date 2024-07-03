#ifndef DIRECTORY_H
#define DIRECTORY_H

int directory_exists(const char *dir_name);
void create_directory(const char *dir_name);

int file_exists(const char *file_name);

void create_file_c_dc_dn(const char *file_name, const char *contents, const int dir_count, const char **dir_names);
void create_file_c_dn(const char *file_name, const char *contents, const char *dir_name);
void create_file_dn(const char *file_name, const char *dir_name);
void create_file_c(const char *file_name, const char *contents);
void create_file(const char *file_name);

#endif // DIRECTORY_H