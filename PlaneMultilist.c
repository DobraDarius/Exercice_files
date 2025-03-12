#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stddef.h>

#define FLIGHTMAX 10
#define FLIGHTS 4
#define PASSAGERMAXCODE 8
#define PASSAGERMAX 4

//i am gonna use simply linked list in order to make
//the multilist
typedef struct Passager{
    int numericCode[PASSAGERMAXCODE];
    struct Passager* nextPassager;
} Passager;

typedef struct Flight{
    char flightNumber[FLIGHTMAX];
    Passager* passagerList;
    struct Flight* nextFlight;
} Flight;

void addPassager(Passager** head, int numericCode[PASSAGERMAXCODE]){
    Passager* newPassager = (Passager*)malloc(sizeof(Passager));
    if(newPassager == NULL){
        printf("Error while allocating memory");
        exit(1);
    }

    for(int i = 0; i < PASSAGERMAXCODE; i++){
        newPassager->numericCode[i] = numericCode[i];
    }

    newPassager->nextPassager = *head;
    *head = newPassager;
}

void printPassagers(Passager* head){
    Passager* current = head;
    while(current != NULL){
        printf("Passager code: ");
        for(int i = 0; i < PASSAGERMAXCODE; i++){
            printf("%d ", current->numericCode[i]);
        }
        printf("\n");
        current = current->nextPassager;
    }
}

void printFlights(Flight* head){
    Flight* current = head;
    while(current != NULL){
        printf("Flight number: %s\n", current->flightNumber);
        printPassagers(current->passagerList);
        current = current->nextFlight;
    }
}

void removePassager(Passager** head, int numericCode[PASSAGERMAXCODE]){
    Passager* current = *head;
    Passager* prev = NULL;

    while(current != NULL){
        int match = 1;
        for(int i = 0; i < PASSAGERMAXCODE; i++){
            if(current->numericCode[i] != numericCode[i]){
                match = 0;
                break;
            }
        }

        if(match){
            if(prev == NULL){
                *head = current->nextPassager;
            }else{
                prev->nextPassager = current->nextPassager;
            }
            free(current);
            printf("Passager removed\n");
            return;
        }

        prev = current;
        current = current->nextPassager;
    }
    printf("Passager not found\n");
}

Flight* createFlight(char* flightNumber){
    Flight* newFlight = (Flight*)malloc(sizeof(Flight));
    if(newFlight == NULL){
        printf("Error while allocating memory for a flight\n");
        exit(1);
    }

    strncpy(newFlight->flightNumber, flightNumber, FLIGHTMAX);
    newFlight->passagerList = NULL;
    newFlight->nextFlight = NULL;
    return newFlight;
}

int main(){
    Flight* head = createFlight("F1");
    Flight* current = head;
    for(int i = 0; i < PASSAGERMAX; i++){
        int numericCode[PASSAGERMAXCODE] = {1, i+1, 0, 0, 0, 0, 0, 0};
        addPassager(&current->passagerList, numericCode);
    }
    //create all the flights, with all the passagers
    for(int i = 2; i <= FLIGHTS; i++){
        char flightNumber[FLIGHTMAX];
        sprintf(flightNumber, "F%d", i);
        Flight* newFlight = createFlight(flightNumber);
        current->nextFlight = newFlight;
        current = newFlight;
        for(int j = 0; j < PASSAGERMAX; j++){
            int numericCode[PASSAGERMAXCODE] = {i, j+1, 0, 0, 0, 0, 0, 0};
            addPassager(&current->passagerList, numericCode);
        }
    }

    //print flights with passagers
    printFlights(head);

    //remove a passager
    int numericCode[PASSAGERMAXCODE] = {1, 2, 0, 0, 0, 0, 0, 0};
    removePassager(&head->passagerList, numericCode);

    printFlights(head);

    //for adding a passager is O(1) because we add linearly through the list
    //for removing a passager is O(n) because we have to search for the passager
}
