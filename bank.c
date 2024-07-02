#include "bank.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int initialize_bank_system(void) {
    // Initialiser les ressources nécessaires
    return 0;
}

int shutdown_bank_system(void) {
    // Libérer les ressources allouées
    return 0;
}

int create_account(const char* account_holder, double initial_balance) {
    // Créer un compte bancaire
    return 0;
}

int close_account(int account_number) {
    // Fermer un compte bancaire
    return 0;
}

double get_balance(int account_number) {
    // Retourner le solde du compte
    return 0;
}

int deposit(int account_number, double amount) {
    // Déposer de l'argent sur un compte
    return 0;
}

int withdraw(int account_number, double amount) {
    // Retirer de l'argent d'un compte
    return 0;
}

int transfer(int from_account_number, int to_account_number, double amount) {
    // Transférer de l'argent entre comptes
    return 0;
}

int get_transaction_history(int account_number, Transaction* transactions, int max_transactions) {
    // Retourner l'historique des transactions
    return -1;
}
