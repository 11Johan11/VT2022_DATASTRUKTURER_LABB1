//Author Johan Sollenius

#define _CRT_SECURE_NO_WARNINGS
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

//A node in the linked list
typedef struct Phonerecord
{
    char *phoneNumber; //Pointer to a phonenumber malloced on the heap
    char *name; //Pointer to a name malloced on the heap
    Phonerecord *next; //Pointer to the next node in the linked list
}Phonerecord;

Phonerecord* head = NULL; //The first node in the linked list

//This function prints out all the phone records in the linked lists, Displaying phone number & name
void printRecords();
//This function receives a phone number & name input from the console and creates a new node
//A pointer to the newly created node is returned
Phonerecord* createRecord();
//This function finds the record that matches a phonenumber
//returns the previous node (Helper function for delete record)
Phonerecord* searchRecord(char* num, int* flag);
//Add a Phonerecord to the linked list in the beginning
//Returns -1 if not found else 0 if found
int insertRecord(Phonerecord* record);
//Delete a Phonerecord from the linked list based on phonenumber
//Returns -1 if not found else 0 if found
int deleteRecord(char* num);
//Find a Phonerecord either from phonenumber or name, option=0(name), option=1(number)
//Returns a pointer to the found record else null
Phonerecord* query(char* query, int option);
//This function displays the main menu
void displayMainMenu();

int main()
{
    char queryStr[30];
    int choice;
    Phonerecord* record;
    displayMainMenu();
    while (1)
    {
        printf("?:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            //Display records
            printRecords();
            break;
        case 2:
            //Create a record & Insert
            if (insertRecord(createRecord()) == -1) puts("Phone record already exists");
            else puts("Phone record added succesfully");
            break;
        case 3:
            //Delete a record
            printf("\nEnter phone number to delete: ");
            scanf("%s", queryStr);
            if (deleteRecord(queryStr) == 0) puts("Record was deleted succesfully");
            else puts("Phone number not found");
            break;
        case 4:
            //Who's phone number is this?
            printf("\nEnter phone number: ");
            scanf("%s", queryStr);
            record = query(queryStr, 1);
            if (record != NULL) printf("Person tied to this phone number: %s\n", record->name);
            else puts("Phone number not found");
            break;
        case 5:
            //Does this person have a phone number?
            printf("\nEnter name: ");
            scanf("%s", queryStr);
            record = query(queryStr, 0);
            if (record != NULL) printf("Phone number tied to this person: %s\n", record->phoneNumber);
            else puts("Person not found");
            break;
        case 6:
            //Display main menu?
            displayMainMenu();
            break;
        case -1:
            exit(0);
            break;
        }
    }

    return 0;
}

void displayMainMenu()
{
    puts("1. Display records");
    puts("2. Add a record");
    puts("3. Delete a record (By phone number)");
    puts("4. Who's phone number is this?");
    puts("5. Find a persons phone number");
    puts("6. Display main menu");
    puts("-1. Exit");
}

void printRecords()
{
    Phonerecord* record = head;
    puts("-PHONEBOOK-RECORDS-");
    for (int c = 0; record != NULL; c++)
    {
        puts("---------------------");
        printf("%d.\n", c);
        printf("Phone number: %s\n", record->phoneNumber);
        printf("Name: %s\n", record->name);
        puts("---------------------");
        record = record->next;
    }
}

Phonerecord* createRecord()
{
    
    char *name = (char*)malloc((sizeof(char) * 30));
    if (name == NULL) exit(0);

    printf("Name?: ");
    scanf("%s", name);

    char* num = (char*)malloc((sizeof(char) * 30));
    if (num == NULL) exit(0);

    printf("Phone number?: ");
    scanf("%s", num);

    Phonerecord* record = (Phonerecord*)malloc(sizeof(Phonerecord));
    record->name = name;
    record->phoneNumber = num;
    return record;
}

int insertRecord(Phonerecord* record)
{

    Phonerecord* tmp = head;
    while (tmp != NULL)
    {
        if (record == tmp) return -1;
        tmp = tmp->next;
    }

    record->next = head;
    head = record;
    return 0;
}

int deleteRecord(char* num)
{

    int found;
    Phonerecord* prev = searchRecord(num, &found);

    if (!found) return -1;

    if (prev == NULL) 
    {
        Phonerecord* tmp = head;
        head = head->next; //Change head to the next record after the one that is gonna get deleted
        free(tmp);
    }
    else
    {
        Phonerecord* tmp = prev->next;
        prev->next = prev->next->next; //The previous should point to the next record after the one that is gonna get deleted
        free(tmp);
    }

    return 0;
}

Phonerecord* searchRecord(char* num, int* flag)
{
    Phonerecord* record = head;
    Phonerecord* prev = NULL;

    while (record != NULL)
    {
        if (strcmp(record->phoneNumber,num) == 0)
        {
            *flag = 1;
            return prev;
        }
        prev = record;
        record = record->next;
    }

    *flag = 0;
    return prev;
}

Phonerecord* query(char* query, int option)
{
    Phonerecord* record = head;
    while (record != NULL)
    {
        if (option == 1) if (strcmp(record->phoneNumber,query) == 0) return record;
        if (option == 0) if (strcmp(record->name,query) == 0) return record;
        record = record->next;
    }
    
    return record; //null
}
