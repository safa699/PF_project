#include <iostream>
#include <string>
#include <cmath> // For rounding
using namespace std;

// Constants
const int MAX_TABLES = 10;
const int MAX_STAFF = 5;
const int MAX_ITEMS = 5;

// Data Structures
string staff[MAX_STAFF] = {"Alice", "Bob", "Charlie", "Daisy", "Eve"};
int tableStatus[MAX_TABLES] = {0,1,0,1}; // 0 = Available, 1 = Occupied
string inventory[MAX_ITEMS] = {"Burger", "Pizza", "Pasta", "Salad", "Drinks"};
int stock[MAX_ITEMS] = {10, 8, 12, 15, 20}; // Initial stock for each item
double prices[MAX_ITEMS] = {5.99, 8.99, 7.49, 4.99, 2.99};

// Function to display the menu
void displayMenu() {
    cout << "\n========== MENU ==========" << endl;
    for (int i = 0; i < MAX_ITEMS; i++) {
        cout << i + 1 << ". " << inventory[i] << " - $";
        cout << round(prices[i] * 100) / 100.0 << " (" << stock[i] << " available)" << endl;
    }
    cout << "===========================" << endl;
}

// Function to display the staff
void displayStaff() {
    cout << "\n========== STAFF ==========" << endl;
    for (int i = 0; i < MAX_STAFF; i++) {
        cout << i + 1 << ". " << staff[i] << endl;
    }
    cout << "===========================" << endl;
}

// Function to display table statuses
void displayTables() {
    cout << "\n========== TABLE STATUS ==========" << endl;
    for (int i = 0; i < MAX_TABLES; i++) {
        cout << "Table " << i + 1 << ": " << (tableStatus[i] == 0 ? "Available" : "Occupied") << endl;
    }
    cout << "===================================" << endl;
}

// Function to manage table occupancy
int chooseTable() 
{
    int tableNumber;
    while (true) 
	{
        cout << "Enter a table number (1-" << MAX_TABLES << "): ";
        cin >> tableNumber;
        if (tableNumber < 1 || tableNumber > MAX_TABLES) {
            cout << "Invalid table number. Try again." << endl;
        } 
		else if (tableStatus[tableNumber - 1] == 1) 
		{
            cout << "Table " << tableNumber << " is already occupied. Try another." << endl;
        } 
		else 
		{
            tableStatus[tableNumber - 1] = 1; // Mark as occupied
            cout << "Table " << tableNumber << " is now assigned to you." << endl;
            return tableNumber;
        }
    }
}

// Function to release a table
void releaseTable(int tableNumber) {
    tableStatus[tableNumber - 1] = 0; // Mark as available
    cout << "Table " << tableNumber << " is now available." << endl;
}

// Function to take an order
double takeOrder() {
    int choice, quantity;
    double total = 0.0;

    while (true) {
        displayMenu();
        cout << "Enter the item number to order (0 to finish): ";
        cin >> choice;

        if (choice == 0) {
            break; // Exit ordering
        } else if (choice < 1 || choice > MAX_ITEMS) {
            cout << "Invalid choice. Try again." << endl;
            continue;
        }

        cout << "Enter the quantity: ";
        cin >> quantity;

        // Check stock availability
        if (stock[choice - 1] < quantity) {
            cout << "Sorry, not enough stock available. Only " << stock[choice - 1] << " left." << endl;
        } else {
            // Update stock and calculate total
            stock[choice - 1] -= quantity;
            double itemTotal = prices[choice - 1] * quantity;
            total += itemTotal;
            cout << "Added to order. Subtotal: $" << round(total * 100) / 100.0 << endl;
        }
    }
    return total;
}

// Function to collect feedback
void collectFeedback() {
    int rating;
    cout << "\nPlease rate your experience (1-5): ";
    cin >> rating;

    if (rating >= 1 && rating <= 5) {
        cout << "Thank you for your feedback! You rated us " << rating << " stars." << endl;
    } else {
        cout << "Invalid rating. Feedback not recorded." << endl;
    }
}

// Main function
int main() {
    int tableNumber;
    double totalBill;

    cout << "Welcome to the Restaurant!" << endl;

    // Staff display
    displayStaff();

    // Table management
    displayTables();
    tableNumber = chooseTable();

    // Ordering process
    cout << "\nStart placing your order." << endl;
    totalBill = takeOrder();

    // Final bill
    cout << "\n========== BILL ==========" << endl;
    cout << "Total bill for Table " << tableNumber << ": $" << round(totalBill * 100) / 100.0 << endl;
    cout << "==========================" << endl;

    // Feedback collection
    collectFeedback();

    // Release table
    releaseTable(tableNumber);

    cout << "Thank you for visiting! Have a great day!" << endl;
    return 0;
}