#include <stdio.h>
#include "bank.h"

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

    if (shutdown_bank_system() != 0)
    {
        printf("Erreur lors de la fermeture du système bancaire !\n");
        return 1;
    }
    else
        printf("Fermeture du système bancaire terminée !\n");

    return 0;
}