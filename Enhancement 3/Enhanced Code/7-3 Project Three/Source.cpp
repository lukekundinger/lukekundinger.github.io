#include <iostream>     // for input and output
#include <fstream>      // for file input/output
#include <map>          // for using the map container
#include <string>       // for using strings
#include <limits>       // for numeric_limits, used when handling invalid input

using namespace std;

// Class to track frequency of words/items from a file
class WordFrequency {
private:
    map<string, int> itemFreqMap; // map to store item names and their corresponding frequencies

public:
    // Loads item frequencies from a given file
    void loadFile(const string& filename) {
        ifstream inputFile(filename); // open file for reading
        if (!inputFile) {
            cerr << "Error: Cannot open file " << filename << endl;
            return; // exit function if file cannot be opened
        }

        string item;
        while (inputFile >> item) { // read each item (word) from file
            ++itemFreqMap[item];    // increment frequency count
        }

        inputFile.close(); // close file when done
    }

    // Returns the frequency of a specific item
    int getFrequency(const string& item) const {
        auto it = itemFreqMap.find(item); // search for item in map
        return (it != itemFreqMap.end()) ? it->second : 0; // return frequency or 0 if not found
    }

    // Prints all item frequencies
    void printFrequency() const {
        if (itemFreqMap.empty()) { // check if data has been loaded
            cout << "No data loaded.\n";
            return;
        }

        cout << "\nItem Frequencies:\n";
        for (const auto& pair : itemFreqMap) { // loop through all items
            cout << pair.first << ": " << pair.second << endl; // print item and frequency
        }
    }

    // Prints histogram of items using asterisks to represent counts
    void printHistogram() const {
        if (itemFreqMap.empty()) { // check if map has any data
            cout << "No data to display.\n";
            return;
        }

        cout << "\nItem Histogram:\n";
        for (const auto& pair : itemFreqMap) { // loop through each item
            cout << pair.first << ": " << string(pair.second, '*') << endl; // display item and stars
        }
    }

    // Saves item frequencies to a new file
    void saveFrequencyData(const string& filename) const {
        ofstream outputFile(filename); // open file for writing
        if (!outputFile) {
            cerr << "Error: Cannot write to file " << filename << endl;
            return;
        }

        for (const auto& pair : itemFreqMap) { // loop through all items
            outputFile << pair.first << " " << pair.second << endl; // write item and frequency to file
        }

        outputFile.close(); // close the output file
    }
};

// Displays the main menu
void displayMenu() {
    cout << "\nMenu Options:\n";
    cout << "1 - Get frequency of a specific item\n";
    cout << "2 - Display frequency of all items\n";
    cout << "3 - Print item histogram\n";
    cout << "4 - Exit program\n";
    cout << "Enter your choice: ";
}

int main() {
    WordFrequency tracker; // create an instance of WordFrequency

    tracker.loadFile("wordList.txt");         // load item data from input file
    tracker.saveFrequencyData("frequency.dat"); // save the frequency data to an output file

    int choice;
    string item;

    // Loop to keep showing the menu until the user exits
    while (true) {
        displayMenu(); // show menu
        cin >> choice; // get user's menu choice

        if (cin.fail()) { // check for invalid input (e.g., letters instead of numbers)
            cin.clear(); // reset error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number from 1 to 4.\n";
            continue; // prompt user again
        }

        // Process the user's menu choice
        switch (choice) {
        case 1: // get frequency of a specific item
            cout << "Enter item: ";
            cin >> item;
            cout << "Frequency of \"" << item << "\": " << tracker.getFrequency(item) << endl;
            break;
        case 2: // display all item frequencies
            tracker.printFrequency();
            break;
        case 3: // print histogram using asterisks
            tracker.printHistogram();
            break;
        case 4: // exit the program
            cout << "Exiting program. Goodbye!\n";
            return 0;
        default: // handle menu options outside 1-4
            cout << "Invalid choice. Please enter a number from 1 to 4.\n";
        }
    }

    return 0; // not reached, but good practice
}
