#include <iostream>
#include <vector>
#include <stack>
#include <tuple>
#include <string>
#include <unordered_map>

using namespace std;

class CashFlowMinimizer {
public:
    void displayWelcomeMessage();
    void createUsers(vector<string>& users);
    void addDebt(vector<tuple<int, int, int>>& transactions, stack<vector<tuple<int, int, int>>>& transactionHistory);
    void displayTransactions(const vector<tuple<int, int, int>>& transactions);
    void undoLastTransaction(vector<tuple<int, int, int>>& transactions, stack<vector<tuple<int, int, int>>>& transactionHistory);
    void minimizeTransactions(const vector<tuple<int, int, int>>& transactions, const vector<string>& users);
    bool validateInput(int lender, int borrower, int amount);
    void displayMenu();
};

void CashFlowMinimizer::displayWelcomeMessage() {
    cout << "------------------ Cash Flow Minimizer ------------------\n";
    cout << "Welcome to the Cash Flow Minimizer Program!\n";
    cout << "This program helps manage transactions and minimize cash flow.\n";
}

void CashFlowMinimizer::createUsers(vector<string>& users) {
    int numUsers;
    cout << "Enter the number of users: ";
    cin >> numUsers;
    users.resize(numUsers);

    for (int i = 0; i < numUsers; ++i) {
        cout << "Enter name for User " << i << ": ";
        cin >> users[i];
    }
}

void CashFlowMinimizer::addDebt(vector<tuple<int, int, int>>& transactions, stack<vector<tuple<int, int, int>>>& transactionHistory) {
    int lender, borrower, amount;
    cout << "Enter lender ID, borrower ID, and amount: ";
    cin >> lender >> borrower >> amount;

    if (validateInput(lender, borrower, amount)) {
        transactionHistory.push(transactions);  // Save current state for undo functionality
        transactions.push_back(make_tuple(lender, borrower, amount));
    }
}

void CashFlowMinimizer::displayTransactions(const vector<tuple<int, int, int>>& transactions) {
    cout << "\nTransaction History:\n";
    for (const auto& transaction : transactions) {
        int lender = get<0>(transaction);
        int borrower = get<1>(transaction);
        int amount = get<2>(transaction);
        cout << "Lender " << lender << " lends " << amount << " to Borrower " << borrower << endl;
    }
}

void CashFlowMinimizer::undoLastTransaction(vector<tuple<int, int, int>>& transactions, stack<vector<tuple<int, int, int>>>& transactionHistory) {
    if (!transactionHistory.empty()) {
        transactions = transactionHistory.top();
        transactionHistory.pop();
        cout << "Last transaction undone.\n";
    } else {
        cout << "No transactions to undo.\n";
    }
}

bool CashFlowMinimizer::validateInput(int lender, int borrower, int amount) {
    if (lender < 0 || borrower < 0 || amount <= 0) {
        cout << "Invalid input: Lender and borrower IDs should be non-negative, and amount should be positive.\n";
        return false;
    }
    return true;
}

void CashFlowMinimizer::minimizeTransactions(const vector<tuple<int, int, int>>& transactions, const vector<string>& users) {
    int numUsers = users.size();
    vector<int> balance(numUsers, 0);

    // Step 1: Calculate net balance for each user
    for (const auto& transaction : transactions) {
        int lender = get<0>(transaction);
        int borrower = get<1>(transaction);
        int amount = get<2>(transaction);
        balance[lender] += amount;    // Lender gains
        balance[borrower] -= amount;  // Borrower owes
    }

    // Step 2: Separate users into creditors and debtors
    vector<pair<int, int>> creditors, debtors;
    for (int i = 0; i < numUsers; ++i) {
        if (balance[i] > 0) creditors.emplace_back(i, balance[i]);
        else if (balance[i] < 0) debtors.emplace_back(i, -balance[i]);
    }

    // Step 3: Minimize transactions by matching creditors with debtors
    vector<tuple<int, int, int>> minimizedTransactions;
    int i = 0, j = 0;
    while (i < creditors.size() && j < debtors.size()) {
        int creditor = creditors[i].first;
        int debtor = debtors[j].first;
        int amount = min(creditors[i].second, debtors[j].second);

        minimizedTransactions.push_back(make_tuple(debtor, creditor, amount));

        creditors[i].second -= amount;
        debtors[j].second -= amount;

        if (creditors[i].second == 0) i++;
        if (debtors[j].second == 0) j++;
    }

    // Step 4: Display minimized transactions
    cout << "\nMinimized Transactions:\n";
    for (const auto& transaction : minimizedTransactions) {
        int lender = get<1>(transaction);    // Lender's ID
        int borrower = get<0>(transaction);  // Borrower's ID
        int amount = get<2>(transaction);    // Amount to transfer
        cout << "User " << users[borrower] << " owes " << amount << " to User " << users[lender] << endl;
    }
}

void CashFlowMinimizer::displayMenu() {
    cout << "\n------------------ Cash Flow Minimizer ------------------\n";
    cout << "1. Add Debt\n";
    cout << "2. Display Transactions\n";
    cout << "3. Display Minimized Transactions\n";
    cout << "4. Undo Last Transaction\n";
    cout << "5. Display Transaction History\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    vector<string> users;
    vector<tuple<int, int, int>> transactions;
    stack<vector<tuple<int, int, int>>> transactionHistory;
    CashFlowMinimizer cfm;

    cfm.displayWelcomeMessage();
    cfm.createUsers(users);

    // Ask user for the number of transactions to enter
    int numTransactions;
    cout << "Enter the number of transactions: ";
    cin >> numTransactions;

    for (int i = 0; i < numTransactions; ++i) {
        cout << "Transaction " << (i + 1) << ":\n";
        cfm.addDebt(transactions, transactionHistory);
    }

    int choice;
    do {
        cfm.displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cfm.addDebt(transactions, transactionHistory);
                break;
            case 2:
                cfm.displayTransactions(transactions);
                break;
            case 3:
                cfm.minimizeTransactions(transactions, users);
                break;
            case 4:
                cfm.undoLastTransaction(transactions, transactionHistory);
                break;
            case 5:
                cfm.displayTransactions(transactions);
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 6);

    return 0;
}