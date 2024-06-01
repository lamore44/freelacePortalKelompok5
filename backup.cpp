#include <iostream>
#include <string>
using namespace std;

struct Service {
    string title;
    string description;
    int price;
};

struct Order {
    string serviceTitle;
    string orderDescription;
    string username;
    int price;
    bool isCompleted;
    bool isCanceled;
};

void menuFreelancer();
void menuUser();
void topUp();
void order();
void addService();
void deleteService();
void viewProfile();
void displayServices();
void viewOrders();
void cancelOrder();
void completeOrder();

struct User {
    string username;
    string password;
    int balance;
} currentUser;

Service* services[100];
Order* orders[100];
int serviceCount = 0;
int orderCount = 0;

int main() {
    string username, password;
    int choice;

    while (true) {
        cout << "1. Register\n2. Login\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            currentUser = {username, password, 0};
            cout << "Registration successful.\n";
        } else if (choice == 2) {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            if (username == currentUser.username && password == currentUser.password) {
                cout << "Login successful.\n";
                break;
            } else {
                cout << "Invalid credentials.\n";
            }
        }
    }

    while (true) {
        cout << "1. Freelancer Menu\n2. User Menu\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            menuFreelancer();
        } else if (choice == 2) {
            menuUser();
        }
    }

    return 0;
}

void menuFreelancer() {
    int choice;
    while (true) {
        cout << "1. View Profile\n2. View Orders\n3. Add Service\n4. Delete Service\n5. Complete Order\n6. Cancel Order\n7. Logout\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            viewProfile();
        } else if (choice == 2) {
            viewOrders();
        } else if (choice == 3) {
            addService();
        } else if (choice == 4) {
            deleteService();
        } else if (choice == 5) {
            completeOrder();
        } else if (choice == 6) {
            cancelOrder();
        } else if (choice == 7) {
            break;
        }
    }
}

void menuUser() {
    int choice;
    while (true) {
        cout << "1. Top Up\n2. Place Order\n3. View Profile\n4. Logout\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            topUp();
        } else if (choice == 2) {
            order();
        } else if (choice == 3) {
            viewProfile();
        } else if (choice == 4) {
            break;
        }
    }
}

void topUp() {
    int amount;
    cout << "Enter amount to top-up (100k, 500k, 1jt, 2jt): ";
    cin >> amount;
    currentUser.balance += amount;
    cout << "Top-up successful. Current balance: " << currentUser.balance << endl;
}

void order() {
    displayServices();
    if (serviceCount == 0) {
        cout << "No services available.\n";
        return;
    }
    
    int serviceIndex;
    cout << "Enter the number of the service to order: ";
    cin >> serviceIndex;
    
    if (serviceIndex < 1 || serviceIndex > serviceCount) {
        cout << "Invalid service number.\n";
        return;
    }

    Service* selectedService = services[serviceIndex - 1];
    cout << "You have selected: " << selectedService->title << "\n";
    cout << "Enter a description for your order: ";
    cin.ignore();
    string orderDescription;
    getline(cin, orderDescription);
    
    if (currentUser.balance < selectedService->price) {
        cout << "Insufficient balance. Order failed.\n";
        return;
    }

    currentUser.balance -= selectedService->price;
    
    // Record the order
    Order* newOrder = new Order;
    newOrder->serviceTitle = selectedService->title;
    newOrder->orderDescription = orderDescription;
    newOrder->username = currentUser.username;
    newOrder->price = selectedService->price;
    newOrder->isCompleted = false;
    newOrder->isCanceled = false;
    orders[orderCount++] = newOrder;
    
    cout << "Order successful. Current balance: " << currentUser.balance << endl;
}

void addService() {
    if (serviceCount >= 100) {
        cout << "Service limit reached.\n";
        return;
    }

    Service* newService = new Service;
    cout << "Enter service title: ";
    cin.ignore();
    getline(cin, newService->title);
    cout << "Enter service description: ";
    getline(cin, newService->description);
    cout << "Enter service price: ";
    cin >> newService->price;
    services[serviceCount++] = newService;
    cout << "Service added: " << newService->title << endl;
}

void deleteService() {
    displayServices();
    if (serviceCount == 0) {
        cout << "No services available to delete.\n";
        return;
    }
    
    int serviceIndex;
    cout << "Enter the number of the service to delete: ";
    cin >> serviceIndex;
    
    if (serviceIndex < 1 || serviceIndex > serviceCount) {
        cout << "Invalid service number.\n";
        return;
    }

    // Check if the service has any active orders
    bool hasOrders = false;
    for (int i = 0; i < orderCount; ++i) {
        if (orders[i]->serviceTitle == services[serviceIndex - 1]->title && !orders[i]->isCompleted && !orders[i]->isCanceled) {
            hasOrders = true;
            break;
        }
    }
    
    if (hasOrders) {
        cout << "Cannot delete service. There are active orders for this service.\n";
        return;
    }

    delete services[serviceIndex - 1];

    for (int i = serviceIndex - 1; i < serviceCount - 1; ++i) {
        services[i] = services[i + 1];
    }

    serviceCount--;
    cout << "Service deleted successfully.\n";
}

void viewProfile() {
    cout << "Username: " << currentUser.username << "\nBalance: " << currentUser.balance << endl;
}

void displayServices() {
    if (serviceCount == 0) {
        cout << "No services available.\n";
        return;
    }

    for (int i = 0; i < serviceCount; ++i) {
        cout << i + 1 << ". " << services[i]->title << " - " << services[i]->description << " - " << services[i]->price << endl;
    }
}

void viewOrders() {
    if (orderCount == 0) {
        cout << "No orders available.\n";
        return;
    }

    for (int i = 0; i < orderCount; ++i) {
        cout << i + 1 << ". " << orders[i]->serviceTitle << " - " << orders[i]->orderDescription << " by " << orders[i]->username 
             << " - " << orders[i]->price;
        if (orders[i]->isCompleted) {
            cout << " (Completed)";
        } else if (orders[i]->isCanceled) {
            cout << " (Canceled)";
        }
        cout << endl;
    }
}

void cancelOrder() {
    viewOrders();
    if (orderCount == 0) {
        cout << "No orders available to cancel.\n";
        return;
    }

    int orderIndex;
    cout << "Enter the number of the order to cancel: ";
    cin >> orderIndex;

    if (orderIndex < 1 || orderIndex > orderCount) {
        cout << "Invalid order number.\n";
        return;
    }

    Order* selectedOrder = orders[orderIndex - 1];

    if (selectedOrder->isCompleted) {
        cout << "Order is already completed and cannot be canceled.\n";
        return;
    }

    selectedOrder->isCanceled = true;

    // Find the user who placed the order and refund the balance
    if (selectedOrder->username == currentUser.username) {
        currentUser.balance += selectedOrder->price;
    }

    cout << "Order canceled successfully. The customer has been refunded.\n";
}

void completeOrder() {
    viewOrders();
    if (orderCount == 0) {
        cout << "No orders available to complete.\n";
        return;
    }

    int orderIndex;
    cout << "Enter the number of the order to complete: ";
    cin >> orderIndex;

    if (orderIndex < 1 || orderIndex > orderCount) {
        cout << "Invalid order number.\n";
        return;
    }

    Order* selectedOrder = orders[orderIndex - 1];

    if (selectedOrder->isCanceled) {
        cout << "Order is canceled and cannot be completed.\n";
        return;
    }

    selectedOrder->isCompleted = true;

    cout << "Order completed successfully. The customer has been notified.\n";
}
