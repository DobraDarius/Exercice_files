/*Write, in C, the necessary data structures and algorithms which do the following:

Create a dynamically allocated linked list of nodes with 32-bit unsigned integers as data payload based on whitespace-separated values from a file. 
The name of the file, which contains the full relevant path, will be the only command line argument for your compiled program. 
The size of this file is not considered known.
Sort this list so when traversed from the beginning to end it will generate an ordered sequence of those 32-bit unsigned integers, 
without touching the same node more than once.
Traverse this list only one time and print the values of each node to the standard output. Values will be separated by one space. 
The last value will also have one space after it. This will output an ordered sequence for those values.

Constraints:
Any form of array is off-limits.
Unnecessary code will result in points deductions.
No unnecessary memory allocations. After the file is read and the list generated, no more memory allocations should happen.
Memory leaks will trigger massive points deduction.
Make sure to free the memory before exit.
Code should be neatly divided into relevant functions.
Code should be legible. If you think the grader will need more than a few minutes to understand what you did, 
please explain what that section of code does using comments.
There is a maximum of 20 seconds execution time when testing. If the code takes longer then it is considered that it does not work at all.*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// struct for node that contains the needed data
typedef struct node{
    unsigned int data;
    struct node* next;
}node;

// function for creating a new node for the data readed from the file
node* createNode(unsigned int data){
    node* newNode = (node*)malloc(sizeof(node));// we allocate memory for the new node, only when we need a new node

    if(newNode == NULL){
        printf("memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

// function for adding a node to the list

void addNode(node** head, unsigned int data){
    node* temp = *head;

    if(*head == NULL){
        *head = createNode(data);
        return;
    }

    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = createNode(data);
}

//function for sorting the list. In order to not use any extra memory, i use merge sort
//in order to perform merge sort on a list, we need to split the list. I will use the slow-fast pointer technique to split the list

void splitList(node* head, node** front, node** back){
    node* slow = head; // move to the next 1 node at a time
    node* fast = head->next; // move to the next 2 nodes at a time

    //check while moving fast if it's reaching null or the next is null
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }

    *front = head; // list from the begining untill the middle
    *back = slow->next; // list from the middle untill the last
    slow->next = NULL;
}

// function for sort merge the lists

node* sortMerge(node* n1, node* n2){
    // case when one of the lists in empty
    if(n1 == NULL){
        return n2;
    }
    if(n2 == NULL){
        return n1;
    }

    node* result = NULL;

    //in this if-else condition, we sort and merge the lists togheter
    if(n1->data <= n2->data){
        result = n1;
        result->next = sortMerge(n1->next, n2);
    }else{
        result = n2;
        result->next = sortMerge(n1, n2->next);
    }

    return result;
}

// now we implement the function for mergesort

void MergeSort(node** headRef){
    if(*headRef == NULL || (*headRef)->next == NULL){
        return; //basecase, if list is empty or only one element
    }

    node* head = *headRef;
    node* n1;
    node* n2;

    splitList(head, &n1, &n2);

    //sort both halves
    MergeSort(&n1);
    MergeSort(&n2);

    *headRef = sortMerge(n1, n2);
}

void ReadDataFromFile(node** head, const char* filename){
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("Error while opening the file in reading mode!\n");
        exit(1);
    }

    unsigned int value;
    while(fscanf(file, "%u", &value) == 1){
        addNode(head, value);
    }

    fclose(file);
}

// function in order to free the memory allocated for the list

void erase(node* head){
    node* temp;
    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}

void printList(node* head){
    node* temp = head;
    while(temp != NULL){
        printf("%u ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}


int main(int argc, char** argv){
    if(argc != 2){
        printf("argument for filepath is missing!\n");
        return 1;
    }
    node* head = NULL;
    const char* filepath = argv[1]; 
    ReadDataFromFile(&head, filepath);

    MergeSort(&head);

    printList(head);

    erase(head);

    //printList(head);

    return 0;

}

