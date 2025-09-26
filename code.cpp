#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

struct Product {
    string name;
    double price;
};

int main() {
    char choice;

    // Define product catalog
    vector<Product> catalog = {
        {"Shoes", 120.00}, {"T-shirt", 50.00}, {"Jeans", 90.00}, {"Jacket", 150.00},
        {"Backpack", 80.00}, {"Watch", 200.00}, {"Headphones", 180.00}, {"Smartphone", 1200.00},
        {"Laptop", 3500.00}, {"Mouse", 60.00}, {"Keyboard", 150.00}, {"Power Bank", 100.00},
        {"Water Bottle", 30.00}, {"Sunglasses", 70.00}, {"Perfume", 250.00}
    };

    // Main Menu UI
    do {
        cout << "======================================" << endl;
        cout << "       Welcome to E-Commerce Cart" << endl;
        cout << "======================================" << endl;

        // Display product catalog
        cout << "\nAvailable Products:\n";
        cout << "--------------------------------------" << endl;
        for (size_t i = 0; i < catalog.size(); i++) {
            cout << setw(2) << i + 1 << ". " << left << setw(20) << catalog[i].name
                 << " RM " << right << fixed << setprecision(2) << setw(8) << catalog[i].price << endl;
        }
        cout << "--------------------------------------" << endl;

        int numItems;
        cout << "Enter number of different products to buy: ";
        while (!(cin >> numItems) || numItems <= 0) {
            cout << "Invalid input! Please enter a positive integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        vector<string> chosenNames;
        vector<double> chosenPrices;

        for (int i = 0; i < numItems; i++) {
            int productChoice, quantity;
            cout << "Select product #" << (i + 1) << " (1-15): ";
            while (!(cin >> productChoice) || productChoice < 1 || productChoice > 15) {
                cout << "Invalid input! Please select between 1 and 15: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Enter quantity for " << catalog[productChoice - 1].name << ": ";
            while (!(cin >> quantity) || quantity <= 0) {
                cout << "Invalid input! Please enter a positive quantity: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            chosenNames.push_back(catalog[productChoice - 1].name + " x" + to_string(quantity));
            chosenPrices.push_back(catalog[productChoice - 1].price * quantity);
        }

        // Subtotal
        double subtotal = 0.0;
        for (double p : chosenPrices) subtotal += p;

        cout << "\nSubtotal: RM" << subtotal << endl;

        // Offer to add more goods
        char addMore;
        while (subtotal < 100) {
            cout << "Your subtotal is below RM100. Do you want to add more items for free shipping? (Y/N): ";
            cin >> addMore;
            if (addMore == 'Y' || addMore == 'y') {
                int productChoice, quantity;
                cout << "Select extra product (1-15): ";
                while (!(cin >> productChoice) || productChoice < 1 || productChoice > 15) {
                    cout << "Invalid input! Please select between 1 and 15: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cout << "Enter quantity for " << catalog[productChoice - 1].name << ": ";
                while (!(cin >> quantity) || quantity <= 0) {
                    cout << "Invalid input! Please enter a positive quantity: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                chosenNames.push_back(catalog[productChoice - 1].name + " x" + to_string(quantity));
                chosenPrices.push_back(catalog[productChoice - 1].price * quantity);
                subtotal += catalog[productChoice - 1].price * quantity;

                cout << "New Subtotal: RM" << subtotal << endl;
            } else break;
        }

        // Discount code
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string discountCode;
        cout << "Enter discount code (SAVE10, DISC20, FREESHIP, or press Enter to skip): ";
        getline(cin, discountCode);

        double discount = 0.0;
        bool freeShipping = false;

        if (discountCode == "SAVE10") discount = 10.0;
        else if (discountCode == "DISC20") discount = subtotal * 0.20;
        else if (discountCode == "FREESHIP") freeShipping = true;

        double discountedTotal = subtotal - discount;
        if (discountedTotal < 0) discountedTotal = 0;

        // Tax + Shipping
        double tax = discountedTotal * 0.06;
        double totalWithTax = discountedTotal + tax;
        double shippingFee = (totalWithTax < 100 && !freeShipping) ? 5.0 : 0.0;
        double finalTotal = totalWithTax + shippingFee;

        // Payment Method
        int paymentChoice;
        cout << "\nSelect Payment Method:\n1. Cash on Delivery\n2. Online Banking\n3. E-Wallet\nEnter choice (1-3): ";
        while (!(cin >> paymentChoice) || paymentChoice < 1 || paymentChoice > 3) {
            cout << "Invalid input! Please select 1, 2, or 3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        string paymentMethod = (paymentChoice == 1 ? "Cash on Delivery" :
                               paymentChoice == 2 ? "Online Banking" : "E-Wallet");

        // Print receipt
        cout << fixed << setprecision(2);
        cout << "\n===============================" << endl;
        cout << "         ORDER RECEIPT" << endl;
        cout << "===============================" << endl;
        for (size_t i = 0; i < chosenNames.size(); i++) {
            cout << left << setw(20) << chosenNames[i]
                 << " RM " << right << setw(8) << chosenPrices[i] << endl;
        }
        cout << "-------------------------------" << endl;
        cout << left << setw(20) << "Subtotal:" << " RM " << right << setw(8) << subtotal << endl;
        cout << left << setw(20) << "Discount:" << " RM " << right << setw(8) << -discount << endl;
        cout << left << setw(20) << "SST (6%):" << " RM " << right << setw(8) << tax << endl;
        cout << left << setw(20) << "Shipping:" << " RM " << right << setw(8) << shippingFee;
        if (shippingFee == 0) cout << " (Free shipping > RM100)";
        cout << endl;
        cout << "-------------------------------" << endl;
        cout << left << setw(20) << "Final Total:" << " RM " << right << setw(8) << finalTotal << endl;
        cout << left << setw(20) << "Payment Method:" << paymentMethod << endl;
        cout << "===============================" << endl;
        cout << "Thank you for shopping with us!" << endl;
        cout << "===============================\n" << endl;

        cout << "Do you want to shop again? (Y/N): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (choice == 'Y' || choice == 'y');

    cout << "Goodbye! Thank you for using our E-Commerce Cart." << endl;
    return 0;
