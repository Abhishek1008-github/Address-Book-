#include <stdio.h>
#include <stdlib.h>
#include "file.h"

// Function to save all contacts to a file
void saveContactsToFile(AddressBook *addressBook) 
{
    
    FILE *fptr = fopen("contact.csv","w");
    
    fprintf(fptr,"%d\n",addressBook->contactCount);
    
    
    int i ;
    for(i = 0;i< addressBook->contactCount; i++)
    {
        fprintf(fptr,"%s,",addressBook->contacts[i].name);
        fprintf(fptr,"%s,",addressBook->contacts[i].phone);
        fprintf(fptr,"%s\n",addressBook->contacts[i].email);
    }
    fclose(fptr);
  
}
// Function to load all contacts from a file
void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr = fopen("contact.csv","r");

    // Check if the file exists or opened successfully
    if(fptr == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }

    char str[100];
    fscanf(fptr,"%s\n",str);
    int count = atoi(str); // Convert string to integer
    addressBook->contactCount = count;
    for(int i = 0;i < addressBook->contactCount ; i++)
    // Read name, phone, and email separated by commas
    {
        fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    fclose(fptr);
}