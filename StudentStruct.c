#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stddef.h>

#define MAX 10

typedef struct{
    char name[35];
    int year;
    int award; // 1 if is, 0 if not
} Student;

//function to merge the two halves, for Mergesort
void merge(Student* students, int left, int right, int mid){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    //malloc memory for the temporary arrays
    Student* L = (Student*)malloc(n1 * sizeof(Student));
    Student* R = (Student*)malloc(n2* sizeof(Student));

    if(L == NULL || R == NULL){
        printf("Error while allocating memory");
        exit(1);
    }

    for(int i = 0; i < n1; i++){
        L[i] = students[left+i];
    }

    for(int i = 0; i < n2; i++){
        R[i] = students[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;

    while(i < n1 && j < n2){
        if(L[i].award >= R[j].award){
            students[k++] = L[i++];
        }else{
            students[k++] = R[j++];
        }
    }

    while(i < n1){
        students[k++] = L[i++];
    }

    while(j < n2){
        students[k++] = R[j++];
    }

    free(L);
    free(R);
}

void MergeSort(Student* students, int left, int right){
    int mid = 0;
    if(left < right){
        mid = left + (right - left) / 2;
    

    MergeSort(students, left, mid);
    MergeSort(students, mid + 1, right);

    merge(students, left, right, mid);
    }
}

//in order to determine where we start the sorting
int findFirstWhitoutAward(Student* students, int n){
    for(int i = 0; i < n; i++){
        if(students[i].award == 0){
            return i;
        }
    }
    return -1;
}

// function for quicksort functionality
int partition(Student* students, int low, int high){
    Student pivot = students[high];
    int i = low - 1;

    for(int j = low; j < high; j++){
        if(strcmp(students[j].name, pivot.name) > 0){
            i++;
            //swap the students
            Student temp = students[i];
            students[i] = students[j];
            students[j] = temp;
        }
    }

    Student temp = students[i + 1];
    students[i + 1] = students[high];
    students[high] = temp;

    return i + 1;
}

void quicksort(Student* students, int low, int high){
    if(low < high){
        int p = partition(students, low, high);

        quicksort(students, low, p - 1);
        quicksort(students, p + 1, high);
    }
}

void printStudents(Student* students, int n){
    for(int i = 0; i < n; i++){
        printf("Name: %s, Year: %d, Award: %d\n", students[i].name, students[i].year, students[i].award);
    }
}

int main(){
    Student students[MAX] = {
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
    printStudents(students, MAX);

    //sort the students by award
    MergeSort(students, 0, MAX - 1);

    //find the first student without award
    int firstWithoutAward = findFirstWhitoutAward(students, MAX);

    //use quicksort to sort the students without award
    if(firstWithoutAward != -1){
        quicksort(students, firstWithoutAward, MAX - 1);
    }

    printf("After sorting:\n");
    printStudents(students, MAX);

    return 0;
}