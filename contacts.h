#ifndef CONTACTS_H_INCLUDED
#define CONTACTS_H_INCLUDED

//defines all the constants
#define MAX_CONTACTS 100
#define MAX_NAME_LENGTH 100
#define MAX_EMAIL_LENGTH 100
#define MAX_PHONE_LENGTH 20

// Contact structure use to represent a contact
struct Contact {
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone[MAX_PHONE_LENGTH];
};

//Declaring all functions used in the program
void init_contacts(struct Contact contacts[]);
void add_contact(struct Contact contacts[]);
void edit_contact(struct Contact contacts[]);
void delete_contact(struct Contact contacts[]);
void search_contact(const struct Contact contacts[]);
void display_all_contacts();
void save_contacts(const struct Contact contacts[]);
int load_contacts(struct Contact contacts[]);
int get_remaining_slots();
int get_total_contacts_count();

#endif
