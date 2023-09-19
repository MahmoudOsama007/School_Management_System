/************************************************************************************************************************/
/*********************************************** NTI 4M (R5 G2)**********************************************************/
/************************************* school management software (C Project) *******************************************/
/***************************************** Eng: Mahmoud Osama Mahmoud ***************************************************/
/************************************************ Version : 1 ***********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ErrorState.h"
#include "config.h"
#include "school.h"



typedef unsigned char   u8;
typedef unsigned int   u32;


ErrorState_t List_init(List_t* pl)
{
    if (pl == NULL)
    {
        return NULL_PTR;
    }

    pl->pHead = NULL;
    pl->pTail = NULL;
    pl->ListSize = 0;

    return SUCCESS;
}


ErrorState_t List_insertStudent(List_t* pl, const ListEntry_t* pe)
{
    if (pl == NULL || pe == NULL)
    {
        return NULL_PTR;
    }

    // Create a new node
    ListNode_t* newNode = (ListNode_t*)malloc(sizeof(ListNode_t));
    if (newNode == NULL)
    {
        return OUT_OF_RANGE_ERR;
    }

    // Set the node's entry
    newNode->entry = *pe;

    // Find the correct position to insert the new node
    ListNode_t* current = pl->pHead;
    while (current != NULL && strcmp(current->entry.Name, pe->Name) < 0)
    {
        current = current->pNext;
    }

    // Insert the new node at the correct position
    if (current == NULL)
    {
        // Insert at the end of the list
        if (pl->pTail != NULL)
        {
            pl->pTail->pNext = newNode;
        }
        newNode->pPrev = pl->pTail;
        newNode->pNext = NULL;
        pl->pTail = newNode;
        if (pl->pHead == NULL)
        {
            pl->pHead = newNode;
        }
    }
    else
    {
        // Insert before the current node
        newNode->pNext = current;
        newNode->pPrev = current->pPrev;
        if (current->pPrev != NULL)
        {
            current->pPrev->pNext = newNode;
        }
        else
        {
            pl->pHead = newNode;
        }
        current->pPrev = newNode;
    }

    pl->ListSize++;

    return SUCCESS;
}

ErrorState_t List_searchStudent(const List_t* pl, u8 copy_u8ID, ListNode_t** pFoundStudent)
{
    if (pl == NULL || pFoundStudent == NULL)
    {
        return NULL_PTR;
    }

    ListNode_t* current = pl->pHead;
    while (current != NULL)
    {
        if (current->entry.ID == copy_u8ID)
        {
            *pFoundStudent = current;
            return SUCCESS;
        }
        current = current->pNext;
    }

    *pFoundStudent = NULL;
    return OUT_OF_RANGE_ERR;
}

ErrorState_t List_deleteStudent(List_t* pl, u8 copy_u8ID)
{
    if (pl == NULL)
    {
        return NULL_PTR;
    }

    ListNode_t* current = pl->pHead;
    while (current != NULL)
    {
        if (current->entry.ID == copy_u8ID)
        {
            if (current->pPrev != NULL)
            {
                current->pPrev->pNext = current->pNext;
            }
            else
            {
                pl->pHead = current->pNext;
            }

            if (current->pNext != NULL)
            {
                current->pNext->pPrev = current->pPrev;
            }
            else
            {
                pl->pTail = current->pPrev;
            }

            free(current);
            pl->ListSize--;

            return SUCCESS;
        }
        current = current->pNext;
    }

    return OUT_OF_RANGE_ERR;
}

ErrorState_t List_editStudent(const List_t* pl, u8 copy_u8ID)
{
    if (pl == NULL)
    {
        return NULL_PTR;
    }

    ListNode_t* current = pl->pHead;
    while (current != NULL)
    {
        if (current->entry.ID == copy_u8ID)
        {
            printf("\033[0;33mEnter the new age: ");
            printf("\033[0m");
            scanf("%hhu", &current->entry.age);

            printf("\033[0;33mEnter the new math degree: ");
            printf("\033[0m");
            scanf("%hhu", &current->entry.degress.math_deg);

            printf("\033[0;33mEnter the new English degree: ");
            printf("\033[0m");
            scanf("%hhu", &current->entry.degress.english_deg);

            printf("\033[0;33mEnter the new Arabic degree: ");
            printf("\033[0m");
            scanf("%hhu", &current->entry.degress.arabic_deg);

            printf("\033[0;33mEnter the new phone number: ");
            printf("\033[0m");
            scanf("%u", &current->entry.data.phone);

            printf("\033[0;33mEnter the new address: ");
            printf("\033[0m");
            scanf(" %[^\n]s", current->entry.data.address);

            return SUCCESS;
        }
        current = current->pNext;
    }

    return OUT_OF_RANGE_ERR;
}

ErrorState_t List_updateScore(const List_t* pl, u8 copy_u8ID)
{
    if (pl == NULL)
    {
        return NULL_PTR;
    }

    ListNode_t* current = pl->pHead;
    while (current != NULL)
    {
        if (current->entry.ID == copy_u8ID)
        {
            printf("\033[0;33mEnter the new math degree: ");
            printf("\033[0m");
            scanf("%hhu", &current->entry.degress.math_deg);

            printf("\033[0;33mEnter the new English degree: ");
            printf("\033[0m");
            scanf("%hhu", &current->entry.degress.english_deg);

            printf("\033[0;33mEnter the new Arabic degree: ");
            printf("\033[0m");
            scanf("%hhu", &current->entry.degress.arabic_deg);

            return SUCCESS;
        }
        current = current->pNext;
    }

    return OUT_OF_RANGE_ERR;
}

ErrorState_t List_printList(const List_t* pl)
{
    if (pl == NULL)
    {
        return NULL_PTR;
    }

    ListNode_t* current = pl->pHead;

    // Create an array of students to store the nodes' data
    Student_t* students = (Student_t*)malloc(pl->ListSize * sizeof(Student_t));
    if (students == NULL)
    {
        return OUT_OF_RANGE_ERR;
    }

    // Copy the data from the list nodes to the students array
    int i = 0;
    while (current != NULL)
    {
        students[i] = current->entry;
        current = current->pNext;
        i++;
    }

    // Sort the students array based on names using bubble sort
    for (int j = 0; j < pl->ListSize - 1; j++)
    {
        for (int k = 0; k < pl->ListSize - j - 1; k++)
        {
            if (strcmp(students[k].Name, students[k + 1].Name) > 0)
            {
                Student_t temp = students[k];
                students[k] = students[k + 1];
                students[k + 1] = temp;
            }
        }
    }

    // Print the IDs and names of the students in alphabetical order
    for (int j = 0; j < pl->ListSize; j++)
    {
        printf("\033[0;33mID: %hhu, Name: %s\n", students[j].ID, students[j].Name);
        printf("\033[0m");
    }

    free(students);

    return SUCCESS;
}

ErrorState_t List_listSize(const List_t* pl, u32* pSize)
{
    if (pl == NULL || pSize == NULL)
    {
        return NULL_PTR;
    }

    *pSize = pl->ListSize;

    return SUCCESS;
}

ErrorState_t List_freeList(List_t* pl)
{
    if (pl == NULL)
    {
        return NULL_PTR;
    }

    ListNode_t* current = pl->pHead;

    while (current != NULL)
    {
        ListNode_t* nextNode = current->pNext;
        free(current);
        current = nextNode;
    }

    List_init(pl);

    return SUCCESS;
}


ErrorState_t print_student_list(const List_t* studentList)
{
    if (studentList == NULL)
    {
        return NULL_PTR;
    }

    ListNode_t* current = studentList->pHead;

    while (current != NULL)
    {
        printf("\033[0;33mID: %hhu, Name: %s\n",
               current->entry.ID, current->entry.Name);
        printf("\033[0m");
        current = current->pNext;
    }

    return SUCCESS;
}





//printf(“\033[0;33m”); //set the text to Yellow color
//printf("\033[0m"); // Reset the text to default color


void screen()
{
    printf("\n\n\n\n");
    printf("\033[0;33m\t\t\t\t\tschool management software\n");
    printf("\033[0;33m\t\t\t\t\t******************************\n");
    printf("\033[0;33m\t\t\t\t\t1. Add Student\n");
    printf("\033[0;33m\t\t\t\t\t2. Edit Student\n");
    printf("\033[0;33m\t\t\t\t\t3. Delete Student\n");
    printf("\033[0;33m\t\t\t\t\t4. Update Student Scores\n");
    printf("\033[0;33m\t\t\t\t\t5. Print Student List\n");
    printf("\033[0;33m\t\t\t\t\t6. Exit\n");
    printf("\033[0;33m\t\t\t\t\t******************************\n");
    printf("\033[0;33m\t\t\t\t\tEnter your choice: ");
    printf("\033[0m");
}


void add_student(List_t* studentList)
{
    Student_t newStudent;

    printf("\033[0;33mEnter Student ID: ");
    printf("\033[0m");
    scanf("%hhu", &newStudent.ID);

    // Check for duplicate IDs
    ListNode_t* foundStudent;
    ErrorState_t result = List_searchStudent(studentList, newStudent.ID, &foundStudent);
    if (result == SUCCESS)
    {
        printf("\033[0;33mThis ID already exists. Please enter a different ID.\n");
        Sleep(500);
        printf("\033[0m");
        return;
    }

    printf("\033[0;33mEnter Student Name: ");
    printf("\033[0m");
    scanf(" %[^\n]s", newStudent.Name);

    printf("\033[0;33mEnter Student Age: ");
    printf("\033[0m");
    scanf("%hhu", &newStudent.age);

    printf("\033[0;33m\033[0;33mEnter Student Math Degree: ");
    printf("\033[0m");
    scanf("%hhu", &newStudent.degress.math_deg);

    printf("\033[0;33mEnter Student English Degree: ");
    printf("\033[0m");
    scanf("%hhu", &newStudent.degress.english_deg);

    printf("\033[0;33mEnter Student Arabic Degree: ");
    printf("\033[0m");
    scanf("%hhu", &newStudent.degress.arabic_deg);

    printf("\033[0;33mEnter Student Phone Number: ");
    printf("\033[0m");
    scanf("%u", &newStudent.data.phone);

    printf("\033[0;33mEnter Student Address: ");
    printf("\033[0m");
    scanf(" %[^\n]s", newStudent.data.address);

    result = List_insertStudent(studentList, &newStudent);
    if (result == SUCCESS)
    {
        printf("\033[0;33mStudent added successfully.\n");
        printf("\033[0m");
    }
    else
    {
        printf("Failed to add student.\n");
        printf("\033[0m");
    }
}

void edit_student(List_t* studentList)
{
    int studentID;

    printf("\033[0;33mEnter the ID of the student to edit: ");
    printf("\033[0m");
    scanf("%d", &studentID);

    ListNode_t* foundStudent;
    ErrorState_t result = List_searchStudent(studentList, studentID, &foundStudent);

    if (result == SUCCESS)
    {
        printf("\033[0;33mEnter the new age: ");
        printf("\033[0m");
        scanf("%hhu", &foundStudent->entry.age);

        printf("\033[0;33mEnter the new math degree: ");
        printf("\033[0m");
        scanf("%hhu", &foundStudent->entry.degress.math_deg);

        printf("\033[0;33mEnter the new English degree: ");
        printf("\033[0m");
        scanf("%hhu", &foundStudent->entry.degress.english_deg);

        printf("\033[0;33mEnter the new Arabic degree: ");
        printf("\033[0m");
        scanf("%hhu", &foundStudent->entry.degress.arabic_deg);

        printf("\033[0;33mEnter the new phone number: ");
        printf("\033[0m");
        scanf("%u", &foundStudent->entry.data.phone);

        printf("\033[0;33mEnter the new address: ");
        printf("\033[0m");
        scanf(" %[^\n]s", foundStudent->entry.data.address);

        printf("\033[0;33mStudent edited successfully.\n");
        printf("\033[0m");
    }
    else
    {
        printf("\033[0;33mStudent not found.\n");
        printf("\033[0m");
    }
}

void delete_student(List_t* studentList)
{
    int studentID;

    printf("\033[0;33mEnter the ID of the student to delete: ");
    printf("\033[0m");
    scanf("%d", &studentID);

    ErrorState_t result = List_deleteStudent(studentList, studentID);

    if (result == SUCCESS)
    {
        printf("\033[0;33mStudent deleted successfully.\n");
        printf("\033[0m");
    }
    else
    {
        printf("\033[0;33mStudent not found.\n");
        printf("\033[0m");
    }
}

void update_student_data(List_t* studentList)
{
    int studentID;

    printf("\033[0;33mEnter the ID of the student to update scores: ");
    printf("\033[0m");
    scanf("%d", &studentID);

    ListNode_t* foundStudent;
    ErrorState_t result = List_searchStudent(studentList, studentID, &foundStudent);

    if (result == SUCCESS)
    {
        printf("\033[0;33mEnter the new math degree: ");
        printf("\033[0m");
        scanf("%hhu", &foundStudent->entry.degress.math_deg);

        printf("\033[0;33mEnter the new English degree: ");
        printf("\033[0m");
        scanf("%hhu", &foundStudent->entry.degress.english_deg);

        printf("\033[0;33mEnter the new Arabic degree: ");
        printf("\033[0m");
        scanf("%hhu", &foundStudent->entry.degress.arabic_deg);

        printf("\033[0;33mStudent scores updated successfully.\n");
        printf("\033[0m");
    }
    else
    {
        printf("\033[0;33mStudent not found.\n");
        printf("\033[0m");
    }
}

void delete_list(List_t* studentList)
{
    ErrorState_t result = List_freeList(studentList);
    if (result != SUCCESS)
    {
        printf("\033[0;33mFailed to free student list.\n");
        printf("\033[0m");
    }
    printf("\033[0;33mExiting...\n");
    printf("\033[0m");
}

void start_Screen(void)
{
    //printf("\033[0;33m");
    char s[]= {"Loading..."};
    printf("\t");


    for(int i =0; i<3; i++)
    {
        printf("\t\t\t\t\n\n\n\n\n\n\n\n\n ");

        for(int i =0; s[i]; i++)
        {
            printf("\t%2c",s[i]);
            Sleep(50);
        }
        Sleep(500);
        system("cls");
    }

    printf(" \n\n\n\n\n");
    char s1[]= {"Welcome"};
    printf("\t");
    for(int i =0; i<1; i++)
    {
        printf("\n");

        for(int i =0; s1[i]; i++)
        {
            if(i==0)
            {
                printf("\t\t\t\t\t\t");
            }
            printf("\033[0;33m%c",s1[i]);
            printf("\033[0m");
            Sleep(50);
        }
        Sleep(1000);
        printf("\n\n\n");
    }

    char s3[]="  To school management software ";
    printf("\t");
    for(int i =0; i<1; i++)
    {

        printf("\n");

        for(int i =0; s3[i]; i++)
        {
            if(i==0)
            {
                printf("\t\t\t\t\t");
            }
            printf("\033[0;33m%c",s3[i]);
            Sleep(50);
        }
        Sleep(1000);
        printf("\n\n\n\n");
    }
    char s4[]="Engoy ^_^";
    printf("\t");
    for(int i =0; i<1; i++)
    {

        printf("\n");

        for(int i =0; s4[i]; i++)
        {
            if(i==0)
            {
                printf("\t\t\t\t\t\t");
            }
            printf("\033[0;33m%c",s4[i]);
            printf("\033[0m");
            Sleep(50);
        }
        Sleep(1000);
        printf("\n\n\n\n\n");

    }
    char s5[]=" Designed By Eng: Mahmoud Osama ";
    printf("\n");
    for(int i =0; i<1; i++)
    {
        printf("\t\t\t\t");

        for(int i =0; s5[i]; i++)
        {
            if(i==0)
            {
                printf("\t\t\t\t\t\t");
            }
            printf("\033[0;33m%c",s5[i]);
            printf("\033[0m");
            Sleep(50);
        }
        Sleep(1000);
        printf("\n\n\n\n\n");
        system("cls");
    }
    printf("\033[0m");
}

void end_screen()
{
    Sleep(500);
    printf("\t\t\t\t\n\n\n\n\n\n\n\n\n ");
    char s5[]="Thank You,See you Soon ^_^";

    for(int i =0; i<1; i++)
    {
        printf("\t\t\t\t");

        for(int i =0; s5[i]; i++)
        {
            if(i==0)
            {
                printf("\t\t\t\t\t\t");
            }
            printf("\033[0;33m%c",s5[i]);
            printf("\033[0m");
            Sleep(50);
        }
        Sleep(1000);
        printf("\n\n\n\n\n");
        system("cls");
    }
    printf("\033[0m");

    Sleep(100);
    exit(1);

}

