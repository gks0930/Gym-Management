#include <iostream>
#include <fstream>
#include <string>
#include <limits> 
#include <cstdlib>
#include <algorithm>
using namespace std;

class Member {
public:
    int id;
    string name;
    int age;
    string contact;
    string membershipType;

    Member(int _id, string _name, int _age, string _contact, string _membershipType) {
        id = _id;
        name = _name;
        age = _age;
        contact = _contact;
        membershipType = _membershipType;
    }

    void display() {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Contact: " << contact << endl;
        cout << "Membership Type: " << membershipType << endl;
    }
};

bool isIdUnique(int id) {
    ifstream memberFile("members.txt");
    string line;

    while (getline(memberFile, line)) {
        size_t pos = line.find('|');
        int existingId = stoi(line.substr(0, pos));

        if (existingId == id) {
            memberFile.close();
            return false;
        }
    }
    memberFile.close();
    return true;
}

bool isValidName(const string &name) {
    for (char c : name) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

string toLowerCase(const string &str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void addMember() {
    system("cls");
    int id, age;
    string name, contact, membershipType;

    while (true) {
        cout << "Enter Member ID: ";
        cin >> id;
        if (cin.fail() || id <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid positive integer.\n";
            continue;
        }
        if (!isIdUnique(id)) {
            cout << "Error: Member ID already exists!\n";
            continue;
        }
        break;
    }
    cin.ignore();

    while (true) {
        cout << "Enter Member Name: ";
        getline(cin, name);
        if (!isValidName(name)) {
            cout << "Invalid input! Name must contain only letters and spaces.\n";
            continue;
        }
        break;
    }

    while (true) {
        cout << "Enter Age: ";
        cin >> age;
        if (cin.fail() || age <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid positive integer.\n";
            continue;
        }
        break;
    }
    cin.ignore();

    cout << "Enter Contact: ";
    getline(cin, contact);

    while (true) {
        cout << "Enter Membership Type (Monthly/Yearly): ";
        getline(cin, membershipType);
        string lower_type = toLowerCase(membershipType);
        if (lower_type != "monthly" && lower_type != "yearly") {
            cout << "Invalid input! Membership Type must be 'Monthly' or 'Yearly'.\n";
            continue;
        }
        break;
    }

    Member newMember(id, name, age, contact, membershipType);

    ofstream memberFile("members.txt", ios::app);
    if (memberFile.is_open()) {
        memberFile << id << "|" << name << "|" << age << "|" << contact << "|" << membershipType << endl;
        memberFile.close();
        cout << "Member added successfully!" << endl;
    } else {
        cout << "Unable to open file!" << endl;
    }
}

void displayAllMembers() {
    ifstream memberFile("members.txt");
    string line;

    if (memberFile.is_open()) {
        while (getline(memberFile, line)) {
            size_t pos1 = 0, pos2 = 0;

            pos2 = line.find('|', pos1);
            string id = line.substr(pos1, pos2 - pos1);

            pos1 = pos2 + 1;
            pos2 = line.find('|', pos1);
            string name = line.substr(pos1, pos2 - pos1);

            pos1 = pos2 + 1;
            pos2 = line.find('|', pos1);
            string age = line.substr(pos1, pos2 - pos1);

            pos1 = pos2 + 1;
            pos2 = line.find('|', pos1);
            string contact = line.substr(pos1, pos2 - pos1);

            pos1 = pos2 + 1;
            string membershipType = line.substr(pos1);

            cout << "ID: " << id << endl;
            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Contact: " << contact << endl;
            cout << "Membership Type: " << membershipType << endl;
            cout << "--------------------------" << endl;
        }
        memberFile.close();
    } else {
        cout << "Unable to open file!" << endl;
    }
}

void makePayment() {
    system("cls");
    int memberId;
    double amount;

    while (true) {
        cout << "Enter Member ID: ";
        cin >> memberId;
        if (cin.fail() || memberId <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid positive integer.\n";
            continue;
        }
        if (isIdUnique(memberId)) {
            cout << "Error: Member ID does not exist.\n";
            continue;
        }
        break;
    }

    while (true) {
        cout << "Enter Payment Amount: ";
        cin >> amount;
        if (cin.fail() || amount <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid positive number.\n";
            continue;
        }
        break;
    }

    ofstream paymentFile("payments.txt", ios::app);
    if (paymentFile.is_open()) {
        paymentFile << memberId << "|" << amount << endl;
        paymentFile.close();
        cout << "Payment recorded successfully!" << endl;
    } else {
        cout << "Unable to open file!" << endl;
    }
}

void viewPayments() {
    ifstream paymentFile("payments.txt");
    string line;

    if (paymentFile.is_open()) {
        while (getline(paymentFile, line)) {
            size_t pos = line.find('|');
            int memberId = stoi(line.substr(0, pos));
            string amount = line.substr(pos + 1);

            cout << "Member ID: " << memberId  << ", Amount: " << amount << endl;
        }
        paymentFile.close();
    } else {
        cout << "Unable to open file!" << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n--- Gym Management System ---\n";
        cout << "1. Add Member\n";
        cout << "2. Display All Members\n";
        cout << "3. Make Payment\n";
        cout << "4. View Payment History\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addMember();
                break;
            case 2:
                displayAllMembers();
                break;
            case 3:
                makePayment();
                break;
            case 4:
                viewPayments();
                break;
            case 5:
                cout << "Exiting the system...\n";
                exit(0);
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
