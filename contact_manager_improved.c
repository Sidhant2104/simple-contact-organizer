#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NAME_LEN 50
#define PHONE_LEN 15
#define EMAIL_LEN 100
#define FILENAME "contacts.txt"

typedef struct Contact {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
    struct Contact* next;
} Contact;

Contact* head = NULL;

// Input validation functions
int is_valid_phone(const char* phone) {
    if (strlen(phone) < 10) return 0;
    for (int i = 0; phone[i]; i++) {
        if (!isdigit(phone[i]) && phone[i] != '-' && phone[i] != ' ' && phone[i] != '(' && phone[i] != ')') {
            return 0;
        }
    }
    return 1;
}

int is_valid_email(const char* email) {
    return strchr(email, '@') != NULL && strchr(email, '.') != NULL;
}

// Safe string copy with null termination
void safe_strcpy(char* dest, const char* src, size_t size) {
    strncpy(dest, src, size - 1);
    dest[size - 1] = '\0';
}

// Create contact with validation
Contact* create_contact(const char* name, const char* phone, const char* email) {
    if (!name || !phone || strlen(name) == 0 || strlen(phone) == 0) {
        return NULL;
    }
    
    if (!is_valid_phone(phone)) {
        printf("Error: Invalid phone number format\n");
        return NULL;
    }
    
    if (email && strlen(email) > 0 && !is_valid_email(email)) {
        printf("Error: Invalid email format\n");
        return NULL;
    }
    
    Contact* new_contact = malloc(sizeof(Contact));
    if (!new_contact) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    
    safe_strcpy(new_contact->name, name, NAME_LEN);
    safe_strcpy(new_contact->phone, phone, PHONE_LEN);
    safe_strcpy(new_contact->email, email ? email : "", EMAIL_LEN);
    new_contact->next = NULL;
    
    return new_contact;
}

// Add contact with duplicate check
int add_contact(const char* name, const char* phone, const char* email) {
    // Check for duplicates
    Contact* temp = head;
    while (temp) {
        if (strcmp(temp->name, name) == 0) {
            printf("Error: Contact with name '%s' already exists\n", name);
            return 0;
        }
        temp = temp->next;
    }
    
    Contact* new_contact = create_contact(name, phone, email);
    if (!new_contact) return 0;
    
    if (!head) {
        head = new_contact;
    } else {
        temp = head;
        while (temp->next) temp = temp->next;
        temp->next = new_contact;
    }
    
    printf("Contact added successfully\n");
    return 1;
}

// Search contact (case-insensitive)
Contact* search_contact(const char* name) {
    Contact* temp = head;
    while (temp) {
        if (strcasecmp(temp->name, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Delete contact
int delete_contact(const char* name) {
    if (!head) {
        printf("Error: Contact list is empty\n");
        return 0;
    }
    
    Contact* temp = head;
    Contact* prev = NULL;
    
    while (temp && strcasecmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }
    
    if (!temp) {
        printf("Error: Contact '%s' not found\n", name);
        return 0;
    }
    
    if (!prev) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    
    free(temp);
    printf("Contact deleted successfully\n");
    return 1;
}

// Display all contacts
void display_contacts() {
    if (!head) {
        printf("No contacts to display\n");
        return;
    }
    
    printf("\n=== Contact List ===\n");
    Contact* temp = head;
    int count = 1;
    
    while (temp) {
        printf("%d. Name: %s\n", count, temp->name);
        printf("   Phone: %s\n", temp->phone);
        if (strlen(temp->email) > 0) {
            printf("   Email: %s\n", temp->email);
        }
        printf("   ---\n");
        temp = temp->next;
        count++;
    }
}

// Save contacts to file
void save_contacts() {
    FILE* file = fopen(FILENAME, "w");
    if (!file) {
        printf("Error: Cannot save contacts to file\n");
        return;
    }
    
    Contact* temp = head;
    while (temp) {
        fprintf(file, "%s|%s|%s\n", temp->name, temp->phone, temp->email);
        temp = temp->next;
    }
    
    fclose(file);
    printf("Contacts saved successfully\n");
}

// Load contacts from file
void load_contacts() {
    FILE* file = fopen(FILENAME, "r");
    if (!file) return;
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove newline
        
        char* name = strtok(line, "|");
        char* phone = strtok(NULL, "|");
        char* email = strtok(NULL, "|");
        
        if (name && phone) {
            Contact* new_contact = create_contact(name, phone, email);
            if (new_contact) {
                if (!head) {
                    head = new_contact;
                } else {
                    Contact* temp = head;
                    while (temp->next) temp = temp->next;
                    temp->next = new_contact;
                }
            }
        }
    }
    
    fclose(file);
}

// Free all contacts
void free_contacts() {
    Contact* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Get safe input
void get_input(const char* prompt, char* buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin)) {
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline
    }
}

int main() {
    int choice;
    char name[NAME_LEN], phone[PHONE_LEN], email[EMAIL_LEN];
    
    load_contacts();
    printf("Contact Manager Started - Loaded existing contacts\n");
    
    while (1) {
        printf("\n=== Contact Management System ===\n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Delete Contact\n");
        printf("4. Display All Contacts\n");
        printf("5. Save Contacts\n");
        printf("6. Exit\n");
        printf("Enter choice (1-6): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Error: Invalid input\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        getchar(); // Consume newline
        
        switch(choice) {
            case 1:
                get_input("Enter name: ", name, NAME_LEN);
                get_input("Enter phone: ", phone, PHONE_LEN);
                get_input("Enter email (optional): ", email, EMAIL_LEN);
                add_contact(name, phone, strlen(email) > 0 ? email : NULL);
                break;
                
            case 2:
                get_input("Enter name to search: ", name, NAME_LEN);
                Contact* found = search_contact(name);
                if (found) {
                    printf("\nContact found:\n");
                    printf("Name: %s\n", found->name);
                    printf("Phone: %s\n", found->phone);
                    if (strlen(found->email) > 0) {
                        printf("Email: %s\n", found->email);
                    }
                } else {
                    printf("Contact not found\n");
                }
                break;
                
            case 3:
                get_input("Enter name to delete: ", name, NAME_LEN);
                delete_contact(name);
                break;
                
            case 4:
                display_contacts();
                break;
                
            case 5:
                save_contacts();
                break;
                
            case 6:
                save_contacts();
                free_contacts();
                printf("Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid choice! Please enter 1-6\n");
        }
    }
    
    return 0;
}