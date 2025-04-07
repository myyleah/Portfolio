#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//CSE 130 FINAL PROJECT BY MYLEAH JONES
// Define constants for maximum limits on books, borrowers, and string lengths
#define MAX_BOOKS 100
#define MAX_BORROWERS 100
#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 100
#define MAX_ISBN_LENGTH 20
#define MAX_NAME_LENGTH 100
#define MAX_ID_LENGTH 20

// Structure to represent a book
typedef struct {
    char title[MAX_TITLE_LENGTH];    // Title of the book
    char author[MAX_AUTHOR_LENGTH];  // Author of the book
    char ISBN[MAX_ISBN_LENGTH];      // ISBN of the book
    int isAvailable;                 // Availability status (1 if available, 0 if borrowed)
} Book;

// Structure to represent a borrower
typedef struct {
    char name[MAX_NAME_LENGTH];      // Name of the borrower
    char ID[MAX_ID_LENGTH];          // ID of the borrower
    char borrowedBooks[MAX_BOOKS][MAX_ISBN_LENGTH]; // List of borrowed book ISBNs
    time_t dueDates[MAX_BOOKS];      // Due dates for borrowed books
    int numBorrowedBooks;            // Number of books currently borrowed
} Borrower;

// Structure to represent the library
typedef struct {
    Book books[MAX_BOOKS];           // Array of books in the library
    int numBooks;                    // Number of books in the library
    Borrower borrowers[MAX_BORROWERS]; // Array of borrowers
    int numBorrowers;                // Number of borrowers in the library
} Library;

// Function to add a new book to the library
void addBook(Library *library, char *title, char *author, char *ISBN) {
    if (library->numBooks >= MAX_BOOKS) { // Check if library is full
        printf("Library is full.\n");
        return;
    }
    // Set book details
    strcpy(library->books[library->numBooks].title, title);
    strcpy(library->books[library->numBooks].author, author);
    strcpy(library->books[library->numBooks].ISBN, ISBN);
    library->books[library->numBooks].isAvailable = 1; // Mark book as available
    library->numBooks++; // Increment the count of books
    printf("Book added successfully.\n");
}

// Function to remove a book from the library
void removeBook(Library *library, char *ISBN) {
    for (int i = 0; i < library->numBooks; i++) {
        if (strcmp(library->books[i].ISBN, ISBN) == 0) { // Find the book
            // Shift remaining books to the left to fill the gap
            for (int j = i; j < library->numBooks - 1; j++) {
                library->books[j] = library->books[j + 1];
            }
            library->numBooks--; // Decrement the count of books
            printf("Book removed successfully.\n");
            return;
        }
    }
    printf("Book not found.\n");
}

// Function to search for a book by title
void searchBookByTitle(Library *library, char *title) {
    for (int i = 0; i < library->numBooks; i++) {
        if (strcmp(library->books[i].title, title) == 0) { // Find the book
            printf("Book found: %s by %s (ISBN: %s)\n",
                   library->books[i].title,
                   library->books[i].author,
                   library->books[i].ISBN);
            return;
        }
    }
    printf("Book not found.\n");
}

// Function to search for a book by author
void searchBookByAuthor(Library *library, char *author) {
    for (int i = 0; i < library->numBooks; i++) {
        if (strcmp(library->books[i].author, author) == 0) { // Find the book
            printf("Book found: %s by %s (ISBN: %s)\n",
                   library->books[i].title,
                   library->books[i].author,
                   library->books[i].ISBN);
            return;
        }
    }
    printf("Book not found.\n");
}

// Function to search for a book by ISBN
void searchBookByISBN(Library *library, char *ISBN) {
    for (int i = 0; i < library->numBooks; i++) {
        if (strcmp(library->books[i].ISBN, ISBN) == 0) { // Find the book
            printf("Book found: %s by %s (ISBN: %s)\n",
                   library->books[i].title,
                   library->books[i].author,
                   library->books[i].ISBN);
            return;
        }
    }
    printf("Book not found.\n");
}

// Function to register a new borrower
void registerBorrower(Library *library, char *name, char *ID) {
    if (library->numBorrowers >= MAX_BORROWERS) { // Check if borrower list is full
        printf("Borrower list is full.\n");
        return;
    }
    for (int i = 0; i < library->numBorrowers; i++) {
        if (strcmp(library->borrowers[i].ID, ID) == 0) { // Check if borrower already exists
            printf("Borrower already exists.\n");
            return;
        }
    }
    // Set borrower details
    strcpy(library->borrowers[library->numBorrowers].name, name);
    strcpy(library->borrowers[library->numBorrowers].ID, ID);
    library->borrowers[library->numBorrowers].numBorrowedBooks = 0; // Initialize borrowed books count
    library->numBorrowers++; // Increment the count of borrowers
    printf("Borrower registered successfully.\n");
}

// Function to remove a borrower from the library
void removeBorrower(Library *library, char *ID) {
    for (int i = 0; i < library->numBorrowers; i++) {
        if (strcmp(library->borrowers[i].ID, ID) == 0) { // Find the borrower
            // Shift remaining borrowers to the left to fill the gap
            for (int j = i; j < library->numBorrowers - 1; j++) {
                library->borrowers[j] = library->borrowers[j + 1];
            }
            library->numBorrowers--; // Decrement the count of borrowers
            printf("Borrower removed successfully.\n");
            return;
        }
    }
    printf("Borrower not found.\n");
}

// Function to search for a borrower by name
void searchBorrowerByName(Library *library, char *name) {
    for (int i = 0; i < library->numBorrowers; i++) {
        if (strcmp(library->borrowers[i].name, name) == 0) { // Find the borrower
            printf("Borrower found: %s (ID: %s)\n",
                   library->borrowers[i].name,
                   library->borrowers[i].ID);
            return;
        }
    }
    printf("Borrower not found.\n");
}

// Function to search for a borrower by ID
void searchBorrowerByID(Library *library, char *ID) {
    for (int i = 0; i < library->numBorrowers; i++) {
        if (strcmp(library->borrowers[i].ID, ID) == 0) { // Find the borrower
            printf("Borrower found: %s (ID: %s)\n",
                   library->borrowers[i].name,
                   library->borrowers[i].ID);
            return;
        }
    }
    printf("Borrower not found.\n");
}

// Function to check out a book to a borrower
void checkOutBook(Library *library, char *ISBN, char *borrowerID) {
    for (int i = 0; i < library->numBooks; i++) {
        if (strcmp(library->books[i].ISBN, ISBN) == 0 && library->books[i].isAvailable) { // Find the book and check if available
            for (int j = 0; j < library->numBorrowers; j++) {
                if (strcmp(library->borrowers[j].ID, borrowerID) == 0) { // Find the borrower
                    if (library->borrowers[j].numBorrowedBooks < MAX_BOOKS) { // Check if borrower has not exceeded limit
                        library->books[i].isAvailable = 0; // Mark book as borrowed
                        time_t now = time(0); // Get current time
                        time_t dueDate = now + 14 * 24 * 60 * 60; // Set due date to 2 weeks from now
                        strcpy(library->borrowers[j].borrowedBooks[library->borrowers[j].numBorrowedBooks], ISBN);
                        library->borrowers[j].dueDates[library->borrowers[j].numBorrowedBooks] = dueDate;
                        library->borrowers[j].numBorrowedBooks++; // Increment number of borrowed books
                        printf("Book checked out successfully!\n");
                        return;
                    } else {
                        printf("Borrower has reached the maximum number of borrowed books.\n");
                        return;
                    }
                }
            }
            printf("Borrower ID not found.\n");
            return;
        }
    }
    printf("Book is not available.\n");
}

// Function to return a borrowed book
void returnBook(Library *library, char *ISBN, char *borrowerID) {
    for (int i = 0; i < library->numBorrowers; i++) {
        if (strcmp(library->borrowers[i].ID, borrowerID) == 0) { // Find the borrower
            for (int j = 0; j < library->borrowers[i].numBorrowedBooks; j++) {
                if (strcmp(library->borrowers[i].borrowedBooks[j], ISBN) == 0) { // Find the borrowed book
                    for (int k = 0; k < library->numBooks; k++) {
                        if (strcmp(library->books[k].ISBN, ISBN) == 0) { // Find the book in the library
                            library->books[k].isAvailable = 1; // Mark book as available
                            // Shift remaining borrowed books to the left to fill the gap
                            for (int l = j; l < library->borrowers[i].numBorrowedBooks - 1; l++) {
                                strcpy(library->borrowers[i].borrowedBooks[l], library->borrowers[i].borrowedBooks[l + 1]);
                                library->borrowers[i].dueDates[l] = library->borrowers[i].dueDates[l + 1];
                            }
                            library->borrowers[i].numBorrowedBooks--; // Decrement number of borrowed books
                            printf("Book returned successfully!\n");
                            return;
                        }
                    }
                    printf("Book not found in library.\n");
                    return;
                }
            }
            printf("Book was not borrowed by this borrower.\n");
            return;
        }
    }
    printf("Borrower ID not found.\n");
}

// Function to generate a report of overdue books
void generateOverdueReport(Library *library) {
    time_t now = time(0); // Get current time
    printf("Overdue Books Report:\n");
    for (int i = 0; i < library->numBorrowers; i++) {
        for (int j = 0; j < library->borrowers[i].numBorrowedBooks; j++) {
            if (library->borrowers[i].dueDates[j] < now) { // Check if the book is overdue
                printf("Borrower ID: %s, Book ISBN: %s\n",
                       library->borrowers[i].ID,
                       library->borrowers[i].borrowedBooks[j]);
            }
        }
    }
}

// Function to display all borrowed books
void displayAllBorrowedBooks(Library *library) {
    printf("All Borrowed Books:\n");
    for (int i = 0; i < library->numBorrowers; i++) {
        printf("Borrower ID: %s\n", library->borrowers[i].ID);
        for (int j = 0; j < library->borrowers[i].numBorrowedBooks; j++) {
            printf("    Book ISBN: %s\n", library->borrowers[i].borrowedBooks[j]);
        }
    }
}

// Main function to run the library management system
int main() {
    Library library;
    library.numBooks = 0; // Initialize number of books
    library.numBorrowers = 0; // Initialize number of borrowers

    int choice; // Variable to store user choice
    char title[MAX_TITLE_LENGTH]; // Variable to store book title
    char author[MAX_AUTHOR_LENGTH]; // Variable to store book author
    char ISBN[MAX_ISBN_LENGTH]; // Variable to store book ISBN
    char name[MAX_NAME_LENGTH]; // Variable to store borrower name
    char ID[MAX_ID_LENGTH]; // Variable to store borrower ID

    while (1) {
        // Display menu options
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Remove Book\n");
        printf("3. Search Book by Title\n");
        printf("4. Search Book by Author\n");
        printf("5. Search Book by ISBN\n");
        printf("6. Register Borrower\n");
        printf("7. Remove Borrower\n");
        printf("8. Search Borrower by Name\n");
        printf("9. Search Borrower by ID\n");
        printf("10. Check Out Book\n");
        printf("11. Return Book\n");
        printf("12. Generate Overdue Report\n");
        printf("13. Display All Borrowed Books\n");
        printf("14. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                // Add a new book
                printf("Enter title: ");
                fgets(title, MAX_TITLE_LENGTH, stdin);
                title[strcspn(title, "\n")] = '\0'; // Remove newline
                printf("Enter author: ");
                fgets(author, MAX_AUTHOR_LENGTH, stdin);
                author[strcspn(author, "\n")] = '\0'; // Remove newline
                printf("Enter ISBN: ");
                fgets(ISBN, MAX_ISBN_LENGTH, stdin);
                ISBN[strcspn(ISBN, "\n")] = '\0'; // Remove newline
                addBook(&library, title, author, ISBN);
                break;

            case 2:
                // Remove a book
                printf("Enter ISBN: ");
                fgets(ISBN, MAX_ISBN_LENGTH, stdin);
                ISBN[strcspn(ISBN, "\n")] = '\0'; // Remove newline
                removeBook(&library, ISBN);
                break;

            case 3:
                // Search for a book by title
                printf("Enter title: ");
                fgets(title, MAX_TITLE_LENGTH, stdin);
                title[strcspn(title, "\n")] = '\0'; // Remove newline
                searchBookByTitle(&library, title);
                break;

            case 4:
                // Search for a book by author
                printf("Enter author: ");
                fgets(author, MAX_AUTHOR_LENGTH, stdin);
                author[strcspn(author, "\n")] = '\0'; // Remove newline
                searchBookByAuthor(&library, author);
                break;

            case 5:
                // Search for a book by ISBN
                printf("Enter ISBN: ");
                fgets(ISBN, MAX_ISBN_LENGTH, stdin);
                ISBN[strcspn(ISBN, "\n")] = '\0'; // Remove newline
                searchBookByISBN(&library, ISBN);
                break;

            case 6:
                // Register a new borrower
                printf("Enter name: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline
                printf("Enter ID: ");
                fgets(ID, MAX_ID_LENGTH, stdin);
                ID[strcspn(ID, "\n")] = '\0'; // Remove newline
                registerBorrower(&library, name, ID);
                break;

            case 7:
                // Remove a borrower
                printf("Enter ID: ");
                fgets(ID, MAX_ID_LENGTH, stdin);
                ID[strcspn(ID, "\n")] = '\0'; // Remove newline
                removeBorrower(&library, ID);
                break;

            case 8:
                // Search for a borrower by name
                printf("Enter name: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline
                searchBorrowerByName(&library, name);
                break;

            case 9:
                // Search for a borrower by ID
                printf("Enter ID: ");
                fgets(ID, MAX_ID_LENGTH, stdin);
                ID[strcspn(ID, "\n")] = '\0'; // Remove newline
                searchBorrowerByID(&library, ID);
                break;

            case 10:
                // Check out a book
                printf("Enter ISBN: ");
                fgets(ISBN, MAX_ISBN_LENGTH, stdin);
                ISBN[strcspn(ISBN, "\n")] = '\0'; // Remove newline
                printf("Enter Borrower ID: ");
                fgets(ID, MAX_ID_LENGTH, stdin);
                ID[strcspn(ID, "\n")] = '\0'; // Remove newline
                checkOutBook(&library, ISBN, ID);
                break;

            case 11:
                // Return a borrowed book
                printf("Enter ISBN: ");
                fgets(ISBN, MAX_ISBN_LENGTH, stdin);
                ISBN[strcspn(ISBN, "\n")] = '\0'; // Remove newline
                printf("Enter Borrower ID: ");
                fgets(ID, MAX_ID_LENGTH, stdin);
                ID[strcspn(ID, "\n")] = '\0'; // Remove newline
                returnBook(&library, ISBN, ID);
                break;

            case 12:
                // Generate overdue report
                generateOverdueReport(&library);
                break;

            case 13:
                // Display all borrowed books
                displayAllBorrowedBooks(&library);
                break;

            case 14:
                // Exit the program
                exit(0);

            default:
                // Handle invalid choices
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
