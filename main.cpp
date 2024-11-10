#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

class CashFlowMinimizer {
public:
    void displayWelcomeMessage();
    void createUsers(vector<string>& users);
    void addDebt(vector<tuple<int, int, int>>& transactions);
    void displayTransactions(const vector<tuple<int, int, int>>& transactions);
    void minimizeTransactions(const vector<tuple<int, int, int>>& transactions, const vector<string>& users);
    void displayMenu();
    
private:
    bool validateInput(int lender, int borrower, int amount);
    bool spfa(int source, int sink, vector<int>& dist, vector<int>& parent, vector<vector<int>>& capacity, vector<vector<int>>& cost, int numUsers);
    void minCostMaxFlow(int source, int sink, vector<vector<int>>& capacity, vector<vector<int>>& cost, const vector<string>& users, int numUsers);
};

void CashFlowMinimizer::displayWelcomeMessage() {
    cout << "------------------ Cash Flow Minimizer ------------------\n";
    cout << "Welcome to the Cash Flow Minimizer Program!\n";
    cout << "This program helps manage transactions and minimize cash flow using advanced graph algorithms.\n";
}

void CashFlowMinimizer::createUsers(vector<string>& users) {
    int numUsers;
    cout << "Enter the number of users: ";
    cin >> numUsers;
    users.resize(numUsers);

    for (int i = 0; i < numUsers; ++i) {
        cout << "Enter name for User " << i + 1 << ": ";
        cin >> users[i];
    }
}

void CashFlowMinimizer::addDebt(vector<tuple<int, int, int>>& transactions) {
    int lender, borrower, amount;
    cout << "Enter lender ID, borrower ID, and amount: ";
    cin >> lender >> borrower >> amount;

    if (validateInput(lender, borrower, amount)) {
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

bool CashFlowMinimizer::validateInput(int lender, int borrower, int amount) {
    if (lender < 0 || borrower < 0 || amount <= 0) {
        cout << "Invalid input: Lender and borrower IDs should be non-negative, and amount should be positive.\n";
        return false;
    }
    return true;
}

bool CashFlowMinimizer::spfa(int source, int sink, vector<int>& dist, vector<int>& parent, vector<vector<int>>& capacity, vector<vector<int>>& cost, int numUsers) {
    vector<bool> inQueue(numUsers, false);
    dist.assign(numUsers, INT_MAX);
    parent.assign(numUsers, -1);

    dist[source] = 0;
    queue<int> q;
    q.push(source);
    inQueue[source] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = false;

        for (int v = 0; v < numUsers; ++v) {
            if (capacity[u][v] > 0 && dist[u] + cost[u][v] < dist[v]) {
                dist[v] = dist[u] + cost[u][v];
                parent[v] = u;
                if (!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = true;
                }
            }
        }
    }
    return dist[sink] < INT_MAX;
}

void CashFlowMinimizer::minCostMaxFlow(int source, int sink, vector<vector<int>>& capacity, vector<vector<int>>& cost, const vector<string>& users, int numUsers) {
    int totalFlow = 0;
    int totalCost = 0;
    
    vector<int> dist(numUsers), parent(numUsers);
    
    while (spfa(source, sink, dist, parent, capacity, cost, numUsers)) {
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, capacity[u][v]);
        }
        
        // Update capacities and total cost
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= pathFlow;
            capacity[v][u] += pathFlow;
            totalCost += pathFlow * cost[u][v];
        }
        totalFlow += pathFlow;
    }

    cout << "\nTotal Flow: " << totalFlow << "\n";
    cout << "Total Minimized Cost: " << totalCost << "\n";
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

    // Step 2: Build a graph and apply Min-Cost Max-Flow algorithm
    vector<vector<int>> capacity(numUsers, vector<int>(numUsers, 0));
    vector<vector<int>> cost(numUsers, vector<int>(numUsers, 0));

    // Create a flow network: capacity and cost
    for (int i = 0; i < numUsers; ++i) {
        for (int j = 0; j < numUsers; ++j) {
            if (i != j && balance[i] > 0 && balance[j] < 0) {
                capacity[i][j] = abs(balance[j]);
                cost[i][j] = 1;  // You can change this to be more realistic
            }
        }
    }

    // Apply Min-Cost Max-Flow to minimize the transactions
    int source = 0;
    int sink = numUsers - 1;
    minCostMaxFlow(source, sink, capacity, cost, users, numUsers);
}

void CashFlowMinimizer::displayMenu() {
    cout << "\n------------------ Cash Flow Minimizer ------------------\n";
    cout << "1. Add Debt\n";
    cout << "2. Display Transactions\n";
    cout << "3. Display Minimized Transactions\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    vector<string> users;
    vector<tuple<int, int, int>> transactions;
    CashFlowMinimizer cfm;

    cfm.displayWelcomeMessage();
    cfm.createUsers(users);

    int numTransactions;
    cout << "Enter the number of transactions: ";
    cin >> numTransactions;

    for (int i = 0; i < numTransactions; ++i) {
        cout << "Transaction " << (i + 1) << ":\n";
        cfm.addDebt(transactions);
    }

    int choice;
    do {
        cfm.displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cfm.addDebt(transactions);
                break;
            case 2:
                cfm.displayTransactions(transactions);
                break;
            case 3:
                cfm.minimizeTransactions(transactions, users);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}
