#include<iostream>
#include<string>
using namespace std;

class Book {
private:
    string title;
    string author;
    int reviews_integer;
    double* array_of_scores;

    // Private function to calculate the average review score
    double calculate_average_score() const {
        if (reviews_integer == 0) return 0.0;  // Avoid division by zero
        double total = 0;
        for (int i = 0; i < reviews_integer; i++) {
            total += array_of_scores[i];
        }
        return total / reviews_integer;
    }

    // Private function to return the total number of reviews
    int get_total_reviews() const {
        return reviews_integer;
    }

public:
    // Default constructor
    Book() {
        title = "";
        author = "";
        reviews_integer = 0;
        array_of_scores = nullptr;
    }

    // Parameterized constructor
    Book(string t, string a, int r, double* s) {
        title = t;
        author = a;
        reviews_integer = r;
        array_of_scores = new double[reviews_integer];
        for (int i = 0; i < reviews_integer; i++) {
            array_of_scores[i] = s[i];
        }
    }

    // Copy constructor (Deep copy)
    Book(const Book& other) {
        title = other.title;
        author = other.author;
        reviews_integer = other.reviews_integer;

        if (reviews_integer > 0) {
            array_of_scores = new double[reviews_integer];
            for (int i = 0; i < reviews_integer; i++) {
                array_of_scores[i] = other.array_of_scores[i];
            }
        }
        else {
            array_of_scores = nullptr;
        }
    }

    // Destructor
    ~Book() {
        delete[] array_of_scores;  // Free the dynamically allocated memory
    }

    // Constant member functions to display book details
    void display() const {
        cout << "Book Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Number of Reviews: " << reviews_integer << endl;
        cout << "Scores: ";
        for (int i = 0; i < reviews_integer; i++) {
            cout << array_of_scores[i] << " ";
        }
        cout << endl;
        cout << "Average Score: " << calculate_average_score() << endl;
    }

    // Public function to add new reviews
    void add_reviews(int new_reviews, double* new_scores) {
        int new_total_reviews = reviews_integer + new_reviews;
        double* new_array_of_scores = new double[new_total_reviews];

        // Copy old reviews to the new array
        for (int i = 0; i < reviews_integer; i++) {
            new_array_of_scores[i] = array_of_scores[i];
        }

        // Add new reviews to the new array
        for (int i = 0; i < new_reviews; i++) {
            new_array_of_scores[reviews_integer + i] = new_scores[i];
        }

        // Replace old array with the new one
        delete[] array_of_scores;
        array_of_scores = new_array_of_scores;
        reviews_integer = new_total_reviews;
    }
};

int main() {
    // Create first book using parameterized constructor
    string title1 = "Book 1";
    string author1 = "Author A";
    int reviews1 = 3;
    double scores1[] = { 4.5, 3.8, 5.0 };
    Book book1(title1, author1, reviews1, scores1);

    // Create second book using default constructor and pointer
    Book* book_ptr = new Book();
    *book_ptr = book1;  // Deep copy using copy constructor

    // Create another book to demonstrate shallow copy problem
    Book shallow_copy_book = *book_ptr;  // This performs deep copy because of the copy constructor

    // Modify book1's array and show that shallow_copy_book is unaffected
    double new_scores[] = { 2.0, 3.0, 4.0 };
    book1.add_reviews(3, new_scores);  // Add new reviews to book1

    // Display book details
    cout << "Details of Book 1 after adding new reviews:" << endl;
    book1.display();  // Display book1 details after modification

    cout << "Details of Book 2 (copied from Book 1 via pointer):" << endl;
    book_ptr->display();  // Display the book pointed to by book_ptr

    cout << "Details of Shallow Copy Book (copied from book_ptr):" << endl;
    shallow_copy_book.display();  // Display the shallow copy book

    // Clean up memory
    delete book_ptr;  // Free the pointer

    // Shallow Copy Problem:
    // If we had done shallow copying (i.e., copied only the pointer to the array), 
    // modifying the original array would have also modified the copied object. 
    // This could lead to unexpected behavior or crashes due to double deletion of the same memory.

    return 0;
}
