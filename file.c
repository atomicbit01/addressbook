#include "file.h"
#include <stdio.h>

void saveContactsToFile(AddressBook *addressBook) {
  // Create a file pointer in write mode
  FILE *fp = fopen("contacts.csv", "w");
  if (fp == NULL) {
    printf("Error: Could not open file for saving data.\n");
    return;
  }

  // Save total count first
  fprintf(fp, "%d\n", addressBook->contactCount);

  // Save each contact line by line
  for (int i = 0; i < addressBook->contactCount; i++) {
    fprintf(fp, "%s,%s,%s\n", addressBook->contacts[i].name,
            addressBook->contacts[i].phone, addressBook->contacts[i].email);
  }

  fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook) {
  // Create a file pointer in read mode
  FILE *fp = fopen("contacts.csv", "r");

  // If file does not exist yet, set count to 0 and exit
  if (fp == NULL) {
    addressBook->contactCount = 0;
    return;
  }

  // 1. Load the total count from the file first
  if (fscanf(fp, "%d\n", &addressBook->contactCount) != 1) {
    addressBook->contactCount = 0;
    fclose(fp);
    return;
  }

  // 2. Loop through the contacts
  for (int i = 0; i < addressBook->contactCount; i++) {

    fscanf(fp, "%[^,\n],%[^,\n],%[^\n]\n", addressBook->contacts[i].name,
           addressBook->contacts[i].phone, addressBook->contacts[i].email);
  }

  fclose(fp);
}
