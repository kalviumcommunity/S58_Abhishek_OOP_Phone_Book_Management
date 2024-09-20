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
    vector<Contact*> contacts;  // Store pointers to Contact objects

public:
    ~PhoneBook() {
        // Ensure we free up dynamically allocated memory
        for (auto contact : contacts) {
            delete contact;
        }
    }

    void addContact(const string& name, const string& phoneNumber) {
        // Dynamically allocate memory for the new contact
        Contact* newContact = new Contact(name, phoneNumber);
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
            contact->displayContact();  // Dereference the pointer to call displayContact
        }
    }
};

int main() {
    PhoneBook myPhoneBook;

    // Dynamically allocate initial contacts using new
    Contact* initialContacts[] = {
        new Contact("Alice", "123-456-7890"),
        new Contact("Bob", "987-654-3210"),
        new Contact("Charlie", "555-123-4567")
    };

    for (const auto& contact : initialContacts) {
        myPhoneBook.addContact(contact->getName(), contact->getName());
        // Free the memory allocated for initialContacts array, since they are already copied
        delete contact;
    }

    myPhoneBook.displayAllContacts();

    return 0;
}
