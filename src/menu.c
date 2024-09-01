#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bank.h"
#include "../include/linkedlist.h"
#include "../include/types.h"

void ask(char *demand, char *answer, size_t max_length)
{
    char prompt[256];
    printf("%s ", demand);
    scanf("%256s", prompt);
    printf("\n");
    memcpy(answer, prompt, max_length);
    *(answer + max_length - 1) = '\0';
}

int menu_exit(void)
{
    printf("\nFermeture du menu...\n\n");
    return 0;
}

int menu_graph(void)
{
    print_graph(get_account_nodehead(), print_account_id);
    printf("\n");
    return 0;
}

int menu_account_add(void)
{
    char
        prmpt_account_name[32],
        prmpt_account_lastname[32],
        prmpt_account_password[64],
        prmpt_account_balance[10];

    ask("Quel est le prenom ?", prmpt_account_name, 32);
    ask("Quel est le nom de famille ?", prmpt_account_lastname, 32);
    ask("Quel est le mot de passe de l'utilisateur ?", prmpt_account_password, 64);
    ask("Quel est le montant ?", prmpt_account_balance, 10);

    double account_balance = strtod(prmpt_account_balance, NULL);

    unsigned int account_id =
        create_account(prmpt_account_name, prmpt_account_lastname, prmpt_account_password, account_balance)
            ->account_id;

    printf("\nLe compte [%d] a ete cree !\n\n", account_id);

    return 0;
}

int menu_account_remove(void)
{
    char input[32];
    ask("Veuillez saisir le numéro du compte :", input, 32);
    unsigned int account_id = atoi(input);

    if (close_account(account_id) != 0)
    {
        printf("Le compte [%d] n'a pas ete trouve!\n\n", account_id);
        return 1;
    }

    printf("Le compte [%d] a ete ferme !\n\n", account_id);
    return 0;
}

int menu_account_get(void)
{
    char input[32];
    ask("Veuillez saisir le numero du compte :", input, 32);
    unsigned int account_id = atoi(input);

    Account *account = get_account_from_id(account_id);

    if (account == NULL)
    {
        printf("Le compte [%d] n'a pas ete trouve\n", account_id);
        return 1;
    }

    printf("\n====================\n");
    printf("Identifiant du compte : %d\n", account->account_id);
    printf("Proprietaire du compte : %s %s\n", account->account_lastname, account->account_name);
    printf("Mot de passe : %s\n", account->password);
    printf("Solde actuel : %.2lf\n", account->balance);
    printf("====================\n\n");

    return 0;
}

int menu_account_balance(void)
{
    char input[32];
    ask("Veuillez saisir le numéro du compte :", input, 32);
    unsigned int account_id = atoi(input);

    Account *account = get_account_from_id(account_id);

    if (account == NULL)
    {
        printf("\nLe compte [%d] n'a pas ete trouve\n\n", account_id);
        return 1;
    }
    printf("\n%s %s : %lf\n\n", account->account_name, account->account_lastname, account->balance);
    return 0;
}

int menu_account_list(void)
{

    int n = get_account_nodehead()->total_node;
    if (n == 0)
    {
        printf("\nIl n'y a aucun compte enregistre a ce jour !\n\n");
        return -1;
    }

    printf("\nIl y a %d comptes enregistre.s e ce jour\n\n", n);

    Node *current = get_account_nodehead()->head;
    int i = 0;
    while (current != NULL && i < n)
    {
        GenericNode *g_node = (GenericNode *)current;
        Account *account = (Account *)g_node->data;

        printf("\n====================\n");
        printf("Identifiant du compte : %d\n", account->account_id);
        printf("Proprietaire du compte : %s %s\n", account->account_lastname, account->account_name);
        printf("Mot de passe : %s\n", account->password);
        printf("Solde actuel : %.2lf\n", account->balance);
        printf("====================\n\n");

        current = current->next;
        i++;
    }

    return 0;
}

int menu_account_transfert(void)
{
    char
        input_from[32],
        input_to[32],
        input_balance[10];

    ask("Veuillez saisir le numéro du compte à débiter :", input_from, 32);
    unsigned int from = atoi(input_from);
    ask("Veuillez saisir le numéro du compte à créditer :", input_to, 32);
    unsigned int to = atoi(input_to);
    ask("Quel est le montant ?", input_balance, 10);
    double account_balance = strtod(input_balance, NULL);

    Account
        *from_acc = get_account_from_id(from),
        *to_acc = get_account_from_id(to);

    account_balance = account_balance < 0 ? -account_balance : account_balance;
    from_acc->balance -= account_balance;
    to_acc->balance += account_balance;

    printf("Nouveaux montant des comptes :\n");

    printf("\t- Débiteur n° %d : %.3f€\n", from_acc->account_id, from_acc->balance);
    printf("\t+ Créditeur n° %d : %.3f€\n", to_acc->account_id, to_acc->balance);

    return 0;
}