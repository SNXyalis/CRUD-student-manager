#include "student.h"

/*WARNING!
DO NOT FORGET TO GIVE 
THE FILENAME THROUGH THE 
COMMANDLINE WHEN EXECUTING
THE PROGRAM*/

int main(int argc, char* argv[]) {

    char filename[MAXSTRING];
    strcpy(filename, argv[1]);
    strcat(filename, ".dat");
    list l = load(filename);

    int flag = 1;
    char choice = 0;

    while (flag) {
        printMenu();
        do {
            choice = getchar();
        }while(choice < '1' || choice > '7');
        switch (choice) {
            student temp;
            student* tempPtr;
            node tempNode;
            int n;

            case '1':
                do {
                    n = 1000+ rand() % 99999;
                }while( doesIdExist(n, l) == 1);
                temp.id = n; 
                printf("\n***Your new ID is %d***\n", temp.id);
                puts("You may use the update option to change it.\n");
                puts("Enter student\'s name");
                fscanf(stdin, "%s", temp.name);
                if ( addStudent(temp, l) == 1) {
                    printf("\n***Student added successfully***\n");
                }
                break;
            case '2':
                puts("Enter students id");
                //ID Check
                if(scanf("%d", &temp.id) != 1) {
                    puts("\n**Wrong input. ID should be a number.**\n");
                    break;
                }
                if( doesIdExist(temp.id, l) == 0) {
                    puts("\n**Error, ID doesn't exist.**\n");
                    break;
                }
                tempPtr = findStudent(temp.id , l);
                tempNode = find_node(tempPtr, l);
                if ( deleteStudent(tempNode->data, l) == 1) {
                    printf("\n***Student deleted successfully***\n");
                }
                break;
            case '3':
                puts("Enter the ID of the student you wish to update.");
                //ID Check
                if(scanf("%d", &temp.id) != 1) {
                    puts("\n**Wrong input. ID should be a number.**\n");
                    break;
                }
                if( doesIdExist(temp.id, l) == 0) {
                    puts("\n**Error, ID doesn't exist.**\n");
                    break;
                }
                tempPtr = findStudent(temp.id , l);
                tempNode = find_node(tempPtr, l);
                if ( updateStudent(tempNode->data, l) == 1 ) {
                    printf("\n***Student's info updated successfully***\n");
                }
                break;

            case '4':
                puts("Enter the ID of the student you wish to print.");
                //ID Check
                if(scanf("%d", &temp.id) != 1) {
                    puts("\n**Wrong input. ID should be a number.**\n");
                    break;
                }
                if( doesIdExist(temp.id, l) == 0) {
                    puts("\n**Error, ID doesn't exist.**\n");
                    break;
                }
                tempPtr = findStudent(temp.id , l);
                tempNode = find_node(tempPtr, l);
                print(tempNode->data);
                break;
            case '5':
                printstudents(l);
                break;
            case '6':
                flag = 0;
                break;
        }
    }
    
    save(filename, l);
    
    return 0;
}