#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
unsigned int DEFAULT_SIZE = 1;
//define a structure to hold bid information
struct Course {
    string courseNumber; //unique identifier
    string name;
    string prerequisites;
};
//hash table class definition
class HashTable {
//define structures to hold course info
private:
    struct Node {
        Course course;
        unsigned int key;
        Node* next;
        //default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }
        //initialize with a course
        Node(Course aCourse) : Node() {
            course = aCourse;
        }
        //initialize with a course and a key
        Node(Course aCourse, unsigned int aKey) : Node(aCourse) {
            key = aKey;
        }
    };

    unsigned int tableSize = DEFAULT_SIZE;

    unsigned int hash(int key);

public:
    vector<Node> nodes;
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(Course course);
    Course Search(string coursenum);
    void selectionSort(vector<Node>& nodes);
    void readFile(HashTable* hashTable);

};

HashTable::HashTable() {
    //initialize node structure by resizing table
    nodes.resize(tableSize);
}
//specify size of table
HashTable::HashTable(unsigned int size) {
    this->tableSize = size;//invoke local table size
    nodes.resize(tableSize);//resize nodes size

}
//destructor
HashTable::~HashTable() {
    //erase nodes beginning
    nodes.erase(nodes.begin());
}
//calculate hash value of a key
unsigned int HashTable::hash(int key) {
    //calculate hash value
    key = key % tableSize;
    return key;//return key
}
//function to read file
void HashTable::readFile(HashTable* hashTable) {

    ifstream infile;
    string fileName = "courseInfo.txt";
    infile.open(fileName);
    string line;
    char seperator = ',';
    //if file matches courses file
    if (infile.is_open()) {
        while (!infile.eof()) {//get all courses until end
            getline(infile, line);
            stringstream s_stream(line);
            vector<string> courseInfo;
            while (s_stream.good()) {
                string substr;
                getline(s_stream, substr, ',');
                courseInfo.push_back(substr);
            }
            //create course in hash table
            Course newcourse;
            newcourse.courseNumber = courseInfo[0];
            newcourse.name = courseInfo[1];
            //for courses with prerequisites
            if (courseInfo.size() > 2) {
                for (int i = 2; i < courseInfo.size() - 1; ++i) {
                    newcourse.prerequisites = courseInfo[i] + ", " + courseInfo[i + 1];
                }
            }
            hashTable->Insert(newcourse);//insert into hash table
        }
    }
}
//add courses to vector and sort courses in alphanumeric order
void HashTable::selectionSort(vector<Node>& vecToSort) {
    cout << "Here is a sample schedule: " << endl;//output for option 2
    cout << endl;

    vector<Node> sortedCourses;
    unsigned int i;
    unsigned int j;
    unsigned int indexSmallest = 0;
    Node temp;
    vector <Node> vecs;

    for (unsigned int n = 0; n < nodes.size(); n++) {//loop each course until end
        unsigned key = hash(atoi(nodes.at(n).course.courseNumber.c_str()));
        Node* node = &(nodes.at(key));
        if (nodes.at(key).key != UINT_MAX) {
            sortedCourses.push_back(nodes.at(n));
            while (node->next != nullptr) {
                node = node->next;//node equal to next
                sortedCourses.push_back(*node);
            }
        }
    }
    for (i = 0; i < sortedCourses.size() - 1; ++i) {//sort courses in order
        indexSmallest = i;
        for (j = i + 1; j < sortedCourses.size(); ++j) {
            if (sortedCourses[j].course.courseNumber < sortedCourses[indexSmallest].course.courseNumber) {
                indexSmallest = j;
            }
        }
        temp = sortedCourses[i];//temp value
        sortedCourses[i] = sortedCourses[indexSmallest];
        sortedCourses[indexSmallest] = temp;//added value to sort
    }
    for (i = 0; i < sortedCourses.size(); i++) {//print sorted courses
        cout << sortedCourses.at(i).course.courseNumber << ", " << sortedCourses.at(i).course.name << endl;
    }
}

void HashTable::Insert(Course course) {
    //key for given course
    unsigned key = hash(atoi(course.courseNumber.c_str()));
    //retrieve node using key
    Node* oldNode = &(nodes.at(key));
    //if no entry found for key assign node to key position
    if (oldNode == nullptr) {
        Node* newNode = new Node(course, key);
        nodes.insert(nodes.begin() + key, (*newNode));
    }
    else {//if node is not used
        if (oldNode->key == UINT_MAX) {//assign old node to UINT_MAX
            oldNode->key = key;//set to key
            oldNode->course = course;//set old node to course
            oldNode->next = nullptr;//set old node next to null pointer
        }
        else {
            //find next open node
            while (oldNode->next != nullptr) {
                oldNode = oldNode->next;
            }
            oldNode->next = new Node(course, key);//new node to end

        }
    }
}

Course HashTable::Search(string coursenum) {
    Course course;
    //create key for given course
    unsigned key = hash(atoi(coursenum.c_str()));
    //if entry found for key
    Node* node = &(nodes.at(key));
    //if node not equal to null pointer return it
    if (node != nullptr && node->key != UINT_MAX&& node->course.courseNumber.compare(coursenum) == 0) {
        return node->course;
    }
    if (node == nullptr || node->key == UINT_MAX) {
        return course;
    }
    while (node != nullptr) {
        if (node->key != UINT_MAX && node->course.courseNumber.compare(coursenum) == 0) {
            return node->course;
        }
        node = node->next;
    }
    return course;
}

//one and only main method
int main() {
    Course course;
    int choice = 0;
    HashTable* courseTable = nullptr;
    cout << "Welcome to the schedule planner." << endl;//display menu
    cout << endl;
    cout << "  1. Load Data Structure." << endl;
    cout << "  2. Print Course List." << endl;
    cout << "  3. Print Course." << endl;
    cout << "  4. Exit" << endl;
    choice = choice;

    while (choice != 4){//enter loop until user chooses quit
        cout << "What would you like to do?" << endl;//prompt user for choice
        cin >> choice;//return choice
        switch (choice) {//menu loop

            case 1: {//necessary to load data
                courseTable = new HashTable();
                courseTable->readFile(courseTable);
                break;
            }
            case 2: {//lists all courses in alphanumeric order
                courseTable->selectionSort(courseTable->nodes);
                break;
            }
            case 3: {//get info for specific course
                string coursenum;
                cout << "What course do you want to know about?" << endl;//prompt user for course
                cin >> coursenum;//return course

                course = courseTable->Search(coursenum);//find course user wants
                cout << course.courseNumber << ", " << course.name << endl;//print in format
                cout << "Prerequisites: " << course.prerequisites << endl;
                break;
            }
            case 4: {//if user enters quit
                break;
            }
            default: {//if number 1-4 is not entered
                cout << choice << " is not a valid option." << endl;
                break;
            }
        }
    }//end program
    cout << "Thank you for using the course planner!" << endl;
    return 0;
}


