#include <stdio.h>
#include <stdlib.h>
#include "../include/bank.h"
#include "../include/dictionnary.h"
#include "../include/types.h"

int menu_exit(void)
{
    return 0;
}

int menu_account_add(void)
{
    char account_holder[32], in_balance[10];

    printf("Quel est le nom du compte ? ");
    scanf("%32s", account_holder);

    printf("Quel est le montant du compte ? ");
    scanf("%10s", in_balance);

    double account_balance = atof(in_balance);

    int account_id = create_account(account_holder, account_balance);

    printf("Votre compte a ete cree, l'identifiant du compte est : %d\n", account_id);

    return 0;
}

int menu_account_remove(void)
{
    char input[32];
    printf("Veuillez saisir le numero du compte : ");
    scanf("%32s", input);

    const int account_id = atoi(input);

    if (
        close_account(atoi(input)) == 0)
    {
        printf("Le compte n°%d n'a pas ete trouve!\n", account_id);
        return 1;
    }

    printf("Le compte n°%d a ete ferme !\n", account_id);
    return 0;
}

int menu_account_get(void)
{
    char input[32];
    printf("Veuillez saisir le numero du compte : ");
    scanf("%32s", input);

    const int account_id = atoi(input);
    Account *account = get_account_from_id(account_id);

    if (account == NULL)
    {
        printf("Votre compte n°%d n'a pas ete trouve\n", account_id);
        return 1;
    }

    printf("\nCompte trouve !\n\n");
    printf("====================\n");
    printf("Identifiant du compte : %d\n", account->account_id);
    printf("Proprietaire du compte : %s\n", account->account_holder);
    printf("Solde actuel : %.2f\n", account->balance);
    printf("====================\n\n");

    return 0;
}

int menu_account_balance(void)
{
    return 0;
}

int menu_account_list(void)
{
    Node *node = dict_get_node();

    unsigned int n = dict_length();
    if (n == 0)
        printf("Il n'y a aucun compte enregistre a ce jour !\n");
    else
        printf("Il a %u compte.s enregistre a ce jour !\n", n);

    while (node != NULL)
    {
        Account *acc = node->account;

        printf("====================\n");
        printf("Identifiant du compte : %d\n", acc->account_id);
        printf("Proprietaire du compte : %s\n", acc->account_holder);
        printf("Solde actuel : %.2f\n", acc->balance);
        printf("====================\n\n");

        node = node->next;
    }

    return 0;
}

int menu_account_transactions(void)
{
    return 0;
}

int menu_transactions(void)
{
    return 0;
}