#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Transaction {
public:
    int id;
    float amount;
    int approvals;

    Transaction(int i, float a) {
        id = i;
        amount = a;
        approvals = 0;
    }
};

vector<Transaction> transactions;

// Save to file
void saveToFile() {
    ofstream file("data.txt");
    for (auto &t : transactions) {
        file << t.id << " " << t.amount << " " << t.approvals << endl;
    }
    file.close();
}

// Load from file
void loadFromFile() {
    ifstream file("data.txt");
    if (!file) return;

    Transaction t(0,0);
    while (file >> t.id >> t.amount >> t.approvals) {
        transactions.push_back(t);
    }
    file.close();
}

// Add transaction
void addTransaction() {
    float amount;
    cout << "Enter amount: ";
    cin >> amount;

    int id = transactions.size() + 1;
    Transaction t(id, amount);

    transactions.push_back(t);
    saveToFile();

    cout << "Transaction Added!\n";
}

// Approve transaction
void approveTransaction() {
    int id;
    cout << "Enter transaction ID: ";
    cin >> id;

    for (auto &t : transactions) {
        if (t.id == id) {
            t.approvals++;
            saveToFile();
            cout << "Approved!\n";
            return;
        }
    }

    cout << "Transaction not found!\n";
}

// Show transactions
void showTransactions() {
    cout << "\n--- Transactions ---\n";
    for (auto &t : transactions) {
        cout << "ID: " << t.id
             << " | Amount: " << t.amount
             << " | Approvals: " << t.approvals << endl;
    }
}

// Calculate credit score
void calculateScore() {
    int totalTx = transactions.size();
    int totalApproval = 0;

    for (auto &t : transactions) {
        totalApproval += t.approvals;
    }

    int score = 300 + (totalTx * 5) + (totalApproval * 10);

    if (score > 900) score = 900;

    cout << "\nYour Credit Score: " << score << endl;
}

int main() {
    loadFromFile();

    int choice;

    do {
        cout << "\n==== Credo Setu System ====\n";
        cout << "1. Add Transaction\n";
        cout << "2. Approve Transaction\n";
        cout << "3. Show Transactions\n";
        cout << "4. Credit Score\n";
        cout << "5. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addTransaction(); break;
            case 2: approveTransaction(); break;
            case 3: showTransactions(); break;
            case 4: calculateScore(); break;
            case 5: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}