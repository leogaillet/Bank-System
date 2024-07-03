#ifndef DICTIONNARY_H
#define DICTIONNARY_H

#include "../types.h"

unsigned int hash(const char *key);
Entry *create_entry(const char *key, const char *value);

HashTable *create_table(void);
void clear_table(HashTable *table);

void dict_set(HashTable *table, const char *key, const Account *value);
Account *dict_get(HashTable *table, const char *key);
void dict_delete(HashTable *table, const char *key);

#endif // DICTIONNARY_H