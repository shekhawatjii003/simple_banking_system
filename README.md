# simple_banking_system
Simple Command-Line Banking System in C
A console-based application written in C that simulates basic banking operations, including deposits, withdrawals, and transaction history, with data persistence to a file.

This project is a practical example of using fundamental C programming concepts such as structures, arrays, file I/O, and functions to create a functional application.
**DEMO OUTPU**T:-
===== Banking System Menu =====
1. Deposit Money
2. Withdraw Money
3. Show Mini Statement
4. Exit
===============================
Enter your choice: 1
Enter Account Number: 101
Enter Amount to Deposit: $500.50
SUCCESS: Amount $500.50 deposited. New Balance: $5500.50


===== Banking System Menu =====
1. Deposit Money
2. Withdraw Money
3. Show Mini Statement
4. Exit
===============================
Enter your choice: 3
Enter Account Number: 101

--- Mini Statement for Account No: 101 ---
Account Holder: Alice Johnson
Current Balance: $5500.50
----------------------------------------
Recent Transactions:
1. Type: Deposit    | Amount: $500.50
----------------------------------------
**Features**
Account Management: The system can manage multiple user accounts (up to 10 by default).

Deposit & Withdraw: Perform basic credit and debit transactions.

Mini Statement: View the recent transaction history for any account (up to the last 5 transactions).

Data Persistence: All account data and transaction history are saved to a binary file (accounts.dat) and automatically loaded when the program starts.

Error Handling: Includes basic checks for invalid user input, non-existent accounts, and insufficient funds.

Struct-based Design: Uses structs to cleanly organize Account and Transaction data.

**How It Works**
Data Structures
The program is built around two main structs:

Transaction: Holds the type (e.g., "Deposit") and amount of a single transaction.

Account: Contains the accountNumber, name, balance, and an array of Transaction structures to store the history.

Data Persistence
On exit (by choosing option 4), the program calls the saveData() function. This function writes the current state of all accounts from the accounts array into a binary file named accounts.dat.

When the program starts, the loadData() function is called. It checks if accounts.dat exists.

If it exists, it reads the data from the file into memory.

If it doesn't exist, it initializes the system with two default accounts.

Getting Started
To compile and run this project on your local machine, you will need a C compiler like GCC.

Prerequisites
A C compiler (GCC is recommended). You can install it on Linux with sudo apt-get install gcc or on Windows using MinGW.

Compilation & Execution
Save the Code: Save the code into a file named banking_system.c.

Open your terminal or command prompt and navigate to the directory where you saved the file.

Compile the code using the following command:
gcc banking_system.c -o banking_system
This command compiles the C source file and creates an executable file named banking_system.

Run the executable:

Bash

./banking_system
On Windows, you might just run it as:

Bash

banking_system.exe
The program will start, load or create account data, and display the main menu for you to interact with.
