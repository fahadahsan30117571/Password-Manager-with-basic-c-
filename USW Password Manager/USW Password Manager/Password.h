#pragma once
#include <string>
#include "Category.h"
using namespace std;
class Password : public Category {
private:
    string site_name;
    string link;
    string password;

public:
    Password() {}

    void setSiteName(const string& name) {
        site_name = name;
    }

    string getSiteName() const {
        return site_name;
    }

    void setLink(const string& url) {
        link = url;
    }

    string getLink() const {
        return link;
    }

    void setPassword(const string& pass) {
        password = pass;  
    }

    string getPassword() const {
        return password;
    }

    static string encryptDecrypt(const string& input) {
        string result = input;
        char key = 'X';  // Simple XOR key
        for (char& c : result) c ^= key;
        return result;
    }

    // Save password data to a file (encrypts password before saving)
    void saveToFile(ofstream& file) const {
        file << category_name << "\n" << site_name << "\n" << link << "\n" << encryptDecrypt(password) << "\n";
    }

    // Load password data from a file (decrypts password after loading)
    void loadFromFile(ifstream& file) {
        getline(file, category_name);
        getline(file, site_name);
        getline(file, link);
        string encryptedPassword;
        getline(file, encryptedPassword);
        password = encryptDecrypt(encryptedPassword);
    }

    // Display password details (in plaintext)
    void display() const {
        cout << "Category: " << category_name << endl;
        cout << "Site Name: " << site_name << endl;
        cout << "Link: " << link << endl;
        cout << "Password: " << password << endl;
    }
};

