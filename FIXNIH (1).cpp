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
}; // Struct untuk jasa yang ditawarkan

struct Order {
    string serviceTitle;
    string orderDescription;
    string username;
    string provider;
    int price;
    bool isCompleted;
    bool isCanceled;
    bool isDeleted;
}; // Struct untuk jasa yang dipesan

struct User {
    string username;
    string password;
    int balance;
    bool isFreelancer;
}; // Struct untuk akun pengguna

void banner();
void menuAwal();
void registerUser();
void loginUser();
void menuFreelancer();
void menuUser();
void viewProfile();
void viewOrders();
void addService();
void deleteService();
void completeOrder();
void cancelOrder();
void displayServices();
void noDisplayServices();
void topUp();
void order();

User* users[100]; // Batas jumlah pengguna 100
Service* services[100]; // Batas jumlah jasa 100
Order* orders[100]; // Batas jumlah pesanan 100
int userCount = 0; // Jumlah pengguna di set dari 0
int serviceCount = 0; // Jumlah jasa di set dari 0
int orderCount = 0; // Jumlah pesanan di set dari 0
User* currentUser = nullptr; // Di set tidak login ke akun apa pun
string username, password;
int choice;

int main() {
    menuAwal();
    return 0;
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

void menuAwal(){
    int numItem = 3, selItem = 0;
    while (true) {
        system("cls");
        banner();
        for(int i = 0; i < numItem; ++i){
            if(i == selItem) cout << "\033[34m";
            else cout << "\033[0m";
            
            if (i == 0)      cout << "||=======================||\n||        REGISTER       ||\n||=======================||\n";
            else if (i == 1) cout << "||=======================||\n||         LOGIN         ||\n||=======================||\n";
            else if (i == 2) cout << "||=======================||\n||          EXIT         ||\n||=======================||\n";
            
            if (i == numItem-1) cout << "\033[0m";
        }
        int key = getch();
        if(key == 72) selItem = (selItem + numItem - 1) % numItem;
        else if(key == 80) selItem = (selItem + 1) % numItem;
        else if(key == 13){
            if(selItem == numItem-1) return;
            else{
                if(selItem == 0) registerUser();
                else if(selItem == 1) loginUser();
                else if(selItem == 2) break;
            }
        }
    }
} // Fungsi memilih menu dengan getch

void registerUser(){
    system("cls");
    cout << "||=======================||\n||        REGISTER       ||\n||=======================||\n";
    cout << "Masukkan username: "; cin >> username;
    cout << "Masukkan password: "; cin >> password;
    char role;
    while (true) {
        cout << "Apakah kamu freelancer? (y/n): ";
        cin >> role;
        if (role == 'y' || role == 'Y' || role == 'n' || role == 'N') {
            break;
        } else {
            cout << "Input tidak valid. Mohon masukkan 'y' atau 'n'.\n";
        }
    }

    for (int i = 0; i < userCount; ++i) {
        if (users[i]->username == username) {
            cout << "Username sudah digunakan.\n";
            system("pause");
            return;
        }
    }

    User* newUser = new (nothrow) User;
    if (!newUser) {
        cout << "Alokasi memori gagal.\n";
        system("pause");
        return;
    }

    newUser->username = username; // Username pengguna baru di set sesuai input
    newUser->password = password; // Password pengguna baru di set sesuai input
    newUser->balance = 0; // Saldo pengguna baru di set ke 0
    newUser->isFreelancer = (role == 'y' || role == 'Y');
    users[userCount++] = newUser;
    cout << "Registrasi berhasil!\n";
    system("pause");
}

void loginUser(){
    system("cls");
    cout << "||=======================||\n||         LOGIN         ||\n||=======================||\n";
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;
    
    for (int i = 0; i < userCount; ++i) {
        if (users[i]->username == username && users[i]->password == password) {
            currentUser = users[i];
            cout << "Login berhasil!.\n";
            system("pause");
            if (currentUser->isFreelancer) menuFreelancer();
            else menuUser();
            return;
        }
    } // Perulangan untuk mengecek username dan password akun
    cout << "Username atau Password tidak sesuai!.\n";
    system("pause");
}

void menuFreelancer() {
    int numItem = 7, selItem = 0;
    while (true) {
        system("cls");
        cout << "||=============================||\n||       FREELANCER MENU       ||\n||=============================||\n";
        for(int i = 0; i < numItem; ++i){
            if(i == selItem) cout << "=> \033[34m";
            else cout << "\033[0m";
            
            if (i == 0) cout << "view profile\n";
            else if (i == 1) cout << "view orders\n";
            else if (i == 2) cout << "add service\n";
            else if (i == 3) cout << "delete service\n";
            else if (i == 4) cout << "complete order\n";
            else if (i == 5) cout << "cancel order\n";
            else if (i == 6) cout << "logout\n";
            
            if (i == numItem-1) cout << "";
        }
        int key = getch();
        if(key == 72) selItem = (selItem + numItem - 1) % numItem;
        else if(key == 80) selItem = (selItem + 1) % numItem;
        else if(key == 13){
            if(selItem == numItem-1) return;
            else{
                if(selItem == 0) viewProfile();
                else if(selItem == 1) viewOrders();
                else if(selItem == 2) addService();
                else if(selItem == 3) deleteService();
                else if(selItem == 4) completeOrder();
                else if(selItem == 5) cancelOrder();
                else if(selItem == 6) menuAwal();
            }
        }
    }
}

void menuUser() {
    int numItem = 5, selItem = 0;
    while (true) {
        system("cls");
        cout << "||==============================||\n||           USER MENU          ||\n||==============================||\n";
        for(int i = 0; i < numItem; ++i){
            if(i == selItem) cout << "=> \033[34m";
            else cout << "\033[0m";
            
            if (i == 0) cout << "view profile\n";
            else if (i == 1) cout << "view services\n";
            else if (i == 2) cout << "top up balance\n";
            else if (i == 3) cout << "order\n";
            else if (i == 4) cout << "logout\n";
            
            if (i == numItem-1) cout << "";
        }
        int key = getch();
        if(key == 72) selItem = (selItem + numItem - 1) % numItem;
        else if(key == 80) selItem = (selItem + 1) % numItem;
        else if(key == 13){
            if(selItem == numItem-1) return;
            else{
                if(selItem == 0) viewProfile();
                else if(selItem == 1) displayServices();
                else if(selItem == 2) topUp();
                else if(selItem == 3) order();
                else if(selItem == 4) menuAwal();
            }
        }
    }
}

void viewProfile(){
    system("cls");
    cout << "|+|===============================|+|\n|+|            PROFILE            |+|\n|+|===============================|+|\n";
    cout << "Username: " << currentUser->username << endl;
    cout << "Saldo: Rp." << currentUser->balance << endl;
    cout << "Role: " << (currentUser->isFreelancer ? "Penyedia Jasa" : "Pelanggan") << endl;    
    system("pause");
}

void viewOrders(){
    system("cls");
    cout << "|+|===============================|+|\n|+|            ORDERS             |+|\n|+|===============================|+|\n";
    if(orderCount==0) {
        cout << "Tidak ada pesanan untuk saat ini!" << endl;
        system("pause");
        system("cls");
        return;
    }
    else {
        cout << "Jasa yang di pesan:\n";
        for (int i = 0; i < orderCount; ++i) {
            if (orders[i]->username == currentUser->username || orders[i]->provider == currentUser->username) {
                cout << "Nama jasa: " << orders[i]->serviceTitle << "\nHarga: " << orders[i]->price << "\nPemesan: " << orders[i]->username << "\nPenyedia: " << orders[i]->provider << "\nDiselesaikan: " << (orders[i]->isCompleted ? "Iya" : "Tidak") << "\nDibatalkan: " << (orders[i]->isCanceled ? "Iya" : "Tidak") << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            }
        }
        cout << endl;
        system("pause");
        system("cls");
        return;
    }
}

int hitungPanjangStr(const string& str) {
    int count = 0;
    for (char c : str) {
        count++;
    }
    return count;
}

void addService() {
    system("cls");
    cout << "|+|===============================|+|\n|+|          ADD SERVICE          |+|\n|+|===============================|+|\n";
    Service* newService = new (nothrow) Service;
    if (!newService) {
        cout << "Alokasi memori gagal.\n";
        system("pause");
        return;
    }
    cin.ignore();
    
    // Input nama jasa
    while (true) {
        cout << "Masukkan nama jasa: ";
        getline(cin, newService->title);
        if (hitungPanjangStr(newService->title) > 4) break;
        cout << "Input tidak valid! Usahakan lebih dari 4 karakter.\n";
    }
    // Input deskripsi jasa
    while (true) {
        cout << "Masukkan deskripsi jasa: ";
        getline(cin, newService->description);
        if (hitungPanjangStr(newService->description) > 12) break;
        cout << "Input tidak valid! Usahakan lebih dari 12 karakter.\n";
    }
    // Input harga jasa
    while (true) {
        cout << "Masukkan harga: ";
        if (cin >> newService->price) break;
        cout << "Input tidak valid! Input harus berupa bilangan bulat.\n";
        cin.clear(); // Clear the error flag
        cin.ignore(INT_MAX, '\n'); // Discard invalid input
    }
    newService->provider = currentUser->username;
    services[serviceCount++] = newService;
    cout << "Jasa berhasil ditambahkan!\n";
    system("pause");
}

void deleteService(){
    system("cls");
    cout << "|+|===============================|+|\n|+|         DELETE SERVICE        |+|\n|+|===============================|+|\n";
    if (serviceCount == 0) noDisplayServices();
    else {
        displayServices();
        string serviceName;
        cout << "Masukkan nama jasa yang akan dihapus: ";
        cin.ignore();
        getline(cin, serviceName);
        for (int i = 0; i < serviceCount; ++i) {
            if (services[i]->title == serviceName && services[i]->provider == currentUser->username) {
                // Menandai pesanan yang seusai sebagai terhapus
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
}

void completeOrder() {
    system("cls");
    cout << "|+|==============================|+|\n|+|         COMPLETE ORDER       |+|\n|+|==============================|+|\n";
    if (orderCount == 0) {
        viewOrders();
        return;
    } else {
        displayServices();
        string serviceName;
        cout << "Masukkan nama jasa untuk diselesaikan: ";
        cin.ignore();
        getline(cin, serviceName);

        int matchingOrders[100];
        int matchingCount = 0;

        // Mengecek pesanan yang cocok
        for (int i = 0; i < orderCount; ++i) {
            if (orders[i] != nullptr && orders[i]->serviceTitle == serviceName && orders[i]->provider == currentUser->username && !orders[i]->isDeleted) {
                matchingOrders[matchingCount++] = i;
            }
        }

        // Mengecek apakah tidak ada pesanan yang sesuai
        if (matchingCount == 0) {
            cout << "Tidak ditemukan pesanan yang sesuai!\n";
            system("pause");
            return menuFreelancer();
        }

        // Menampilkan pesanan yang sesuai
        cout << "Nama jasa sesuai:\n";
        for (int i = 0; i < matchingCount; ++i) {
            int index = matchingOrders[i];
            cout << i << ": " << "Pesanan jasa untuk " << orders[index]->serviceTitle << " dari " << orders[index]->username 
                << ", Harga: " << orders[index]->price 
                << ", Terselesaikan: " << (orders[index]->isCompleted ? "Ya" : "Tidak") 
                << ", Dibatalkan: " << (orders[index]->isCanceled ? "Ya" : "Tidak") << endl;
        }

        // Indeks pesanan
        cout << "Masukkan nomor pesanan untuk diselesaikan: ";
        int orderIndex;
        cin >> orderIndex;

        // Validasi indeks pesanan
        if (orderIndex < 0 || orderIndex >= matchingCount) {
            cout << "Nomor tidak sesuai!\n";
            system("pause");
            return;
        }

        int selectedOrder = matchingOrders[orderIndex];
        if (orders[selectedOrder] == nullptr) {
            cout << "Pesanan sudah dihapus/atau dibatalkan sehingga tidak dapat diselesaikan.\n";
        } else if (!orders[selectedOrder]->isCompleted && !orders[selectedOrder]->isCanceled) {
            orders[selectedOrder]->isCompleted = true;

            // Melakukan pengiriman uang
            for (int j = 0; j < userCount; ++j) {
                if (users[j]->username == orders[selectedOrder]->provider) {
                    users[j]->balance += orders[selectedOrder]->price;
                    break;
                }
            }

            cout << "Pesanan berhasil diselesaikan.\n";
        } else {
            cout << "Pesanan jasa telah diselesaikan atau dibatalkan!\n";
        }
        system("pause");
    }
}

void cancelOrder() {
    system("cls");
    cout << "|+|==============================|+|\n|+|         CANCEL ORDER         |+|\n|+|==============================|+|\n";
    if (orderCount == 0) {
        viewOrders();
        return;
    } else {
        displayServices();
        string serviceName;
        cout << "Masukkan nama jasa untuk dibatalkan: ";
        cin.ignore();
        getline(cin, serviceName);

        int matchingOrders[100];
        int matchingCount = 0;

        // Mengecek pesanan yang cocok
        for (int i = 0; i < orderCount; ++i) {
            if (orders[i] != nullptr && orders[i]->serviceTitle == serviceName && !orders[i]->isDeleted) {
                if (orders[i]->username == currentUser->username || orders[i]->provider == currentUser->username) {
                    matchingOrders[matchingCount++] = i;
                }
            }
        }

        // Mengecek apakah tidak ada pesanan yang sesuai
        if (matchingCount == 0) {
            cout << "Tidak ditemukan pesanan yang sesuai atau anda tidak memiliki izin untuk melakukan pembatalan!\n";
            system("pause");
            return;
        }

        // Menampilkan pesanan yang sesuai
        cout << "Nama jasa sesuai:\n";
        for (int i = 0; i < matchingCount; ++i) {
            int index = matchingOrders[i];
            cout << i << ": " << "Pesanan jasa untuk " << orders[index]->serviceTitle << " dari " << orders[index]->username 
                << ", Harga: " << orders[index]->price 
                << ", Terselesaikan: " << (orders[index]->isCompleted ? "Ya" : "Tidak") 
                << ", Dibatalkan: " << (orders[index]->isCanceled ? "Ya" : "Tidak") << endl;
        }

        // Indeks pesanan
        cout << "Masukkan nomor pesanan untuk dibatalkan: ";
        int orderIndex;
        cin >> orderIndex;

        // Validasi indeks pesanan
        if (orderIndex < 0 || orderIndex >= matchingCount) {
            cout << "Nomor tidak sesuai!\n";
            system("pause");
            return;
        }

        int selectedOrder = matchingOrders[orderIndex];
        if (orders[selectedOrder] == nullptr) {
            cout << "Pesanan telah dihapus, tidak dapat melakukan pembatalan!\n";
        } else if (!orders[selectedOrder]->isCompleted && !orders[selectedOrder]->isCanceled) {
            orders[selectedOrder]->isCanceled = true;

            // Jika pengguna saat ini adalah penyedia, kembalikan uang kepada pelanggan
            if (orders[selectedOrder]->provider == currentUser->username) {
                for (int j = 0; j < userCount; ++j) {
                    if (users[j]->username == orders[selectedOrder]->username) {
                        users[j]->balance += orders[selectedOrder]->price;
                        cout << "Pesanan dibatalkan! Refund uang ke pelanggan berhasil.\n";
                        system("pause");
                        return;
                    }
                }
            } else {
                cout << "Pesanan berhasil dibatalkan!\n";
            }
        } else {
            cout << "Pesanan jasa telah diselesaikan atau dibatalkan!\n";
        }
        system("pause");
    }
}

void displayServices(){
    system("cls");
    cout << "|+|==============================|+|\n|+|          DAFTAR JASA         |+|\n|+|==============================|+|\n";
    cout << "Jasa yang tersedia:\n";
    for (int i = 0; i < serviceCount; ++i) cout << "Judul: " << services[i]->title << "\nDeskripsi: " << services[i]->description << "\nHarga: " << services[i]->price << "\nPenyedia: " << services[i]->provider << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< endl;
    system("pause");
}

void noDisplayServices(){
    system("cls");
    cout << "|+|==============================|+|\n|+|          DAFTAR JASA         |+|\n|+|==============================|+|\n";
    cout << "Tidak ada jasa yang ditawarkan untuk saat ini!\n";
    system("pause");
    system("cls");
    return; 
}

void topUp(){
    system("cls");
    cout << "|+|==============================|+|\n|+|            TOP-UP            |+|\n|+|==============================|+|\n";
    int amount;
    cout << "Besaran nilai Top-Up\nRp. 500.000\nRp. 1.000.000\nRp. 2.000.000\nRp. 5.000.000\nRp. 10.000.000\nMasukkan jumlah uang: ";
    cin >> amount;
    while (true){
        if(amount==500000||amount==1000000||amount==2000000||amount==5000000||amount==10000000){
            currentUser->balance += amount;
            cout << "Top up Berhasil!\nSaldo anda sekarang: " << currentUser->balance << endl;
            system("pause");
            break;
        } else {
            cin.clear();
            cin.ignore();
            cout << "Input tidak valid, Masukkan Input sesuai nilai yang diberikan!" << endl;
            system("pause");
            break;
        }
    }
}

void order(){
    system("cls");
    cout << "|+|==============================|+|\n|+|             ORDER             |+|\n|+|==============================|+|\n";
    if (serviceCount == 0) {
        noDisplayServices();
        system("cls");
        return; 
    }
    else {
        displayServices();
        string serviceName;
        cout << "Masukkan nama jasa yang diinginkan: ";
        cin.ignore();
        getline(cin>>ws, serviceName);
        for (int i = 0; i < serviceCount; ++i) {
            if (services[i]->title == serviceName) {
                if (currentUser->balance >= services[i]->price) {
                    Order* newOrder = new (nothrow) Order;
                    if (!newOrder) {
                        cout << "Alokasi memori gagal.\n";
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
                    cout << "Berhasil memesan!\n";
                    system("pause");
                    return;
                } else {
                    cout << "Saldo anda tidak mencukupi silahkan lakukan top-up terlebih dahulu ^_^.\n";
                    system("pause");
                    return;
                }
            }
        }
        cout << "Nama jasa tidak ditemukan.\n";
        system("pause");
    }
}