#include <iostream>
#include <vector>

using namespace std;

vector<int> serviceChoice{ 1,2,1,1,2 }; // store service choices for clients
int service1 = serviceChoice[0];
int service2 = serviceChoice[1];
int service3 = serviceChoice[2];
int service4 = serviceChoice[3];
int service5 = serviceChoice[4];

int CheckUserPermissionAccess() { //check if password is correct
    string username;
    string password;
    int answer = 0;

    cout << "Enter username: "; //username does not matter
    cin >> username;

    cout << "Enter password: "; //password must match
    cin >> password;

    if (password == "123") { //matching password
        answer = 1;
    }
    else { //wrong password
        answer = 2;
    }

    return answer; //for permission
}

void DisplayInfo() { //displays clients and their selected service
    cout << "Bob Jones " << "selected option " << service1 << endl;
    cout << "Sarah Davis " << "selected option " << service2 << endl;
    cout << "Amy Friendly " << "selected option " << service3 << endl;
    cout << "Johnny Smith " << "selected option " << service4 << endl;
    cout << "Carol Spears " << "selected option " << service5 << endl;

    return;
}

void ChangeCustomerChoice() { //change service of client
    int clientNum;
    int serviceChoice;

    cout << "Enter the number of the client you would like to change." << endl;
    cin >> clientNum;
    cout << "Please enter the client's new service choice (1 = brokerage, 2 = retirement)." << endl;
    cin >> serviceChoice;

    if (clientNum == 1) { //selected client
        service1 = serviceChoice; //new service choice
    }
    else if (clientNum == 2) {
        service2 = serviceChoice;
    }
    else if (clientNum == 3) {
        service3 = serviceChoice;
    }
    else if (clientNum == 4) {
        service4 = serviceChoice;
    }
    else if (clientNum == 5) {
        service5 = serviceChoice;
    }

    return;
}

int main() {

    cout << "Created by Luke Kundinger" << endl;
    cout << "Hello! Welcome to our Investment Company." << endl;

    int answer = CheckUserPermissionAccess(); //check permission
    if (answer == 1) { //permission allowed
        /* menu options*/
        cout << "What would you like to do?" << endl;
        cout << "DISPLAY the client list (enter 1)" << endl;
        cout << "CHANGE a client's choice (enter 2)" << endl;
        cout << "EXIT the program (enter 3)" << endl;
        int choice;
        cin >> choice; //get user choice
        cout << "You chose " << choice << endl;
        if (choice != 1 && choice != 2 && choice != 3) {
            cin.clear();
            cout << "Invalid choice. Please try again." << endl;
        }
        /* loop for navigating menu and function calls */
        if (choice == 1) {
            DisplayInfo();
        }
        else if (choice == 2) {
            ChangeCustomerChoice();
        }
        else if (choice == 3) {
            return 0;
        }
        else {
            return 0;
        }
    }
    else { //permission denied
        cout << "Invalid Password. Please try again." << endl;
    }
    return 0;
}
