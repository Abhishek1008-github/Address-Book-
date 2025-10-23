#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    int index=1;
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("Sl.no\tName\t\t\tPhn_no\t\t\tEmail_id\n");
    printf("---------------------------------------------------------------------------------------------------\n");
    for(int i=0 ; i < (addressBook->contactCount) ; i++)
    {
        printf("%d\t",index++);
        printf("%-20s\t",addressBook->contacts[i].name);
        printf("%-20s\t",addressBook->contacts[i].phone);
        printf("%s\n",addressBook->contacts[i].email);
        printf("---------------------------------------------------------------------------------------------------\n");
    }

    
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    printf("Enter the name: ");
    scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].name);

    char ph_no[20];
    do
    {
        printf("Enter the mobile number: ");
        scanf("%s",ph_no);
    } while (!(Validate_phn(ph_no,addressBook)));
    strcpy(addressBook->contacts[addressBook->contactCount].phone,ph_no);

    char email[50];
    do
    {
        printf("Enter the e-mail id: ");
        scanf("%s",email);
    } while (!(Validate_email(email,addressBook)));
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);

    //increment contact cpunt
    (addressBook->contactCount)++;

}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    //Menu
    int choice;
    char str[5];
    char search_term[50];
    do
    {
        printf("1.Search by name.\n");
        printf("2.Search by phone number.\n");
        printf("3.Search by email id.\n");
        printf("4.EXIT\n");
        printf("Enter your choice: ");
        scanf("%s",str);
        choice = atoi(str);

        int index=1,flag=0;
        switch (choice)
        {
            case 1: char name[50];
                    printf("Enter the name: ");
                    scanf(" %[^\n]",name);
                    printf("--------------------------------------------------------------------------\n");
                    printf("Sl.no\tName\t\tPhn_no\t\tEmail_id\n");
                    printf("--------------------------------------------------------------------------\n");
                    for(int i=0 ; i < (addressBook->contactCount) ; i++)
                    {
                        if((strcmp(name,addressBook->contacts[i].name)) == 0)
                        {
                            flag=1;
                            printf("%d\t",index++);
                            printf("%s\t",addressBook->contacts[i].name);
                            printf("%s\t",addressBook->contacts[i].phone);
                            printf("%s\n",addressBook->contacts[i].email);
                            printf("--------------------------------------------------------------------------\n");
                        }
                    }
                    if(flag==0)
                    {
                        printf("Not found\n");
                    }

                    break;
            case 2: search_number(search_term , addressBook);
                    break;
            case 3:search_mail(search_term , addressBook);
                    break;
            case 4:break;
                
        default: printf("Invalid choice.\n");
        }
    }
    while(choice > 0 && choice <=3);
}

void editContact(AddressBook *addressBook)
{
    
    /* Define the logic for search */
    //Menu
    int choice;
    char str[5];
    char search_term[50];
    int index_arr[addressBook->contactCount];
    
    do
    {
    
        printf("1.Search by name.\n");
        printf("2.Search by phone number.\n");
        printf("3.Search by email id.\n");
        printf("4.EXIT.\n");
        printf("Enter your choice: ");
        scanf("%s",str);
        choice = atoi(str);

        int index=1,flag=0;
        switch (choice)
        {
            case 1: int res1 = search_name(search_term ,addressBook,index_arr);
                    editing_contact(res1 ,addressBook);
                    break;
            case 2: int res2 = search_number(search_term , addressBook);
                    editing_contact(res2 , addressBook);
                    break;
            case 3:int res3 = search_mail(search_term , addressBook);
                    editing_contact(res3 , addressBook);
                    break;
            case 4:break;
                
            default: printf("Invalid choice.\n");
        }
    }
    while(choice > 0 && choice <=3);
}

	
    


void deleteContact(AddressBook *addressBook)

{
    
    /* Define the logic for search */
    //Menu
    int choice;
    char str[5];
    char search_term[50];
    int index_arr[addressBook->contactCount];
    do
    {
    
        printf("1.Search by name.\n");
        printf("2.Search by phone number.\n");
        printf("3.Search by email id.\n");
        printf("4.Exit.\n");
        printf("Enter your choice: ");
        scanf("%s",str);
        choice = atoi(str);

        int index=1,flag=0;
        switch (choice)
        {
            case 1: int res1 = search_name(search_term ,addressBook,index_arr);
                    delete_contact(res1 ,addressBook);
                    break;
            case 2: int res2 = search_number(search_term , addressBook);
                    delete_contact(res2 , addressBook);
                    break;
            case 3:int res3 = search_mail(search_term , addressBook);
                    delete_contact(res3 , addressBook);
                    break;
            case 4:break;
                
            default: printf("Invalid choice.\n");
        }
    }
    while(choice > 0 && choice <=3);
}
   


int Validate_phn(char *phn,AddressBook *addressBook)
{
    //Check 10 characters present or not
    if(strlen(phn)!=10)
    {
        printf("Phone number should contain 10 digits!!!\n");
        return 0;
    }

    //Check 10 characters are digits
    int i=0;
    while(phn[i])
    {
        if(isdigit(phn[i]))
        i++;
        else
        {
            printf("Phone number should contain only digits!!!\n");
            return 0;
        } 
    }

    //Check the number is unique
    for(int i=0 ; i < (addressBook->contactCount) ; i++)
    {
        if((strcmp(phn,addressBook->contacts[i].phone)) == 0)
        {
            printf("Duplicate phone number exist!!!\n");
            return 0;
        }
    }
    
    //if all validation is passed
    return 1;
}

int Validate_email(char *email,AddressBook *addressBook)
{
    //Check '@' present or not
    if(strchr(email,'@') == 0)
    {
        printf("Invalid email id\n");
        return 0;
    }

    //check .com is present and its present at the end//
    char *index = strstr(email,".com");
    if(index == 0)
    {
        printf("Invalid email id\n");
        return 0;
    }
    else if(strcmp(index,".com"))
    {
        printf("Invalid email id\n");
        return 0;
    }

    //Check for upper case letters
    int i=0;
    while (email[i])
    {
        if(isupper(email[i]))
        {
            printf("email id should not contain uppercase letters!!!\n");
            return 0;
        }
        i++;
    }

    //Verify atleast one character present before and after '@'
    if(email[0]=='@')
    {
        printf("Invalid email id\n");
        return 0;
    }
    if(isalnum(*((strchr(email,'@'))+1)) == 0)
    {
        printf("Invalid email id\n");
        return 0;
    }

    //Check email id is unique
    for(int i=0 ; i < (addressBook->contactCount) ; i++)
    {
        if((strcmp(email,addressBook->contacts[i].email)) == 0)
        {
            printf("Duplicate email id exist!!!\n");
            return 0;
        }
    }
    
    //if all the validations are passed
    return 1;
}
int search_number(char *search_term,AddressBook *addressBook)
{
    int foundindex=-1,index=1,flag=0;
    char phn[20];
                printf("Enter the Phone number: ");
                scanf(" %s",phn);
                printf("--------------------------------------------------------------------------\n");
                printf("Sl.no\tName\t\tPhn_no\t\tEmail_id\n");
                printf("--------------------------------------------------------------------------\n");
                for(int i=0 ; i < (addressBook->contactCount) ; i++)
                {
                    if((strcmp(phn,addressBook->contacts[i].phone)) == 0)
                    {
                        flag=1;
                        printf("%d\t",index++);
                        printf("%s\t",addressBook->contacts[i].name);
                        printf("%s\t",addressBook->contacts[i].phone);
                        printf("%s\n",addressBook->contacts[i].email);
                        printf("--------------------------------------------------------------------------\n");
                        foundindex=i;
                        break;
                    }
                }
                if(flag==1)
                {
                    return foundindex;
                }
                if(flag==0)
                {
                    printf("Not found\n");
                    return 0;
                
                }

}
int search_mail(char *search_term,AddressBook *addressBook)
{
    int foundindex=-1,index=1,flag=0;
    char email[50];
                printf("Enter the email id: ");
                scanf(" %s",email);
                printf("--------------------------------------------------------------------------\n");
                printf("Sl.no\tName\t\tPhn_no\t\tEmail_id\n");
                printf("--------------------------------------------------------------------------\n");
                for(int i=0 ; i < (addressBook->contactCount) ; i++)
                {
                    if((strcmp(email,addressBook->contacts[i].email)) == 0)
                    {
                        flag=1;
                        printf("%d\t",index++);
                        printf("%s\t",addressBook->contacts[i].name);
                        printf("%s\t",addressBook->contacts[i].phone);
                        printf("%s\n",addressBook->contacts[i].email);
                        printf("--------------------------------------------------------------------------\n");
                        foundindex=i;
                        break;
                    }
                }
                if(flag==1)
                {
                    return foundindex;
                }
                if(flag==0)
                {
                    printf("Not found\n");
                    return 0;
                
                }

                
}
int editing_contact(int res,AddressBook *addressBook)
{
    //menu
    int opt;
    char str[5];
    if(res == 0)
    {
        return 0;
    }
    do
    {
        printf("Choose the field you want to edit.\n");
        printf("1. NAME\n2. PHONE NUMBER\n3. EMAIL.ID\n4. EXIT\n");
        printf("Enter your choice : ");
        scanf("%s",str);
        opt = atoi(str);
        switch(opt)
        {
            case 1: char Name[50];
                    printf("Enter the new name : ");
                    scanf(" %[^\n]",Name);
                    strcpy(addressBook->contacts[res].name,Name);
                    printf("\nName update succesfully.\n");
                    break;

            case 2: char phno[20];
                    do
                    {
                        printf("Enter the mobile number: ");
                        scanf("%s",phno);
                    }
                    while (!(Validate_phn(phno,addressBook)));
                    strcpy(addressBook->contacts[res].phone,phno);
                    printf("Phone Number updated succesfully\n");
                    break;
        
            case 3: char email_id[50];
                    do
                    {
                        printf("Enter the e-mail id: ");
                        scanf("%s",email_id);
                    } 
                    while (!(Validate_email(email_id,addressBook)));
                    strcpy(addressBook->contacts[res].email,email_id);
                    printf("Email.Id updated succesfully\n");
                    break;

            case 4: break;

            default:printf("Invaild Input");


        }

    }
    while (opt > 0 && opt <=3);
    
    
}
int search_name(char *search_term ,AddressBook *addressBook,int *index_arr)
{
    int i=0,flag=0,j=0,index=1,contact;
    printf("Enter the Name : ");
    scanf(" %[^\n]",search_term);
    for(i=0 ; i < (addressBook->contactCount) ; i++)
                {
                    if((strcmp(search_term,addressBook->contacts[i].name)) == 0)
                        {
                            flag=1;
                            printf("--------------------------------------------------------------------------\n");
                            printf("Sl.no\tName\t\tPhn_no\t\tEmail_id\n");
                            printf("--------------------------------------------------------------------------\n");
                            printf("%d\t",index++);
                            printf("%s\t",addressBook->contacts[i].name);
                            printf("%s\t",addressBook->contacts[i].phone);
                            printf("%s\n",addressBook->contacts[i].email);
                            printf("--------------------------------------------------------------------------\n");
                            index_arr[j]=i;
                            j++;
                        }
                }
                if(flag==0)
                {
                    printf("Not found\n");
                    return 0;
                }
                printf("Choose the contact : ");
                scanf("%d",&contact);
                return index_arr[contact-1];
}
int delete_contact(int res,AddressBook *addressBook)
{
    int opt;
    char str[5];
    if(res == 0)
    {
        return 0;
    }
    
    printf("Do you want to Delete the contact\n");
    printf("1.YES\n2.NO\n");
    scanf("%s",str);
    opt = atoi(str);
   

    switch(opt)
    {
        case 1: for(int i=res;i < addressBook->contactCount;i++)
                {
                    strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
                    strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
                    strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email);
                }
                 (addressBook->contactCount)--;
                 printf("contact Deleteing succesfully\n"); 
                break;
        case 2: break;
    
        default:printf("Invalid choice");
    }
}


