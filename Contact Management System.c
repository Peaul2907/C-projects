#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "contacts.dat"

struct Contact {
    char name[50];
    char phone[15];
    char email[50];
};

// Function declarations
void addContact();
void viewContacts();
void searchContact();
void deleteContact();
void updateContact();
void clearBuffer();

int main() {
    int choice;
    
    while (1) {
        printf("\n--- Contact Management System ---\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Update Contact\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearBuffer();

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                updateContact();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to clear input buffer
void clearBuffer() {
    while (getchar() != '\n');
}

// Function to add a contact
void addContact() {
    FILE *file = fopen(FILE_NAME, "ab");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Contact contact;
    printf("Enter Name: ");
    fgets(contact.name, sizeof(contact.name), stdin);
    contact.name[strcspn(contact.name, "\n")] = '\0';

    printf("Enter Phone: ");
    fgets(contact.phone, sizeof(contact.phone), stdin);
    contact.phone[strcspn(contact.phone, "\n")] = '\0';

    printf("Enter Email: ");
    fgets(contact.email, sizeof(contact.email), stdin);
    contact.email[strcspn(contact.email, "\n")] = '\0';

    fwrite(&contact, sizeof(contact), 1, file);
    fclose(file);

    printf("Contact added successfully!\n");
}

// Function to view all contacts
void viewContacts() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No contacts found!\n");
        return;
    }

    struct Contact contact;
    printf("\n--- Contact List ---\n");
    while (fread(&contact, sizeof(contact), 1, file)) {
        printf("Name: %s\n", contact.name);
        printf("Phone: %s\n", contact.phone);
        printf("Email: %s\n\n", contact.email);
    }

    fclose(file);
}

// Function to search a contact
void searchContact() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No contacts found!\n");
        return;
    }

    char searchName[50];
    printf("Enter name to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    struct Contact contact;
    int found = 0;
    while (fread(&contact, sizeof(contact), 1, file)) {
        if (strcmp(contact.name, searchName) == 0) {
            printf("\nContact Found:\n");
            printf("Name: %s\n", contact.name);
            printf("Phone: %s\n", contact.phone);
            printf("Email: %s\n", contact.email);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Contact not found!\n");
    }

    fclose(file);
}

// Function to delete a contact
void deleteContact() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No contacts found!\n");
        return;
    }

    char deleteName[50];
    printf("Enter name to delete: ");
    fgets(deleteName, sizeof(deleteName), stdin);
    deleteName[strcspn(deleteName, "\n")] = '\0';

    FILE *tempFile = fopen("temp.dat", "wb");
    struct Contact contact;
    int found = 0;

    while (fread(&contact, sizeof(contact), 1, file)) {
        if (strcmp(contact.name, deleteName) == 0) {
            found = 1;
            continue;
        }
        fwrite(&contact, sizeof(contact), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found) {
        printf("Contact deleted successfully!\n");
    } else {
        printf("Contact not found!\n");
    }
}

// Function to update a contact
void updateContact() {
    FILE *file = fopen(FILE_NAME, "rb+");
    if (file == NULL) {
        printf("No contacts found!\n");
        return;
    }

    char updateName[50];
    printf("Enter name to update: ");
    fgets(updateName, sizeof(updateName), stdin);
    updateName[strcspn(updateName, "\n")] = '\0';

    struct Contact contact;
    int found = 0;

    while (fread(&contact, sizeof(contact), 1, file)) {
        if (strcmp(contact.name, updateName) == 0) {
            printf("Enter new Phone: ");
            fgets(contact.phone, sizeof(contact.phone), stdin);
            contact.phone[strcspn(contact.phone, "\n")] = '\0';

            printf("Enter new Email: ");
            fgets(contact.email, sizeof(contact.email), stdin);
            contact.email[strcspn(contact.email, "\n")] = '\0';

            fseek(file, -sizeof(contact), SEEK_CUR);
            fwrite(&contact, sizeof(contact), 1, file);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) {
        printf("Contact updated successfully!\n");
    } else {
        printf("Contact not found!\n");
    }
}