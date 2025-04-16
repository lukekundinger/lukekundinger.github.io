#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Client {
    string name;
    int serviceChoice; // 1 = brokerage, 2 = retirement
};

vector<Client> clients = {
    {"Bob Jones", 1},
    {"Sarah Davis", 2},
    {"Amy Friendly", 1},
    {"Johnny Smith", 1},
    {"Carol Spears", 2}
};

bool CheckUserPermissionAccess() {
    string username;
    string password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    return password == "123";
}

void DisplayInfo() {
    cout << "\nClient List:\n";
    for (size_t i = 0; i < clients.size(); ++i) {
        cout << i + 1 << ". " << clients[i].name
            << " selected option " << clients[i].serviceChoice << endl;
    }
}

void ChangeCustomerChoice() {
    int clientNum;
    int newService;

    DisplayInfo();

    cout << "\nEnter the number of the client you would like to change (1-" << clients.size() << "): ";
    cin >> clientNum;

    if (clientNum < 1 || clientNum > static_cast<int>(clients.size())) {
        cout << "Invalid client number.\n";
        return;
    }

    cout << "Enter the client's new service choice (1 = brokerage, 2 = retirement): ";
    cin >> newService;

    if (newService != 1 && newService != 2) {
        cout << "Invalid service option.\n";
        return;
    }

    clients[clientNum - 1].serviceChoice = newService;
    cout << "Service updated successfully.\n";
}

int main() {
    cout << "Created by Luke Kundinger\n";
    cout << "Hello! Welcome to our Investment Company.\n";

    if (!CheckUserPermissionAccess()) {
        cout << "Invalid Password. Please try again.\n";
        return 0;
    }

    int choice = 0;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1 - DISPLAY the client list\n";
        cout << "2 - CHANGE a client's service choice\n";
        cout << "3 - EXIT the program\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1:
            DisplayInfo();
            break;
        case 2:
            ChangeCustomerChoice();
            break;
        case 3:
            cout << "Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
