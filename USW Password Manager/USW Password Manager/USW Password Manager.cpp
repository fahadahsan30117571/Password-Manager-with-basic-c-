
#include <iostream>
#include "Password.h"

void addPassword();
void showAllPasswords();
void updatePassword();
void deletePassword();

int main() {
    int choice;
    while (true) {
        cout << "\n--- Password Manager ---\n";
        cout << "1. Add Password\n2. Show All Passwords\n3. Update Password\n4. Delete Password\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1: addPassword(); break;
        case 2: showAllPasswords(); break;
        case 3: updatePassword(); break;
        case 4: deletePassword(); break;
        case 5: return 0;
        default: cout << "Invalid choice. Try again.\n";
        }
    }
}

// Add a new password //
void addPassword() {
    Password p;
    string category, site, link, pass;

    cout << "Enter Category Name: "; getline(cin, category);
    cout << "Enter Site Name: "; getline(cin, site);
    cout << "Enter Link: "; getline(cin, link);
    cout << "Enter Password: "; getline(cin, pass);

    p.setCategoryName(category);
    p.setSiteName(site);
    p.setLink(link);
    p.setPassword(pass);

    ofstream file("passwords.txt", ios::app);
    if (file.is_open()) {
        p.saveToFile(file);
        cout << "Password added successfully!\n";
    }
    else {
        cerr << "Error opening file.\n";
    }
}

// Display all saved passwords
void showAllPasswords() {
    ifstream file("passwords.txt");
    if (file.is_open()) {
        while (!file.eof()) {
            Password p;
            p.loadFromFile(file);
            if (file.eof()) break;
            p.display();
            cout << "-------------------------\n";
        }
    }
    else {
        cerr << "Error opening file.\n";
    }
}

// Update a password based on site name
void updatePassword() {
    string site, new_pass;
    cout << "Enter the site name to update: ";
    getline(cin, site);

    ifstream file("passwords.txt");
    ofstream tempFile("temp.txt");
    bool found = false;

    if (file.is_open() && tempFile.is_open()) {
        while (!file.eof()) {
            Password p;
            p.loadFromFile(file);
            if (file.eof()) break;

            if (p.getSiteName() == site) {
                cout << "Enter new password: ";
                getline(cin, new_pass);
                p.setPassword(new_pass);
                found = true;
                cout << "Password updated successfully!\n";
            }
            p.saveToFile(tempFile);
        }
        file.close();
        tempFile.close();

        remove("passwords.txt");
        rename("temp.txt", "passwords.txt");

        if (!found) cout << "Site not found.\n";
    }
    else {
        cerr << "Error opening file.\n";
    }
}

// Delete a password based on site name
void deletePassword() {
    string site;
    cout << "Enter the site name to delete: ";
    getline(cin, site);

    ifstream file("passwords.txt");
    ofstream tempFile("temp.txt");
    bool found = false;

    if (file.is_open() && tempFile.is_open()) {
        while (!file.eof()) {
            Password p;
            p.loadFromFile(file);
            if (file.eof()) break;

            if (p.getSiteName() != site) {
                p.saveToFile(tempFile);
            }
            else {
                found = true;
                cout << "Password deleted successfully!\n";
            }
        }
        file.close();
        tempFile.close();

        remove("passwords.txt");
        rename("temp.txt","passwords.txt");

        if (!found) cout << "Site not found.\n";
    }
    else {
        cerr << "Error opening file.\n";
    }
}
