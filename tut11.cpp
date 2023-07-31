#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Student {
int rollno;
char name[50];
int marks[5];
double average;
char grade;
public:
void getDetails();
void calculate();
void display();
int getRollNo();
};

void Student::getDetails() {
cout << "Enter Roll Number: ";
cin >> rollno;
cin.ignore();
cout << "Enter Name: ";
cin.getline(name, 50);
for (int i = 0; i < 5; i++) {
cout << "Enter Marks for Subject " << i + 1 << ": ";
cin >> marks[i];
}

}

void Student::calculate() {

int total = 0;
for (int i = 0; i < 5; i++) {
total += marks[i];
}
average = (double)total / 5.0;
if (average >= 90) {
grade = 'A';
} else if (average >= 80) {
grade = 'B';
} else if (average >= 70) {
grade = 'C';
} else if (average >= 60) {
grade = 'D';
} else {
grade = 'F';
}
}

void Student::display() {
cout << setw(10) << rollno << setw(20) << name << setw(10) << marks[0] << setw(10) <<
marks[1] << setw(10) << marks[2] << setw(10) << marks[3] << setw(10) << marks[4] <<
setw(10) << average << setw(10) << grade << endl;
}
int Student::getRollNo() {
return rollno;
}
void addStudentRecord() {
ofstream file;
file.open("student.dat", ios::binary | ios::app);
Student s;
s.getDetails();
s.calculate();
file.write((char *)&s, sizeof(s));
file.close();
cout << "Student record has been added successfully!" << endl;
}
void displayAllRecords() {
ifstream file;
file.open("student.dat", ios::binary);
if (!file) {
cout << "File not found!" << endl;
return;
}
Student s;
cout << setw(10) << "Roll No" << setw(20) << "Name" << setw(10) << "Sub1" << setw(10) 
<< "Sub2" << setw(10) << "Sub3" << setw(10) << "Sub4" << setw(10) << "Sub5" << setw(10) 
<< "Average" << setw(10) << "Grade" << endl;
while (file.read((char *)&s, sizeof(s))) {
s.display();
}
file.close();
}
void searchStudentRecord() {
ifstream file;
file.open("student.dat", ios::binary);
if (!file) {
cout << "File not found!" << endl;
return;
}
int rollno;
cout << "Enter Roll Number to search: ";
cin >> rollno;
Student s;
bool found = false;
while (file.read((char *)&s, sizeof(s))) {
if (s.getRollNo() == rollno) {
found = true;
s.display();
break;
}
}
if (!found) {
cout << "Record not found!" << endl;
}
file.close();
}
void deleteStudentRecord() {
ifstream file;
file.open("student.dat", ios::binary);
if (!file) {
cout << "File not found!" << endl;
return;
}
ofstream temp;
temp.open("temp.dat", ios::binary);
int rollno;
cout << "Enter Roll Number to delete: ";
cin >> rollno;
Student s;
bool found = false;
while (file.read((char *)&s, sizeof(s))) {
if (s.getRollNo() != rollno) {
temp.write((char *)&s, sizeof(s));
} else {
found = true;
}
}
if (found) {
cout << "Record deleted successfully!" << endl;
} else {
cout << "Record not found!" << endl;
}
file.close();
temp.close();
remove("student.dat");
rename("temp.dat", "student.dat");
}
int main() {
int choice;
do {
cout << "Select an operation:" << endl;
cout << "1. Add Student Record" << endl;
cout << "2. Display All Records" << endl;
cout << "3. Search Student Record" << endl;
cout << "4. Delete Student Record" << endl;
cout << "5. Exit" << endl;
cout << "Enter your choice: ";
cin >> choice;
switch (choice) {
case 1:
addStudentRecord();
break;
case 2:
displayAllRecords();
break;
case 3:
searchStudentRecord();
break;
case 4:
deleteStudentRecord();
break;
case 5:
cout << "Exiting program..." << endl;
break;
default:
cout << "Invalid choice! Please try again." << endl;
}
} while (choice != 5);

return 0;

}