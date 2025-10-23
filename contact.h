#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
int Validate_phn(char *phn,AddressBook *addressBook);
int Validate_email(char *email,AddressBook *addressBook);
int search_mail(char *search_term,AddressBook *addressBook);
int search_number(char *search_term,AddressBook *addressBook);
int editing_contact(int res,AddressBook *addressBook);
int search_name(char *search_term ,AddressBook *addressBook,int *index_arr);
int delete_contact(int res,AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);


#endif
