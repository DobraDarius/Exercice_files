#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stddef.h>

#define MAX_X 5
#define MAX_Y 5

char UncollouredMap[MAX_X][MAX_Y] = {
    {'-', '-', '-', '-', '-'}, 
    {'-', '-', '-', '-', '-'}, 
    {'-', '-', '-', '-', '-'}, 
    {'-', '-', '-', '-', '-'}, 
    {'-', '-', '-', '-', '-'}
};

char Collours[2][2] = {{'R','G'},{'B','Y'}};//possible collours

//we dont have specific constraints for this task, so
//i will implement a simple algorithm to solve the collouring problem

void CollourTheMap(char Map[MAX_X][MAX_Y], char Collours[2][2]){
    //I will start from the top left corner and move in a square pattern of 2x2, like the collours map
    for(int i = 0; i < MAX_X; i+=2){
        for(int j = 0; j < MAX_Y; j+=2){
            //case when we have space for the 2x2 square
            if(i + 1 < MAX_X && j + 1 < MAX_Y){
                Map[i][j] = Collours[0][0];
                Map[i][j+1] = Collours[0][1];
                Map[i+1][j] = Collours[1][0];
                Map[i+1][j+1] = Collours[1][1];
            }
            //handel edges when we don't have space
            else if(i + 1 < MAX_X && j + 1 >= MAX_Y){
                Map[i][j] = Collours[0][0];
                Map[i+1][j] = Collours[1][0];
            }
            else if(i + 1 >= MAX_X && j + 1 < MAX_Y){
                Map[i][j] = Collours[0][0];
                Map[i][j+1] = Collours[0][1];
            }
            // handle if is one cell left
            else{
                Map[i][j] = Collours[0][0];
            }
        }
    }
}
// for this function we have O((n*m)/4)
//because we increment i and j by 2, so we will have n/2 * m/2 iterations
void PrintMap(char Map[MAX_X][MAX_Y]){
    for(int i = 0; i < MAX_X; i++){
        for(int j = 0; j < MAX_Y; j++){
            printf("%c ", Map[i][j]);
        }
        printf("\n");
    }   
}

int main(){

    PrintMap(UncollouredMap);
    printf("\n");
    CollourTheMap(UncollouredMap, Collours);
    PrintMap(UncollouredMap);
    return 0;
}