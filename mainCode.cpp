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

// Cart class to handle products and their quantities
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

// User class with membership handling
class User {
private:
    string username;
    string email;
    bool isPremium;

public:
    User(string uname, string uemail, bool premium) : username(uname), email(uemail), isPremium(premium) {}

    void displayTotalAmount(Cart& cart) {
        double total = cart.calculateTotal();
        if (isPremium) {
            double discount = total * 0.10;
            total -= discount;
            cout << "User " << username << " (Premium): Total after discount: $" << total << endl;
        } else {
            cout << "User " << username << ": Total Amount: $" << total << endl;
        }
    }

    void toggleMembership() {
        isPremium = !isPremium;
        if (isPremium) {
            cout << "You are now a Premium User!\n";
        } else {
            cout << "You have canceled your Premium Membership.\n";
        }
    }
};

int main() {
    Product product1(1, "Laptop", 999.99);
    Product product2(2, "Smartphone", 499.99);
    Product product3(3, "Tablet", 299.99);
    Product product4(4, "Headphones", 199.99);

    // User input for account details
    string username, email, userType;
    cout << "Are you a General User or Premium User? (Enter 'General' or 'Premium'): ";
    cin >> userType;
    cout << "Enter your name: ";
    cin >> username;
    cout << "Enter your email: ";
    cin >> email;

    bool isPremium = (userType == "Premium");
    User user(username, email, isPremium);

    Cart userCart;
    char addMore = 'y';
    int productId, quantity;

    // Display available products
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
            cout << "Invalid Product ID.\n";
        }

        cout << "Do you want to add more items to the cart? (y/n): ";
        cin >> addMore;
    } while (addMore == 'y' || addMore == 'Y');

    // Display cart and total for the user
    userCart.displayCart();
    user.displayTotalAmount(userCart);

    // Ask to change membership status
    char changeMembership;
    cout << "\nDo you want to change your membership status? (y/n): ";
    cin >> changeMembership;

    if (changeMembership == 'y' || changeMembership == 'Y') {
        user.toggleMembership();
    }

    // Display total again after possible membership change
    user.displayTotalAmount(userCart);

    return 0;
}
