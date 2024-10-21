#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Contact {
private:
    string name;
    string phoneNumber;

public:
    Contact() {
        cout << "Default constructor called" << endl;
        name = "Unknown";
        phoneNumber = "000-000-0000";
    }

    Contact(const string& name, const string& phoneNumber) {
        cout << "Parameterized constructor called" << endl;
        setName(name);
        setPhoneNumber(phoneNumber);
    }

    Contact(const Contact& other) {
        cout << "Copy constructor called" << endl;
        name = other.name;
        phoneNumber = other.phoneNumber;
    }

    Contact(Contact&& other) noexcept {
        cout << "Move constructor called" << endl;
        name = move(other.name);
        phoneNumber = move(other.phoneNumber);
        other.name = "Unknown";
        other.phoneNumber = "000-000-0000";
    }

    void setName(const string& name) {
        this->name = name;
    }

    string getName() const {
        return this->name;
    }

    void setPhoneNumber(const string& phoneNumber) {
        this->phoneNumber = phoneNumber;
    }

    string getPhoneNumber() const {
        return this->phoneNumber;
    }

    void displayContact() const {
        cout << "Name: " << getName() << ", Phone Number: " << getPhoneNumber() << endl;
    }
};

class PhoneBook {
private:
    vector<Contact*> contacts;
    static int totalContacts;
    static const int maxContacts;

public:
    ~PhoneBook() {
        for (auto contact : contacts) {
            delete contact;
        }
    }

    void addContact(const string& name, const string& phoneNumber) {
        if (totalContacts >= maxContacts) {
            cout << "Cannot add more contacts. Maximum limit of " << maxContacts << " reached." << endl;
            return;
        }
        Contact* newContact = new Contact(name, phoneNumber);
        contacts.push_back(newContact);
        totalContacts++;
        cout << "Contact added successfully!" << endl;
    }

    void addContact() {  
        if (totalContacts >= maxContacts) {
            cout << "Cannot add more contacts. Maximum limit of " << maxContacts << " reached." << endl;
            return;
        }
        Contact* newContact = new Contact();  
        contacts.push_back(newContact);
        totalContacts++;
        cout << "Default contact added successfully!" << endl;
    }

    void addCopyContact(const Contact& existingContact) {
        if (totalContacts >= maxContacts) {
            cout << "Cannot add more contacts. Maximum limit of " << maxContacts << " reached." << endl;
            return;
        }
        Contact* copyContact = new Contact(existingContact);
        contacts.push_back(copyContact);
        totalContacts++;
        cout << "Copy contact added successfully!" << endl;
    }

    void addMoveContact(Contact&& tempContact) {
        if (totalContacts >= maxContacts) {
            cout << "Cannot add more contacts. Maximum limit of " << maxContacts << " reached." << endl;
            return;
        }
        Contact* moveContact = new Contact(move(tempContact));
        contacts.push_back(moveContact);
        totalContacts++;
        cout << "Move contact added successfully!" << endl;
    }

    void displayAllContacts() const {
        if (contacts.empty()) {
            cout << "Phone book is empty." << endl;
            return;
        }
        cout << "Contacts in Phone Book:" << endl;
        for (const auto& contact : contacts) {
            contact->displayContact();
        }
    }

    static void displayTotalContacts() {
        cout << "Total Contacts: " << totalContacts << endl;
    }
};

int PhoneBook::totalContacts = 0;
const int PhoneBook::maxContacts = 10;

int main() {
    PhoneBook myPhoneBook;

    myPhoneBook.addContact("Alice", "123-456-7890");
    myPhoneBook.addContact("Bob", "987-654-3210");
    myPhoneBook.addContact("Charlie", "555-123-4567");

    myPhoneBook.addContact();

    Contact copiedContact("David", "111-222-3333");
    myPhoneBook.addCopyContact(copiedContact);

    Contact tempContact("Eve", "444-555-6666");
    myPhoneBook.addMoveContact(move(tempContact));

    myPhoneBook.displayAllContacts();
    PhoneBook::displayTotalContacts();

    return 0;
}
