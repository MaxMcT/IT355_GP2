#include <iostream>
#include <string>
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

    double calculateGPA {
        //TODO
        return 0;
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
        delete[] students;
        students = temp;
    }

public:
    StudentAccount(int initialCapacity = 2) : capacity(initialCapacity), size(0) {
        students = new Student[capacity];
    }

    ~StudentAccount() {
        delete[] students;
    }

    void addStudent(int id, string firstName, string lastName, double gpa) {
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
		//TODO
		return 1;
	}
};

int main() {
    StudentAccount account;

    account.addStudent(account.generateID(), "Luke", "Larry", 3.5);
    account.addStudent(account.generateID(), "Bob", "Bart", 3.8);

	cout << "Student List:\n";
    account.printArray();

    cout << "Student an index 1:\n";
    account.printStudent(1);

    cout << "Accessing outside of array:\n";
    account.printStudent(2);

    return 0;
}
