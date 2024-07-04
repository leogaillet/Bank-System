#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/types.h"

// Pointeur de tête de la liste chaînée (dictionnaire)
Node *head = NULL;

// Fonction pour ajouter un compte au dictionnaire
void dict_set(char *account_holder, Account *account)
{
    // Allouer de la mémoire pour un nouveau nœud
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        printf("Erreur : Échec de l'allocation mémoire pour le nouveau nœud.\n");
        return;
    }

    // Allouer de la mémoire pour une nouvelle structure Account
    Account *new_account = (Account *)malloc(sizeof(Account));
    if (new_account == NULL)
    {
        printf("Erreur : Échec de l'allocation mémoire pour la nouvelle structure Account.\n");
        free(new_node);
        return;
    }

    // Copier les données du compte dans la nouvelle structure Account
    new_account->account_id = account->account_id;
    strcpy(new_account->account_holder, account_holder);
    new_account->balance = account->balance;

    // Assigner la nouvelle structure Account au nœud
    new_node->account = new_account;
    new_node->next = NULL;

    // Insérer le nouveau nœud au début de la liste chaînée
    if (head == NULL)
    {
        head = new_node;
    }
    else
    {
        new_node->next = head;
        head = new_node;
    }
}

// Fonction pour récupérer un compte à partir du nom du titulaire
Account *dict_get(char *account_holder)
{
    Node *current = head;
    while (current != NULL)
    {
        if (strcmp(current->account->account_holder, account_holder) == 0)
        {
            return current->account;
        }
        current = current->next;
    }
    // Si aucun compte correspondant n'est trouvé
    return NULL;
}

// Fonction pour retirer un compte à partir du nom du titulaire
void dict_remove(char *account_holder)
{
    Node *current = head;
    Node *prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->account->account_holder, account_holder) == 0)
        {
            if (prev == NULL)
            {
                // Le compte à supprimer est en tête de liste
                head = current->next;
            }
            else
            {
                prev->next = current->next;
            }

            // Libérer la mémoire allouée pour la structure Account et le nœud
            free(current->account);
            free(current);
            printf("Le compte pour %s a été retiré avec succès.\n", account_holder);
            return;
        }

        prev = current;
        current = current->next;
    }

    // Si aucun compte correspondant n'est trouvé
    printf("Aucun compte trouvé pour le titulaire : %s\n", account_holder);
}

void dict_free(void)
{
    // Libération de la mémoire allouée pour les comptes restants
    Node *current = head;
    Node *next;
    while (current != NULL)
    {
        next = current->next;
        free(current->account); // Libérer la mémoire de la structure Account
        free(current);          // Libérer la mémoire du nœud
        current = next;
    }
}

/*

// Fonction principale pour tester l'utilisation du dictionnaire
int main()
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

    // Libération de la mémoire allouée pour les comptes restants
    Node *current = head;
    Node *next;
    while (current != NULL)
    {
        next = current->next;
        free(current->account); // Libérer la mémoire de la structure Account
        free(current);          // Libérer la mémoire du nœud
        current = next;
    }

    return 0;
}

*/