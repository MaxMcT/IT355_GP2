#include <iostream>
#include <string>
#include <random>
using namespace std;

class Student {
private:
    int id;
    string firstName;
    string lastName;
    double gpa;

public:
    Student() : id(0), firstName(""), lastName(""), gpa(0.0) {}
    Student(int id, string firstName, string lastName, double gpa) : id(id), firstName(firstName), lastName(lastName), gpa(gpa) {}

    void print() {
        cout << "ID: " << id << ", Name: " << firstName << " " << lastName << ", GPA: " << gpa << "\n";
    }

};

class StudentAccount {
private:
    Student* students;
    int capacity;
    int size;

    void resize() {
        capacity *= 2;
        Student* temp = new Student[capacity];
        for (int i = 0; i < size; ++i) {
            temp[i] = students[i];
        }
	//Use correct deallocate call to free memory
        delete[] students;
        students = temp;
    }

public:
    StudentAccount(int initialCapacity = 2) : capacity(initialCapacity), size(0) {
        //Initialize pointer, preventing access to the unitialized pointer
	students = new Student[capacity];
    }

    ~StudentAccount() {
	//Use correct deallocate call to free memory
        delete[] students;
    }

    void addStudent(int id, string firstName, string lastName, double gpa) {
        //Prevent out of bounds write when capacity is met
	if (size == capacity) {
            resize();
        }
        students[size++] = Student(id, firstName, lastName, gpa);
    }

    void printStudent(int index) {
        //Prevent buffer overflow or underflow by adding conditional for accessing the array
        if (index < 0 || index > size - 1) {
            cout << "Invalid index.\n";
        }
        else {
            students[index].print();
        }
    }

    void printArray() {
        for (int i = 0; i < size; ++i) {
            students[i].print();
        }
    }
	
    int generateID() {
    	//Add entropy to the seed to avoid predictable output
	random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<int> distrubtion(1000000, 9999999);
        return distrubtion(generator);
    }

    double calculateGPA() {
        //TODO
        return 0;
    }
};

int main() {
    StudentAccount account;
    int choice = 0;
    while (choice != 4) {
        cout << "\nStudent Account Options:\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. View a Student by Index\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string firstName, lastName;
                double gpa;
                cout << "Enter first name: ";
                cin >> firstName;
                cout << "Enter last name: ";
                cin >> lastName;
                cout << "Enter GPA: ";
                cin >> gpa;

                int id = account.generateID();
                account.addStudent(id, firstName, lastName, gpa);
                cout << "Student added successfully with ID: " << id << "\n";
                break;
            }
            case 2:
                cout << "\nPrinting all students:\n";
                account.printArray();
                break;

            case 3: {
                int index;
                cout << "Enter student index: ";
                cin >> index;
                cout << "\nPrinting student at index " << index << "\n";
                account.printStudent(index);
                break;
            }

            case 4:
                cout << "Exiting program. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
