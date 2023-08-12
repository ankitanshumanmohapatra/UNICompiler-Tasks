#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Book {
    string title;
    string author;
    bool available;

    Book(string t, string a) : title(t), author(a), available(true) {}
};

class Library {
private:
    vector<Book> books;
    map<string, string> users; // Username to password mapping
    map<string, vector<Book*>> borrowedBooks; // Username to borrowed books mapping

public:
    void addUser(string username, string password) {
        users[username] = password;
    }

    bool login(string username, string password) {
        if (users.find(username) != users.end() && users[username] == password) {
            return true;
        }
        return false;
    }

    void addBook(string title, string author) {
        books.push_back(Book(title, author));
    }

    void searchBook(string title) {
        cout << "Search results for '" << title << "':" << endl;
        for (const Book& book : books) {
            if (book.title.find(title) != string::npos) {
                cout << book.title << " by " << book.author;
                if (book.available) {
                    cout << " [Available]";
                } else {
                    cout << " [Borrowed]";
                }
                cout << endl;
            }
        }
    }

    void removeBook(string title) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->title == title) {
                books.erase(it);
                cout << "Book '" << title << "' removed." << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void borrowBook(string username, string title) {
        if (borrowedBooks[username].size() >= 3) {
            cout << "You have borrowed the maximum number of books." << endl;
            return;
        }

        for (Book& book : books) {
            if (book.title == title && book.available) {
                book.available = false;
                borrowedBooks[username].push_back(&book);
                cout << "Book '" << title << "' borrowed successfully." << endl;
                return;
            }
        }
        cout << "Book not found or already borrowed." << endl;
    }

    void returnBook(string username, string title) {
        for (Book*& book : borrowedBooks[username]) {
            if (book->title == title) {
                book->available = true;
                borrowedBooks[username].erase(std::remove(borrowedBooks[username].begin(), borrowedBooks[username].end(), book), borrowedBooks[username].end());
                cout << "Book '" << title << "' returned successfully." << endl;
                return;
            }
        }
        cout << "Book not found or not borrowed by you." << endl;
    }
};

int main() {
    Library library;

    library.addUser("user1", "pass1");
    library.addUser("user2", "pass2");

    library.addBook("Book 1", "Author 1");
    library.addBook("Book 2", "Author 2");
    library.addBook("Book 3", "Author 3");

    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (library.login(username, password)) {
        while (true) {
            cout << "\nLibrary Management System\n";
            cout << "1. Search Book\n";
            cout << "2. Borrow Book\n";
            cout << "3. Return Book\n";
            cout << "4. Exit\n";
            int choice;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    string title;
                    cout << "Enter book title to search: ";
                    cin.ignore();
                    getline(cin, title);
                    library.searchBook(title);
                    break;
                case 2:
                    string borrowTitle;
                    cout << "Enter book title to borrow: ";
                    cin.ignore();
                    getline(cin, borrowTitle);
                    library.borrowBook(username, borrowTitle);
                    break;
                case 3:
                    string returnTitle;
                    cout << "Enter book title to return: ";
                    cin.ignore();
                    getline(cin, returnTitle);
                    library.returnBook(username, returnTitle);
                    break;
                case 4:
                    cout << "Exiting...";
                    return 0;
                default:
                    cout << "Invalid choice. Please enter a valid option.";
            }
        }
    } else {
        cout << "Login failed. Invalid username or password." << endl;
    }

    return 0;
}

