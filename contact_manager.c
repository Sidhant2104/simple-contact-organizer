#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50
#define PHONE_LEN 15

// Contact node structure
typedef struct Contact {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    struct Contact* next;
} Contact;

Contact* head = NULL;

// Function to create a new contact node
Contact* create_contact(const char* name, const char* phone) {
    Contact* new_contact = (Contact*)malloc(sizeof(Contact));
    if (!new_contact) {
        printf("Memory allocation error\n");
        exit(1);
    }
    strncpy(new_contact->name, name, NAME_LEN);
    strncpy(new_contact->phone, phone, PHONE_LEN);
    new_contact->next = NULL;
    return new_contact;
}

// Add contact at the end
void add_contact(const char* name, const char* phone) {
    Contact* new_contact = create_contact(name, phone);
    if (head == NULL) {
        head = new_contact;
        return;
    }
    Contact* temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = new_contact;
    printf("Contact added successfully.\n");
}

// Search contact by name
void search_contact(const char* name) {
    Contact* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("Contact found: %s -> %s\n", temp->name, temp->phone);
            return;
        }
        temp = temp->next;
    }
    printf("Contact not found.\n");
}

// Delete contact by name
void delete_contact(const char* name) {
    if (head == NULL) {
        printf("Contact list empty.\n");
        return;
    }
    Contact* temp = head;
    Contact* prev = NULL;

    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Contact not found.\n");
        return;
    }
    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
    printf("Contact deleted successfully.\n");
}

// Display all contacts
void display_contacts() {
    if (head == NULL) {
        printf("No contacts to display.\n");
        return;
    }
    Contact* temp = head;
    printf("Contact List:\n");
    while (temp != NULL) {
        printf("Name: %s, Phone: %s\n", temp->name, temp->phone);
        temp = temp->next;
    }
}

// Free all contacts (cleanup)
void free_contacts() {
    Contact* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int choice;
    char name[NAME_LEN];
    char phone[PHONE_LEN];

    while (1) {
        printf("\nContact Management System\n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Delete Contact\n");
        printf("4. Display All Contacts\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // consume newline char

        switch(choice) {
            case 1:
                printf("Enter name: ");
                fgets(name, NAME_LEN, stdin);
                name[strcspn(name, "\n")] = 0;  // remove newline
                printf("Enter phone: ");
                fgets(phone, PHONE_LEN, stdin);
                phone[strcspn(phone, "\n")] = 0;
                add_contact(name, phone);
                break;
            case 2:
                printf("Enter name to search: ");
                fgets(name, NAME_LEN, stdin);
                name[strcspn(name, "\n")] = 0;
                search_contact(name);
                break;
            case 3:
                printf("Enter name to delete: ");
                fgets(name, NAME_LEN, stdin);
                name[strcspn(name, "\n")] = 0;
                delete_contact(name);
                break;
            case 4:
                display_contacts();
                break;
            case 5:
                free_contacts();
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
