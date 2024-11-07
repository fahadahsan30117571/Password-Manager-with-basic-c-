#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Category {
protected:
    string category_name;

public:
    Category() {}

    void setCategoryName(const string& name) {
        category_name = name;
    }

    string getCategoryName() const {
        return category_name;
    }
};

