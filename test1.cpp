#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Contact {
protected:
    string name;
    string phoneNumber;

public:
    Contact(const string& name, const string& phoneNumber) 
        : name(name), phoneNumber(phoneNumber) {}

    virtual ~Contact() = default;

    virtual void displayContact() const {
        cout << "Name: " << name << ", Phone Number: " << phoneNumber << endl;
    }
};

class BusinessContact : public Contact {
private:
    string companyName;

public:
    BusinessContact(const string& name, const string& phoneNumber, const string& companyName)
        : Contact(name, phoneNumber), companyName(companyName) {}

    void displayContact() const override {
        cout << "Business Contact - ";
        Contact::displayContact();
        cout << "Company: " << companyName << endl;
    }
};

class PersonalContact : public Contact {
private:
    string birthday;

public:
    PersonalContact(const string& name, const string& phoneNumber, const string& birthday)
        : Contact(name, phoneNumber), birthday(birthday) {}

    void displayContact() const override {
        cout << "Personal Contact - ";
        Contact::displayContact();
        cout << "Birthday: " << birthday << endl;
    }
};

class PhoneBook {
private:
    vector<Contact*> contacts;
    static const int maxContacts;
    static int totalContacts;

public:
    ~PhoneBook() {
        for (auto contact : contacts) {
            delete contact;
        }
    }

    void addContact(Contact* newContact) {
        if (totalContacts >= maxContacts) {
            cout << "Cannot add more contacts. Maximum limit of " << maxContacts << " reached." << endl;
            delete newContact;
            return;
        }
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

    myPhoneBook.addContact(new Contact("Alice", "123-456-7890"));
    myPhoneBook.addContact(new BusinessContact("Bob", "987-654-3210", "Acme Corp"));
    myPhoneBook.addContact(new PersonalContact("Charlie", "555-123-4567", "01-01-1990"));

    class EmergencyContact : public Contact {
    private:
        string relation;

    public:
        EmergencyContact(const string& name, const string& phoneNumber, const string& relation)
            : Contact(name, phoneNumber), relation(relation) {}

        void displayContact() const override {
            cout << "Emergency Contact - ";
            Contact::displayContact();
            cout << "Relation: " << relation << endl;
        }
    };

    myPhoneBook.addContact(new EmergencyContact("Dave", "444-333-2222", "Brother"));

    myPhoneBook.displayAllContacts();
    PhoneBook::displayTotalContacts();

    return 0;
}
