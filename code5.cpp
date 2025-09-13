// 🔹 Advanced Project: Library Management System (Binary Search + Add + Delete + Search)
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

// ------------------- Utility Functions -------------------

// Convert string to lowercase (for case-insensitive search)
string toLowerCase(const string &s) {
    string lower = s;
    transform(lower.begin(), lower.end(), lower.begin(),
              [](unsigned char c) { return tolower(c); });
    return lower;
}

// Keep books sorted (case-insensitive)
void sortBooks(vector<string>& books) {
    sort(books.begin(), books.end(), [](const string& a, const string& b) {
        return toLowerCase(a) < toLowerCase(b);
    });
}

// ------------------- Binary Search Functions -------------------

// Iterative Binary Search
int binarySearchIterative(const vector<string>& books, const string& target, int& steps) {
    int left = 0, right = books.size() - 1;
    steps = 0;
    string t = toLowerCase(target);

    while (left <= right) {
        steps++;
        int mid = left + (right - left) / 2;
        string midVal = toLowerCase(books[mid]);

        if (midVal == t)
            return mid;
        else if (midVal < t)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// Recursive Binary Search
int binarySearchRecursive(const vector<string>& books, int left, int right, const string& target, int& steps) {
    steps++;
    if (left > right) return -1;

    int mid = left + (right - left) / 2;
    string midVal = toLowerCase(books[mid]);
    string t = toLowerCase(target);

    if (midVal == t)
        return mid;
    else if (midVal < t)
        return binarySearchRecursive(books, mid + 1, right, target, steps);
    else
        return binarySearchRecursive(books, left, mid - 1, target, steps);
}

// ------------------- Library Management Functions -------------------

void displayBooks(const vector<string>& books) {
    cout << "\n📚 Library Books:" << endl;
    if (books.empty()) {
        cout << "No books available." << endl;
        return;
    }
    for (int i = 0; i < books.size(); i++) {
        cout << i << ". " << books[i] << endl;
    }
}

void addBook(vector<string>& books) {
    string book;
    cin.ignore();
    cout << "Enter new book title: ";
    getline(cin, book);
    books.push_back(book);
    sortBooks(books);
    cout << "✅ Book added successfully!" << endl;
}

void removeBook(vector<string>& books) {
    string book;
    cin.ignore();
    cout << "Enter book title to remove: ";
    getline(cin, book);
    int steps = 0;
    int index = binarySearchIterative(books, book, steps);
    if (index != -1) {
        books.erase(books.begin() + index);
        cout << "✅ Book removed successfully!" << endl;
    } else {
        cout << "❌ Book not found!" << endl;
    }
}

void searchBook(const vector<string>& books) {
    if (books.empty()) {
        cout << "❌ No books available to search." << endl;
        return;
    }
    string target;
    cin.ignore();
    cout << "Enter book title to search: ";
    getline(cin, target);

    int choice, result, steps = 0;
    cout << "Choose Search Method:\n1. Iterative\n2. Recursive\n";
    cin >> choice;

    if (choice == 1) {
        result = binarySearchIterative(books, target, steps);
    } else {
        result = binarySearchRecursive(books, 0, books.size() - 1, target, steps);
    }

    if (result != -1)
        cout << "✅ Book found at index " << result << " → \"" << books[result] << "\" (Steps: " << steps << ")" << endl;
    else
        cout << "❌ Book not found (Steps: " << steps << ")" << endl;
}

// ------------------- Main Program -------------------

int main() {
    vector<string> books = {
        "Algorithms Unlocked",
        "C++ Programming",
        "Data Structures and Algorithms",
        "Harry Potter",
        "Introduction to AI",
        "Machine Learning Basics",
        "Operating Systems",
        "The C Programming Language"
    };
    sortBooks(books);

    int choice;
    cout << "========================================" << endl;
    cout << "   📚 Library Management System (Binary Search)" << endl;
    cout << "   👨‍💻 Programmed by: THE RAHUL CHAUHAN" << endl;
    cout << "========================================" << endl;

    do {
        cout << "\n----- MENU -----" << endl;
        cout << "1. Display all books" << endl;
        cout << "2. Add a book" << endl;
        cout << "3. Remove a book" << endl;
        cout << "4. Search a book" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: displayBooks(books); break;
            case 2: addBook(books); break;
            case 3: removeBook(books); break;
            case 4: searchBook(books); break;
            case 5: cout << "Exiting... 👋" << endl; break;
            default: cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);

    return 0;
}
