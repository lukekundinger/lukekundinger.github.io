#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <limits>

using namespace std;

class WordFrequency {
private:
    map<string, int> itemFreqMap;

public:
    void loadFile(const string& filename) {
        ifstream inputFile(filename);
        if (!inputFile) {
            cerr << "Error: Cannot open file " << filename << endl;
            return;
        }

        string item;
        while (inputFile >> item) {
            ++itemFreqMap[item];
        }

        inputFile.close();
    }

    int getFrequency(const string& item) const {
        auto it = itemFreqMap.find(item);
        return (it != itemFreqMap.end()) ? it->second : 0;
    }

    void printFrequency() const {
        if (itemFreqMap.empty()) {
            cout << "No data loaded.\n";
            return;
        }

        cout << "\nItem Frequencies:\n";
        for (const auto& pair : itemFreqMap) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }

    void printHistogram() const {
        if (itemFreqMap.empty()) {
            cout << "No data to display.\n";
            return;
        }

        cout << "\nItem Histogram:\n";
        for (const auto& pair : itemFreqMap) {
            cout << pair.first << ": " << string(pair.second, '*') << endl;
        }
    }

    void saveFrequencyData(const string& filename) const {
        ofstream outputFile(filename);
        if (!outputFile) {
            cerr << "Error: Cannot write to file " << filename << endl;
            return;
        }

        for (const auto& pair : itemFreqMap) {
            outputFile << pair.first << " " << pair.second << endl;
        }

        outputFile.close();
    }
};

void displayMenu() {
    cout << "\nMenu Options:\n";
    cout << "1 - Get frequency of a specific item\n";
    cout << "2 - Display frequency of all items\n";
    cout << "3 - Print item histogram\n";
    cout << "4 - Exit program\n";
    cout << "Enter your choice: ";
}

int main() {
    WordFrequency tracker;
    tracker.loadFile("wordList.txt");
    tracker.saveFrequencyData("frequency.dat");

    int choice;
    string item;

    while (true) {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); // clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
            cout << "Invalid input. Please enter a number from 1 to 4.\n";
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter item: ";
            cin >> item;
            cout << "Frequency of \"" << item << "\": " << tracker.getFrequency(item) << endl;
            break;
        case 2:
            tracker.printFrequency();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            cout << "Exiting program. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Please enter a number from 1 to 4.\n";
        }
    }

    return 0;
}