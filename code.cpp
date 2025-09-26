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

