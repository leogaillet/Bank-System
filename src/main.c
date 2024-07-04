#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bank.h"
#include "../include/dictionnary.h"

int main(void)
{
    // Création de quelques comptes
    Account acc1 = {1, "John Doe", 1000.0};
    Account acc2 = {2, "Jane Smith", 2000.0};
    Account acc3 = {3, "Bob Johnson", 500.0};

    // Ajout des comptes au dictionnaire
    dict_set(acc1.account_holder, &acc1);
    dict_set(acc2.account_holder, &acc2);
    dict_set(acc3.account_holder, &acc3);

    // Recherche de comptes par nom du titulaire
    char search_name[32];
    printf("Entrez le nom du titulaire pour rechercher le compte : ");
    fgets(search_name, sizeof(search_name), stdin);
    search_name[strcspn(search_name, "\n")] = '\0'; // Supprimer le retour à la ligne de fgets

    Account *found_account = dict_get(search_name);
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

    dict_remove(remove_name);

    dict_free();

    if (initialize_bank_system() != 0)
    {
        printf("Erreur lors de l'initialisation du système bancaire !\n");
        return 1;
    }
    else
        printf("Initialisation du système bancaire terminée !\n");

    printf("\n");

    if (shutdown_bank_system() != 0)
    {
        printf("Erreur lors de la fermeture du système bancaire !\n");
        return 1;
    }
    else
        printf("Fermeture du système bancaire terminée !\n");

    return 0;
}