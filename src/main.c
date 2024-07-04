#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bank.h"
#include "../include/dictionnary.h"

int main(void)
{
    if (initialize_bank_system() != 0)
    {
        printf("Erreur lors de l'initialisation du système bancaire !\n");
        return 1;
    }
    else
        printf("Initialisation du système bancaire terminée !\n");

    printf("\n");
    // Création de quelques comptes
    create_account("John Doe", 1000.0);
    create_account("Jane Smith", 2000.0);
    create_account("Bob Johnson", 500.0);

    // Recherche de comptes par nom du titulaire
    char search_name[32];
    printf("Entrez le nom du titulaire pour rechercher le compte : ");
    fgets(search_name, sizeof(search_name), stdin);
    search_name[strcspn(search_name, "\n")] = '\0'; // Supprimer le retour à la ligne de fgets

    Account *found_account = get_account(search_name);
    if (found_account != NULL)
    {
        printf("Compte trouvé :\n");
        printf("ID du compte : %d\n", found_account->account_id);
        printf("Titulaire du compte : %s\n", found_account->account_holder);
        printf("Solde du compte : %.2f\n", found_account->balance);
    }
    else
    {
        printf("Aucun compte trouvé pour le titulaire : %s\n", search_name);
    }

    // Suppression d'un compte par nom du titulaire
    char remove_name[32];
    printf("Entrez le nom du titulaire pour retirer le compte : ");
    fgets(remove_name, sizeof(remove_name), stdin);
    remove_name[strcspn(remove_name, "\n")] = '\0'; // Supprimer le retour à la ligne de fgets

    found_account = get_account(remove_name);
    if (found_account != NULL)
    {
        printf("Compte trouvé pour le titulaire %s a été fermé\n", remove_name);
        close_account(found_account->account_id);
    }
    else
    {
        printf("Aucun compte trouvé pour le titulaire : %s\n", remove_name);
    }

    if (shutdown_bank_system() != 0)
    {
        printf("Erreur lors de la fermeture du système bancaire !\n");
        return 1;
    }
    else
        printf("Fermeture du système bancaire terminée !\n");

    return 0;
}