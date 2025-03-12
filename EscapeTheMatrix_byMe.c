#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 4

unsigned int emptyMap[MAP_SIZE][MAP_SIZE] = {0};

// Directions (Left, Up-Left, Up, Up-Right, Right, Down-Right, Down, Down-Left)
int dx[] = {0, -1, -1, -1, 0, 1, 1, 1};
int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

FILE* openFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error while opening the file\n");
        exit(1);
    }
    return file;
}

unsigned int** getMap(const char* filename, int size) {
    FILE* file = openFile(filename);

    unsigned int** map = (unsigned int**)malloc(size * sizeof(unsigned int*));
    for (int i = 0; i < size; i++) {
        map[i] = (unsigned int*)malloc(size * sizeof(unsigned int));
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fscanf(file, "%u", &map[i][j]);
        }
    }

    fclose(file);
    return map;
}

void getCoordinates(int* x, int* y) {
    printf("Enter the start coordinates (inside the map, not the border): ");
    scanf("%d %d", x, y);

    if (*x < 1 || *y < 1 || *x >= MAP_SIZE - 1 || *y >= MAP_SIZE - 1) {
        printf("Invalid coordinates. Choose a position inside the map!\n");
        exit(1);
    }
}

// **Fixed Movement Condition**
int checkCell(unsigned int** map, int x, int y, int prevX, int prevY) {
    if (x < 0 || y < 0 || x >= MAP_SIZE || y >= MAP_SIZE) {
        return 0; // Out of bounds
    }
    if (x == 0 || y == 0 || x == MAP_SIZE - 1 || y == MAP_SIZE - 1) {
        return 1; // Reached border (successful path)
    }
    if (map[x][y] > map[prevX][prevY]) {
        return 0; // Can't move to a larger value
    }
    return -1; // Valid move
}

void backtrack(unsigned int** map, unsigned int emptyMap[MAP_SIZE][MAP_SIZE], 
               int x, int y, int prevX, int prevY, 
               unsigned int path[MAP_SIZE * MAP_SIZE], int step, int* paths) {
    
    int result = checkCell(map, x, y, prevX, prevY);
    
    if (result == 1) {  // Reached the border, print path
        path[step] = map[x][y]; // Store last step
        *paths += 1;
        printf("Path %d: ", *paths);
        for (int i = 0; i <= step; i++) {
            printf("%u ", path[i]);
        }
        printf("\n");
        return;
    }
    if (result == 0 || emptyMap[x][y] == 1) {
        return; // Invalid move or already visited
    }

    emptyMap[x][y] = 1; // Mark as visited
    path[step] = map[x][y];  // Store value in path before moving

    int validMoves = 0;

    for (int i = 0; i < 8; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (checkCell(map, newX, newY, x, y) == -1 && emptyMap[newX][newY] == 0) {
            validMoves++;
            backtrack(map, emptyMap, newX, newY, x, y, path, step + 1, paths);
        }
    }

    if (validMoves == 0 && step == 0) {
        printf("No valid paths from (%d, %d).\n", x, y);
    }

    emptyMap[x][y] = 0; // Backtrack: unmark cell
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Provide a single file for the program of unsigned integers\n ./file <filename>\n");
        exit(1);
    }

    const char* filename = argv[1];
    unsigned int** map = getMap(filename, MAP_SIZE);

    printf("Loaded Map:\n");
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            printf("%u ", map[i][j]);
        }
        printf("\n");
    }

    int x, y;
    getCoordinates(&x, &y);

    // Reset emptyMap before each run
    memset(emptyMap, 0, sizeof(emptyMap));

    unsigned int path[MAP_SIZE * MAP_SIZE];
    int paths = 0;

    backtrack(map, emptyMap, x, y, x, y, path, 0, &paths);

    if (paths == 0) {
        printf("No valid paths found from (%d, %d).\n", x, y);
    }

    for (int i = 0; i < MAP_SIZE; i++) {
        free(map[i]);
    }
    free(map);

    return 0;
}
