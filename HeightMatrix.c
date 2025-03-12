#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MATRIXSIZE1 4
#define MATRIXSIZE2 4
#define STARTX 2
#define STARTY 2

// Directions: up, down, left, right
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// Function for printing the matrix
void printHeightMatrix(int matrix[MATRIXSIZE1][MATRIXSIZE2]) {
    for (int i = 0; i < MATRIXSIZE1; i++) {
        for (int j = 0; j < MATRIXSIZE2; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Recursive function to find all paths
void findPaths(int x, int y, int matrix[MATRIXSIZE1][MATRIXSIZE2], int visited[MATRIXSIZE1][MATRIXSIZE2], int path[], int step, int* pathCount) {
    // Base Case: If the ball reaches the frame of the matrix, print the path
    if (x == 0 || x == MATRIXSIZE1 - 1 || y == 0 || y == MATRIXSIZE2 - 1) { 
        path[step] = matrix[x][y];  // Add the current position to the path
        (*pathCount)++;  // Increment the escape path counter
        printf("Escape path %d: ", *pathCount);
        for (int i = 0; i <= step; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
        return;
    }

    // Mark the current cell as visited and store it in the path
    visited[x][y] = 1;
    path[step] = matrix[x][y];

    // Try all possible moves
    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        // Check if the neighbor is valid and move if the next cell is strictly higher
        if (newX >= 0 && newX < MATRIXSIZE1 && newY >= 0 && newY < MATRIXSIZE2 &&
            matrix[newX][newY] > matrix[x][y] && visited[newX][newY] == 0) {
            findPaths(newX, newY, matrix, visited, path, step + 1, pathCount);
        }
    }

    // Backtrack: Unmark the current cell as visited
    visited[x][y] = 0;
}

int main() {
    // The matrix that represents the height of the terrain
    int heightMatrix[MATRIXSIZE1][MATRIXSIZE2] = {
        {7, 5, 8, 9},
        {1, 4, 5, 6},
        {9, 7, 3, 2},
        {1, 8, 1, 4}
    };

    printf("Height Matrix:\n");
    printHeightMatrix(heightMatrix);

    // Starting position
    printf("\nStarting position is (%d, %d)\n\n", STARTX, STARTY);

    // Visited matrix to track visited cells
    int visited[MATRIXSIZE1][MATRIXSIZE2] = {0};

    // Path to store the current escape path
    int path[MATRIXSIZE1 * MATRIXSIZE2];

    // Counter to count the total number of escape paths
    int pathCount = 0;

    // Start finding paths
    printf("Finding Escape Paths:\n");
    findPaths(STARTX, STARTY, heightMatrix, visited, path, 0, &pathCount);

    // Print the total number of escape paths
    printf("\nTotal number of escape paths: %d\n", pathCount);

    return 0;
}
