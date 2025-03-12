/*A field is represented as a matrix A with m rows and n columns. The elements A(i, j), which belong to the set of real numbers, represent the elevations 
(heights) of different parts of the land. It is assumed that a ball is on a portion A(a, b) (read from the keyboard).
Specify all the routes that can be followed by the ball so that it leaves the field, knowing that it can move on any adjacent part of the field with a level 
strictly lower than the level of the field on which the ball is located.
Present and argue the choice of algorithm and data structures.

Exemplify the operation of the algorithm for a minimum 3×3 matrix.*/

#include <stdio.h>

#define N 4
#define M 4
#define START_X 1
#define START_Y 1

// Define the 4x4 matrix representing the elevation map
float A[M][N] = {
    {5.2, 4.8, 6.1, 7.0},
    {3.9, 4.5, 5.0, 6.2},
    {2.1, 3.7, 4.6, 5.9},
    {1.0, 2.5, 3.8, 4.2}
};

int check[M][N] = {0}; // matrix to mark the visited cells

// in order to move in all 8 directions, i will start with the left cell neighbor and traverse the neighbors in a clockwise manner
int dx[] = {0, -1, -1, -1, 0, 1, 1, 1};// vecror for the x axis movement
int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};// vector for the y axis movement

// function to check if the cell is valid or not
int isValid(int x, int y, int prevX, int prevY){
    return (x >= 0 && x < M && y >= 0 && y < N && A[x][y] < A[prevX][prevY] && check[x][y] == 0);
}

// function to print the path, i will use the values of the map in order to easy check if is a valid path(strict lower than the previous cell) 

void printPath(float path[], int pathLen, int pathcounter){
    printf("Path %d: ", pathcounter);
    for(int i = 0; i < pathLen; i++){
        printf("%.1f ", path[i]);
    }
    printf("\n");
}

// function to find the path

void backtrackFinding(int x, int y, float path[], int step, int *pathcounter){
    path[step] = A[x][y]; // add the first cell to the path
    check[x][y] = 1; //mark first cell as visited
    
    //we need the basecase in order to stop the recursion(assume that if we reach the frame of the matrix, we stop, because we found a path)
    if(x == 0 || x == M - 1 || y == 0 || y == N - 1){
        (*pathcounter)++;
        printPath(path, step + 1, *pathcounter);
        check[x][y] = 0; // unmark the cell
        return;
    }

    // recursive call to find the path
    for(int i = 0; i < 8; i++){
        int newX = x + dx[i];
        int newY = y + dy[i];

        if(isValid(newX, newY, x, y)){
            backtrackFinding(newX, newY, path, step + 1, pathcounter);
        }
    }
    check[x][y] = 0; // unmark the cell
}

int main(){
    float path[M * N];
    int pathcounter = 0;
    printf("Possible paths from (%d, %d):\n", START_X, START_Y);
    backtrackFinding(START_X, START_Y, path, 0, &pathcounter);
    return 0;
}