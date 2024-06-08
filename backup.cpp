#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
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

void banner();
void firstInterface();
void secondInterface();
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
void registerUser();
void login();
struct User {
    string username;
    string password;
    int balance;
} currentUser;

Service* services[100];
Order* orders[100];
int serviceCount = 0;
int orderCount = 0;
string username, password;
int choice;

int main() {
    firstInterface();
    return 0;
}

void firstInterface(){
    int numItem = 3, selItem = 0;
    while (true) {
        system("cls");
        banner();
        for(int i = 0; i < numItem; ++i){
            if(i == selItem){
                cout << "\033[35m";
            }else{
                cout << "\033[0m";
            }
            if (i == 0){
                cout << "||======================||\n||        REGISTER      ||\n||======================||\n";
            }else if (i == 1){
                cout << "||======================||\n||         LOGIN        ||\n||======================||\n";
            }else if (i == 2){
                cout << "||======================||\n||          EXIT        ||\n||======================||\n";
            }
            if (i == numItem-1){
                cout << "\033[0m";
            }
        }
        int key = getch();
        if(key == 72){
            selItem = (selItem + numItem - 1) % numItem;
        }else if(key == 80){
            selItem = (selItem + 1) % numItem;
        }else if(key == 13){
            if(selItem == numItem-1){
                return;
            }else{
                if(selItem == 0){
                    registerUser();
                }else if(selItem == 1){
                    login();
                }else if(selItem == 2){
                    break;
                }
            }
        }
    }
}
void secondInterface(){
    int numItem = 3, selItem = 0;
    while (true) {
        system("cls");
        banner();
        for(int i = 0; i < numItem; ++i){
            if(i == selItem){
                cout << "\033[34m";
            }else{
                cout << "\033[0m";
            }
            if (i == 0){
                cout << "||======================||\n||       FREELANCER     ||\n||======================||\n";
            }else if (i == 1){
                cout << "||======================||\n||          USER        ||\n||======================||\n";
            }else if (i == 2){
                cout << "||======================||\n||         LOG-OUT      ||\n||======================||\n";
            }
            if (i == numItem-1){
                cout << "\033[0m";
            }
        }
        int key = getch();
        if(key == 72){
            selItem = (selItem + numItem - 1) % numItem;
        }else if(key == 80){
            selItem = (selItem + 1) % numItem;
        }else if(key == 13){
            if(selItem == numItem-1){
                return;
            }else{
                if(selItem == 0){
                    menuFreelancer();
                }else if(selItem == 1){
                   menuUser();
                }else if(selItem == 2){
                    firstInterface();
                }
            }
        }
    }
}
void registerUser(){
    system("cls");
    cout << "||======================||\n||        REGISTER      ||\n||======================||\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    currentUser = {username, password, 0};
    cout << "Registration successful.\n";
    system("pause");
}
void login(){
    system("cls");
    cout << "||======================||\n||         LOGIN        ||\n||======================||\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    if (username == currentUser.username && password == currentUser.password) {
        cout << "Login successful.\n";
        secondInterface();
    } else {
        cout << "Invalid credentials.\n";
    }
    system("pause");
}
void banner(){
    cout << R"(
      ________  _______   _______  ___      ___  __     ______    _______  
 /"       )/"     "| /"      \|"  \    /"  ||" \   /" _  "\  /"     "| 
(:   \___/(: ______)|:        |\   \  //  / ||  | (: ( \___)(: ______) 
 \___  \   \/    |  |_____/   ) \\  \/. ./  |:  |  \/ \      \/    |   
  __/  \\  // ___)_  //      /   \.    //   |.  |  //  \ _   // ___)_  
 /" \   :)(:      "||:  __   \    \\   /    /\  |\(:   _) \ (:      "| 
(_______/  \_______)|__|  \___)    \__/    (__\_|_)\_______) \_______) 
                                                                       
      ________  _______    __    __    _______   _______    _______    
     /"       )|   __ "\  /" |  | "\  /"     "| /"      \  /"     "|   
    (:   \___/ (. |__) :)(:  (__)  :)(: ______)|:        |(: ______)   
     \___  \   |:  ____/  \/      \/  \/    |  |_____/   ) \/    |     
      __/  \\  (|  /      //  __  \\  // ___)_  //      /  // ___)_    
     /" \   :)/|__/ \    (:  (  )  :)(:      "||:  __   \ (:      "|   
    (_______/(_______)    \__|  |__/  \_______)|__|  \___) \_______)   
                                                                       
    )" << endl;
}

void menuFreelancer() {
    int numItem = 7, selItem = 0;
    while (true) {
        system("cls");
        for(int i = 0; i < numItem; ++i){
            if(i == selItem){
                cout << "=> ";
            }else{
                cout << "\033[0m";
            }
            if (i == 0){
                cout << "view profile\n";
            }else if (i == 1){
                cout << "view order\n";
            }else if (i == 2){
                cout << "add service\n";
            }else if (i == 3){
                cout << "detele service\n";
            }else if (i == 4){
                cout << "complete order\n";
            }else if (i == 5){
                cout << "cancel order\n";
            }else if (i == 6){
                cout << "logout\n";
            }
            if (i == numItem-1){
                cout << "";
            }
        }
        int key = getch();
        if(key == 72){
            selItem = (selItem + numItem - 1) % numItem;
        }else if(key == 80){
            selItem = (selItem + 1) % numItem;
        }else if(key == 13){
            if(selItem == numItem-1){
                return;
            }else{
                if(selItem == 0){
                    viewProfile();
                }else if(selItem == 1){
                    viewOrders();
                }else if(selItem == 2){
                    addService();
                }else if(selItem == 3){
                    deleteService();
                }else if(selItem == 4){
                    completeOrder();
                }else if(selItem == 5){
                    cancelOrder();
                }else if(selItem == 6){
                    secondInterface();
                }
            }
        }
    }
}

void menuUser() {
    int numItem = 4, selItem = 0;
    while (true) {
        system("cls");
        for(int i = 0; i < numItem; ++i){
            if(i == selItem){
                cout << "=> ";
            }else{
                cout << "\033[0m";
            }
            if (i == 0){
                cout << "Top-Up\n";
            }else if (i == 1){
                cout << "Place Order\n";
            }else if (i == 2){
                cout << "View Profile\n";
            }else if (i == 3){
                cout << "logout\n";
            }
            if (i == numItem-1){
                cout << "";
            }
        }
        int key = getch();
        if(key == 72){
            selItem = (selItem + numItem - 1) % numItem;
        }else if(key == 80){
            selItem = (selItem + 1) % numItem;
        }else if(key == 13){
            if(selItem == numItem-1){
                return;
            }else{
                if(selItem == 0){
                    topUp();
                }else if(selItem == 1){
                    order();
                }else if(selItem == 2){
                    viewProfile();
                }else if(selItem == 3){
                    secondInterface();
                }
            }
        }
    }
}

void topUp() {
    int amount;
    system("cls");
    cout << "||======================||\n||        TOP-UP        ||\n||======================||\n";
    cout << "Enter amount to top-up (100k, 500k, 1jt, 2jt): ";
    cin >> amount;
    currentUser.balance += amount;
    cout << "Top-up successful. Current balance: " << currentUser.balance << endl;
    system("pause");
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
    system("pause");
}

void deleteService() {
    system("cls");
    displayServices();
    if (serviceCount == 0) {
        cout << "No services available to delete.\n";
        system("pause");
        return;
    }
    
    int serviceIndex;
    cout << "Enter the number of the service to delete: ";
    cin >> serviceIndex;
    
    if (serviceIndex < 1 || serviceIndex > serviceCount) {
        cout << "Invalid service number.\n";
        system("pause");
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
        system("pause");
        return;
    }

    delete services[serviceIndex - 1];

    for (int i = serviceIndex - 1; i < serviceCount - 1; ++i) {
        services[i] = services[i + 1];
    }

    serviceCount--;
    cout << "Service deleted successfully.\n";
    system("pause");
}

void viewProfile() {
    system("cls");
    cout <<"||========================||\n||      PROFILE ANDA      ||\n||========================||\n";
    cout << "Username: " << currentUser.username << "\nBalance: Rp." << currentUser.balance << endl;
    system("pause");
}

void displayServices() {
    if (serviceCount == 0) {
        cout << "No services available.\n";
        system("pause");
        return;
    }

    for (int i = 0; i < serviceCount; ++i) {
        cout << i + 1 << ". " << services[i]->title << " - " << services[i]->description << " - " << services[i]->price << endl;
    }
    system("pause");
}

void viewOrders() {
    system("cls");
    if (orderCount == 0) {
        cout << "No orders available.\n";
        system("pause");
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
    system("cls");
    viewOrders();
    if (orderCount == 0) {
        cout << "No orders available to cancel.\n";
        system("pause");
        return;
    }

    int orderIndex;
    cout << "Enter the number of the order to cancel: ";
    cin >> orderIndex;

    if (orderIndex < 1 || orderIndex > orderCount) {
        cout << "Invalid order number.\n";
        system("pause");
        return;
    }

    Order* selectedOrder = orders[orderIndex - 1];

    if (selectedOrder->isCompleted) {
        cout << "Order is already completed and cannot be canceled.\n";
        system("pause");
        return;
    }

    selectedOrder->isCanceled = true;

    // Find the user who placed the order and refund the balance
    if (selectedOrder->username == currentUser.username) {
        currentUser.balance += selectedOrder->price;
    }

    cout << "Order canceled successfully. The customer has been refunded.\n";
    system("pause");

}

void completeOrder() {
    system("cls");
    viewOrders();
    if (orderCount == 0) {
        cout << "No orders available to complete.\n";
        system("pause");
        return;
    }

    int orderIndex;
    cout << "Enter the number of the order to complete: ";
    cin >> orderIndex;

    if (orderIndex < 1 || orderIndex > orderCount) {
        cout << "Invalid order number.\n";
        system("pause");
        return;
    }

    Order* selectedOrder = orders[orderIndex - 1];

    if (selectedOrder->isCanceled) {
        cout << "Order is canceled and cannot be completed.\n";
        system("pause");
        return;
    }

    selectedOrder->isCompleted = true;

    cout << "Order completed successfully. The customer has been notified.\n";


}
