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
    bool isDeleted;
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
    while (true) {
        cout << "Are you a freelancer? (y/n): ";
        cin >> role;
        if (role == 'y' || role == 'Y' || role == 'n' || role == 'N') {
            break;
        } else {
            cout << "Invalid input. Please enter 'y' or 'n'.\n";
        }
    }

    for (int i = 0; i < userCount; ++i) {
        if (users[i]->username == username) {
            cout << "Username already exists.\n";
            system("pause");
            return;
        }
    }

    User* newUser = new (nothrow) User;
    if (!newUser) {
        cout << "Memory allocation failed.\n";
        system("pause");
        return;
    }

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
        cout << "||=============================||\n||      FREELANCER MENU        ||\n||=============================||\n";
        for(int i = 0; i < numItem; ++i){
            if(i == selItem){
                cout << "=> \033[34m";
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
                    firstInterface();
                }
            }
        }
    }
}

void menuUser() {
    int numItem = 5, selItem = 0;
    while (true) {
        system("cls");
        cout << "||=============================||\n||         USER MENU           ||\n||=============================||\n";
        for(int i = 0; i < numItem; ++i){
            if(i == selItem){
                cout << "=> \033[34m";
            }else{
                cout << "\033[0m";
            }
            if (i == 0){
                cout << "view profile\n";
            }else if (i == 1){
                cout << "view services\n";
            }else if (i == 2){
                cout << "top up balance\n";
            }else if (i == 3){
                cout << "order\n";
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
                    topUp();
                }else if(selItem == 3){
                    order();
                }else if(selItem == 4){
                    firstInterface();
                }
            }
        }
    }
}

void topUp(){
    system("cls");
    cout << "|+|=============================|+|\n||            TOPUP            |+|\n|+|=============================|+|\n";
    int amount;
    cout << "Masukkan jumlah uang: ";
    cin >> amount;
    currentUser->balance += amount;
    cout << "Top up Berhasil!\nSaldo anda: " << currentUser->balance << endl;
    system("pause");
}
void order(){
    system("cls");
    cout << "|+|=============================|+|\n|+|            ORDER            |+|\n|+|=============================|+|\n";
    displayServices();
    string serviceName;
    cout << "Masukkan nama jasa yang diinginkan: ";
    cin.ignore();
    getline(cin, serviceName);
    for (int i = 0; i < serviceCount; ++i) {
        if (services[i]->title == serviceName) {
            if (currentUser->balance >= services[i]->price) {
                Order* newOrder = new (nothrow) Order;
                if (!newOrder) {
                    cout << "Memory allocation failed.\n";
                    system("pause");
                    return;
                }
                newOrder->serviceTitle = services[i]->title;
                newOrder->price = services[i]->price;
                newOrder->username = currentUser->username;
                newOrder->provider = services[i]->provider;
                newOrder->isCompleted = false;
                newOrder->isCanceled = false;
                currentUser->balance -= services[i]->price;
                orders[orderCount++] = newOrder;
                cout << "BERHASIL MEMESAN!!\n";
                system("pause");
                return;
            } else {
                cout << "Saldo anda tidak mencukupi silahkan top-up terlebih dahulu ^_^.\n";
                system("pause");
                return;
            }
        }
    }
    cout << "Service not found.\n";
    system("pause");
}

void addService(){
    system("cls");
    cout << "|+|=============================|+|\n|+|         ADD SERVICE         |+|\n|+|=============================|+|\n";
    Service* newService = new (nothrow) Service;
    if (!newService) {
        cout << "Memory allocation failed.\n";
        system("pause");
        return;
    }
    cout << "Masukkan nama jasa: ";
    cin.ignore();
    getline(cin, newService->title);
    cout << "Masukkan deskripsi jasa: ";
    getline(cin, newService->description);
    cout << "Masukkan harga: ";
    cin >> newService->price;
    newService->provider = currentUser->username;
    services[serviceCount++] = newService;
    cout << "Jasa berhasil ditambahkan!\n";
    system("pause");
}
void deleteService(){
    system("cls");
    cout << "|+|=============================|+|\n|+|         DELETE SERVICE       |+|\n|+|=============================|+|\n";
    displayServices();
    string serviceName;
    cout << "Masukkan nama jasa yang akan dihapus: ";
    cin.ignore();
    getline(cin, serviceName);
    for (int i = 0; i < serviceCount; ++i) {
        if (services[i]->title == serviceName && services[i]->provider == currentUser->username) {
            // Mark related orders as deleted
            for (int j = 0; j < orderCount; ++j) {
                if (orders[j]->serviceTitle == serviceName) {
                    orders[j]->isDeleted = true;
                }
            }

            delete services[i];
            for (int j = i; j < serviceCount - 1; ++j) {
                services[j] = services[j + 1];
            }
            --serviceCount;
            cout << "Jasa berhasil dihapus.\n";
            system("pause");
            return;
        }
    }
    cout << "Jasa tidak ditemukan atau anda bukan penyedia jasa yang dimaksud!\n";
    system("pause");
}


void viewProfile(){
    system("cls");
    cout << "|+|=============================|+|\n|+|          PROFILE            |+|\n|+|=============================|+|\n";
    cout << "Username: " << currentUser->username << endl;
    cout << "Saldo: Rp." << currentUser->balance << endl;
    cout << "Role: " << (currentUser->isFreelancer ? "Freelancer" : "User") << endl;
    system("pause");
}

void displayServices(){
    cout << "Available services:\n";
    for (int i = 0; i < serviceCount; ++i) {
        cout << "Judul: " << services[i]->title << "\nDeskripsi: " << services[i]->description << "\nHarga: " << services[i]->price << "\nPenyedia: " << services[i]->provider << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< endl;
    }
    system("pause");
}

void viewOrders(){
    system("cls");
    cout << "|+|=============================|+|\n|+|           ORDERS            |+|\n|+|=============================|+|\n";
    cout << "Your orders:\n";
    for (int i = 0; i < orderCount; ++i) {
        if (orders[i]->username == currentUser->username || orders[i]->provider == currentUser->username) {
            cout << "Nama jasa: " << orders[i]->serviceTitle << "\nHarga: " << orders[i]->price << "\nPemesan: " << orders[i]->username << "\nPenyedia: " << orders[i]->provider << "\nDiselesaikan: " << (orders[i]->isCompleted ? "Iya" : "Tidak") << "\nDibatalkan: " << (orders[i]->isCanceled ? "Iya" : "Tidak") << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        }
    }
    system("pause");
}
void cancelOrder() {
    system("cls");
    cout << "|+|=============================|+|\n|+|          CANCEL ORDER        |+|\n|+|=============================|+|\n";
    viewOrders();
    string serviceName;
    cout << "Enter service name to cancel order: ";
    cin.ignore();
    getline(cin, serviceName);

    int matchingOrders[100];
    int matchingCount = 0;

    // Find matching orders
    for (int i = 0; i < orderCount; ++i) {
        if (orders[i] != nullptr && orders[i]->serviceTitle == serviceName && !orders[i]->isDeleted) {
            if (orders[i]->username == currentUser->username || orders[i]->provider == currentUser->username) {
                matchingOrders[matchingCount++] = i;
            }
        }
    }

    // Check if there are no matching orders
    if (matchingCount == 0) {
        cout << "No matching orders found or you don't have permission to cancel any orders.\n";
        system("pause");
        return;
    }

    // Display matching orders
    cout << "Matching orders:\n";
    for (int i = 0; i < matchingCount; ++i) {
        int index = matchingOrders[i];
        cout << i << ": " << "Order for " << orders[index]->serviceTitle << " by " << orders[index]->username 
             << ", Price: " << orders[index]->price 
             << ", Completed: " << (orders[index]->isCompleted ? "Yes" : "No") 
             << ", Canceled: " << (orders[index]->isCanceled ? "Yes" : "No") << endl;
    }

    // Prompt for order index
    cout << "Enter the index of the order to cancel: ";
    int orderIndex;
    cin >> orderIndex;

    // Validate order index
    if (orderIndex < 0 || orderIndex >= matchingCount) {
        cout << "Invalid index.\n";
        system("pause");
        return;
    }

    int selectedOrder = matchingOrders[orderIndex];
    if (orders[selectedOrder] == nullptr) {
        cout << "The order has been deleted and cannot be canceled.\n";
    } else if (!orders[selectedOrder]->isCompleted && !orders[selectedOrder]->isCanceled) {
        orders[selectedOrder]->isCanceled = true;

        // If the current user is the provider, refund the customer
        if (orders[selectedOrder]->provider == currentUser->username) {
            for (int j = 0; j < userCount; ++j) {
                if (users[j]->username == orders[selectedOrder]->username) {
                    users[j]->balance += orders[selectedOrder]->price;
                    cout << "Order canceled and money refunded to the user successfully.\n";
                    system("pause");
                    return;
                }
            }
        } else {
            cout << "Order canceled successfully.\n";
            system("pause");
            return;
        }
    } else {
        cout << "Order already completed or canceled.\n";
    }

    system("pause");
}
void completeOrder() {
    system("cls");
    cout << "|+|=============================|+|\n|+|         COMPLETE ORDER       |+|\n|+|=============================|+|\n";
    viewOrders();
    string serviceName;
    cout << "Enter service name to complete order: ";
    cin.ignore();
    getline(cin, serviceName);

    int matchingOrders[100];
    int matchingCount = 0;

    // Find matching orders
    for (int i = 0; i < orderCount; ++i) {
        // Assuming deleted orders are set to null or handled by a specific flag.
        if (orders[i] != nullptr && orders[i]->serviceTitle == serviceName && orders[i]->provider == currentUser->username && !orders[i]->isDeleted) {
            matchingOrders[matchingCount++] = i;
        }
    }

    // Check if there are no matching orders
    if (matchingCount == 0) {
        cout << "No matching orders found.\n";
        system("pause");
        return;
    }

    // Display matching orders
    cout << "Matching orders:\n";
    for (int i = 0; i < matchingCount; ++i) {
        int index = matchingOrders[i];
        cout << i << ": " << "Order for " << orders[index]->serviceTitle << " by " << orders[index]->username 
             << ", Price: " << orders[index]->price 
             << ", Completed: " << (orders[index]->isCompleted ? "Yes" : "No") 
             << ", Canceled: " << (orders[index]->isCanceled ? "Yes" : "No") << endl;
    }

    // Prompt for order index
    cout << "Enter the index of the order to complete: ";
    int orderIndex;
    cin >> orderIndex;

    // Validate order index
    if (orderIndex < 0 || orderIndex >= matchingCount) {
        cout << "Invalid index.\n";
        system("pause");
        return;
    }

    int selectedOrder = matchingOrders[orderIndex];
    if (orders[selectedOrder] == nullptr) {
        cout << "The order has been deleted and cannot be completed.\n";
    } else if (!orders[selectedOrder]->isCompleted && !orders[selectedOrder]->isCanceled) {
        orders[selectedOrder]->isCompleted = true;
        
        // Transfer money to freelancer
        for (int j = 0; j < userCount; ++j) {
            if (users[j]->username == orders[selectedOrder]->provider) {
                users[j]->balance += orders[selectedOrder]->price;
                break;
            }
        }

        cout << "Order completed successfully.\n";
    } else {
        cout << "Order already completed or canceled.\n";
    }

    system("pause");
}


