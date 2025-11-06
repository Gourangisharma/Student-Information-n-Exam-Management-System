# Student Information & Exam Management System

A comprehensive, self-contained C++ program that implements a Student Information & Exam Management System and explicitly demonstrates all major RTU syllabus topics.

## 🎯 Features Implemented

### Core Features
- ✅ **Add new student** - Admin can add students with roll number, name, course, and subjects
- ✅ **Update student details** - Admin can modify student information
- ✅ **Conduct exam and enter marks** - Teachers and Admin can enter marks for students
- ✅ **Search student by roll number** - Quick search functionality
- ✅ **Sort students by marks** - Sort in ascending or descending order
- ✅ **Teacher login** - Restricted access for teachers
- ✅ **Admin login** - Full system access for administrators

### RTU Syllabus Topics Demonstrated

#### 1. **Classes & Objects**
- Multiple classes: `Student`, `User`, `Admin`, `Teacher`, `Exam`, `ManagementSystem`, `Container`
- Proper encapsulation with private/protected/public members

#### 2. **Pointers & Dynamic Memory**
- Dynamic arrays using `new` and `delete` operators
- Vector of pointers: `vector<Student*>`, `vector<User*>`
- Smart memory management in destructors
- Dynamic array resizing in template class

#### 3. **Constructors & Destructors**
- Default constructors
- Parameterized constructors
- Copy constructors
- Virtual destructors
- Proper cleanup in destructors to prevent memory leaks

#### 4. **Inheritance & Virtual/Abstract Classes**
- `User` is an abstract base class with pure virtual function
- `Admin` and `Teacher` inherit from `User`
- Virtual function overriding
- Polymorphic behavior through base class pointers

#### 5. **Polymorphism & Operator Overloading**
- Runtime polymorphism with virtual functions
- Operator overloading:
  - Assignment operator (`=`)
  - Comparison operators (`<`, `>`)
  - Stream insertion operator (`<<`)
- Virtual function calls through base class pointers

#### 6. **Templates**
- Template class: `Container<T>` for generic data storage
- Template function: `bubbleSort<T>` for generic sorting
- Lambda functions with templates

#### 7. **Exception Handling**
- Custom exception classes:
  - `InvalidCredentialsException`
  - `StudentNotFoundException`
  - `InvalidMarksException`
- Try-catch blocks throughout the program
- Standard library exceptions: `runtime_error`, `out_of_range`

## 🚀 Compilation & Execution

### Using Makefile (Recommended)

```bash
# Compile the program
make

# Run the program
make run

# Clean compiled files
make clean
```

### Manual Compilation

```bash
# Compile
g++ -std=c++11 -Wall -Wextra -o student_management_system student_management_system.cpp

# Run
./student_management_system
```

## 🔐 Default Login Credentials

### Admin Account
- **Username:** `admin`
- **Password:** `admin123`
- **Privileges:** Full system access (add, update, conduct exams, search, sort, view all)

### Teacher Accounts

**Teacher 1 (Mathematics)**
- **Username:** `teacher1`
- **Password:** `teacher123`
- **Privileges:** Conduct exams, search students, sort, view all

**Teacher 2 (Physics)**
- **Username:** `teacher2`
- **Password:** `teacher456`
- **Privileges:** Conduct exams, search students, sort, view all

## 📖 Usage Guide

### 1. Login
- Start the program and select "Login"
- Enter username and password
- System will display your role and privileges

### 2. Add New Student (Admin Only)
- Select "Add New Student" from menu
- Enter roll number, name, course, and number of subjects
- Student is created with marks initialized to 0

### 3. Update Student Details (Admin Only)
- Select "Update Student Details"
- Enter roll number to search
- Choose what to update (name, course, or both)

### 4. Conduct Exam & Enter Marks
- Select "Conduct Exam & Enter Marks"
- Enter student roll number
- Enter marks for each subject (0-100)
- System validates marks and calculates average

### 5. Search Student
- Select "Search Student by Roll Number"
- Enter roll number
- View complete student information with marks and grade

### 6. Sort Students by Marks
- Select "Sort Students by Marks"
- Choose ascending or descending order
- View sorted list with averages and grades

### 7. Display All Students
- View complete list of all students in the system

## 🎓 Grading System

- **A+**: 90-100
- **A**: 80-89
- **B**: 70-79
- **C**: 60-69
- **D**: 50-59
- **F**: Below 50

## 🛡️ Security Features

- Password-protected login system
- Role-based access control
- Input validation for marks (0-100 range)
- Exception handling for invalid operations
- Protected roll number uniqueness

## 📊 Technical Highlights

### Memory Management
- Proper use of `new` and `delete` operators
- No memory leaks with destructors
- Deep copy in copy constructor and assignment operator

### Object-Oriented Design
- Abstract base class for polymorphic behavior
- Clear inheritance hierarchy
- Encapsulation of data members
- Proper use of access specifiers

### Error Handling
- Custom exception classes for specific errors
- Try-catch blocks for robust error handling
- Input validation and buffer clearing

### Generic Programming
- Template class for flexible data structures
- Template function for type-independent sorting
- Lambda functions for custom comparisons

## 🔧 System Requirements

- C++ compiler with C++11 support (g++, clang++, etc.)
- Standard C++ library
- Linux/Unix, macOS, or Windows with appropriate compiler

## 📝 Code Structure

```
student_management_system.cpp
├── Exception Classes
│   ├── InvalidCredentialsException
│   ├── StudentNotFoundException
│   └── InvalidMarksException
├── Template Classes & Functions
│   ├── Container<T>
│   └── bubbleSort<T>
├── Abstract Base Class
│   └── User (abstract)
├── Derived Classes
│   ├── Admin : User
│   └── Teacher : User
├── Main Classes
│   ├── Student (with operator overloading)
│   ├── Exam
│   └── ManagementSystem
└── Main Function & Menu System
```

## 🌟 Advanced Features

1. **Dynamic Array Resizing**: Container template class automatically resizes when capacity is reached
2. **Operator Overloading**: Student class supports comparison and streaming operators
3. **Polymorphic Collections**: Vectors of base class pointers for runtime polymorphism
4. **Role-Based Menus**: Different menu options based on user role
5. **Grade Calculation**: Automatic grade assignment based on average marks
6. **Formatted Output**: Professional-looking formatted output with boxes

## 🎉 Demonstration of Concepts

This program serves as a complete demonstration of:
- Object-oriented programming principles
- Memory management in C++
- Generic programming with templates
- Exception handling best practices
- Polymorphism and inheritance
- Operator overloading
- Real-world application development

Perfect for understanding RTU syllabus topics in a practical, integrated manner!
