#ifndef MENU
#define MENU

void ask(char *demand, char *answer, size_t max_length);

int menu_exit(void);
int menu_graph(void);
int menu_account_add(void);
int menu_account_remove(void);
int menu_account_get(void);
int menu_account_balance(void);
int menu_account_list(void);
int menu_account_transfert(void);

#endif // MENU
