let users = [];
let transactions = [];
let transactionHistory = [];

// Function to create users
function createUsers() {
    const numUsers = parseInt(document.getElementById('numUsers').value);
    if (isNaN(numUsers) || numUsers <= 0) {
        document.getElementById('userStatus').innerText = 'Please enter a valid number of users.';
        return;
    }
    users = Array.from({ length: numUsers }, (_, i) => `User ${i + 1}`);
    document.getElementById('userStatus').innerText = `${numUsers} users created.`;
    console.log("Users created:", users); // Debug
}

// Function to add a transaction
function addTransaction() {
    const lender = parseInt(document.getElementById('lender').value);
    const borrower = parseInt(document.getElementById('borrower').value);
    const amount = parseInt(document.getElementById('amount').value);

    if (isNaN(lender) || isNaN(borrower) || isNaN(amount) || lender < 1 || borrower < 1 || amount <= 0 || lender === borrower) {
        document.getElementById('transactionStatus').innerText = 'Please enter valid lender, borrower, and amount.';
        return;
    }

    transactionHistory.push([...transactions]); // Save state for undo
    transactions.push({ lender, borrower, amount });
    document.getElementById('transactionStatus').innerText = `Transaction added: User ${lender} lends ${amount} to User ${borrower}`;
    console.log("Transaction added:", transactions); // Debug
    renderGraph(transactions); // Update the transaction graph immediately after adding
}

// Function to display current transactions on the graph
function displayTransactions() {
    renderGraph(transactions); // Display all current transactions in the graph
    document.getElementById('transactionStatus').innerText = 'Displaying current transactions.';
    console.log("Displaying transactions:", transactions); // Debug
}

// Function to minimize transactions and display as a graph
function minimizeTransactions() {
    let netBalances = Array(users.length).fill(0);

    // Calculate net balance for each user
    transactions.forEach(({ lender, borrower, amount }) => {
        netBalances[lender - 1] += amount;
        netBalances[borrower - 1] -= amount;
    });

    let creditors = [];
    let debtors = [];
    let minimizedTransactions = [];

    // Separate creditors and debtors
    netBalances.forEach((balance, index) => {
        if (balance > 0) creditors.push({ id: index + 1, amount: balance });
        else if (balance < 0) debtors.push({ id: index + 1, amount: -balance });
    });

    // Minimize transactions by matching creditors with debtors
    let i = 0, j = 0;
    while (i < creditors.length && j < debtors.length) {
        const amount = Math.min(creditors[i].amount, debtors[j].amount);
        minimizedTransactions.push({ lender: creditors[i].id, borrower: debtors[j].id, amount });

        creditors[i].amount -= amount;
        debtors[j].amount -= amount;

        if (creditors[i].amount === 0) i++;
        if (debtors[j].amount === 0) j++;
    }

    // Render minimized transactions as a graph
    renderGraph(minimizedTransactions);
    document.getElementById('transactionStatus').innerText = 'Displaying minimized transactions.';
}

// Function to undo the last transaction
function undoLastTransaction() {
    if (transactionHistory.length > 0) {
        transactions = transactionHistory.pop();
        renderGraph(transactions); // Display updated transactions in graph
        document.getElementById('transactionStatus').innerText = 'Last transaction undone.';
    } else {
        document.getElementById('transactionStatus').innerText = 'No transactions to undo.';
    }
}

// Function to render graph of transactions using vis.js
function renderGraph(data) {
    const nodes = users.map((user, index) => ({ id: index + 1, label: user }));
    const edges = data.map(transaction => ({
        from: transaction.lender,
        to: transaction.borrower,
        label: `${transaction.amount}`,
        arrows: 'to'
    }));

    const container = document.getElementById('graph');
    const networkData = { nodes: new vis.DataSet(nodes), edges: new vis.DataSet(edges) };
    const options = { physics: false, edges: { color: 'gray', font: { align: 'middle' } } };

    new vis.Network(container, networkData, options);
    console.log("Graph rendered with data:", data); // Debug
}
