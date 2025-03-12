dfc#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

//create the struct for the node in order to make a simply linked list

typedef struct node{
    unsigned int value;
    struct node* next;
}Node;

//we dont know the size of the list, so we make a function that manually alocate the memory for the list

Node* createNode(unsigned int value){
    Node* temp = (Node*)malloc(sizeof(Node));

    temp->value = value;
    temp->next = NULL;

    return temp;
}

//in order to create the propper list, we need a function that add nodes to the list

void addNodeToList(Node** head, unsigned int value){
    //first we check that we have a empty list
    if(*head == NULL){
        *head = createNode(value);
        return;
    }

    //in order to form the list in the order of the given values, we will put the nodes from head to tail
    Node* temp = createNode(value);
    Node* current = *head;

    while(current->next != NULL){
        current = current->next;
    }

    current->next = temp;
}

//in order to create the list, we know the given values are from a file, so we need a function that reads the values from the file,
//and use the addNodeToList function to create the list

void CreateList(const char* filename, Node** head){
    FILE* file = fopen(filename, "r");

    //check if the process of opening the file was succesfull

    if(file == NULL){
        printf("error while opening the file");
        exit(1);
    }

    //we know the format of the data provided by the file, so we will read the values from the file and add them to the list

    unsigned int value;//like the datatype from the file

    while(fscanf(file, "%u", &value) == 1){
        addNodeToList(head, value);
    }
}

// we finished the functions for creating the list, now we need a function that will print the list

void printList(Node* head){
    Node* current = head;

    while(current != NULL){
        printf("%u ", current->value);
        current = current->next;
    }
    printf("\n");
}

//we also need a function that will free the memory after we done with the list

void freeList(Node* head){
    Node* current = head;
    Node* next = NULL;

    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
}

//we finished the functions that manipulates the list, now we need the function for sorting the content of the list
//i will choose merge sort, because it's a efficient algorithm to sort lists, and don't use external memory(like arrays)

// i need a function to split the list in two parts, in order to sort them

void SplitList(Node* head, Node** left, Node** right){
    Node* slow = head;//will travel slow through the list
    Node* fast = head->next;//will travel fast through the list

    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }

    *left = head;
    *right = slow->next;
    slow->next = NULL;
}

//now, we have 2 sublists from the big list, we need a function that will merge the list in a sorted manner

Node* mergeList(Node* left, Node* right){
    if(left == NULL){
        return right;
    }
    if(right == NULL){
        return left;
    }

    Node* result = NULL;
    //if one of the sublists is emtpty, we proceed with the other one

    if(left->value <= right->value){
        result = left;
        result->next = mergeList(left->next, right);
    }else{
        result = right;
        result->next = mergeList(left, right->next);
    }

    return result;
}

//now we need the merge sort function

void mergeSort(Node** head){
    Node* temp = *head;
    if(temp == NULL || temp->next == NULL){
        return;
    }

    Node* left = NULL;
    Node* right = NULL;

    SplitList(temp, &left, &right);

    mergeSort(&left);
    mergeSort(&right);

    *head = mergeList(left, right);
}

//we have the sorting function, now just implement the main function

int main(int argc, char* argv[]){
    //check if the user provided a file
    if(argc != 2){
        printf("provide a single file for the program of unsigned intigers \n ./file <filename>");
        exit(1);
    }

    const char* filename = argv[1];

    Node* head = NULL;

    CreateList(filename, &head);
    printf("Unsorted list: ");
    printList(head);

    printf("\n\n");
    printf("Sorted list: ");
    mergeSort(&head);
    printList(head);

    freeList(head);

    printList(head);

    return 0;
}