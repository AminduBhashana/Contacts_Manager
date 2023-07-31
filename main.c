#include <stdio.h>
#include "contacts.h"
#include "validations.c"
#include "contacts.c"

void main() {
    struct Contact contacts[MAX_CONTACTS];
    //loads contacts from the file
    load_contacts(contacts);

    int choice;
    printf("\n************************\n");
    printf(" *   Contacts Manager   *\n");
    printf("************************\n");

    do {
        //Display Contact Manager's Main Menu
        printf("\n-------------------------\n");
        printf("# Contacts Manager Menu #\n");
        printf("-------------------------\n");
        printf(" 1. Add Contact\n");
        printf(" 2. Edit Contact\n");
        printf(" 3. Delete Contact\n");
        printf(" 4. Search Contact\n");
        printf(" 5. Display All Contacts\n");
        printf(" 6. Exit\n");
        printf("\n Enter your choice: ");
        choice = get_integer_input();

        //use switch case to perform suitable task according to user input
        switch (choice) {
            case 1:
                add_contact(contacts);
                break;
            case 2:
                edit_contact(contacts);
                break;
            case 3:
                delete_contact(contacts);
                break;
            case 4:
                search_contact(contacts);
                break;
            case 5:
                display_all_contacts();
                break;
            case 6:
                printf("\n Exiting Contacts Manager. Goodbye!\n");
                break;
            default:
                printf("\n Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 6);
}

