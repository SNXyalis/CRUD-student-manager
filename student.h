#ifndef STUDENT_H
#define STUDENT_H
//Included Libraries
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//Preprocessor Variables
#define MAXSTRING 50

//Structs
typedef struct {
    char name[MAXSTRING];
    int id;
} student;

//List Structs
typedef struct _node* node;

struct _node {
    student data;
    node next;
};

typedef struct _list* list;

struct _list {
    node head;
    int size;
};

//Functions
void printMenu(); //Shows Menu
void print(student st); //Shows a Student
void printstudents(list l); //Shows an array of Students
list load(char *filename); //Loads the list of students from a file
void save(char *filename, list l); //Saves a list of students to a file
int addStudent(student st, list l); //Adds a student
student* findStudent(int id, list l); //Finds a student based ID
int deleteStudent(student st, list l); //Deletes a student based on ID
int updateStudent(student st, list l); //Updates a students info based on ID

//List Functions
list create_list();
node create_node(student data);
void free_node(node n);
node list_first(list l);
node list_next(node n);
student list_data(node n);
int list_empty(list l);
int list_size(list l);
void list_insertfirst(list l, node n);
node list_deletefirst(list l);
node list_deletenode(list l, node prev);
node find_node(student* data,list l);
void list_destroy(list l);

//Error Check Functions
int doesIdExist(int num, list l);


//Extra Functions to improve readability
void printStudUpdateMenu();
#endif // STUDENT_H_INCLUDED