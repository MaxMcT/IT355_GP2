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
