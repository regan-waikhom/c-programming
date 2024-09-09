#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Student structure
typedef struct Student {
    int rollNumber;
    char name[50];
    float marks;
    struct Student* next;
} Student;

// Define the Node for Binary Search Tree
typedef struct BSTNode {
    int rollNumber;
    Student* student;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// Function prototypes
void addStudent(Student** head, int rollNumber, char* name, float marks);
void deleteStudent(Student** head, int rollNumber);
void updateStudent(Student* head, int rollNumber, char* name, float marks);
void displayStudents(Student* head);
Student* searchStudentByRollNumber(Student* head, int rollNumber);
void sortStudentsByMarks(Student* head);
void sortStudentsByName(Student* head);
void bstInsert(BSTNode** root, Student* student);
Student* bstSearch(BSTNode* root, int rollNumber);
void inorderTraversal(BSTNode* root);

// Helper function to create a new Student node
Student* createStudent(int rollNumber, char* name, float marks) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    newStudent->rollNumber = rollNumber;
    strcpy(newStudent->name, name);
    newStudent->marks = marks;
    newStudent->next = NULL;
    return newStudent;
}

// Helper function to create a new BST Node
BSTNode* createBSTNode(Student* student) {
    BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
    newNode->rollNumber = student->rollNumber;
    newNode->student = student;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to add a new student to the linked list and BST
void addStudent(Student** head, int rollNumber, char* name, float marks) {
    // Create a new student node
    Student* newStudent = createStudent(rollNumber, name, marks);
    newStudent->next = *head;
    *head = newStudent;
}

// Function to delete a student by roll number from the linked list
void deleteStudent(Student** head, int rollNumber) {
    Student* temp = *head, *prev;
    if (temp != NULL && temp->rollNumber == rollNumber) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->rollNumber != rollNumber) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    prev->next = temp->next;
    free(temp);
}

// Function to update a student's information in the linked list
void updateStudent(Student* head, int rollNumber, char* name, float marks) {
    Student* student = searchStudentByRollNumber(head, rollNumber);
    if (student != NULL) {
        strcpy(student->name, name);
        student->marks = marks;
    } else {
        printf("Student with roll number %d not found.\n", rollNumber);
    }
}

// Function to display all student records
void displayStudents(Student* head) {
    Student* temp = head;
    while (temp != NULL) {
        printf("Roll Number: %d, Name: %s, Marks: %.2f\n", temp->rollNumber, temp->name, temp->marks);
        temp = temp->next;
    }
}

// Function to search for a student by roll number in the linked list
Student* searchStudentByRollNumber(Student* head, int rollNumber) {
    Student* temp = head;
    while (temp != NULL) {
        if (temp->rollNumber == rollNumber)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// Helper function to swap two students (used in sorting)
void swapStudents(Student* a, Student* b) {
    int tempRollNumber = a->rollNumber;
    float tempMarks = a->marks;
    char tempName[50];
    strcpy(tempName, a->name);
    
    a->rollNumber = b->rollNumber;
    a->marks = b->marks;
    strcpy(a->name, b->name);
    
    b->rollNumber = tempRollNumber;
    b->marks = tempMarks;
    strcpy(b->name, tempName);
}

// Function to sort students by marks using Bubble Sort
void sortStudentsByMarks(Student* head) {
    int swapped;
    Student* ptr1;
    Student* lptr = NULL;

    if (head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->marks > ptr1->next->marks) {
                swapStudents(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Function to sort students by name using Bubble Sort
void sortStudentsByName(Student* head) {
    int swapped;
    Student* ptr1;
    Student* lptr = NULL;

    if (head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->name, ptr1->next->name) > 0) {
                swapStudents(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Function to insert a student into the BST based on roll number
void bstInsert(BSTNode** root, Student* student) {
    if (*root == NULL) {
        *root = createBSTNode(student);
        return;
    }

    if (student->rollNumber < (*root)->rollNumber)
        bstInsert(&((*root)->left), student);
    else
        bstInsert(&((*root)->right), student);
}

// Function to search for a student in BST by roll number
Student* bstSearch(BSTNode* root, int rollNumber) {
    if (root == NULL || root->rollNumber == rollNumber)
        return (root != NULL) ? root->student : NULL;

    if (rollNumber < root->rollNumber)
        return bstSearch(root->left, rollNumber);

    return bstSearch(root->right, rollNumber);
}

// Function for in-order traversal of BST
void inorderTraversal(BSTNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Roll Number: %d, Name: %s, Marks: %.2f\n", root->student->rollNumber, root->student->name, root->student->marks);
        inorderTraversal(root->right);
    }
}

// Main function
int main() {
    Student* head = NULL;
    BSTNode* bstRoot = NULL;

    int choice, rollNumber;
    char name[50];
    float marks;
    Student* student;

    do {
        printf("\n--- Student Record Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Delete Student\n");
        printf("3. Update Student\n");
        printf("4. Display Students\n");
        printf("5. Search Student by Roll Number (Linked List)\n");
        printf("6. Sort Students by Marks\n");
        printf("7. Sort Students by Name\n");
        printf("8. Search Student by Roll Number (BST)\n");
        printf("9. Display Students in BST (In-order)\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Roll Number: ");
                scanf("%d", &rollNumber);
                printf("Enter Name: ");
                scanf("%s", name);
                printf("Enter Marks: ");
                scanf("%f", &marks);
                addStudent(&head, rollNumber, name, marks);
                bstInsert(&bstRoot, searchStudentByRollNumber(head, rollNumber));
                break;

            case 2:
                printf("Enter Roll Number to Delete: ");
                scanf("%d", &rollNumber);
                deleteStudent(&head, rollNumber);
                break;

            case 3:
                printf("Enter Roll Number to Update: ");
                scanf("%d", &rollNumber);
                printf("Enter New Name: ");
                scanf("%s", name);
                printf("Enter New Marks: ");
                scanf("%f", &marks);
                updateStudent(head, rollNumber, name, marks);
                break;

            case 4:
                displayStudents(head);
                break;

            case 5:
                printf("Enter Roll Number to Search: ");
                scanf("%d", &rollNumber);
                student = searchStudentByRollNumber(head, rollNumber);
                if (student != NULL)
                    printf("Found: Roll Number: %d, Name: %s, Marks: %.2f\n", student->rollNumber, student->name, student->marks);
                else
                    printf("Student not found.\n");
                break;

            case 6:
                sortStudentsByMarks(head);
                printf("Students sorted by marks.\n");
                displayStudents(head);
                break;

            case 7:
                sortStudentsByName(head);
                printf("Students sorted by name.\n");
                displayStudents(head);
                break;

            case 8:
                printf("Enter Roll Number to Search in BST: ");
                scanf("%d", &rollNumber);
                student = bstSearch(bstRoot, rollNumber);
                if (student != NULL)
                    printf("Found in BST: Roll Number: %d, Name: %s, Marks: %.2f\n", student->rollNumber, student->name, student->marks);
                else
                    printf("Student not found in BST.\n");
                break;

            case 9:
                printf("In-order Traversal of BST:\n");
                inorderTraversal(bstRoot);
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
