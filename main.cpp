
#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string id, title, author;

public:
    Book(string i, string t, string a) {
        id = i;
        title = t;
        author = a;
    }

    void show() {
        cout << id << " | " << title << " | "
             << author << endl;
    }
};

int main() {
    Book b1("101", "40 Din", "Gurpreet Singh Dhugga");
    Book b2("102", "Mera Pin", "Giani Gurdit Singh");

    cout << "Library Management System\n";
    cout << "ID | Title | Author\n";

    b1.show();
    b2.show();

    return 0;
}
