#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Contact {
private:
    string name;
    string phoneNumber;

public:
    Contact(string name, string phoneNumber) {
        this->name = name;
        this->phoneNumber = phoneNumber;
    }

    void displayContact() const {
        cout << "Name: " << name << ", Phone Number: " << phoneNumber << endl;
    }

    string getName() const {
        return this->name;
    }
};

class PhoneBook {
private:
    vector<Contact> contacts;

public:
    void addContact(const string& name, const string& phoneNumber) {
        Contact newContact(name, phoneNumber);
        this->contacts.push_back(newContact);
        cout << "Contact added successfully!" << endl;
    }

    void displayAllContacts() const {
        if (this->contacts.empty()) {
            cout << "Phone book is empty." << endl;
            return;
        }
        cout << "Contacts in Phone Book:" << endl;
        for (const auto& contact : this->contacts) {
            contact.displayContact();
        }
    }
};

int main() {
    PhoneBook myPhoneBook;
    myPhoneBook.addContact("Alice", "123-456-7890");
    myPhoneBook.addContact("Bob", "987-654-3210");
    myPhoneBook.displayAllContacts();

    return 0;
}
