#include <iostream>
#include <fstream>
#include <map>

using namespace std;

class wordFrequency {
private:
    map<string, int> itemFreqMap;

public:
    wordFrequency() {}

    void loadFile(string wordList) { // function to load input file
        ifstream inputFile(wordList);
        string item;
        while (inputFile >> item) {
            itemFreqMap[item]++;
        }
    }

    int getFrequency(string item) { // function to return frequency for an item
        if (itemFreqMap.find(item) == itemFreqMap.end()) {
            return 0;
        }
        else {
            return itemFreqMap[item];
        }
    }

    void printFrequency() { // function to print frequency
        for (auto const& item : itemFreqMap) {
            cout << item.first << " " << item.second << endl;
        }
    }

    void printHistogram() { // function to print histogram
        int maxFreq = 0;
        for (auto const& item : itemFreqMap) {
            if (item.second > maxFreq) {
                maxFreq = item.second;
            }
        }
        for (auto const& item : itemFreqMap) { // use '*' in place of number
            cout << item.first << " ";
            for (int i = 0; i < item.second; i++) {
                cout << "*";
            }
            cout << endl;
        }
    }
    void saveFrequencyData(string frequency) { // save data for backup
        ofstream outputFile(frequency);
        for (auto const& item : itemFreqMap) {
            outputFile << item.first << " " << item.second << endl;
        }
        outputFile.close();
    }
};

int main() {
    wordFrequency tracker; // declare variables
    tracker.loadFile("wordList.txt");
    tracker.saveFrequencyData("frequency.dat");

    int choice;
    string item;
    do { // display menu and prompt user to make choice
        cout << endl;
        cout << "Enter (1) to get frequency of item." << endl;
        cout << "Enter (2) to get frequency of all items." << endl;
        cout << "Enter (3) to print item histogram." << endl;
        cout << "Enter (4) to exit." << endl;
        cout << "Enter choice:" << endl;
        cin >> choice;

        switch (choice) { // switch statement with cases for user until finished
        case 1:
            cout << "Enter item: ";
            cin >> item;
            cout << tracker.getFrequency(item) << endl; // access function for each case
            break;
        case 2:
            tracker.printFrequency();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            cout << "Done." << endl;
            break;
        default:
            cout << "Choice invalid." << endl;
        }
    } while (choice != 4); // break loop if user enters 4 to quit

    return 0;
}