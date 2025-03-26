#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _employee {
    char name[32];
    int age;
} Employee;

typedef struct _node {
    void *data;
    struct _node *next;
} Node;

typedef struct _linked_list {
    Node *head;
    Node *tail;
} LinkedList;

void addHead(LinkedList *list, void *data) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->data = data;
    
    if(list->tail == NULL) {
         node->next = NULL;
         list->tail = node;
    } else {
        node->next = list->head;
    }

    list->head = node;
}

void addTail(LinkedList *list, void *data) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;

    if(list->head == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }

    list->tail = node;
}

void initiliseList(LinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
}

void displayList(LinkedList *list) {
    Node *current = list->head;
    while(current != NULL) {
        Employee *data = (Employee *) current->data;
        if(current == list->head) {
            printf("%s, %d\n", data->name, data->age);
        } else {
            printf("-> %s, %d\n", data->name, data->age);
        }
        current = current->next;
    }
}

int main() {
    LinkedList list;

    Employee *emp1 = (Employee*) malloc(sizeof(Employee));
    strcpy(emp1->name, "Ek");
    emp1->age = 1;

    Employee *emp2 = (Employee*) malloc(sizeof(Employee));
    strcpy(emp2->name, "Do");
    emp2->age = 2;

    Employee *emp3 = (Employee*) malloc(sizeof(Employee));
    strcpy(emp3->name, "Teen");
    emp3->age = 3;

    initiliseList(&list);

    addHead(&list, emp2);
    addTail(&list, emp3);
    addHead(&list, emp1);
    
    // Will print
    // Ek, 1
    // -> Do, 2
    // -> Teen, 3
    displayList(&list);

    return 0;
}


