#include <iostream>
using namespace std;

// Product class
class Product {
private:
    int id;
    string name;
    double price;

public:
    Product() {} // Default constructor for array initialization
    Product(int pid, string pname, double pprice) : id(pid), name(pname), price(pprice) {}

    int getID() { return id; }
    string getName() { return name; }
    double getPrice() { return price; }

    void displayProduct() {
        cout << "Product ID: " << id << ", Name: " << name << ", Price: $" << price << endl;
    }
};

// Cart class
class Cart {
private:
    Product items[10]; // Array to hold products, max 10 items for simplicity
    int itemCount;

public:
    Cart() : itemCount(0) {}

    void addProduct(Product p) {
        items[itemCount] = p;
        itemCount++;
        cout << "Added to cart: " << p.getName() << endl;
    }

    double calculateTotal() {
        double total = 0;
        for (int i = 0; i < itemCount; i++) {
            total += items[i].getPrice();
        }
        return total;
    }

    void displayCart() {
        cout << "\nCart Items: \n";
        for (int i = 0; i < itemCount; i++) {
            items[i].displayProduct();
        }
    }
};

// User class
class User {
protected:
    string username;
    string email;

public:
    User(string uname, string uemail) : username(uname), email(uemail) {}

    virtual void displayTotalAmount(Cart& cart) {
        double total = cart.calculateTotal();
        cout << "User " << username << ": Total Amount: $" << total << endl;
    }

    virtual ~User() {}
};

// Premium User class
class PremiumUser : public User {
public:
    PremiumUser(string uname, string uemail) : User(uname, uemail) {}

    void displayTotalAmount(Cart& cart) override {
        double total = cart.calculateTotal();
        double discount = 0.10;
        double finalAmount = total - (total * discount);
        cout << "User " << username << " (Premium): Total after Discount: $" << finalAmount << endl;
    }
};

// Function to display available products
void displayProducts(Product products[], int size) {
    cout << "\nAvailable Products:\n";
    for (int i = 0; i < size; i++) {
        products[i].displayProduct();
    }
}

// Main function
int main() {
    // Create a list of products
    Product products[4] = {
        Product(1, "Laptop", 999.99),
        Product(2, "Smartphone", 499.99),
        Product(3, "Tablet", 299.99),
        Product(4, "Headphones", 199.99)
    };

    string userType, username, email;
    int productChoice;
    char moreItems;
    bool isPremium;

    // User type input
    cout << "Welcome to the Online Shopping System!\n";
    cout << "Are you a General User or Premium User? (Enter 'General' or 'Premium'): ";
    cin >> userType;

    // Collect user information
    cout << "Enter your name: ";
    cin.ignore(); // To ignore any leftover newline characters
    getline(cin, username);
    cout << "Enter your email: ";
    getline(cin, email);

    isPremium = (userType == "Premium");

    // Create user object based on user type
    User* user;
    if (isPremium) {
        user = new PremiumUser(username, email);
    } else {
        user = new User(username, email);
    }

    Cart userCart;
    
    // Shopping process
    do {
        displayProducts(products, 4);

        // Let user select a product
        cout << "\nEnter the Product ID to add to the cart: ";
        cin >> productChoice;

        // Add the selected product to the user's cart
        if (productChoice >= 1 && productChoice <= 4) {
            userCart.addProduct(products[productChoice - 1]);
        } else {
            cout << "Invalid Product ID. Please try again.\n";
        }

        // Ask if user wants to add more items
        cout << "Do you want to add more items to the cart? (y/n): ";
        cin >> moreItems;
    } while (moreItems == 'y' || moreItems == 'Y');

    // Display the final cart and total amount
    cout << "\nYour Cart:\n";
    userCart.displayCart();
    user->displayTotalAmount(userCart);

    // Cleanup dynamic memory
    delete user;

    return 0;
}
