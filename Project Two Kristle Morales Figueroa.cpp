//============================================================================
// Name        : Project Two Kristle Morales Figueroa.cpp
// Author      : Kristle Morales Figueroa
// Version     : 1.0
// Description : Hash Table for a course list.
//============================================================================


#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <algorithm>
#include <vector>

using namespace std;

//============================================================================
//    Defining structures
//============================================================================

const unsigned int DEFAULT_SIZE = 180;

struct Course {        // structure to hold course information
    string courseId;
    string courseName;
    string preReq1;
    string preReq2;

};

//============================================================================
//    Class definitions
//============================================================================

class HashTable {

private:
    
    struct Node {
        Course course;
        unsigned int key;
        Node* next;

        Node() {  //default constructor
            key = UINT_MAX;
            next = nullptr;
        }

        Node(Course aCourse) : Node() {   //initializing constructore with a course
            course = aCourse;
        }

        Node(Course aCourse, unsigned int aKey) : Node(aCourse) {    //initializing with a course and a key
            key = aKey;
        }
    };

    vector<Node> nodes;

    unsigned int tableSize = DEFAULT_SIZE;

    unsigned int hash(int key) const;

public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(Course course);
    void PrintAll();
    Course Search(string courseId);
};

// ** Default Constructor ** //
HashTable::HashTable() {     // initilizing the data structure to hold course information
    nodes.resize(tableSize);
}

// ** Constructor for table size ** //
HashTable::HashTable(unsigned int size) {
    this->tableSize = size;
    nodes.resize(tableSize);

}

// ** Destructor ** //
HashTable::~HashTable() {   //freeing some storage by erasing nodes at the begining 
    nodes.erase(nodes.begin());
}

unsigned int HashTable::hash(int key) const {  //Calculating the hash value of a given key
    return key % tableSize;
}

// ** Insert data into the structure ** //
void HashTable::Insert(Course course) {
    unsigned key = hash(atoi(course.courseId.c_str()));   //create a key the given course
    
    Node* oldNode = &(nodes.at(key));   //retrieve node using key

    if (oldNode == nullptr) {  //if no entry is found
        Node* newNode = new Node(course, key);  //assign this node to the key position
        nodes.insert(nodes.begin() + key, (*newNode));
    }
    else {   // a node is found
        if (oldNode->key == UINT_MAX) {
            oldNode->key = key;     //assign the key
            oldNode->course = course;    //assign the course
            oldNode->next = nullptr;     //assign the next node to the nullptr
        }
        else {    //otherwise chain the node until null
            while (oldNode->next != nullptr) {
                oldNode = oldNode->next;
            }
            oldNode->next = new Node(course, key);
        }
    }
}

// ** Printing all courses ** //
void HashTable::PrintAll() {
    for (unsigned int i = 0; i < tableSize; i++) {  //loop to iterate through list
        Node* currNode = &nodes.at(i);

        if (currNode->key != UINT_MAX) {    //if the key is not UINT_MAX
            cout << currNode->key << " : " << currNode->course.courseId << " | " << currNode->course.courseName << " | " << currNode->course.preReq1 << " , " << currNode->course.preReq2 << endl;
        }
        else {    //node is equal to next iter

            while (currNode->next != nullptr) {
                cout << currNode->key << " : " << currNode->course.courseId << " | " << currNode->course.courseName << " | " << currNode->course.preReq1 << " , " << currNode->course.preReq2 << endl;

                currNode = currNode->next;
            }
            
        }
    }
    return;
}

// ** Search for a course ** //
Course HashTable::Search(string courseId) {
    Course course;
    unsigned key = hash(atoi(courseId.c_str()));    // create a key for the course
    Node* node = &(nodes.at(key));

    if (node != nullptr || node->key != UINT_MAX) {   // if no entry is found
        return course; // return course
    }

    if (node != nullptr && node->key != UINT_MAX && node->course.courseId.compare(courseId) == 0) {
        return node->course;
    }
    while (node != nullptr) {
        if (node->key != UINT_MAX && node->course.courseId.compare(courseId) == 0) {
            return node->course;
        }
        node = node->next;
    }
    return course;
}

// ** static methods ** //
void displayCourse(Course course) {
    cout << course.courseId << " : " << course.courseName << " | " << course.preReq1 << " , " << course.preReq2 << endl;
    return;
}

void loadCourses(string csvPath, HashTable* hashTable) {
    cout << "Load CSV file" << csvPath << endl;
    cout << "Enter file name: " << endl;
    cin >> "";
    
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        for (unsigned int i = 0; i < file.rowCount(); i++) {
            Course course;
            course.courseId = file[i][0];
            course.courseName = file[i][1];
            course.preReq1 = file[i][2];
            course.preReq2 = file[i][3];

            hashTable->Insert(course);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}



int main(int argc, char* argv[])
{
    HashTable* courseTable;

    Course course;
    courseTable = new HashTable();

    int choice = 0;
    while (choice != 9) {
        cout << "Welcome to the course planner." << endl;
        cout << " 1.Load Data Structure." << endl;
        cout << " 2.Print Course List." << endl;
        cout << " 3.Print Course." << endl;
        cout << " 9.Exit" << endl;
        cout << " What would you like to do?" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            loadCourses(csvPath, courseTable);
            break;

        case 2:
            courseTable->PrintAll();
            break;

        case 3:
            course = courseTable->Search(course.courseId);
            if (!course.courseId.empty()) {
                displayCourse(course);
            }
            else {
                cout << "Course Id " << course.courseId << " not found." << endl;
            }
            break;

        }
    }
    cout << "Good bye." << endl;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
