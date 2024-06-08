#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
using namespace std;

struct Service {
    string title;
    string description;
    int price;
    string provider;
};

struct Order {
    string serviceTitle;
    string orderDescription;
    string username;
    string provider;
    int price;
    bool isCompleted;
    bool isCanceled;
};

struct User {
    string username;
    string password;
    int balance;
    bool isFreelancer;
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

User* users[100];
Service* services[100];
Order* orders[100];
int userCount = 0;
int serviceCount = 0;
int orderCount = 0;
User* currentUser = nullptr;
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
                cout << "\033[34m";
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
    char role;
    cout << "Are you a freelancer? (y/n): ";
    cin >> role;

    for (int i = 0; i < userCount; ++i) {
        if (users[i]->username == username) {
            cout << "Username already exists.\n";
            system("pause");
            return;
        }
    }

    User* newUser = new User;
    newUser->username = username;
    newUser->password = password;
    newUser->balance = 0;
    newUser->isFreelancer = (role == 'y' || role == 'Y');
    users[userCount++] = newUser;
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
    
    for (int i = 0; i < userCount; ++i) {
        if (users[i]->username == username && users[i]->password == password) {
            currentUser = users[i];
            cout << "Login successful.\n";
            system("pause");
            if (currentUser->isFreelancer) {
                menuFreelancer();
            } else {
                menuUser();
            }
            return;
        }
    }
    
    cout << "Invalid credentials.\n";
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
                cout << "view orders\n";
            }else if (i == 2){
                cout << "add service\n";
            }else if (i == 3){
                cout << "delete service\n";
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
    int numItem = 5, selItem = 0;
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
                cout << "display services\n";
            }else if (i == 2){
                cout << "order\n";
            }else if (i == 3){
                cout << "top up\n";
            }else if (i == 4){
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
                    displayServices();
                }else if(selItem == 2){
                    order();
                }else if(selItem == 3){
                    topUp();
                }else if(selItem == 4){
                    secondInterface();
                }
            }
        }
    }
}

void topUp() {
    int amount;
    cout << "Enter amount to top up: ";
    cin >> amount;
    currentUser->balance += amount;
    cout << "Top up successful. New balance: " << currentUser->balance << endl;
    system("pause");
}

void order() {
    displayServices();
    int serviceIndex;
    cout << "Enter the index of the service you want to order: ";
    cin >> serviceIndex;
    if (serviceIndex < 0 || serviceIndex >= serviceCount) {
        cout << "Invalid service index.\n";
        system("pause");
        return;
    }

    Service* service = services[serviceIndex];
    if (currentUser->balance < service->price) {
        cout << "Insufficient balance.\n";
        system("pause");
        return;
    }

    string orderDescription;
    cout << "Enter order description: ";
    cin.ignore();
    getline(cin, orderDescription);

    Order* newOrder = new Order;
    newOrder->serviceTitle = service->title;
    newOrder->orderDescription = orderDescription;
    newOrder->username = currentUser->username;
    newOrder->provider = service->provider;
    newOrder->price = service->price;
    newOrder->isCompleted = false;
    newOrder->isCanceled = false;
    orders[orderCount++] = newOrder;

    currentUser->balance -= service->price;
    cout << "Order placed successfully.\n";
    system("pause");
}

void addService() {
    Service* newService = new Service;
    cout << "Enter service title: ";
    cin.ignore();
    getline(cin, newService->title);
    cout << "Enter service description: ";
    getline(cin, newService->description);
    cout << "Enter service price: ";
    cin >> newService->price;
    newService->provider = currentUser->username;
    services[serviceCount++] = newService;
    cout << "Service added successfully.\n";
    system("pause");
}

void deleteService() {
    displayServices();
    int serviceIndex;
    cout << "Enter the index of the service you want to delete: ";
    cin >> serviceIndex;
    if (serviceIndex < 0 || serviceIndex >= serviceCount || services[serviceIndex]->provider != currentUser->username) {
        cout << "Invalid service index.\n";
        system("pause");
        return;
    }

    delete services[serviceIndex];
    for (int i = serviceIndex; i < serviceCount - 1; ++i) {
        services[i] = services[i + 1];
    }
    --serviceCount;
    cout << "Service deleted successfully.\n";
    system("pause");
}

void viewProfile() {
    cout << "Username: " << currentUser->username << endl;
    cout << "Balance: " << currentUser->balance << endl;
    cout << "Role: " << (currentUser->isFreelancer ? "Freelancer" : "User") << endl;
    system("pause");
}

void displayServices() {
    cout << "Available Services:\n";
    for (int i = 0; i < serviceCount; ++i) {
        cout << i+1 << ". " << services[i]->title << " by " << services[i]->provider << " - $" << services[i]->price << "\n   " << services[i]->description << endl;
    }
    system("pause");
}

void viewOrders() {
    cout << "Your Orders:\n";
    for (int i = 0; i < orderCount; ++i) {
        if (orders[i]->provider == currentUser->username || orders[i]->username == currentUser->username) {
            cout << i+1 << ". Service: " << orders[i]->serviceTitle << "\n   Description: " << orders[i]->orderDescription << "\n   User: " << orders[i]->username << "\n   Provider: " << orders[i]->provider << "\n   Price: $" << orders[i]->price << "\n   Status: " << (orders[i]->isCompleted ? "Completed" : orders[i]->isCanceled ? "Canceled" : "Pending") << endl;
        }
    }
    system("pause");
}
void cancelOrder() {
    viewOrders();
    int orderIndex;
    cout << "Enter the index of the order you want to cancel: ";
    cin >> orderIndex;
    if (orderIndex < 0 || orderIndex >= orderCount || orders[orderIndex]->provider != currentUser->username || orders[orderIndex]->isCompleted || orders[orderIndex]->isCanceled) {
        cout << "Invalid order index.\n";
        system("pause");
        return;
    }

    orders[orderIndex]->isCanceled = true;

    // Find the user who placed the order and refund the amount
    for (int i = 0; i < userCount; ++i) {
        if (users[i]->username == orders[orderIndex]->username) {
            users[i]->balance += orders[orderIndex]->price;
            break;
        }
    }

    cout << "Order canceled successfully. Amount refunded to user.\n";
    system("pause");
}
void completeOrder() {
    viewOrders();
    int orderIndex;
    cout << "Enter the index of the order you want to mark as completed: ";
    cin >> orderIndex;
    if (orderIndex < 0 || orderIndex >= orderCount || orders[orderIndex]->provider != currentUser->username || orders[orderIndex]->isCompleted || orders[orderIndex]->isCanceled) {
        cout << "Invalid order index.\n";
        system("pause");
        return;
    }

    orders[orderIndex]->isCompleted = true;
    for (int i = 0; i < userCount; ++i) {
        if (users[i]->username == orders[orderIndex]->provider) {
            users[i]->balance += orders[orderIndex]->price;
            break;
        }
    }
    cout << "Order marked as completed.\n";
    system("pause");
}
