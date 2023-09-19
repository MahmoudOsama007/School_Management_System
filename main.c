/************************************************************************************************************************/
/*********************************************** NTI 4M (R5 G2)**********************************************************/
/************************************* school management software (C Project) *******************************************/
/***************************************** Eng: Mahmoud Osama Mahmoud ***************************************************/
/************************************************ Version : 1 ***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include "config.h"
#include "ErrorState.h"
#include "school.h"









int main()
{
    start_Screen();
    int numLists;
    printf("\n\n\n\n\t\t\t\t");
    printf("\033[0;33mHow many lists would you like to create? ");
    scanf("%d", &numLists);

    // Allocate an array of List_t structures
    List_t* listArray = (List_t*)malloc(numLists * sizeof(List_t));
    if (listArray == NULL)
    {
        printf("\033[0;33mFailed to allocate memory for list array.\n");
        return 1;
    }

    // Initialise each list in the array
    for (int i = 0; i < numLists; i++)
    {
        List_init(&listArray[i]);
    }

    int option;
    int listIndex;
    int studentID;

    while (1)
    {
        system("cls");// Clear display before printing
        screen();
        printf("\n");
        printf("\033[0;33m*********************\n");
        printf("\033[0m");
        printf("\n");

        printf("\033[0;33mYou can Exit if you insert(-1)\nSelect a list to work with (0-%d): ", numLists - 1);
        printf("\033[0m");
        scanf("%d", &listIndex);
        if(listIndex==-1)
        {
            end_screen();
            Sleep(500);
        }
        printf("\033[0;33mSelect a choice " );
        printf("\033[0m");

        if (listIndex < 0 || listIndex >= numLists)
        {
            printf("\033[0;33mInvalid list selection. Please try again.\n");
            printf("\033[0m");
            continue;
        }


        scanf("%d", &option);
        switch (option)
        {
        case 1:
            system("cls");// Clear display before printing
            screen();
            printf("\n\n");
            printf("\033[0;33m********Add_Student***********\n");
            printf("\n\n");
            printf("\033[0m");
            add_student(&listArray[listIndex]);
            printf("\033[0;33m\nEnter Any Key to continue\n\n");
            printf("\033[0m");
            getch();
            break;

        case 2:
            system("cls");// Clear display before printing
            screen();
            printf("\n\n");
            printf("\033[0;33m*******Edit_Student*********\n");
            printf("\n\n");
            printf("\033[0m");
            print_student_list(&listArray[listIndex]);
            edit_student(&listArray[listIndex]);
            printf("\033[0;33m\nEnter Any Key to continue\n\n");
            printf("\033[0m");
            getch();
            break;

        case 3:
            system("cls");// Clear display before printing
            screen();
            printf("\n\n");
            printf("\033[0;33m*******Delete_Student************\n");
            printf("\n\n");
            printf("\033[0m");
            print_student_list(&listArray[listIndex]);
            delete_student(&listArray[listIndex]);
            printf("\033[0;33m\nEnter Any Key to continue\n\n");
            printf("\033[0m");
            getch();
            break;

        case 4:
            system("cls");// Clear display before printing
            screen();
            printf("\n\n");
            printf("\033[0;33m********Update_Student_Data***********\n");
            printf("\n\n");
            printf("\033[0m");
            print_student_list(&listArray[listIndex]);
            update_student_data(&listArray[listIndex]);
            printf("\033[0;33m\nEnter Any Key to continue\n\n");
            printf("\033[0m");
            getch();
            break;

        case 5:
            system("cls");// Clear display before printing
            screen();
            printf("\n\n");
            printf("\033[0;33m********Print_Student_List***********\n");
            printf("\n\n");
            printf("\033[0m");
            print_student_list(&listArray[listIndex]);
            printf("\033[0;33m\nEnter Any Key to continue\n\n");
            printf("\033[0m");
            getch();
            break;

        case 6:
            delete_list(&listArray[listIndex]);
            end_screen();
            break;



        default:
            printf("\033[0;33mInvalid option. Please try again.\n");
            printf("\033[0m");
            break;
        }
        Sleep(500);
    }
}













