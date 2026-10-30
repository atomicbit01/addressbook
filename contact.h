#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
  char name[50];
  char phone[20];
  char email[50];
} Contact;

typedef struct {
  Contact contacts[MAX_CONTACTS];
  int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
void populateAddressBook(AddressBook *addressBook);
void swapContacts(Contact *c1, Contact *c2);

int isValidEmail(const char *email);
int isValidPhone(const char *phone);
int isValidName(const char *name);

#endif
