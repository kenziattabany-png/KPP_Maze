#include <iostream>
using namespace std;


const int ROWS = 7;
const int COLS = 7;
const int MAX_STEPS = 100;

char maze[ROWS][COLS] = {
    {'#', '#', '#', '#', '#', '#', '#'},
    {'#', 'S', '#', '.', '.', '.', '#'},
    {'#', '.', '#', '.', '#', 'G', '#'},
    {'#', '.', '.', '.', '#', '.', '#'},
    {'#', '#', '#', '.', '.', '.', '#'},
    {'#', 'X', '.', '.', 'F', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#'}
};

bool visited[ROWS][COLS][2] = {};

char path[MAX_STEPS];
int pathlength = 0;

void printMaze()
{

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            cout << maze[row][col] << ' ';
        }

        cout << endl;
    }
}

bool solveMaze(int row, int col, bool hasF){
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS || maze[row][col] == '#' || maze[row][col] == 'X' || visited[row][col][hasF])
    {
        return false;
    }

    if (maze[row][col] == 'F')
    {
        hasF = true;
    }

    int state = hasF ? 1 : 0;
    if (visited[row][col][state])
    {
        return false;
    }
    visited[row][col][state] = true;

    if (maze[row][col] == 'G')
    {
        if (hasF)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    if (solveMaze(row - 1, col, hasF)){
        path[pathlength] = 'U';
        pathlength++;
        return true;
    }

    if (solveMaze(row + 1, col, hasF)){
        path[pathlength] = 'D';
        pathlength++;
        return true;
    }

    if (solveMaze(row, col - 1, hasF)){
        path[pathlength] = 'L';
        pathlength++;
        return true;
    }

    if (solveMaze(row, col + 1, hasF)){
        path[pathlength] = 'R';
        pathlength++;
        return true;
    }

    return false;
}

void markPath (int startRow, int startCol){

    int row = startRow;
    int col = startCol;

    for (int i = pathlength -1; i >= 0; i--){
        int nextRow = row;
        int nextCol = col;

        if (path[i] == 'U'){
            nextRow--;
        }
        else if (path[i] == 'D'){
            nextRow++;
        }
        else if (path[i] == 'L'){
            nextCol--;
        }
        else if (path[i] == 'R'){
            nextCol++;
        }

        if (maze[nextRow][nextCol] == '.'){
            maze[nextRow][nextCol] = 'R';
        }

        row = nextRow;
        col = nextCol;
    }
}

void printPath(){

    cout << "\nPath:\n";

    for (int i=pathlength - 1; i >= 0; i--){
        cout << path[i] << ' ';
    }
    cout << endl;
}

int main(){

    cout << "Maze: " << endl;

    int startRow = -1;
    int startCol = -1;

    for (int row = 0; row < ROWS; row++){
        for (int col = 0; col < COLS; col++){
            if (maze[row][col] == 'S'){
                startRow = row;
                startCol = col;
            }
        }
    }

    printMaze();

    bool solved = solveMaze(startRow, startCol, false);

    if (solved){
        cout << "\nMaze Solved!\n";
        printPath();
        markPath(startRow, startCol);
        cout << "\nSolution:\n";
        printMaze();
        cout << "\nTotal Steps: " << pathlength << endl;
    }

    else {   
        cout << "\nNo solution found.\n";
    }
    return 0;
}