#include <iostream>
#include <vector>
using namespace std;

// Product class
class Product {
private:
    int id;
    string name;
    double price;

public:
    // Constructor
    Product(int pid, string pname, double pprice) {
        id = pid;
        name = pname;
        price = pprice;
    }

    // Getter methods
    int getID() { return id; }
    string getName() { return name; }
    double getPrice() { return price; }

    // Display product details
    void displayProduct() {
        cout << "Product ID: " << id << ", Name: " << name << ", Price: $" << price << endl;
    }
};

// Cart class
class Cart {
private:
    vector<Product> items;  // List of products in the cart

public:
    // Add product to the cart
    void addProduct(Product p) {
        items.push_back(p);
        cout << "Added to cart: " << p.getName() << endl;
    }

    // Calculate the total price of products in the cart
    double calculateTotal() {
        double total = 0;
        for (Product p : items) {
            total += p.getPrice();
        }
        return total;
    }

    // Display all items in the cart
    void displayCart() {
        cout << "\nCart Items: \n";
        for (Product p : items) {
            p.displayProduct();
        }
    }
};

// Base User class
class User {
protected:
    string username;
    string email;

public:
    // Constructor
    User(string uname, string uemail) {
        username = uname;
        email = uemail;
    }

    // Virtual function for polymorphism (overriding in derived class)
    virtual void displayTotalAmount(Cart& cart) {
        double total = cart.calculateTotal();
        cout << "User " << username << " (General): Total Amount: $" << total << endl;
    }

    virtual ~User() {}  // Virtual destructor
};

// Derived PremiumUser class (Inheritance)
class PremiumUser : public User {
public:
    // Constructor
    PremiumUser(string uname, string uemail) : User(uname, uemail) {}

    // Override function for premium user
    void displayTotalAmount(Cart& cart) override {
        double total = cart.calculateTotal();
        double discount = 0.10;  // 10% discount for premium users
        double finalAmount = total - (total * discount);
        cout << "User " << username << " (Premium): Total Amount after Discount: $" << finalAmount << endl;
    }
};

// Main function
int main() {
    // Create some products
    Product product1(1, "Laptop", 999.99);
    Product product2(2, "Smartphone", 499.99);

    // Create a general user and a premium user
    User generalUser("John Doe", "john@example.com");
    PremiumUser premiumUser("Alice Smith", "alice@example.com");

    // Create a shopping cart for each user
    Cart generalCart;
    Cart premiumCart;

    // Add products to carts
    generalCart.addProduct(product1);
    generalCart.addProduct(product2);

    premiumCart.addProduct(product1);
    premiumCart.addProduct(product2);

    // Display cart items and total for general user
    cout << "\nGeneral User's Cart:\n";
    generalCart.displayCart();
    generalUser.displayTotalAmount(generalCart);

    // Display cart items and total for premium user
    cout << "\nPremium User's Cart:\n";
    premiumCart.displayCart();
    premiumUser.displayTotalAmount(premiumCart);

    return 0;
}
