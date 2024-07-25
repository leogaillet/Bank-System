#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bank.h"
#include "../include/linkedlist.h"
#include "../include/menu.h"

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
    char input[99];
    do
    {
        printf("Veuillez saisir une commande : ");
        scanf("%99s", input);

        if (strcmp(input, "help") == 0)
        {
        }
        else if (strcmp(input, "stop") == 0)
        {
        }
        else if (strcmp(input, "list") == 0)
            menu_account_list();

        else if (strcmp(input, "new") == 0)
            menu_account_add();

        else if (strcmp(input, "remove") == 0)
            menu_account_remove();

        else if (strcmp(input, "balance") == 0)
        {
        }
        else if (strcmp(input, "account") == 0)
            menu_account_get();
        else if (strcmp(input, "transactions") == 0)
        {
        }
        else
        {
            printf("Commande introuvable\n");
        }
    } while (strcmp(input, "stop") != 0);
}

/*

    // Creation de quelques comptes
    create_account("John Doe", 1000.0);
    create_account("Jane Smith", 2000.0);
    create_account("Bob Johnson", 500.0);

    // Recherche de comptes par nom du titulaire
    char search_name[32];
    printf("Entrez le nom du titulaire pour rechercher le compte : ");
    fgets(search_name, sizeof(search_name), stdin);
    search_name[strcspn(search_name, "\n")] = '\0'; // Supprimer le retour a la ligne de fgets

    Account *found_account = get_account(search_name);
    if (found_account != NULL)
    {
        printf("Compte trouve :\n");
        printf("ID du compte : %d\n", found_account->account_id);
        printf("Titulaire du compte : %s\n", found_account->account_holder);
        printf("Solde du compte : %.2f\n", found_account->balance);
    }
    else
    {
        printf("Aucun compte trouve pour le titulaire : %s\n", search_name);
    }

    // Suppression d'un compte par nom du titulaire
    char remove_name[32];
    printf("Entrez le nom du titulaire pour retirer le compte : ");
    fgets(remove_name, sizeof(remove_name), stdin);
    remove_name[strcspn(remove_name, "\n")] = '\0'; // Supprimer le retour a la ligne de fgets

    found_account = get_account(remove_name);
    if (found_account != NULL)
    {
        printf("Compte trouve pour le titulaire %s a ete ferme\n", remove_name);
        close_account(found_account->account_id);
    }
    else
    {
        printf("Aucun compte trouve pour le titulaire : %s\n", remove_name);
    }

*/