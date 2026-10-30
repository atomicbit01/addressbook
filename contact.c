#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void listContacts(AddressBook *addressBook) {

  // Sort contacts based on the chosen criteria
  printf("1. Sort by name\n");
  printf("2. Sort by phone\n");
  printf("3. Sort by email\n");
  printf("4. Exit\n");

  int sortchoice;
  printf("Enter your choice for sorting: ");
  scanf("%d", &sortchoice);

  switch (sortchoice) {

  // Sort by name
  case 1:

    for (int i = 0; i < addressBook->contactCount - 1; i++) {
      for (int j = 0; j < addressBook->contactCount - i - 1; j++) {
        if (strcasecmp(addressBook->contacts[j].name,
                       addressBook->contacts[j + 1].name) > 0) {

          swapContacts(&addressBook->contacts[j],
                       &addressBook->contacts[j + 1]);
        }
      }
    }

    break;

  // Sort by phone
  case 2:

    for (int i = 0; i < addressBook->contactCount - 1; i++) {
      for (int j = 0; j < addressBook->contactCount - i - 1; j++) {
        if (strcasecmp(addressBook->contacts[j].phone,
                       addressBook->contacts[j + 1].phone) > 0) {

          swapContacts(&addressBook->contacts[j],
                       &addressBook->contacts[j + 1]);
        }
      }
    }

    break;

  // Sort by email
  case 3:

    for (int i = 0; i < addressBook->contactCount - 1; i++) {
      for (int j = 0; j < addressBook->contactCount - i - 1; j++) {
        if (strcasecmp(addressBook->contacts[j].email,
                       addressBook->contacts[j + 1].email) > 0) {

          swapContacts(&addressBook->contacts[j],
                       &addressBook->contacts[j + 1]);
        }
      }
    }

    break;

  // Exit
  case 4:
    return;
  }
  printf("\nContacts List\n");
  for (int i = 0; i < addressBook->contactCount; i++) {
    printf("Name: %s, ", addressBook->contacts[i].name);
    printf("Phone: %s, ", addressBook->contacts[i].phone);
    printf("Email: %s\n", addressBook->contacts[i].email);
  }
}

void initialize(AddressBook *addressBook) {
  // addressBook->contactCount = 0;
  //  populateAddressBook(addressBook);

  // Load contacts from file during initialization (After files)
  loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
  saveContactsToFile(addressBook); // Save contacts to file
  exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook) {

  if (addressBook->contactCount >= MAX_CONTACTS) {
    printf("Error: Address Book is full\n");
    return;
  }

  char tempName[50], tempPhone[15], tempEmail[50];

  // Validate and Read Name
  do {
    printf("Enter the name: ");
    scanf(" %[^\n]", tempName);
    if (!isValidName(tempName)) {
      printf("Invalid name! Use only letters and spaces (Max 49 chars).\n");
    }
  } while (!isValidName(tempName));

  // Validate and Read Phone
  do {
    printf("Enter the phone number (10 digits): ");
    scanf(" %[^\n]", tempPhone);
    if (!isValidPhone(tempPhone)) {
      printf("Invalid phone number! Must be exactly 10 digits.\n");
    }
  } while (!isValidPhone(tempPhone));

  // Validate and Read Email
  do {
    printf("Enter the email: ");
    scanf(" %[^\n]", tempEmail);
    if (!isValidEmail(tempEmail)) {
      printf("Invalid email format! (e.g., user@example.com).\n");
    }
  } while (!isValidEmail(tempEmail));

  // Copy validated values over to the address book array
  strcpy(addressBook->contacts[addressBook->contactCount].name, tempName);
  strcpy(addressBook->contacts[addressBook->contactCount].phone, tempPhone);
  strcpy(addressBook->contacts[addressBook->contactCount].email, tempEmail);

  addressBook->contactCount++;
  printf("Contact added successfully!\n");
}

int searchContact(AddressBook *addressBook) {

  // Print menu and read choice
  printf("1. Search by name\n");
  printf("2. Search by phone number\n");
  printf("3. Search by email\n");
  printf("4. Exit\n");

  int searchchoice;
  printf("Enter your choice: ");
  scanf("%d", &searchchoice);

  char name[50], phone[15], email[50];

  switch (searchchoice) {

  // Search by name
  case 1:

    printf("Enter the name to search: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < addressBook->contactCount; i++) {
      if (strcasecmp(addressBook->contacts[i].name, name) == 0) {
        printf("Name: %s, ", addressBook->contacts[i].name);
        printf("Phone: %s, ", addressBook->contacts[i].phone);
        printf("Email: %s\n", addressBook->contacts[i].email);

        return i;
      }
    }

    break;

  // Search by phone
  case 2:

    printf("Enter the phone number to search: ");
    scanf(" %[^\n]", phone);

    for (int i = 0; i < addressBook->contactCount; i++) {
      if (strcasecmp(addressBook->contacts[i].phone, phone) == 0) {
        printf("Name: %s, ", addressBook->contacts[i].name);
        printf("Phone: %s, ", addressBook->contacts[i].phone);
        printf("Email: %s\n", addressBook->contacts[i].email);

        return i;
      }
    }

    break;

  // Search by email
  case 3:

    printf("Enter the email to search: ");
    scanf(" %[^\n]", email);

    for (int i = 0; i < addressBook->contactCount; i++) {
      if (strcasecmp(addressBook->contacts[i].email, email) == 0) {
        printf("Name: %s, ", addressBook->contacts[i].name);
        printf("Phone: %s, ", addressBook->contacts[i].phone);
        printf("Email: %s\n", addressBook->contacts[i].email);

        return i;
      }
    }

    break;

  // Exit
  case 4:
    return -1;
  }

  return -2;
}

void editContact(AddressBook *addressBook) {
  // Search for contact to edit FIRST
  int index = searchContact(addressBook);

  if (index == -1) {
    printf("Exit from search contact.\n");
  } else if (index == -2) {
    printf("Contact not found.\n");
  } else {
    // Only print menu if contact exists
    printf("1. Edit name\n");
    printf("2. Edit phone number\n");
    printf("3. Edit email\n");
    printf("4. Exit\n");

    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);

    char temp[50]; // Temporary buffer for validation

    switch (choice) {
    // Edit name
    case 1:
      do {
        printf("Enter the new name: ");
        scanf(" %[^\n]", temp);
        if (!isValidName(temp)) {
          printf("Invalid name! Use only letters and spaces (Max 49 chars).\n");
        }
      } while (!isValidName(temp));

      // Update only after successful validation
      strcpy(addressBook->contacts[index].name, temp);
      printf("Name updated successfully!\n");
      break;

      // Edit phone
    case 2:
      do {
        printf("Enter the new phone number (10 digits): ");
        scanf(" %[^\n]", temp);
        if (!isValidPhone(temp)) {
          printf("Invalid phone number! Must be exactly 10 digits.\n");
        }
      } while (!isValidPhone(temp));

      strcpy(addressBook->contacts[index].phone, temp);
      printf("Phone number updated successfully!\n");
      break;

      // Edit email
    case 3:
      do {
        printf("Enter the new email: ");
        scanf(" %[^\n]", temp);
        if (!isValidEmail(temp)) {
          printf("Invalid email format! (e.g., user@example.com).\n");
        }
      } while (!isValidEmail(temp));

      strcpy(addressBook->contacts[index].email, temp);
      printf("Email updated successfully!\n");
      break;

      // Exit
    case 4:
      return;
    }
  }
}

void deleteContact(AddressBook *addressBook) {

  // search for contact to edit
  int index = searchContact(addressBook);

  if (index == -1) {
    printf("Exit from search contact.\n");
  } else if (index == -2) {
    printf("Contact not found.\n");
  } else {

    // Removing contact if found
    for (int i = index; i < addressBook->contactCount - 1; i++) {
      addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;
  }
}

int isValidName(const char *name) {
  int len = strlen(name);

  // Check if empty or too long
  if (len == 0 || len >= 50) {
    return 0;
  }

  // Ensure it contains only letters and spaces
  for (int i = 0; i < len; i++) {
    if (!isalpha((unsigned char)name[i]) && name[i] != ' ') {
      return 0;
    }
  }

  return 1; // Valid
}

int isValidPhone(const char *phone) {
  int len = strlen(phone);

  // Check for standard 10-digit length requirement
  if (len != 10) {
    return 0;
  }

  // Ensure every character is a digit
  for (int i = 0; i < len; i++) {
    if (!isdigit((unsigned char)phone[i])) {
      return 0;
    }
  }

  return 1; // Valid
}

int isValidEmail(const char *email) {
  int len = strlen(email);
  if (len < 5 || len >= 50)
    return 0; // Too short or too long

  const char *at_ptr = strchr(email, '@');
  if (!at_ptr)
    return 0; // Must contain '@'

  if (at_ptr == email || at_ptr == email + len - 1)
    return 0;

  if (strchr(at_ptr + 1, '@'))
    return 0;

  // Look for '.' after the '@' symbol
  const char *dot_ptr = strchr(at_ptr + 1, '.');
  if (!dot_ptr)
    return 0;

  if (dot_ptr == at_ptr + 1 || dot_ptr == email + len - 1)
    return 0;

  return 1; // Valid
}

void swapContacts(Contact *c1, Contact *c2) {
  Contact temp = *c1;
  *c1 = *c2;
  *c2 = temp;
}
