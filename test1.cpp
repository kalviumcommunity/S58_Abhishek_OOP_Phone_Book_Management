#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Contact {
private:
    string name;
    string phoneNumber;

public:
    Contact(const string& name, const string& phoneNumber) {
        setName(name);
        setPhoneNumber(phoneNumber);
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

    Contact* initialContacts[] = {
        new Contact("Alice", "123-456-7890"),
        new Contact("Bob", "987-654-3210"),
        new Contact("Charlie", "555-123-4567")
    };

    for (const auto& contact : initialContacts) {
        myPhoneBook.addContact(contact->getName(), contact->getPhoneNumber());
        delete contact;
    }

    myPhoneBook.displayAllContacts();
    PhoneBook::displayTotalContacts();

    return 0;
}
