#include <iostream>
using namespace std;

class Product {
private:
    int id;
    string name;
    double price;

public:
    Product(int pid, string pname, double pprice) : id(pid), name(pname), price(pprice) {}

    int getID() { return id; }
    string getName() { return name; }
    double getPrice() { return price; }

    void displayProduct() {
        cout << "Product ID: " << id << ", Name: " << name << ", Price: $" << price << endl;
    }
};

// Cart class to handle products
class Cart {
private:
    struct CartItem {
        Product product;
        int quantity;
        CartItem(Product p, int qty) : product(p), quantity(qty) {}
    };

    CartItem* items[10];
    int itemCount = 0;

public:
    void addProduct(Product p, int quantity) {
        items[itemCount] = new CartItem(p, quantity);
        itemCount++;
        cout << "Added " << p.getName() << " to cart." << endl;
    }

    double calculateTotal() {
        double total = 0;
        for (int i = 0; i < itemCount; i++) {
            total += items[i]->product.getPrice() * items[i]->quantity;
        }
        return total;
    }

    void displayCart() {
        cout << "\nYour Cart:\n";
        for (int i = 0; i < itemCount; i++) {
            cout << items[i]->quantity << " x ";
            items[i]->product.displayProduct();
        }
    }
};

// Base User class (for inheritance)
class User {
protected:
    string username;
    string email;

public:
    User(string uname, string uemail) : username(uname), email(uemail) {}

    // Virtual function for polymorphism
    virtual void displayTotalAmount(Cart& cart) {
        double total = cart.calculateTotal();
        cout << "User " << username << ": Total Amount: $" << total << endl;
    }

    virtual ~User() {}  // Virtual destructor
};

// Derived GeneralUser class
class GeneralUser : public User {
public:
    GeneralUser(string uname, string uemail) : User(uname, uemail) {}

    void displayTotalAmount(Cart& cart) override {
        double total = cart.calculateTotal();
        cout << "User " << username << " (General): Total Amount: $" << total << endl;
    }
};

// Derived PremiumUser class (10% discount)
class PremiumUser : public User {
private:
    double discountPercentage = 0.10;

public:
    PremiumUser(string uname, string uemail) : User(uname, uemail) {}

    void displayTotalAmount(Cart& cart) override {
        double total = cart.calculateTotal();
        double discount = total * discountPercentage;
        total -= discount;
        cout << "User " << username << " (Premium): Total after discount: $" << total << endl;
    }
};

int main() {
    // Creating products
    Product product1(1, "Laptop", 999.99);
    Product product2(2, "Smartphone", 499.99);
    Product product3(3, "Tablet", 299.99);
    Product product4(4, "Headphones", 199.99);

    // User input for account details
    string username, email, userType;
    cout << "Welcome to the Online Shopping System!" << endl;
    cout << "Are you a General User or Premium User? (Enter 'General' or 'Premium'): ";
    cin >> userType;
    cout << "Enter your name: ";
    cin >> username;
    cout << "Enter your email: ";
    cin >> email;

    User* user;
    if (userType == "Premium") {
        user = new PremiumUser(username, email);  // Premium user
    } else {
        user = new GeneralUser(username, email);  // General user
    }

    Cart userCart;
    char addMore = 'y';
    int productId, quantity;

    // Display available products once
    cout << "\nAvailable Products:\n";
    product1.displayProduct();
    product2.displayProduct();
    product3.displayProduct();
    product4.displayProduct();

    // Adding products to the cart
    do {
        cout << "\nEnter the Product ID to add to the cart: ";
        cin >> productId;

        if (productId == 1) {
            cout << "Enter quantity: ";
            cin >> quantity;
            userCart.addProduct(product1, quantity);
        } else if (productId == 2) {
            cout << "Enter quantity: ";
            cin >> quantity;
            userCart.addProduct(product2, quantity);
        } else if (productId == 3) {
            cout << "Enter quantity: ";
            cin >> quantity;
            userCart.addProduct(product3, quantity);
        } else if (productId == 4) {
            cout << "Enter quantity: ";
            cin >> quantity;
            userCart.addProduct(product4, quantity);
        } else {
            cout << "Invalid Product ID. Please try again.\n";
        }

        cout << "Do you want to add more items to the cart? (y/n): ";
        cin >> addMore;
    } while (addMore == 'y' || addMore == 'Y');

    // Display cart and total for the user
    userCart.displayCart();
    user->displayTotalAmount(userCart);

    delete user;  // Clean up memory
    return 0;
}
