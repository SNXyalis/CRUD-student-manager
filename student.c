#include "student.h"

//List Functions
list create_list() {
    list l = (list) malloc(sizeof(struct _list));
    assert(l);
    l->head = NULL;
    l->size = 0;
    return l;
}

node create_node(student data) {
    node n = (node) malloc(sizeof(struct _node));
    assert(n);
    n->data = data;
    n->next = NULL;
    return n;
}

void free_node(node n) {
    assert(n);
    free(n);
}

node list_first(list l) {
    assert(l);
    return l->head;
}

node list_next(node n) {
    assert(n);
    return n->next;
}

student list_data(node n) {
    assert(n);
    return n->data;
}

int list_empty(list l) {
    assert(l);
    return l->head == NULL;
}

int list_size(list l) {
    assert(l);
    return l->size;
}

void list_insertfirst(list l, node n) {
    assert(l && n);
    n->next = l->head;
    l->head = n;
    l->size++;
}

node list_deletefirst(list l) {
    assert(l&& l->head);
    node ret = l->head;
    l->head = ret->next;
    l->size--;
    ret->next = NULL;
    return ret;
}

node list_deletenode(list l, node n) {
    assert(l && n);
    node prev;
    for(prev = list_first(l); prev!= NULL; prev = list_next(prev)) {

        if(prev->next == n) {
            prev->next = n->next;
            n->next = NULL;
            return n;
        }
    }
}

node find_node(student* data,list l) {
    node n;
    student temp = *data;
    for(n = list_first(l); n!= NULL; n = list_next(n)) {
        if(temp.id == n->data.id) {
            return n;
        }
    }
}

void list_destroy(list l) {
    assert(l);
    while(!list_empty(l))
        free_node(list_deletefirst(l));

    free(l);
}

//Error Check Functions
int doesIdExist(int num, list l) {
    node n;
    for(n = list_first(l); n!= NULL; n = list_next(n)) {
        if(num == n->data.id) {
            return 1;
        }
    }
    return 0;
}

//Other Functions
void printMenu() {
    puts("\nChoose between 1 and 7\n");
    puts("1. Add a student");
    puts("2. Delete a student");
    puts("3. Update student's info");
    puts("4. Print a student info");
    puts("5. Print info of all the students");
    puts("6. Quit\n");
}

student* findStudent(int id, list l) {
    node n;
    student* studentPtr = NULL;
    student temp;

    for(n = list_first(l); n!= NULL; n = list_next(n)) {
        temp = list_data(n);

        if (temp.id == id) {
            studentPtr = &temp;
            return studentPtr;
            //return n;
        }
    }
}

int addStudent(student st, list l) {
    list_insertfirst(l, create_node(st));
    if ( list_first(l)->data.id != 0) {
        return 1;
    }
    return 0;
}

int deleteStudent(student st, list l) {
    node n;
    student temp;

    for(n = list_first(l); n!= NULL; n = list_next(n)) {

        temp = list_data(n);
        if (st.id == temp.id) {

            if (n == list_first(l)) {
                free_node( list_deletefirst(l) );
                return 1;

            }else {
                free_node( list_deletenode(l, n) );
                return 1;
            }
        }
    }
    return 0;
}

void print(student st) {
    printf("%d\t%s\n", st.id, st.name);
}

void printstudents(list l) {
    node n;
    student temp;

    for(n = list_first(l); n!= NULL; n = list_next(n)) {
        temp = list_data(n);
        printf("%d\t%s\n", temp.id, temp.name);
    }
}

void save(char *filename, list l) {
    assert(filename && l);

    //Create a file to store the list
    FILE *filePtr;
    filePtr = fopen(filename, "wb");
    assert(filePtr);

    //Write data to file
    node n;
    for(n = list_first(l); n!= NULL; n = list_next(n)) {
        fwrite(&n->data, sizeof(student), 1, filePtr);
    }

    //Clear data
    fclose(filePtr);
    list_destroy(l);

    printf("\n***File saved successfully***\n");
}

list load(char *filename) {
    assert(filename);

    list l = create_list();
    //Read and update a file
    //or procceed to return the list
    FILE *filePtr;
    filePtr = fopen(filename, "rb+");
    if (filePtr == NULL) {
        return l;
    }

    //Finds the size of the File
    fseek(filePtr, 0, SEEK_END);
    long fileSize = ftell(filePtr);
    rewind(filePtr);

    //Calculate the nodes
    int totalNodes = (int) (fileSize / sizeof(student));
    node n;

    for (size_t i = 0; i < totalNodes; i++)
    {
        //Create nodes
        node n = (node) malloc(sizeof(struct _node));
        assert(n);

        //Passes data to node and Insert it to list
        fread(&n->data, sizeof(student),1, filePtr);
        n->next = NULL;
        list_insertfirst(l , n);

    }
    
    fclose(filePtr);

    return l;
}

int updateStudent(student st, list l) {
    node n;
    student temp;

    int flag = 1;
    char choice;
    student newData;

    //Identify which node contains the student
    for(n = list_first(l); n!= NULL; n = list_next(n)) {

        temp = list_data(n);
        if (st.id == temp.id) {
            
            //Update Options
            while(flag) {
                printStudUpdateMenu();
                do {
                    choice = getchar();
                }while(choice < '1' || choice > '4');
                switch (choice)
                {
                    case '1':
                        puts("Enter new ID:");
                        //ID Check
                        if(scanf("%d", &newData.id) != 1 || newData.id < 0) {
                            puts("\n**Wrong input. ID should be a number higher than zero.**\n");
                            break;
                        }
                        //Checks if the ID is the same
                        if (newData.id == n->data.id) {
                            puts("\n**Invalid Input, student has already that ID.**\n");
                            break;
                        }
                        if( doesIdExist(newData.id, l) == 1) {
                            puts("\n**Error, another student uses this ID.**\n");
                            puts("\nPlease check the list to make sure that the ID is available.\n");
                            break;
                        }
                        n->data.id = newData.id;
                        break;
                    case '2':
                        puts("Enter new Name:");
                        fscanf(stdin, "%s", newData.name);
                        strcpy(n->data.name, newData.name);
                        break;
                    case '3':
                        puts("Enter new ID:");
                        //ID Check
                        if(scanf("%d", &newData.id) != 1 || newData.id < 0) {
                            puts("\n**Wrong input. ID should be positive number.**\n");
                            break;
                        }
                        //Checks if the ID is the same
                        if (newData.id == n->data.id) {
                            puts("\n**Invalid Input, student has already that ID.**\n");
                            break;
                        }
                        if( doesIdExist(newData.id, l) == 1) {
                            puts("\n**Error, another student uses this ID.**\n");
                            puts("\nPlease check the list to make sure that the ID is available.\n");
                            break;
                        }
                        n->data.id = newData.id;

                        puts("Enter new Name:");
                        fscanf(stdin, "%s", newData.name);
                        strcpy(n->data.name, newData.name);
                        break;
                    case '4':
                        flag = 0;
                        break;
                }
            }   

            return 1;
        }
    }
    return 0;

}


void printStudUpdateMenu() {
    puts("\nChoose 1 or 2");
    puts("1. Change ID");
    puts("2. Change Name");
    puts("3. Change Both");
    puts("4. Back");
}
