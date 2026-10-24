
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Book {
private:
    string id, title, author;
    bool issued;

public:
    Book(string i, string t, string a, bool s = false)
        : id(i), title(t), author(a), issued(s) {}

    string getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool isIssued() const { return issued; }

    void issue() { issued = true; }
    void giveBack() { issued = false; }

    void show() const {
        cout << id << " | " << title << " | "
             << author << " | "
             << (issued ? "ISSUED" : "AVAILABLE") << '\n';
    }
};

class Library {
private:
    vector<Book> books;

    int findBook(string id) const {
        for (int i = 0; i < (int)books.size(); i++)
            if (books[i].getId() == id)
                return i;

        return -1;
    }

    void loadBooks() {
        ifstream file("books.txt");
        string line;

        while (getline(file, line)) {
            stringstream row(line);
            string id, title, author, status;

            if (getline(row, id, '|') &&
                getline(row, title, '|') &&
                getline(row, author, '|') &&
                getline(row, status)) {
                books.emplace_back(id, title, author, status == "1");
            }
        }
    }

    void saveBooks() const {
        ofstream file("books.txt");

        for (const Book& b : books) {
            file << b.getId() << '|'
                 << b.getTitle() << '|'
                 << b.getAuthor() << '|'
                 << b.isIssued() << '\n';
        }
    }

public:
    Library() { loadBooks(); }

    void addBook() {
        string id, title, author;

        cout << "Enter book ID: ";
        cin >> id;

        if (findBook(id) != -1) {
            cout << "Book ID already exists.\n";
            return;
        }

        cin.ignore();

        cout << "Enter title: ";
        getline(cin, title);

        cout << "Enter author: ";
        getline(cin, author);

        books.emplace_back(id, title, author);
        saveBooks();
        cout << "Book added.\n";
    }

    void viewBooks() const {
        if (books.empty()) {
            cout << "No books available.\n";
            return;
        }

        for (const Book& b : books)
            b.show();
    }

    void changeStatus(bool issueBook) {
        string id;

        cout << "Enter book ID: ";
        cin >> id;

        int index = findBook(id);

        if (index == -1) {
            cout << "Book not found.\n";
            return;
        }

        if (issueBook && books[index].isIssued()) {
            cout << "Book is already issued.\n";
            return;
        }

        if (!issueBook && !books[index].isIssued()) {
            cout << "Book is not issued.\n";
            return;
        }

        if (issueBook)
            books[index].issue();
        else
            books[index].giveBack();

        saveBooks();
        cout << "Book status updated.\n";
    }

    void menu() {
        int choice;

        do {
            cout << "\n1. Add Book\n2. View Books\n";
            cout << "3. Issue Book\n4. Return Book\n5. Exit\n";
            cout << "Choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addBook(); break;
                case 2: viewBooks(); break;
                case 3: changeStatus(true); break;
                case 4: changeStatus(false); break;
                case 5: cout << "Goodbye!\n"; break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 5);
    }
};

int main() {
    Library library;
    library.menu();
    return 0;
}
