# Cash Flow Minimizer

## Overview

The **Cash Flow Minimizer** is a program designed to help individuals or groups of users manage and optimize their cash flow. It allows users to track transactions where one user lends money to another and then minimizes the number of transactions necessary by calculating the net balances of users and optimizing the flow of money. This project incorporates advanced algorithms like **Min-Cost Max-Flow** to reduce the number of debt transactions while maintaining the same overall financial outcome.

### Features:
- **Add Debt**: Users can add transactions where one user lends money to another.
- **Display Transactions**: View all current transactions between users.
- **Minimize Transactions**: The program minimizes transactions to optimize cash flow, reducing the total number of transactions.
- **Undo Last Transaction**: You can undo the most recent transaction added.
- **Graphical Visualization**: Transactions are visualized using an interactive graph to show the flow of money between users.
- **Optimized Flow Calculation**: The system minimizes the total flow while maintaining the same net results for all users.

### Technologies Used:
- **C++** for backend logic, including transaction management and the Min-Cost Max-Flow algorithm.
- **HTML/CSS** for creating the web interface.
- **JavaScript** to handle user interactions, manage state, and render the graph.
- **vis.js** for rendering dynamic and interactive graphs of transactions.

## Project Structure

### Backend (C++ Code)
- **main.cpp**: This file contains the core logic of the program, including user creation, debt management, transaction minimization, and the graph-based algorithm for minimizing cash flow.

### Frontend (Web Interface)
- **index.html**: This is the main HTML file that provides the structure for the web interface.
- **app.js**: Contains JavaScript to manage user interactions, add transactions, minimize transactions, and render graphs using `vis.js`.
- **style.css**: Optional CSS for styling the web page. This file can be modified for further customization of the web interface.

### Graph Visualization
- The program uses **vis.js** to generate interactive graphs. Users can visualize how money flows between borrowers and lenders and see how the system optimizes those flows.

## How to Run the Program

### Running the C++ Backend:

1. **Install a C++ Compiler**: If you don't already have a C++ compiler, you can install one like **GCC** or **Clang**.
2. **Compile the Program**:
    - Open a terminal or command prompt.
    - Navigate to the directory containing the C++ source code (`main.cpp`).
    - Run the following command to compile the program:
    ```bash
    g++ -o CashFlowMinimizer main.cpp
    ```
3. **Run the Program**:
    - After compiling, you can run the program with the following command:
    ```bash
    ./CashFlowMinimizer
    ```

4. **Functionality**:
    - The program will ask for the number of users. You’ll enter the number of users (e.g., 3).
    - Next, you'll be prompted to enter transactions, specifying the lender, borrower, and the amount of money being lent.
    - You can then display the transactions, minimize them, and view the optimized flow.
    - The program will output the minimized transaction costs and flow details.

### Running the Web Interface:

1. **Open the HTML file** (`index.html`) in any modern web browser to interact with the frontend interface.
2. **Input Data**:
    - Enter the number of users.
    - Add transactions by specifying lender, borrower, and amount.
3. **Interact with the Interface**:
    - **Display Transactions**: View the current list of transactions in a graphical format.
    - **Minimize Transactions**: Calculate the optimized transactions that minimize the overall flow.
    - **Undo Last Transaction**: Roll back the last transaction.
4. **Graphical Visualization**: The program uses **vis.js** to visualize the transactions and minimized transactions as a graph of users (nodes) and debt (edges).

## How It Works

### 1. Net Balance Calculation
The first step is to calculate the **net balance** for each user:
- A positive balance means the user is a **lender** (creditor).
- A negative balance means the user is a **borrower** (debtor).

Each transaction between a lender and borrower affects the users' net balances. For example, if **Alice** lends $50 to **Bob**, Alice's balance increases by $50, and Bob's balance decreases by $50.

### 2. Minimizing the Transactions
Once the net balances are calculated, the system minimizes the transactions by:
- Matching **creditors** (users with a positive balance) to **debtors** (users with a negative balance).
- Each creditor will lend money to a debtor in the smallest possible amount to balance their debts. This reduces the total number of transactions.
- The result is a set of minimized transactions that maintain the same total flow but with fewer transactions.

### 3. Min-Cost Max-Flow Algorithm
The **Min-Cost Max-Flow** algorithm is used to optimize the flow of money between users while minimizing transaction costs. The algorithm works by finding the least-cost path for transferring money from one user to another, and ensuring the flow is maximized while minimizing the cost.

### Example Scenario:

1. **Transaction 1**: Alice lends $50 to Bob.
2. **Transaction 2**: Bob lends $30 to Charlie.
3. **Transaction 3**: Charlie lends $20 to Alice.

After calculating the net balances:
- Alice: +$30 (Credit)
- Bob: -$50 (Debt)
- Charlie: +$20 (Credit)

The optimized set of transactions could be:
- Alice lends $30 to Bob, which fully settles Bob’s debt.
- Charlie lends $20 to Bob to fully settle Bob's remaining debt.

Thus, the system reduces the number of transactions to just two, minimizing the flow.

### Graph Visualization

The transactions and minimized transactions are rendered visually using **vis.js**:
- Users are represented as **nodes** in the graph.
- Transactions are represented as **edges** connecting the nodes, with labels showing the transaction amounts.
- Arrows indicate the direction of money flow (from lender to borrower).

## Example Usage

### C++ Example:

Here’s what the terminal output might look like:

```
------------------ Cash Flow Minimizer ------------------
Welcome to the Cash Flow Minimizer Program!
This program helps manage transactions and minimize cash flow using advanced graph algorithms.

Enter the number of users: 3
Enter name for User 1: Alice
Enter name for User 2: Bob
Enter name for User 3: Charlie

Enter the number of transactions: 2
Transaction 1:
Enter lender ID, borrower ID, and amount: 0 1 50
Transaction 2:
Enter lender ID, borrower ID, and amount: 1 2 30

------------------ Cash Flow Minimizer ------------------
1. Add Debt
2. Display Transactions
3. Display Minimized Transactions
4. Exit
Enter your choice: 3

Total Flow: 50
Total Minimized Cost: 50
```

### Frontend Web Example:

1. **Enter the number of users** (e.g., 3).
2. **Add transactions** (e.g., Alice lends 50 to Bob, Bob lends 30 to Charlie).
3. **Click on "Display Transactions"** to see all current transactions in a graph.
4. **Click on "Minimize Transactions"** to see the optimized set of transactions and view the minimized graph.
5. **Click on "Undo Last Transaction"** to undo any added transaction.

### Preview proof
You can see the proof in the index file

```

## Contribution Guidelines
1. **Fork** the repository.
2. **Clone** your forked repository to your local machine.
3. Create a new branch: `git checkout -b feature/your-feature-name`.
4. Make your changes.
5. **Commit** your changes: `git commit -am 'Add your changes'`.
6. **Push** to your branch: `git push origin feature/your-feature-name`.
7. **Create a Pull Request** from your branch.


## Contact Information

If you have any questions or suggestions, feel free to contact me at:
- **Email**:b23cm1028@iitj.ac.in , b23cm1027@iitj.ac.in , b23cm1029@iitj.ac.in , b23cm1018@iitj.ac.in

- **GitHub**:https://github.com/nirmalbi/DSA_Project.git

---

Thank you for using the **Cash Flow Minimizer**! We hope this tool helps you simplify and optimize your financial transactions.
```

### Key Enhancements:
1. **Extended Explanations**: Detailed sections on how the program works, including algorithm descriptions, examples, and graphs.
2. **Usage Examples**: Provided examples for both the C++ program and the web interface.
3. **Contributing**: Nishkarsh verma and Nirmal kumar godara has worked on backend & Parmar prerak and Arjun naik has worked on frontend
