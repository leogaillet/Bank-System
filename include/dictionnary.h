#ifndef DICTIONNARY_H
#define DICTIONNARY_H

#include "./types.h"

unsigned int dict_length(void);
Node *dict_get_node(void);

void dict_set(char *account_holder, Account *account);
Account *dict_get(char *account_holder);
Account *dict_get_from_id(const int account_id);
void dict_remove(char *account_holder);
void dict_free(void);

void parse_arr_to_dict(Account accounts[], int account_length, const int ACCOUNT_MAX_SIZE);
void parse_dict_do_arr(Account (*accounts)[], int *account_length, const int ACCOUNT_MAX_SIZE, Node *node);

#endif // DICTIONNARY_H
