### Fonctions publiques accessibles

#### Initialisation et Finalisation

```c
// Initialise le système bancaire
int initialize_bank_system(void);

// Libère les ressources allouées par le système bancaire
int shutdown_bank_system(void);

```

#### Gestion des comptes

```c
// Crée un nouveau compte bancaire
// Retourne le numéro de compte unique en cas de succès, -1 en cas d'erreur
int create_account(const char* account_holder, double initial_balance);

// Ferme un compte bancaire existant
// Retourne 0 en cas de succès, -1 en cas d'erreur
int close_account(int account_number);

```

#### Opérations de transations

```c
// Consulte le solde d'un compte bancaire
// Retourne le solde en cas de succès, -1 en cas d'erreur
double get_balance(int account_number);

// Dépose un montant sur un compte bancaire
// Retourne 0 en cas de succès, -1 en cas d'erreur
int deposit(int account_number, double amount);

// Retire un montant d'un compte bancaire
// Retourne 0 en cas de succès, -1 en cas d'erreur
int withdraw(int account_number, double amount);

// Transfère un montant d'un compte bancaire à un autre
// Retourne 0 en cas de succès, -1 en cas d'erreur
int transfer(int from_account_number, int to_account_number, double amount);

```

#### Historique des transations

```c

```





```c
#ifndef BANK_H
#define BANK_H

int initialize_bank_system(void);
int shutdown_bank_system(void);

int create_account(const char* account_holder, double initial_balance);
int close_account(int account_number);

double get_balance(int account_number);
int deposit(int account_number, double amount);
int withdraw(int account_number, double amount);
int transfer(int from_account_number, int to_account_number, double amount);

typedef struct {
    int transaction_id;
    int account_number;
    char type[10];
    double amount;
    char date[20];
} Transaction;

int get_transaction_history(int account_number, Transaction* transactions, int max_transactions);

#endif // BANK_H

```
