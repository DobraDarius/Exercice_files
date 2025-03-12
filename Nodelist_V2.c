/*Create a dynamically allocated linked list of nodes containing 32-bit unsigned integers as their payload.

The numbers will be whitespace-separated values from a file.
The filename (with the full path) will be the only command-line argument.
The file size is not known in advance.
Sort the linked list so that when traversed from beginning to end, it outputs an ordered sequence of the numbers.

Sorting should be done after building the list (not while inserting the nodes).
Each node must be touched only once after sorting.
Print the sorted list:

Traverse the list only once and print each value, separated by a single space.
The last value should also have a space after it.

CONSTRAINTS:

Arrays are not allowed.
Unnecessary code will result in point deductions.
No extra memory allocations should be made after reading the file.
Memory leaks will lead to massive point deductions.
All allocated memory must be freed before exiting.
Code should be divided into functions neatly.
Code must be readable and well-commented.
Execution must not exceed 20 seconds, or it will be considered incorrect

FOR GRADE 10:

Nodes must be inserted in the order they appear in the file.
Node data (payload) must not be modified after insertion.
Sorting should happen only after the list is fully built.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

//creating the struct for the node
typedef struct node{
    unsigned int value;
    struct node* next;
}Node;

//creating the function to allocate memory and add the node to the list as we read the values 
//from the file
void addNode(Node** head, unsigned int value){

    Node* temp = (Node*)malloc(sizeof(Node));
    if(!temp){
        printf("Memory allocation error in addNode\n");
        return;
    }

    temp->value = value;
    temp->next = NULL;

    if(*head == NULL){
        *head = temp;
    }else{
        Node* current = *head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = temp;
    }
}

//function for opening the file
FILE* openFile(const char* filename){
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("Error while opening the file!");
        exit(1);
    }
    return file;
}

//function for printng the list
void printList(Node* head){
    Node* current = head;
    while(current != NULL){
        printf("%u ", current->value);
        current = current->next;
    }
    printf("\n");
}

//create a function in order to make the list as we get the values from the file

void makeList(const char* filename, Node** head){
    FILE* file = openFile(filename);
    unsigned int value;

    while(fscanf(file, "%u", &value) == 1){
        addNode(head, value);
    }

    fclose(file);
}

//now i start implementing the sorting algorithm. I will use merge sort 
//as it is the most efficient one for linked lists

//function in order to split the list into two halves

void splitList(Node* head, Node** left, Node** right){
    Node* slow;//slow travel pointer(+1)
    Node* fast;//fast travel pointer(+2)

    //study the case when we got no elements or only one element
    if(head == NULL || head->next == NULL){
        *left = head;
        *right = NULL;
        return;
    }

    slow = head;
    fast = head->next;

    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast  = fast->next->next;
    }

    *left = head;
    *right = slow->next;
    slow->next = NULL;
}

//function to merge the two lists in a sorted manner
Node* mergeSortedLists(Node* left, Node* right){
    Node* result = NULL;

    if(left == NULL){
        return right;
    }else if(right == NULL){
        return left;
    }

    if(left->value <= right->value){
        result = left;
        result->next = mergeSortedLists(left->next, right);
    }else{
        result = right;
        result->next = mergeSortedLists(left, right->next);
    }

    return result;
}

// function to sort the list

void mergeSort(Node** head){
    if(*head == NULL || (*head)->next == NULL){
        return;
    }

    Node* left;
    Node* right;

    splitList(*head, &left, &right);
    mergeSort(&left);
    mergeSort(&right);

    *head = mergeSortedLists(left, right);
}

//function to free the memory allocated for the list

void freeList(Node* head){
    Node* temp;
    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Not enough arguments");
        return 1;
    }
    const char* filename = argv[1];

    Node* head = NULL;

    makeList(filename, &head);

    printf("Unsorted list:\n");
    printList(head);

    printf("Sorted list:\n");
    mergeSort(&head);
    printList(head);

    freeList(head);

    return 0;
}