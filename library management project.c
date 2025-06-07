#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Book Details
struct Book {
    int id;
    char title[50];
    char author[50];
    int quantity;
};

FILE *fp;

// Function to Add New Book
void addBook() {
    struct Book book;
    fp = fopen("library.dat", "ab");
    printf("Enter Book ID: ");
    scanf("%d", &book.id);
    printf("Enter Book Title: ");
    getchar(); // To consume newline
    fgets(book.title, sizeof(book.title), stdin);
    book.title[strcspn(book.title, "\n")] = 0; // Remove newline
    printf("Enter Author: ");
    fgets(book.author, sizeof(book.author), stdin);
    book.author[strcspn(book.author, "\n")] = 0;
    printf("Enter Quantity: ");
    scanf("%d", &book.quantity);
    fwrite(&book, sizeof(book), 1, fp);
    fclose(fp);
    printf("Book Added Successfully!\n");
}

// Function to View All Books
void viewBooks() {
    struct Book book;
    fp = fopen("library.dat", "rb");
    printf("\nID\tTitle\t\tAuthor\t\tQuantity\n");
    printf("-----------------------------------------------------\n");
    while (fread(&book, sizeof(book), 1, fp)) {
        printf("%d\t%s\t\t%s\t\t%d\n", book.id, book.title, book.author, book.quantity);
    }
    fclose(fp);
}

// Function to Search Book by Title
void searchBook() {
    struct Book book;
    char searchTitle[50];
    int found = 0;
    fp = fopen("library.dat", "rb");
    printf("Enter Book Title to Search: ");
    getchar();
    fgets(searchTitle, sizeof(searchTitle), stdin);
    searchTitle[strcspn(searchTitle, "\n")] = 0;

    while (fread(&book, sizeof(book), 1, fp)) {
        if (strcmp(book.title, searchTitle) == 0) {
            printf("\nBook Found!\n");
            printf("ID: %d\nTitle: %s\nAuthor: %s\nQuantity: %d\n", book.id, book.title, book.author, book.quantity);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (!found) {
        printf("Book Not Found!\n");
    }
}

// Function to Issue Book
void issueBook() {
    struct Book book;
    int bookID, found = 0;
    FILE *temp;

    fp = fopen("library.dat", "rb");
    temp = fopen("temp.dat", "wb");

    printf("Enter Book ID to Issue: ");
    scanf("%d", &bookID);

    while (fread(&book, sizeof(book), 1, fp)) {
        if (book.id == bookID) {
            if (book.quantity > 0) {
                book.quantity--;
                printf("Book Issued Successfully!\n");
            } else {
                printf("Book Out of Stock!\n");
            }
            found = 1;
        }
        fwrite(&book, sizeof(book), 1, temp);
    }
    fclose(fp);
    fclose(temp);

    remove("library.dat");
    rename("temp.dat", "library.dat");

    if (!found) {
        printf("Book Not Found!\n");
    }
}

// Function to Return Book
void returnBook() {
    struct Book book;
    int bookID, found = 0;
    FILE *temp;

    fp = fopen("library.dat", "rb");
    temp = fopen("temp.dat", "wb");

    printf("Enter Book ID to Return: ");
    scanf("%d", &bookID);

    while (fread(&book, sizeof(book), 1, fp)) {
        if (book.id == bookID) {
            book.quantity++;
            printf("Book Returned Successfully!\n");
            found = 1;
        }
        fwrite(&book, sizeof(book), 1, temp);
    }
    fclose(fp);
    fclose(temp);

    remove("library.dat");
    rename("temp.dat", "library.dat");

    if (!found) {
        printf("Book Not Found!\n");
    }
}

// Main Function
int main() {
    int choice;
    while (1) {
        printf("\n===== Library Management System =====\n");
        printf("1. Add New Book\n");
        printf("2. View All Books\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                viewBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                issueBook();
                break;
            case 5:
                returnBook();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid Choice! Please try again.\n");
        }
    }
    return 0;
}