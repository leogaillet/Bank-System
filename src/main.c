#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bank.h"
#include "../include/linkedlist.h"
#include "../include/menu.h"
#include "../include/types.h"

void menu(void);

int main(void)
{
    if (initialize_bank_system() != 0)
    {
        printf("Erreur lors de l'initialisation du systeme bancaire !\n");
        return 1;
    }
    else
        printf("Initialisation du systeme bancaire terminee !\n");

    menu();

    if (shutdown_bank_system() != 0)
    {
        printf("Erreur lors de la fermeture du systeme bancaire !\n");
        return 1;
    }
    else
        printf("Fermeture du systeme bancaire terminee !\n");

    return 0;
}

void menu(void)
{

    struct MenuCommand commands[] =
        {
            {"add", &menu_account_add},
            {"new", &menu_account_add},
            {"get", &menu_account_get},
            {"rm", &menu_account_remove},
            {"remove", &menu_account_remove},
            {"balance", &menu_account_balance},
            {"transfer", &menu_account_transfert},
            {"bal", &menu_account_balance},
            {"list", &menu_account_list},
            {"graph", &menu_graph},
            {"exit", &menu_exit}};
    const int commandlength = sizeof(commands) / sizeof(commands[0]);

    char input[32];
    do
    {
        ask("Veuillez saisir une commande :", input, 32);

        int found = 0;
        int i = 0;
        while (found == 0 && i < commandlength)
        {
            if (strcmp(input, commands[i].command_name) == 0)
            {
                found = 1;
                commands[i].menu_function();
            }
            i++;
        }

        if (found == 0)
        {
            printf("Veuillez saisir une commande valide : \n\t");
            for (int i = 0; i < commandlength; i++)
            {
                printf("%s ", commands[i].command_name);
            }
            printf("\n");
        }
    } while (strcmp(input, "exit") != 0);
}
