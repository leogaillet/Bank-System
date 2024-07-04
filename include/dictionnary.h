#ifndef DICTIONNARY_H
#define DICTIONNARY_H

#include "./types.h"

void dict_set(char *account_holder, Account *account);
Account *dict_get(char *account_holder);
Account *dict_get_from_id(const int account_id);
void dict_remove(char *account_holder);
void dict_free(void);

#endif // DICTIONNARY_H