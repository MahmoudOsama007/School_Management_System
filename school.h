#ifndef _SCHOOL_H_
#define _SCHOOL_H_
#include <stdio.h>

#include "ErrorState.h"
#include "config.h"
#include "school.h"

typedef unsigned char   u8;
typedef unsigned int   u32;


typedef struct {
	u8  math_deg;
	u8  english_deg;
	u8  arabic_deg;
}Subject_t;
typedef struct{
	u32  phone;
	u8   address[ADRESSSIZE];
}Personal_t;
typedef struct myStudent{
	u8 ID;
	u8 Name[NAMESIZE];
	u8 age;
	Personal_t  data;
	Subject_t   degress;
}Student_t;
typedef Student_t ListEntry_t;

typedef struct Node{
	struct Node *pNext;
    struct Node *pPrev;
    ListEntry_t   entry;
}ListNode_t;

typedef struct myList{
	ListNode_t * pHead;
	ListNode_t * pTail;
	int ListSize;
}List_t;

ErrorState_t  List_init(List_t* pl); // init head = tail = NULL
ErrorState_t  List_insertStudent( List_t* pl ,const ListEntry_t * pe);
ErrorState_t  List_searchStudent(const List_t* pl , u8 copy_u8ID,ListNode_t ** pFoundStudent );
ErrorState_t  List_deleteStudent(List_t* pl , u8 copy_u8ID);
ErrorState_t  List_editStudent(const List_t* pl , u8 copy_u8ID);
ErrorState_t  List_updateScore(const List_t* pl , u8 copy_u8ID);
ErrorState_t  List_printList(const List_t* pl );
ErrorState_t  List_listSize(const List_t* pl ,u32 * pSize);
ErrorState_t  List_freeList(List_t* pl);

void add_student(List_t *studentList);
void screen();
void add_student(List_t *studentList);
void delete_student(List_t *studentList);
void update_student_data(List_t *studentList);
void delete_list(List_t *studentList);
ErrorState_t print_student_list(const List_t* studentList) ;
void start_Screen(void);
void end_screen();
#endif
