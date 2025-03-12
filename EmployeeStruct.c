#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    char name[35];
    int year;
    int bonus; // 1 if is, 0 if not
} Employee;

// Merge function to combine two sorted halves
void merge(Employee* employees, int left, int mid, int right) {
    int n1 = mid - left + 1; // Size of the left subarray
    int n2 = right - mid;    // Size of the right subarray

    // Dynamically allocate memory for temporary arrays
    Employee* L = (Employee*)malloc(n1 * sizeof(Employee));
    Employee* R = (Employee*)malloc(n2 * sizeof(Employee));

    // Check if memory allocation was successful
    if (L == NULL || R == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // Fill the temporary arrays
    for (int i = 0; i < n1; i++) {
        L[i] = employees[left + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = employees[mid + 1 + i];
    }

    // Merge the temporary arrays back into employees[]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].bonus >= R[j].bonus) {
            employees[k++] = L[i++];
        } else {
            employees[k++] = R[j++];
        }
    }

    // Copy any remaining elements from L[]
    while (i < n1) {
        employees[k++] = L[i++];
    }

    // Copy any remaining elements from R[]
    while (j < n2) {
        employees[k++] = R[j++];
    }

    // Free the dynamically allocated memory
    free(L);
    free(R);
}

// Merge sort function
void MergeSort(Employee* employees, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort the first and second halves
        MergeSort(employees, left, mid);
        MergeSort(employees, mid + 1, right);

        // Merge the sorted halves
        merge(employees, left, mid, right);
    }
}

int findFirstWhitoutBonus(Employee* employees, int n){
    for (int i = 0; i < n; i++) {
        if(employees[i].bonus == 0){
            return i;
        }
    }
    return -1;
}

//function for partition in order to perform QuickSort
int partition(Employee* employees, int low, int high){
    Employee pivot = employees[high];
    int i = low - 1;

    for(int j = low; j < high; j++){
        //compare the names of the employees
        if(strcmp(employees[j].name, pivot.name) > 0){
            i++;
            //swap the employees
            Employee temp = employees[i];
            employees[i] = employees[j];
            employees[j] = temp;
        }
    }

    //place the pivot in the correct position
    Employee temp = employees[i + 1];
    employees[i + 1] = employees[high];
    employees[high] = temp;

    return i + 1;
}

void quicksort(Employee* employees, int low, int high){
    if(low < high){
        //find the partition
        int pi = partition(employees, low, high);

        //recursively sort the elements before and after the partition
        quicksort(employees, low, pi - 1);
        quicksort(employees, pi + 1, high);
    }
}

// Function to print the employees
void printEmployees(Employee* employees, int n) {
    for (int i = 0; i < n; i++) {
        printf("Name: %s, Year: %d, Bonus: %d\n", employees[i].name, employees[i].year, employees[i].bonus);
    }
}

int main() {
    // Initialize the employees array
    Employee employees[MAX] = {
        {"Alice", 2015, 1},
        {"Bob", 2018, 0},
        {"Charlie", 2017, 1},
        {"Diana", 2020, 0},
        {"Eve", 2016, 1},
        {"Frank", 2019, 0},
        {"Grace", 2021, 1},
        {"Hank", 2022, 0},
        {"Ivy", 2014, 1},
        {"Jack", 2013, 0}
    };

    printf("Before sorting:\n");
    printEmployees(employees, MAX);

    // Sort the employees by bonus
    MergeSort(employees, 0, MAX - 1);

    int firstWhitoutBonus = findFirstWhitoutBonus(employees, MAX);
    if(firstWhitoutBonus != -1){
        quicksort(employees, firstWhitoutBonus, MAX - 1);
    }

    printf("\nAfter sorting:\n");
    printEmployees(employees, MAX);

    return 0;
}
