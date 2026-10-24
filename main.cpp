
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Book {
private:
    string id, title, author;

public:
    Book(string i, string t, string a)
        : id(i), title(t), author(a) {}

    string getId() const { return id; }

    void show() const {
        cout << id << " | " << title << " | "
             << author << endl;
    }
};

class Library {
private:
    vector<Book> books;

public:
    void addBook() {
        string id, title, author;

        cout << "Enter book ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter title: ";
        getline(cin, title);

        cout << "Enter author: ";
        getline(cin, author);

        books.emplace_back(id, title, author);
        cout << "Book added successfully.\n";
    }

    void viewBooks() const {
        if (books.empty()) {
            cout << "No books available.\n";
            return;
        }

        for (const Book& book : books)
            book.show();
    }

    void menu() {
        int choice;

        do {
            cout << "\n1. Add Book\n";
            cout << "2. View Books\n";
            cout << "3. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addBook(); break;
                case 2: viewBooks(); break;
                case 3: cout << "Goodbye!\n"; break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 3);
    }
};

int main() {
    Library library;
    library.menu();
    return 0;
}
