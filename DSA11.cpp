#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    string roll;
    string name;
    string division;
    string address;
};

void addStudent() {
    Student s;
    cout << "Enter Roll Number: ";
    cin >> s.roll;
    cin.ignore(); // Ignore newline after roll input
    cout << "Enter Name: ";
    getline(cin, s.name);
    cout << "Enter Division: ";
    getline(cin, s.division);
    cout << "Enter Address: ";
    getline(cin, s.address);

    ofstream outFile("students.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    outFile << s.roll << "," << s.name << "," << s.division << "," << s.address << "\n";
    outFile.close();

    cout << "Student added successfully.\n\n";
}

void deleteStudent() {
    string rollToDelete;
    bool found = false;
    cout << "Enter Roll Number to delete: ";
    cin >> rollToDelete;

    ifstream inFile("students.txt");
    ofstream tempFile("temp.txt");
    if (!inFile || !tempFile) {
        cerr << "Error opening file.\n";
        return;
    }

    string line;
    while (getline(inFile, line)) {
        if (line.substr(0, line.find(',')) != rollToDelete) {
            tempFile << line << "\n";
        } else {
            found = true;
        }
    }

    inFile.close();
    tempFile.close();

    if (remove("students.txt") != 0) {
        cerr << "Error deleting original file.\n";
        return;
    }

    if (rename("temp.txt", "students.txt") != 0) {
        cerr << "Error renaming temporary file.\n";
        return;
    }

    if (found)
        cout << "Student deleted successfully.\n\n";
    else
        cout << "Student record not found.\n\n";
}

void displayStudent() {
    string rollToSearch;
    bool found = false;
    cout << "Enter Roll Number to display: ";
    cin >> rollToSearch;

    ifstream inFile("students.txt");
    if (!inFile) {
        cerr << "Error opening file.\n";
        return;
    }

    string line;
    while (getline(inFile, line)) {
        if (line.substr(0, line.find(',')) == rollToSearch) {
            found = true;

            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);

            cout << "\nStudent Found:\n";
            cout << "Roll No: " << line.substr(0, pos1) << "\n";
            cout << "Name: " << line.substr(pos1 + 1, pos2 - pos1 - 1) << "\n";
            cout << "Division: " << line.substr(pos2 + 1, pos3 - pos2 - 1) << "\n";
            cout << "Address: " << line.substr(pos3 + 1) << "\n\n";
            break;
        }
    }

    inFile.close();
    if (!found)
        cout << "Student record not found.\n\n";
}

int main() {
    int choice;
    do {
        cout << "----- Student Information System -----\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Display Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                displayStudent();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n\n";
        }
    } while (choice != 4);

    return 0;
}
