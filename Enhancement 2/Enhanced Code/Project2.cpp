#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;

// default size for hash table
const unsigned int DEFAULT_SIZE = 10;

// define a structure to hold course information
struct Course {
    string courseNumber;                  // unique identifier
    string name;                          // name of course
    vector<string> prerequisites;        // list of prerequisite course numbers
};

// define a hash table class
class HashTable {
private:
    // define structure to hold individual nodes
    struct Node {
        Course course;                   // course data
        unsigned int key = UINT_MAX;     // hash key
        Node* next = nullptr;            // pointer to next node (linked list)

        Node() = default;                // default constructor
        Node(Course course, unsigned int key) : course(course), key(key) {}
    };

    vector<Node*> table;                 // vector of pointers for hash table
    unsigned int tableSize;              // size of hash table

    // generate hash from course number (simple additive hash)
    unsigned int hash(const string& courseNumber) const {
        unsigned int hashVal = 0;
        for (char c : courseNumber) {
            hashVal += static_cast<unsigned int>(c);
        }
        return hashVal % tableSize;
    }

public:
    // constructor to initialize hash table size
    HashTable(unsigned int size = DEFAULT_SIZE) : tableSize(size) {
        table.resize(tableSize, nullptr);
    }

    // destructor to delete all nodes
    ~HashTable() {
        for (Node* node : table) {
            while (node) {
                Node* temp = node;
                node = node->next;
                delete temp;
            }
        }
    }

    // insert a new course into the hash table
    void Insert(const Course& course) {
        unsigned int key = hash(course.courseNumber);  // generate key
        Node* newNode = new Node(course, key);         // create new node

        if (!table[key]) {
            table[key] = newNode;                      // insert directly if slot is empty
        }
        else {
            Node* current = table[key];
            while (current->next) {
                current = current->next;               // go to end of linked list
            }
            current->next = newNode;                   // append new node
        }
    }

    // search for a course in the hash table
    Course Search(const string& courseNumber) const {
        unsigned int key = hash(courseNumber);         // get hash key
        Node* current = table[key];                    // start at head node

        while (current) {
            if (current->course.courseNumber == courseNumber) {
                return current->course;                // found match
            }
            current = current->next;                   // move to next node
        }

        return Course();                               // return empty if not found
    }

    // read course data from file and insert into table
    void LoadFromFile(const string& fileName) {
        ifstream infile(fileName);                     // open file

        if (!infile.is_open()) {
            cerr << "Failed to open file: " << fileName << endl;
            return;
        }

        string line;
        while (getline(infile, line)) {                // read each line
            stringstream ss(line);
            string segment;
            vector<string> tokens;

            while (getline(ss, segment, ',')) {
                tokens.push_back(segment);             // tokenize by comma
            }

            if (tokens.size() < 2) continue;           // skip invalid lines

            Course course;
            course.courseNumber = tokens[0];           // course number
            course.name = tokens[1];                   // course name

            for (size_t i = 2; i < tokens.size(); ++i) {
                course.prerequisites.push_back(tokens[i]); // store prerequisites
            }

            Insert(course);                            // insert course into hash table
        }

        infile.close();                                // close file
    }

    // print all courses in alphanumeric order
    void PrintAllCourses() const {
        vector<Course> courses;

        // gather all courses from the hash table
        for (Node* node : table) {
            while (node) {
                courses.push_back(node->course);       // add course to list
                node = node->next;
            }
        }

        // sort by course number
        sort(courses.begin(), courses.end(), [](const Course& a, const Course& b) {
            return a.courseNumber < b.courseNumber;
            });

        // output sorted course list
        cout << "\nHere is a sample schedule:\n\n";
        for (const auto& course : courses) {
            cout << course.courseNumber << ", " << course.name << endl;
        }
    }

    // print full details of a specific course
    void PrintCourseDetails(const string& courseNumber) const {
        Course course = Search(courseNumber);          // search for course

        if (course.courseNumber.empty()) {             // check if course was found
            cout << "Course not found.\n";
            return;
        }

        // display course details
        cout << course.courseNumber << ", " << course.name << endl;
        cout << "Prerequisites: ";
        if (course.prerequisites.empty()) {
            cout << "None";
        }
        else {
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                cout << course.prerequisites[i];
                if (i < course.prerequisites.size() - 1)
                    cout << ", ";
            }
        }
        cout << "\n";
    }
};

// main program entry point
int main() {
    HashTable courseTable;                 // create course hash table
    int choice = 0;                        // menu choice from user

    cout << "Welcome to the course planner.\n";

    // loop until user selects exit
    while (choice != 4) {
        // display menu options
        cout << "\n  1. Load Data Structure\n";
        cout << "  2. Print Course List\n";
        cout << "  3. Print Course\n";
        cout << "  4. Exit\n";
        cout << "\nWhat would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:                             // load data from file
            courseTable.LoadFromFile("courseInfo.txt");
            break;
        case 2:                             // print full course list
            courseTable.PrintAllCourses();
            break;
        case 3: {                           // print specific course
            string courseNumber;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            courseTable.PrintCourseDetails(courseNumber);
            break;
        }
        case 4:                             // exit program
            cout << "Thank you for using the course planner!\n";
            break;
        default:                            // invalid input
            cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}

