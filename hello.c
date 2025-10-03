#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ACCOUNTS 10
#define MAX_TRANSACTIONS 5

typedef struct {
    char type[20];
    float amount;
} Transaction;

typedef struct {
    int accountNumber;
    char name[50];
    float balance;
    Transaction history[MAX_TRANSACTIONS];
    int transactionCount;
} Account;

Account accounts[MAX_ACCOUNTS];
int numAccounts = 0;

void saveData();
void loadData();
void addTransaction(Account* acc, const char* type, float amount);
void deposit(int accNum, float amount);
void withdraw(int accNum, float amount);
void printMiniStatement(int accNum);

int main() {
    int choice;
    int accNum;
    float amount;

    loadData();

    while (1) {
        printf("\n\n===== Banking System Menu =====\n");
        printf("1. Deposit Money\n");
        printf("2. Withdraw Money\n");
        printf("3. Show Mini Statement\n");
        printf("4. Exit\n");
        printf("===============================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Account Number: ");
                scanf("%d", &accNum);
                printf("Enter Amount to Deposit: $");
                scanf("%f", &amount);
                if (amount <= 0) {
                    printf("ERROR: Deposit amount must be positive.\n");
                } else {
                    deposit(accNum, amount);
                }
                break;
            case 2:
                printf("Enter Account Number: ");
                scanf("%d", &accNum);
                printf("Enter Amount to Withdraw: $");
                scanf("%f", &amount);
                 if (amount <= 0) {
                    printf("ERROR: Withdrawal amount must be positive.\n");
                } else {
                    withdraw(accNum, amount);
                }
                break;
            case 3:
                printf("Enter Account Number: ");
                scanf("%d", &accNum);
                printMiniStatement(accNum);
                break;
            case 4:
                saveData();
                printf("\nThank you for using our banking system!\n");
                exit(0);
            default:
                printf("\nInvalid choice. Please select an option from 1-4.\n");
        }
    }
    return 0;
}

void saveData() {
    FILE *file = fopen("accounts.dat", "wb");
    if (file == NULL) {
        printf("FATAL ERROR: Could not open data file for saving.\n");
        return;
    }
    fwrite(&numAccounts, sizeof(int), 1, file);
    fwrite(accounts, sizeof(Account), numAccounts, file);
    fclose(file);
    printf("Data saved successfully.\n");
}

void loadData() {
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL) {
        printf("No existing data file found. Creating default accounts...\n");
        numAccounts = 2;
        accounts[0] = (Account){101, "Alice Johnson", 5000.0, {}, 0};
        accounts[1] = (Account){102, "Bob Williams", 3500.0, {}, 0};
        return;
    }
    fread(&numAccounts, sizeof(int), 1, file);
    fread(accounts, sizeof(Account), numAccounts, file);
    fclose(file);
    printf("Account data loaded successfully.\n");
}

void addTransaction(Account* acc, const char* type, float amount) {
    if (acc->transactionCount == MAX_TRANSACTIONS) {
        for (int i = 0; i < MAX_TRANSACTIONS - 1; i++) {
            acc->history[i] = acc->history[i + 1];
        }
        acc->transactionCount--;
    }

    strcpy(acc->history[acc->transactionCount].type, type);
    acc->history[acc->transactionCount].amount = amount;
    acc->transactionCount++;
}

void deposit(int accNum, float amount) {
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accNum) {
            accounts[i].balance += amount;
            addTransaction(&accounts[i], "Deposit", amount);
            printf("SUCCESS: Amount $%.2f deposited. New Balance: $%.2f\n", amount, accounts[i].balance);
            return;
        }
    }
    printf("ERROR: Account number %d not found.\n", accNum);
}

void withdraw(int accNum, float amount) {
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accNum) {
            if (accounts[i].balance >= amount) {
                accounts[i].balance -= amount;
                addTransaction(&accounts[i], "Withdrawal", amount);
                printf("SUCCESS: Amount $%.2f withdrawn. New Balance: $%.2f\n", amount, accounts[i].balance);
            } else {
                printf("ERROR: Insufficient balance. Available: $%.2f, Requested: $%.2f\n", accounts[i].balance, amount);
            }
            return;
        }
    }
    printf("ERROR: Account number %d not found.\n", accNum);
}

void printMiniStatement(int accNum) {
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accNum) {
            printf("\n--- Mini Statement for Account No: %d ---\n", accounts[i].accountNumber);
            printf("Account Holder: %s\n", accounts[i].name);
            printf("Current Balance: $%.2f\n", accounts[i].balance);
            printf("----------------------------------------\n");
            
            if (accounts[i].transactionCount == 0) {
                printf("No transaction history available.\n");
            } else {
                printf("Recent Transactions:\n");
                for (int j = 0; j < accounts[i].transactionCount; j++) {
                    printf("%d. Type: %-10s | Amount: $%.2f\n", j + 1, accounts[i].history[j].type, accounts[i].history[j].amount);
                }
            }
            printf("----------------------------------------\n");
            return;
        }
    }
    printf("ERROR: Account number %d not found.\n", accNum);
}