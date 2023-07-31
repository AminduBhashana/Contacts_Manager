#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "contacts.h"
#include <ctype.h>

//This function checks the all characters of phone number are digits or not
bool all_digits(const char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

// function allows user to input only integer value.
// This is used in getting the user's choice in main menu
int get_integer_input() {
    int choice;
    while (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
        printf("\n Invalid Choice!.\n Please enter a valid choice: ");
    }
    return choice;
}


