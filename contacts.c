#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "contacts.h"

// initializing the contacts array
void init_contacts(struct Contact contacts[]) {
    for (int i = 0; i < MAX_CONTACTS; i++) {
        contacts[i].name[0] = '\0';
        contacts[i].email[0] = '\0';
        contacts[i].phone[0] = '\0';
    }
}

//function to add a new contact
void add_contact(struct Contact contacts[]) {
    int i;
    for (i = 0; i < MAX_CONTACTS; i++) {
        if (contacts[i].name[0] == '\0') {
            printf("\n# Add New Contact\n");
            printf("-----------------\n");
            printf(" Enter Name : ");
            scanf(" %[^\n]s", contacts[i].name);

            printf(" Enter Email (If not required enter 'none') : ");
            scanf("%99s", contacts[i].email);
            getchar();

            printf(" Enter Phone: ");
            char phone[MAX_PHONE_LENGTH];
            scanf("%99s", phone);
            getchar();

           //checks the validity of the of phone number
            if (phone[0] == '+') {
                if (all_digits(phone + 1)) {
                    strcpy(contacts[i].phone, phone);
                    printf("\n Contact added successfully!\n");
                    break;
                }
            } else {
                if (all_digits(phone)) {
                    strcpy(contacts[i].phone, phone);
                    printf("\n Contact added successfully!\n");
                    break;
                }
            }
            printf("\n Invalid phone number format. Try again!\n");
            return;
        }
    }
   //checks the contact list length
    if (i == MAX_CONTACTS) {
        printf(" Contact list is full. Delete some contacts to add new ones.\n");
        return;
    }
    // saving added contact in the file
    save_contacts(contacts);
}

//Use to edit an existing contact
void edit_contact(struct Contact contacts[]) {
    char name[MAX_NAME_LENGTH];
    printf(" Enter the name of the contact you want to edit: ");
    scanf(" %[^\n]s", name);

    int i;
    for (i = 0; i < MAX_CONTACTS; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            printf("\n **If you want to retain the existing value please re-enter that value\n");
            printf("\n Existing name: %s",contacts[i].name);
            printf("\n Enter New Name: ");
            scanf(" %[^\n]s", contacts[i].name);

            printf("\n Existing Email: %s",contacts[i].email);
            printf("\n Enter New Email: ");
            scanf("%s", contacts[i].email);

            printf("\n Existing phone: %s",contacts[i].phone);
            printf("\n Enter New Phone: ");
            scanf("%s", contacts[i].phone);

            printf("\n Contact updated successfully!\n");
            save_contacts(contacts);
            return;
        }
    }
    printf(" Contact not found!\n");
}

//use to delete an existing contact
void delete_contact(struct Contact contacts[]) {
    char name[MAX_NAME_LENGTH];
    int count = 0;
    int indexes[MAX_CONTACTS];

    printf("\n Enter the name of the contact you want to delete: ");
    scanf(" %[^\n]s", name);

    for (int i = 0; i < MAX_CONTACTS; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            indexes[count++] = i;
        }
    }

    if (count == 0) {
        printf("\n Contact not found!\n");
        return;
    }
    // if there are more than one contact with the same name,
    //it shows all of them, and user can select which one to delete.
    if (count == 1) {
        contacts[indexes[0]].name[0] = '\0';
        contacts[indexes[0]].email[0] = '\0';
        contacts[indexes[0]].phone[0] = '\0';
        printf("\n Contact deleted successfully!\n");
        save_contacts(contacts);
    } else {
        printf("\n Multiple contacts found with the same name:\n");
        for (int i = 0; i < count; i++) {
            printf(" %d. Name: %s\n   Email: %s\n   Phone: %s\n\n", i + 1, contacts[indexes[i]].name,
                   contacts[indexes[i]].email, contacts[indexes[i]].phone);
        }

        int selection;
        printf(" Enter the number of the contact to delete (1-%d): ", count);
        scanf("%d", &selection);

        if (selection >= 1 && selection <= count) {
            contacts[indexes[selection - 1]].name[0] = '\0';
            contacts[indexes[selection - 1]].email[0] = '\0';
            contacts[indexes[selection - 1]].phone[0] = '\0';
            printf("\n Contact deleted successfully!\n");
            save_contacts(contacts);
        } else {
            printf("\n Invalid selection. No contact deleted.\n");
        }
    }
}

//This function use to search a specific contact using the name
void search_contact(const struct Contact contacts[]) {
    char name[MAX_NAME_LENGTH];
    printf("\n Enter the name of the contact you want to search: ");
    scanf(" %[^\n]s", name);

    int i,j;
    for (i = 0,j=0; i < MAX_CONTACTS; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            j++;
            printf("\n Name: %s\n", contacts[i].name);
            printf(" Email: %s\n", contacts[i].email);
            printf(" Phone: %s\n", contacts[i].phone);
        }
        if(i==MAX_CONTACTS-1 && j!=0){
             return;
        }
    }
    printf("\n Contact not found!\n");
}

//Display all the contacts save in the file
void display_all_contacts() {
    struct Contact contacts[MAX_CONTACTS];
    int num_contacts = load_contacts(contacts);

    printf("\n All Contacts\n");
    printf("+-------------------------------------------------------------------------+\n");
    printf("| %-20s | %-30s | %-15s |\n", "Name", "Email", "Phone");
    printf("+----------------------+--------------------------------+-----------------+\n");
    for (int i = 0; i < num_contacts; i++) {
        if (contacts[i].name[0] != '\0') {
            printf("| %-20s | %-30s | %-15s |\n", contacts[i].name, contacts[i].email, contacts[i].phone);
        }
    }
    printf("+----------------------+--------------------------------+-----------------+\n");

    //displays the total number of contacts and remaining slots for store contacts
    printf("\n Total contacts count: %d\n", num_contacts);
    printf(" Remaining slots: %d\n", get_remaining_slots());
}

// save all contacts in a file
void save_contacts(const struct Contact contacts[]) {
    FILE* file = fopen("contacts.txt", "w");
    if (file == NULL) {
        printf(" Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < MAX_CONTACTS; i++) {
        if (contacts[i].name[0] != '\0') {
            fprintf(file, "%s;%s;%s\n", contacts[i].name, contacts[i].email, contacts[i].phone);
        }
    }
    fclose(file);
}

// This loads the contacts which are stored in the file
int load_contacts(struct Contact contacts[]){
    FILE* file = fopen("contacts.txt", "r");
    if (file == NULL){
        printf(" Error opening file for reading.\n");
        return 0;
    }
    init_contacts(contacts);

    int i = 0;
    while (i < MAX_CONTACTS && fscanf(file, "%[^;];%[^;];%[^\n]\n",
        contacts[i].name,
        contacts[i].email,
        contacts[i].phone) == 3){
        i++;
    }
    fclose(file);
    return i;
}

//return the count of total number of contacts
int get_total_contacts_count() {
    struct Contact contacts[MAX_CONTACTS];
    int num_contacts = load_contacts(contacts);
    return num_contacts;
}
//return the remaining slots for save new contacts
int get_remaining_slots() {
    int total_contacts = get_total_contacts_count();
    int remaining_slots = MAX_CONTACTS - total_contacts;
    return remaining_slots;
}

