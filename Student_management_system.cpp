/**
 * Student Information & Exam Management System
 * 
 * This program demonstrates all major RTU syllabus topics:
 * - Classes & Objects
 * - Pointers/Dynamic Memory
 * - Constructors/Destructors
 * - Inheritance & Virtual/Abstract Classes
 * - Polymorphism & Operator Overloading
 * - Templates
 * - Exception Handling
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <iomanip>
#include <limits>

// Avoiding 'using namespace std;' for better practice
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::runtime_error;
using std::out_of_range;
using std::exception;
using std::setw;
using std::left;
using std::fixed;
using std::setprecision;
using std::numeric_limits;
using std::streamsize;
using std::ostream;
using std::getline;

// ==================== EXCEPTION HANDLING ====================
// Custom exception classes
class InvalidCredentialsException : public runtime_error {
public:
    InvalidCredentialsException(const string& msg) : runtime_error(msg) {}
};

class StudentNotFoundException : public runtime_error {
public:
    StudentNotFoundException(const string& msg) : runtime_error(msg) {}
};

class InvalidMarksException : public runtime_error {
public:
    InvalidMarksException(const string& msg) : runtime_error(msg) {}
};

// ==================== TEMPLATES ====================
// Template class for generic data storage
template <typename T>
class Container {
private:
    T* data;
    int size;
    int capacity;
    
public:
    // Constructor
    Container(int cap = 10) : size(0), capacity(cap) {
        data = new T[capacity];
    }
    
    // Destructor
    ~Container() {
        delete[] data;
    }
    
    // Copy constructor (Rule of Five)
    Container(const Container& other) : size(other.size), capacity(other.capacity) {
        if (other.data != nullptr && capacity > 0) {
            data = new T[capacity];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
            size = 0;
            capacity = 0;
        }
    }
    
    // Copy assignment operator (Rule of Five)
    Container& operator=(const Container& other) {
        if (this != &other) {
            delete[] data;
            data = nullptr;
            size = other.size;
            capacity = other.capacity;
            
            if (other.data != nullptr && capacity > 0) {
                data = new T[capacity];
                for (int i = 0; i < size; i++) {
                    data[i] = other.data[i];
                }
            } else {
                size = 0;
                capacity = 0;
            }
        }
        return *this;
    }
    
    // Move constructor (Rule of Five)
    Container(Container&& other) noexcept 
        : data(other.data), size(other.size), capacity(other.capacity) {
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    
    // Move assignment operator (Rule of Five)
    Container& operator=(Container&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }
    
    void add(const T& item) {
        if (size >= capacity) {
            // Resize array with exception safety
            int newCapacity = capacity * 2;
            T* newData = nullptr;
            try {
                newData = new T[newCapacity];
                for (int i = 0; i < size; i++) {
                    newData[i] = data[i];
                }
                delete[] data;
                data = newData;
                capacity = newCapacity;
            } catch (...) {
                delete[] newData;
                throw;
            }
        }
        data[size++] = item;
    }
    
    T& get(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    int getSize() const { return size; }
};

// Template function for sorting
template <typename T>
void bubbleSort(vector<T*>& arr, bool (*compare)(T*, T*)) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare(arr[j], arr[j + 1])) {
                T* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// ==================== ABSTRACT BASE CLASS (POLYMORPHISM) ====================
// Abstract base class for Users
class User {
protected:
    string username;
    string password;
    string role;
    
public:
    // Constructor
    User(const string& uname, const string& pass, const string& r) 
        : username(uname), password(pass), role(r) {}
    
    // Virtual destructor
    virtual ~User() {}
    
    // Pure virtual function (abstract method)
    virtual void displayInfo() const = 0;
    
    // Virtual function
    virtual bool authenticate(const string& uname, const string& pass) const {
        return (username == uname && password == pass);
    }
    
    string getRole() const { return role; }
    string getUsername() const { return username; }
};

// ==================== INHERITANCE ====================
// Admin class inherits from User
class Admin : public User {
public:
    Admin(const string& uname, const string& pass) 
        : User(uname, pass, "Admin") {}
    
    void displayInfo() const override {
        cout << "\n╔════════════════════════════════╗" << endl;
        cout << "║        ADMIN PROFILE           ║" << endl;
        cout << "╚════════════════════════════════╝" << endl;
        cout << "Username: " << username << endl;
        cout << "Role: " << role << endl;
        cout << "Privileges: Full system access" << endl;
    }
};

// Teacher class inherits from User
class Teacher : public User {
private:
    string subject;
    
public:
    Teacher(const string& uname, const string& pass, const string& subj) 
        : User(uname, pass, "Teacher"), subject(subj) {}
    
    void displayInfo() const override {
        cout << "\n╔════════════════════════════════╗" << endl;
        cout << "║       TEACHER PROFILE          ║" << endl;
        cout << "╚════════════════════════════════╝" << endl;
        cout << "Username: " << username << endl;
        cout << "Role: " << role << endl;
        cout << "Subject: " << subject << endl;
    }
    
    string getSubject() const { return subject; }
};

// ==================== STUDENT CLASS WITH OPERATOR OVERLOADING ====================
class Student {
private:
    int rollNo;
    string name;
    string course;
    int* marks;  // Dynamic array for marks
    int numSubjects;
    
public:
    // Default Constructor
    Student() : rollNo(0), name(""), course(""), marks(nullptr), numSubjects(0) {}
    
    // Parameterized Constructor
    Student(int roll, const string& n, const string& c, int subjects = 5) 
        : rollNo(roll), name(n), course(c), numSubjects(subjects) {
        // Dynamic memory allocation
        marks = new int[numSubjects];
        for (int i = 0; i < numSubjects; i++) {
            marks[i] = 0;
        }
    }
    
    // Copy Constructor
    Student(const Student& other) 
        : rollNo(other.rollNo), name(other.name), course(other.course), 
          numSubjects(other.numSubjects) {
        if (other.marks != nullptr && numSubjects > 0) {
            marks = new int[numSubjects];
            for (int i = 0; i < numSubjects; i++) {
                marks[i] = other.marks[i];
            }
        } else {
            marks = nullptr;
            numSubjects = 0;  // Ensure consistency
        }
    }
    
    // Destructor
    ~Student() {
        if (marks != nullptr) {
            delete[] marks;
            marks = nullptr;
        }
    }
    
    // Assignment operator overloading
    Student& operator=(const Student& other) {
        if (this != &other) {
            // Delete old data
            if (marks != nullptr) {
                delete[] marks;
                marks = nullptr;
            }
            
            // Copy data
            rollNo = other.rollNo;
            name = other.name;
            course = other.course;
            numSubjects = other.numSubjects;
            
            if (other.marks != nullptr && numSubjects > 0) {
                marks = new int[numSubjects];
                for (int i = 0; i < numSubjects; i++) {
                    marks[i] = other.marks[i];
                }
            } else {
                marks = nullptr;
                numSubjects = 0;  // Ensure consistency
            }
        }
        return *this;
    }
    
    // Comparison operator for sorting (less than)
    bool operator<(const Student& other) const {
        return getAverage() < other.getAverage();
    }
    
    // Comparison operator for sorting (greater than)
    bool operator>(const Student& other) const {
        return getAverage() > other.getAverage();
    }
    
    // Stream insertion operator overloading
    friend ostream& operator<<(ostream& os, const Student& s) {
        os << "Roll No: " << s.rollNo << ", Name: " << s.name 
           << ", Course: " << s.course << ", Average: " 
           << fixed << setprecision(2) << s.getAverage();
        return os;
    }
    
    // Setters
    void setRollNo(int roll) { rollNo = roll; }
    void setName(const string& n) { name = n; }
    void setCourse(const string& c) { course = c; }
    
    void setMarks(int subject, int mark) {
        if (subject < 0 || subject >= numSubjects) {
            throw InvalidMarksException("Invalid subject index");
        }
        if (mark < 0 || mark > 100) {
            throw InvalidMarksException("Marks must be between 0 and 100");
        }
        marks[subject] = mark;
    }
    
    // Getters
    int getRollNo() const { return rollNo; }
    string getName() const { return name; }
    string getCourse() const { return course; }
    int getMarks(int subject) const {
        if (marks == nullptr || subject < 0 || subject >= numSubjects) {
            return 0;
        }
        return marks[subject];
    }
    int getNumSubjects() const { return numSubjects; }
    
    double getAverage() const {
        if (marks == nullptr || numSubjects == 0) return 0.0;
        int total = 0;
        for (int i = 0; i < numSubjects; i++) {
            total += marks[i];
        }
        return static_cast<double>(total) / numSubjects;
    }
    
    void displayInfo() const {
        cout << "\n╔════════════════════════════════════════════╗" << endl;
        cout << "║          STUDENT INFORMATION               ║" << endl;
        cout << "╚════════════════════════════════════════════╝" << endl;
        cout << "Roll Number: " << rollNo << endl;
        cout << "Name: " << name << endl;
        cout << "Course: " << course << endl;
        cout << "Marks:" << endl;
        if (marks != nullptr) {
            for (int i = 0; i < numSubjects; i++) {
                cout << "  Subject " << (i + 1) << ": " << marks[i] << endl;
            }
        } else {
            cout << "  No marks recorded" << endl;
        }
        cout << "Average: " << fixed << setprecision(2) << getAverage() << endl;
        cout << "Grade: " << getGrade() << endl;
    }
    
    string getGrade() const {
        double avg = getAverage();
        if (avg >= 90) return "A+";
        else if (avg >= 80) return "A";
        else if (avg >= 70) return "B";
        else if (avg >= 60) return "C";
        else if (avg >= 50) return "D";
        else return "F";
    }
};

// ==================== EXAM CLASS ====================
class Exam {
private:
    string examName;
    string examDate;
    int totalMarks;
    
public:
    Exam(const string& name, const string& date, int marks) 
        : examName(name), examDate(date), totalMarks(marks) {}
    
    void displayExamInfo() const {
        cout << "\n╔════════════════════════════════╗" << endl;
        cout << "║        EXAM DETAILS            ║" << endl;
        cout << "╚════════════════════════════════╝" << endl;
        cout << "Exam Name: " << examName << endl;
        cout << "Date: " << examDate << endl;
        cout << "Total Marks: " << totalMarks << endl;
    }
    
    string getExamName() const { return examName; }
};

// ==================== MANAGEMENT SYSTEM CLASS ====================
class ManagementSystem {
private:
    vector<Student*> students;  // Using pointers for dynamic polymorphism
    vector<User*> users;
    User* currentUser;
    
    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
public:
    // Constructor
    ManagementSystem() : currentUser(nullptr) {
        // Initialize with default users
        users.push_back(new Admin("admin", "admin123"));
        users.push_back(new Teacher("teacher1", "teacher123", "Mathematics"));
        users.push_back(new Teacher("teacher2", "teacher456", "Physics"));
    }
    
    // Destructor - cleanup dynamic memory
    ~ManagementSystem() {
        for (auto student : students) {
            delete student;
        }
        for (auto user : users) {
            delete user;
        }
    }
    
    // Login functionality
    bool login(const string& username, const string& password) {
        try {
            for (auto user : users) {
                if (user->authenticate(username, password)) {
                    currentUser = user;
                    cout << "\n✓ Login successful!" << endl;
                    currentUser->displayInfo();
                    return true;
                }
            }
            throw InvalidCredentialsException("Invalid username or password");
        } catch (const InvalidCredentialsException& e) {
            cout << "\n✗ Error: " << e.what() << endl;
            return false;
        }
    }
    
    void logout() {
        currentUser = nullptr;
        cout << "\n✓ Logged out successfully!" << endl;
    }
    
    // Add new student
    void addStudent() {
        if (currentUser == nullptr || currentUser->getRole() != "Admin") {
            cout << "\n✗ Only Admin can add students!" << endl;
            return;
        }
        
        try {
            int roll, subjects;
            string name, course;
            
            cout << "\n╔════════════════════════════════╗" << endl;
            cout << "║        ADD NEW STUDENT         ║" << endl;
            cout << "╚════════════════════════════════╝" << endl;
            
            cout << "Enter Roll Number: ";
            cin >> roll;
            clearInputBuffer();
            
            // Check if roll number already exists
            for (auto student : students) {
                if (student->getRollNo() == roll) {
                    throw runtime_error("Student with this roll number already exists");
                }
            }
            
            cout << "Enter Name: ";
            getline(cin, name);
            
            cout << "Enter Course: ";
            getline(cin, course);
            
            cout << "Enter number of subjects (default 5): ";
            cin >> subjects;
            clearInputBuffer();
            
            if (subjects <= 0) {
                throw InvalidMarksException("Number of subjects must be positive");
            }
            
            // Dynamic memory allocation
            Student* newStudent = new Student(roll, name, course, subjects);
            students.push_back(newStudent);
            
            cout << "\n✓ Student added successfully!" << endl;
        } catch (const exception& e) {
            cout << "\n✗ Error: " << e.what() << endl;
        }
    }
    
    // Update student details
    void updateStudent() {
        if (currentUser == nullptr || currentUser->getRole() != "Admin") {
            cout << "\n✗ Only Admin can update student details!" << endl;
            return;
        }
        
        try {
            int roll;
            cout << "\n╔════════════════════════════════╗" << endl;
            cout << "║      UPDATE STUDENT DETAILS    ║" << endl;
            cout << "╚════════════════════════════════╝" << endl;
            cout << "Enter Roll Number: ";
            cin >> roll;
            clearInputBuffer();
            
            Student* student = findStudent(roll);
            if (student == nullptr) {
                throw StudentNotFoundException("Student not found");
            }
            
            cout << "\nCurrent Details:" << endl;
            student->displayInfo();
            
            cout << "\nWhat do you want to update?" << endl;
            cout << "1. Name" << endl;
            cout << "2. Course" << endl;
            cout << "3. Both" << endl;
            cout << "Enter choice: ";
            
            int choice;
            cin >> choice;
            clearInputBuffer();
            
            string name, course;
            
            switch (choice) {
                case 1:
                    cout << "Enter new name: ";
                    getline(cin, name);
                    student->setName(name);
                    break;
                case 2:
                    cout << "Enter new course: ";
                    getline(cin, course);
                    student->setCourse(course);
                    break;
                case 3:
                    cout << "Enter new name: ";
                    getline(cin, name);
                    cout << "Enter new course: ";
                    getline(cin, course);
                    student->setName(name);
                    student->setCourse(course);
                    break;
                default:
                    cout << "Invalid choice!" << endl;
                    return;
            }
            
            cout << "\n✓ Student details updated successfully!" << endl;
            student->displayInfo();
        } catch (const exception& e) {
            cout << "\n✗ Error: " << e.what() << endl;
        }
    }
    
    // Conduct exam and enter marks
    void conductExam() {
        if (currentUser == nullptr) {
            cout << "\n✗ Please login first!" << endl;
            return;
        }
        
        if (currentUser->getRole() != "Admin" && currentUser->getRole() != "Teacher") {
            cout << "\n✗ Only Admin or Teacher can conduct exams!" << endl;
            return;
        }
        
        try {
            int roll;
            cout << "\n╔════════════════════════════════╗" << endl;
            cout << "║      CONDUCT EXAM & ENTER MARKS ║" << endl;
            cout << "╚════════════════════════════════╝" << endl;
            cout << "Enter Student Roll Number: ";
            cin >> roll;
            clearInputBuffer();
            
            Student* student = findStudent(roll);
            if (student == nullptr) {
                throw StudentNotFoundException("Student not found");
            }
            
            cout << "\nEntering marks for: " << student->getName() << endl;
            cout << "Number of subjects: " << student->getNumSubjects() << endl;
            
            for (int i = 0; i < student->getNumSubjects(); i++) {
                int marks;
                cout << "Enter marks for Subject " << (i + 1) << " (0-100): ";
                cin >> marks;
                
                student->setMarks(i, marks);
            }
            clearInputBuffer();
            
            cout << "\n✓ Marks entered successfully!" << endl;
            student->displayInfo();
        } catch (const exception& e) {
            cout << "\n✗ Error: " << e.what() << endl;
            clearInputBuffer();
        }
    }
    
    // Search student by roll number
    void searchStudent() {
        try {
            int roll;
            cout << "\n╔════════════════════════════════╗" << endl;
            cout << "║       SEARCH STUDENT           ║" << endl;
            cout << "╚════════════════════════════════╝" << endl;
            cout << "Enter Roll Number: ";
            cin >> roll;
            clearInputBuffer();
            
            Student* student = findStudent(roll);
            if (student == nullptr) {
                throw StudentNotFoundException("Student not found");
            }
            
            student->displayInfo();
        } catch (const exception& e) {
            cout << "\n✗ Error: " << e.what() << endl;
        }
    }
    
    // Sort students by marks (average)
    void sortStudentsByMarks() {
        if (students.empty()) {
            cout << "\n✗ No students in the system!" << endl;
            return;
        }
        
        cout << "\n╔════════════════════════════════╗" << endl;
        cout << "║     SORT STUDENTS BY MARKS     ║" << endl;
        cout << "╚════════════════════════════════╝" << endl;
        cout << "1. Ascending Order" << endl;
        cout << "2. Descending Order" << endl;
        cout << "Enter choice: ";
        
        int choice;
        cin >> choice;
        clearInputBuffer();
        
        // Validate choice
        if (choice != 1 && choice != 2) {
            cout << "\n✗ Invalid choice! Please select 1 or 2." << endl;
            return;
        }
        
        // Create a copy of the vector for sorting
        vector<Student*> sortedStudents = students;
        
        // Using template function for sorting
        if (choice == 1) {
            bubbleSort<Student>(sortedStudents, [](Student* a, Student* b) {
                return a->getAverage() > b->getAverage();
            });
        } else {
            bubbleSort<Student>(sortedStudents, [](Student* a, Student* b) {
                return a->getAverage() < b->getAverage();
            });
        }
        
        cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                    SORTED STUDENT LIST                     ║" << endl;
        cout << "╚════════════════════════════════════════════════════════════╝" << endl;
        cout << left << setw(10) << "Roll No" << setw(20) << "Name" 
             << setw(15) << "Course" << setw(10) << "Average" << "Grade" << endl;
        cout << string(65, '-') << endl;
        
        for (auto student : sortedStudents) {
            cout << left << setw(10) << student->getRollNo() 
                 << setw(20) << student->getName()
                 << setw(15) << student->getCourse()
                 << setw(10) << fixed << setprecision(2) << student->getAverage()
                 << student->getGrade() << endl;
        }
    }
    
    // Display all students
    void displayAllStudents() {
        if (students.empty()) {
            cout << "\n✗ No students in the system!" << endl;
            return;
        }
        
        cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                      ALL STUDENTS                          ║" << endl;
        cout << "╚════════════════════════════════════════════════════════════╝" << endl;
        cout << left << setw(10) << "Roll No" << setw(20) << "Name" 
             << setw(15) << "Course" << setw(10) << "Average" << "Grade" << endl;
        cout << string(65, '-') << endl;
        
        for (auto student : students) {
            cout << left << setw(10) << student->getRollNo() 
                 << setw(20) << student->getName()
                 << setw(15) << student->getCourse()
                 << setw(10) << fixed << setprecision(2) << student->getAverage()
                 << student->getGrade() << endl;
        }
    }
    
    // Helper function to find student by roll number
    Student* findStudent(int roll) {
        for (auto student : students) {
            if (student->getRollNo() == roll) {
                return student;
            }
        }
        return nullptr;
    }
    
    User* getCurrentUser() const { return currentUser; }
};

// ==================== MAIN MENU FUNCTIONS ====================
void displayMainMenu() {
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║     STUDENT INFORMATION & EXAM MANAGEMENT SYSTEM           ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    cout << "1. Login" << endl;
    cout << "2. Exit" << endl;
    cout << "Enter choice: ";
}

void displayUserMenu(User* user) {
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                      MAIN MENU                             ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    cout << "Logged in as: " << user->getUsername() << " (" << user->getRole() << ")" << endl;
    cout << string(60, '-') << endl;
    
    if (user->getRole() == "Admin") {
        cout << "1. Add New Student" << endl;
        cout << "2. Update Student Details" << endl;
        cout << "3. Conduct Exam & Enter Marks" << endl;
        cout << "4. Search Student by Roll Number" << endl;
        cout << "5. Sort Students by Marks" << endl;
        cout << "6. Display All Students" << endl;
        cout << "7. Logout" << endl;
        cout << "8. Exit" << endl;
    } else if (user->getRole() == "Teacher") {
        cout << "1. Conduct Exam & Enter Marks" << endl;
        cout << "2. Search Student by Roll Number" << endl;
        cout << "3. Sort Students by Marks" << endl;
        cout << "4. Display All Students" << endl;
        cout << "5. Logout" << endl;
        cout << "6. Exit" << endl;
    }
    
    cout << "Enter choice: ";
}

// ==================== MAIN FUNCTION ====================
int main() {
    ManagementSystem system;
    
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                         WELCOME TO                         ║" << endl;
    cout << "║     STUDENT INFORMATION & EXAM MANAGEMENT SYSTEM           ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    cout << "\nThis system demonstrates:" << endl;
    cout << "✓ Classes & Objects" << endl;
    cout << "✓ Pointers & Dynamic Memory" << endl;
    cout << "✓ Constructors & Destructors" << endl;
    cout << "✓ Inheritance & Virtual/Abstract Classes" << endl;
    cout << "✓ Polymorphism & Operator Overloading" << endl;
    cout << "✓ Templates" << endl;
    cout << "✓ Exception Handling" << endl;
    
    cout << "\n\nDefault Login Credentials:" << endl;
    cout << "Admin - Username: admin, Password: admin123" << endl;
    cout << "Teacher 1 - Username: teacher1, Password: teacher123" << endl;
    cout << "Teacher 2 - Username: teacher2, Password: teacher456" << endl;
    
    while (true) {
        if (system.getCurrentUser() == nullptr) {
            displayMainMenu();
            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            if (choice == 1) {
                string username, password;
                cout << "\n╔════════════════════════════════╗" << endl;
                cout << "║           LOGIN                ║" << endl;
                cout << "╚════════════════════════════════╝" << endl;
                cout << "Username: ";
                getline(cin, username);
                cout << "Password: ";
                getline(cin, password);
                
                system.login(username, password);
            } else if (choice == 2) {
                cout << "\nThank you for using the system. Goodbye!" << endl;
                break;
            } else {
                cout << "\n✗ Invalid choice!" << endl;
            }
        } else {
            displayUserMenu(system.getCurrentUser());
            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            if (system.getCurrentUser()->getRole() == "Admin") {
                switch (choice) {
                    case 1:
                        system.addStudent();
                        break;
                    case 2:
                        system.updateStudent();
                        break;
                    case 3:
                        system.conductExam();
                        break;
                    case 4:
                        system.searchStudent();
                        break;
                    case 5:
                        system.sortStudentsByMarks();
                        break;
                    case 6:
                        system.displayAllStudents();
                        break;
                    case 7:
                        system.logout();
                        break;
                    case 8:
                        cout << "\nThank you for using the system. Goodbye!" << endl;
                        return 0;
                    default:
                        cout << "\n✗ Invalid choice!" << endl;
                }
            } else if (system.getCurrentUser()->getRole() == "Teacher") {
                switch (choice) {
                    case 1:
                        system.conductExam();
                        break;
                    case 2:
                        system.searchStudent();
                        break;
                    case 3:
                        system.sortStudentsByMarks();
                        break;
                    case 4:
                        system.displayAllStudents();
                        break;
                    case 5:
                        system.logout();
                        break;
                    case 6:
                        cout << "\nThank you for using the system. Goodbye!" << endl;
                        return 0;
                    default:
                        cout << "\n✗ Invalid choice!" << endl;
                }
            }
        }
    }
    
    return 0;
}
