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
string username, password, serviceName;
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

// void trim(string &str) {
//     // Trim leading whitespace
//     size_t start = str.find_first_not_of(" \t\n\r\f\v");
//     str = (start == string::npos) ? "" : str.substr(start);

//     // Trim trailing whitespace
//     size_t end = str.find_last_not_of(" \t\n\r\f\v");
//     str = (end == string::npos) ? "" : str.substr(0, end + 1);
// }

// string toLower(string str) {
//     for (size_t i = 0; i < str.size(); ++i) {
//         if (str[i] >= 'A' && str[i] <= 'Z') {
//             str[i] += 'a' - 'A';
//         }
//     }
//     return str;
// }

// void order() {
//     system("cls");
//     cout << "|+|=============================|+|\n|+|            ORDER            |+|\n|+|=============================|+|\n";
//     displayServices();
//   
//     cout << "Masukkan nama jasa yang diinginkan: ";
//     cin.ignore();
//     getline(cin, serviceName);
    
//     // Trim and convert to lowercase
//     trim(serviceName);
//     serviceName = toLower(serviceName);

//     for (int i = 0; i < serviceCount; ++i) {
//         string serviceTitle = services[i]->title;
//         trim(serviceTitle);
//         serviceTitle = toLower(serviceTitle);

//         if (serviceTitle == serviceName) {
//             if (currentUser->balance >= services[i]->price) {
//                 Order* newOrder = new (nothrow) Order;
//                 if (!newOrder) {
//                     cout << "Memory allocation failed.\n";
//                     system("pause");
//                     return;
//                 }
//                 newOrder->serviceTitle = services[i]->title;
//                 newOrder->price = services[i]->price;
//                 newOrder->username = currentUser->username;
//                 newOrder->provider = services[i]->provider;
//                 newOrder->isCompleted = false;
//                 newOrder->isCanceled = false;
//                 currentUser->balance -= services[i]->price;
//                 orders[orderCount++] = newOrder;
//                 cout << "BERHASIL MEMESAN!!\n";
//                 system("pause");
//                 return;
//             } else {
//                 cout << "Saldo anda tidak mencukupi silahkan top-up terlebih dahulu ^_^.\n";
//                 system("pause");
//                 return;
//             }
//         }
//     }
//     cout << "Service not found.\n";
//     system("pause");
// }
void order(){
    system("cls");
    cout << "|+|=============================|+|\n|+|            ORDER            |+|\n|+|=============================|+|\n";
    displayServices();
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
    cin.ignore();
    cout << "Masukkan nama jasa yang akan dihapus: ";
    getline(cin, serviceName);
    for (int i = 0; i < serviceCount; ++i) {
        if (services[i]->title == serviceName && services[i]->provider == currentUser->username) {
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

void cancelOrder(){
    system("cls");
    cout << "|+|=============================|+|\n|+|          CANCEL ORDER        |+|\n|+|=============================|+|\n";
    viewOrders();
    cout << "Enter service name to cancel order: ";
    cin.ignore();
    getline(cin, serviceName);
    for (int i = 0; i < orderCount; ++i) {
        if (orders[i]->serviceTitle == serviceName) {
            // cek apakah pengguna login sebagai freelancer atau user biasa
            if (orders[i]->username == currentUser->username || orders[i]->provider == currentUser->username) {
                orders[i]->isCanceled = true;

                // jika pengguna freelancer maka uang dikembalikan
                if (orders[i]->provider == currentUser->username) {
                    for (int j = 0; j < userCount; ++j) {
                        if (users[j]->username == orders[i]->username) {
                            users[j]->balance += orders[i]->price;
                            cout << "Pesanan dibatalkan dan uang telah di-refund kepada user\n";
                            system("pause");
                            return;
                        }
                    }
                } else {
                    cout << "Pesanan berhasil dibatalkan\n";
                    system("pause");
                    return;
                }
            }
        }
    }
    cout << "Order not found or you don't have permission to cancel this order.\n";
    system("pause");
}

void completeOrder() {
    system("cls");
    cout << "|+|=============================|+|\n|+|         COMPLETE ORDER       |+|\n|+|=============================|+|\n";
    viewOrders();
    cout << "Enter service name to complete order: ";
    cin.ignore();
    getline(cin, serviceName);
    for (int i = 0; i < orderCount; ++i) {
        if (orders[i]->serviceTitle == serviceName && orders[i]->provider == currentUser->username) {
            if (!orders[i]->isCompleted && !orders[i]->isCanceled) {
                orders[i]->isCompleted = true;
                
                // Transfer uang ke freelancer
                for (int j = 0; j < userCount; ++j) {
                    if (users[j]->username == orders[i]->provider) {
                        users[j]->balance += orders[i]->price;
                        break;
                    }
                }

                cout << "Pesanan telah diselesaikan\n";
                system("pause");
                return;
            } else {
                cout << "Pesanan mungkin telah diselesaikan atau telah dibatalkan\n";
                system("pause");
                return;
            }
        }
    }
    cout << "Order not found.\n";
    system("pause");
}

