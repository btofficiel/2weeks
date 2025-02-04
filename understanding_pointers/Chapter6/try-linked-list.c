#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void safeFree(void **pp) {
    if(pp != NULL && *pp != NULL) {
        free(*pp);
        *pp = NULL;
    }
}

#define FREE(p) safeFree((void**)&(p))

typedef struct _node {
  void* data;
  struct _node* next;
} Node;

typedef struct LinkedList {
  Node* head;
  Node* tail;
  int length;
} LinkedList;

typedef int (*COMPARE)(void*, void*);
typedef void (*DISPLAY)(void*);

void intializeList(LinkedList* list) {
  list->head = NULL;
  list->tail = NULL;
  list->length = 0;
}

void addHead(LinkedList* list, void* data) {
  Node* node = (Node*)malloc(sizeof(Node));
  node->data = data;
  if (list->head == NULL) {
    list->tail = node;
    node->next = NULL;
  } else {
    node->next = list->head;
  }
  list->head = node;
  list->length++;
}

void addTail(LinkedList* list, void* data) {
  Node* node = (Node*)malloc(sizeof(Node));
  node->data = data;
  node->next = NULL;
  if (list->head == NULL) {
    list->head = node;
  } else {
    list->tail->next = node;
  }
  list->tail = node;
  list->length++;
}


Node* getNode(LinkedList* list, COMPARE compare, void* data) {
  Node* node = list->head;
  while (node != NULL) {
    if (compare(node->data, data) == 0) {
      return node;
    }
    node = node->next;
  }
  return NULL;
}

void delete(LinkedList* list, Node* node) {
  if (node == list->head) {
    if (list->head->next == NULL) {
      list->head = list->tail = NULL;
    } else {
      list->head = list->head->next;
    }
  } else {
    Node* current = list->head;
    while (current != NULL && current->next != node) {
      current = current->next;
    }
    if (current != NULL) {
      current->next = node->next;
      if (current->next == NULL) {
        list->tail = current;
      }
    }
  }
  FREE(node);
  list->length--;
}

void displayList(LinkedList* list, DISPLAY display) {
  Node* current = list->head;
  while (current != NULL) {
    display(current->data);
    current = current->next;
  }
}

typedef struct _employee {
  char* name;
  unsigned int age;
  unsigned int salary;
} Employee;

void initializeEmployee(Employee* employee, char* name, unsigned char age, unsigned int salary) {
  employee->name = (char*)malloc(strlen(name) + 1);
  strcpy(employee->name, name);
  employee->age = age;
  employee->salary = salary;
}

void deallocateEmployee(void* data) {
  Employee* employee = (Employee*)data;
  FREE(employee->name);
  FREE(employee);
}

void displayEmployee(void* data) {
  Employee* employee = (Employee*)data;
  printf("Name: %s, Age: %d, Salary: %u\n", employee->name, employee->age, employee->salary);
}

int compareEmployeeByName(void* data1, void* data2) {
  return strcasecmp(((Employee*)data1)->name, ((Employee*)data2)->name);
}

Employee* inputEmployee() {
  Employee* employee = (Employee*)malloc(sizeof(Employee));
  char *name = (char*)malloc(32 * sizeof(char));
  unsigned int age;
  unsigned int salary;
  printf("Enter employee name: ");
  scanf("%s", name);
  printf("Enter employee age: ");
  scanf("%d", &age);
  printf("Enter employee salary: ");
  scanf("%u", &salary);
  initializeEmployee(employee, name, age, salary);
  return employee;
}

int main() {
  LinkedList list;
  intializeList(&list);

  while (1) {
    char choice;
    printf("Enter 'a' to add an employee\n'd' to display the list\n'f' to find an employee by name\n'q' to quit: ");
    scanf(" %c", &choice);
    switch (choice) {
      case 'a': {
        Employee* employee = inputEmployee();
        addTail(&list, employee);
        printf("Employee added!\n\n");
        break;
      }
      case 'd':
        printf("Employee list: (total %d)\n\n", list.length);
        displayList(&list, displayEmployee);
        printf("End of employee list\n\n");
        break;
      case 'f': {
        char name[32];
        printf("Enter employee name to find: ");
        scanf("%s", name);
        Employee employee;
        initializeEmployee(&employee, name, 0, 0);
        Node* node = getNode(&list, compareEmployeeByName, &employee);
        if (node != NULL) {
          displayEmployee(node->data);
        } else {
          printf("Employee not found!\n");
        }
        break;
      }
      case 'q':
        return 0;
    }
  }

  return 0;
}
