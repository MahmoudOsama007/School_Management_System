# School_Management_System


Project School:
1. The Data structure used is Doubly Linked List , each Node has 2 pointers to next and previous .
2. The DB is sorted all the time by alphabetical order, and when inserting a New Student, it gets inserted in the right place according to its alphabetical order; this place may be in the middle /head or tail of the linked list.
3. You need to use the provided template in your project, it defines the basic structures used, you may add more structures but do not remove from template.
4. You should implement your own string library for the following
   functionalities:
1- string length
2- string copy.
3- String compare.
4- atoi .
feel free to add more functions of your own .
6. Your program should support having many different lists at the same time.
Example :
KG1 list and KG2 list .
7. You Need to implement the
following functions :
 List_create :
this function should initialize head
and tail and any other data in linked
list object .
 List_insertStudent:
this function should receive student
data as input argument and should
create a new student Node in the
linked list .
 List_searchStudent:
this function should receive the
student ID and a pointer to the List ,
should return pointer to the found
Student , if Not found it should
return NULL (Note the returned
value is in the form of pointer
passed as input argument ).
 List_deleteStudent:
this function should receive the
student ID , search for it and then
delete it .
 List_editStudent
edit the info of a student except his
name and his ID
 List_updateScore
update all scores of a certain
student in all of the subjects.
 List_printList
prints student Ids, Names, in
alphabetical order.
 List_listSize
returns the total amount of students
currently in the list
 List_freeList
delete all students in the list
