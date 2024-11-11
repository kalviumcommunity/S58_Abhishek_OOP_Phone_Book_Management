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

    virtual void displayContact() const {
        cout << "Name: " << getName() << ", Phone Number: " << getPhoneNumber() << endl;
    }
};

class BusinessContact : public Contact {
private:
    string companyName;

public:
    BusinessContact(const string& name, const string& phoneNumber, const string& companyName)
        : Contact(name, phoneNumber), companyName(companyName) {}

    void displayContact() const override {
        cout << "Business ";
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
        cout << "Personal ";
        Contact::displayContact();
        cout << "Birthday: " << birthday << endl;
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

    void addContact(const string& name, const string& phoneNumber, const string& companyName) {
        if (totalContacts >= maxContacts) {
            cout << "Cannot add more contacts. Maximum limit of " << maxContacts << " reached." << endl;
            return;
        }
        Contact* newContact = new BusinessContact(name, phoneNumber, companyName);
        contacts.push_back(newContact);
        totalContacts++;
        cout << "Business contact added successfully!" << endl;
    }

    void addContact(const string& name, const string& phoneNumber, const string& birthday, bool isPersonal) {
        if (totalContacts >= maxContacts) {
            cout << "Cannot add more contacts. Maximum limit of " << maxContacts << " reached." << endl;
            return;
        }
        Contact* newContact = new PersonalContact(name, phoneNumber, birthday);
        contacts.push_back(newContact);
        totalContacts++;
        cout << "Personal contact added successfully!" << endl;
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
    myPhoneBook.addContact("Bob", "987-654-3210", "Acme Corp");
    myPhoneBook.addContact("Charlie", "555-123-4567", "01-01-1990", true);

    myPhoneBook.displayAllContacts();
    PhoneBook::displayTotalContacts();

    return 0;
}
