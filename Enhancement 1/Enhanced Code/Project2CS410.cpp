#include <iostream>       // for input/output
#include <vector>         // for using vectors
#include <string>         // for using strings

using namespace std;

// Struct to represent a client with a name and selected service
struct Client {
    string name;
    int serviceChoice; // 1 = brokerage, 2 = retirement
};

// Global list of clients
vector<Client> clients = {
    {"Bob Jones", 1},
    {"Sarah Davis", 2},
    {"Amy Friendly", 1},
    {"Johnny Smith", 1},
    {"Carol Spears", 2}
};

// Function to simulate a login check
bool CheckUserPermissionAccess() {
    string username;
    string password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    // Returns true if password is correct (password is hardcoded for simplicity)
    return password == "123";
}

// Function to display all clients and their selected services
void DisplayInfo() {
    cout << "\nClient List:\n";
    for (size_t i = 0; i < clients.size(); ++i) {
        cout << i + 1 << ". " << clients[i].name
            << " selected option " << clients[i].serviceChoice << endl;
    }
}

// Function to allow changing a client's selected service
void ChangeCustomerChoice() {
    int clientNum;
    int newService;

    // Show current client list first
    DisplayInfo();

    // Ask user to pick a client to modify
    cout << "\nEnter the number of the client you would like to change (1-" << clients.size() << "): ";
    cin >> clientNum;

    // Validate selected client number
    if (clientNum < 1 || clientNum > static_cast<int>(clients.size())) {
        cout << "Invalid client number.\n";
        return;
    }

    // Ask for new service selection
    cout << "Enter the client's new service choice (1 = brokerage, 2 = retirement): ";
    cin >> newService;

    // Validate service option
    if (newService != 1 && newService != 2) {
        cout << "Invalid service option.\n";
        return;
    }

    // Apply the change
    clients[clientNum - 1].serviceChoice = newService;
    cout << "Service updated successfully.\n";
}

// Main function - entry point of the program
int main() {
    cout << "Created by Luke Kundinger\n";
    cout << "Hello! Welcome to our Investment Company.\n";

    // Check if user is authorized to access the system
    if (!CheckUserPermissionAccess()) {
        cout << "Invalid Password. Please try again.\n";
        return 0; // exit the program
    }

    int choice = 0; // user menu selection

    // Menu loop runs until the user chooses to exit
    while (true) {
        cout << "\nMenu:\n";
        cout << "1 - DISPLAY the client list\n";
        cout << "2 - CHANGE a client's service choice\n";
        cout << "3 - EXIT the program\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle invalid (non-numeric) input
        if (cin.fail()) {
            cin.clear(); // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        // Perform the corresponding action
        switch (choice) {
        case 1:
            DisplayInfo(); // show all clients
            break;
        case 2:
            ChangeCustomerChoice(); // modify a client's service
            break;
        case 3:
            cout << "Goodbye!\n"; // end the program
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n"; // handle unexpected numbers
        }
    }
}

