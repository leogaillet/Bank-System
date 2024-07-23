#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/types.h"

// Pointeur de tête de la liste chaînee (dictionnaire)
Node *head = NULL;
unsigned int dict_size = 0;

Node *dict_get_node()
{
    return head;
}

unsigned int dict_length()
{
    return dict_size;
}

// Fonction pour ajouter un compte au dictionnaire
void dict_set(char *account_holder, Account *account)
{
    // Allouer de la memoire pour un nouveau nœud
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        return;
    }

    // Allouer de la memoire pour une nouvelle structure Account
    Account *new_account = (Account *)malloc(sizeof(Account));
    if (new_account == NULL)
    {
        free(new_node);
        return;
    }

    // Copier les donnees du compte dans la nouvelle structure Account
    new_account->account_id = account->account_id;
    strcpy(new_account->account_holder, account_holder);
    new_account->balance = account->balance;

    // Assigner la nouvelle structure Account au nœud
    new_node->account = new_account;
    new_node->next = NULL;

    // Inserer le nouveau nœud au debut de la liste chaînee
    if (head == NULL)
    {
        head = new_node;
    }
    else
    {
        new_node->next = head;
        head = new_node;
    }

    dict_size++;
}

// Fonction pour recuperer un compte a partir du nom du titulaire
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
    // Si aucun compte correspondant n'est trouve
    return NULL;
}

// Fonction pour recuperer un compte a partir de l'identifiant du compte
Account *dict_get_from_id(const int account_id)
{
    Node *current = head;
    while (current != NULL)
    {
        if (current->account->account_id == account_id)
        {
            return current->account;
        }
        current = current->next;
    }
    // Si aucun compte correspondant n'est trouve
    return NULL;
}

// Fonction pour retirer un compte a partir du nom du titulaire
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
                // Le compte a supprimer est en tête de liste
                head = current->next;
            }
            else
            {
                prev->next = current->next;
            }

            // Liberer la memoire allouee pour la structure Account et le nœud
            free(current->account);
            free(current);
            return;
        }

        prev = current;
        current = current->next;
        dict_size--;
    }

    // Si aucun compte correspondant n'est trouve
}

void dict_free(void)
{
    // Liberation de la memoire allouee pour les comptes restants
    Node *current = head;
    Node *next;
    while (current != NULL)
    {
        next = current->next;
        free(current->account); // Liberer la memoire de la structure Account
        free(current);          // Liberer la memoire du nœud
        current = next;
    }
}

/*

// Fonction principale pour tester l'utilisation du dictionnaire
int main()
{
    // Creation de quelques comptes
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
    search_name[strcspn(search_name, "\n")] = '\0'; // Supprimer le retour a la ligne de fgets

    Account *found_account = dict_get(search_name);
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

    dict_remove(remove_name);

    // Liberation de la memoire allouee pour les comptes restants
    Node *current = head;
    Node *next;
    while (current != NULL)
    {
        next = current->next;
        free(current->account); // Liberer la memoire de la structure Account
        free(current);          // Liberer la memoire du nœud
        current = next;
    }

    return 0;
}

*/

void parse_arr_to_dict(Account accounts[], int account_length, const int ACCOUNT_MAX_SIZE)
{
    for (int i = 0; i < account_length && i < ACCOUNT_MAX_SIZE; i++)
        dict_set(accounts[i].account_holder, &accounts[i]);
}
void parse_dict_do_arr(Account *accounts, int *account_length, const int ACCOUNT_MAX_SIZE, Node *node)
{
    int i = 0;

    while (node != NULL && i < ACCOUNT_MAX_SIZE)
    {
        strcpy(accounts[i].account_holder, node->account->account_holder);
        accounts[i].account_id = node->account->account_id;
        accounts[i].balance = node->account->balance;

        i++;
        node = node->next;
    }

    *account_length = i;
}