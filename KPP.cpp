#include <iostream>
#include <cstring>
using namespace std;

const int rows = 7;
const int cols = 7;
const int MAX = 100;


char Grid[rows][cols] = {
    {'#', '#', '#', '#', '#', '#', '#'},
    {'#', 'S', '#', '.', '.', '.', '#'},
    {'#', '.', '#', '.', '#', 'G', '#'},
    {'#', '.', '.', '.', '#', '.', '#'},
    {'#', '#', '#', '.', '.', '.', '#'},
    {'#', 'X', '.', '.', 'F', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#'}
};

bool visited[rows][cols] = {};
char path[MAX];
int pathLength = 0;


void Viz(){
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++){
            cout << Grid[row][col] << ' ';
        }
        cout << endl;
    }
}

bool solveMaze(int row, int col, int targetRow, int targetCol, bool hasFlag){
    if (row < 0 || row >= rows || col < 0 || col >= cols){
        return false;
    }

    if (Grid[row][col] == '#' || Grid[row][col] == 'X'){
        return false;
    }

    // Cannot enter G before getting the flag
    if (Grid[row][col] == 'G' && !hasFlag){
        return false;
    }

    if (visited[row][col]){
        return false;
    }

    visited[row][col] = true;

    if (row == targetRow && col == targetCol){
        return true;
    }

    if (solveMaze(row - 1, col, targetRow, targetCol, hasFlag)){
        path[pathLength] = 'U';
        pathLength++;
        return true;
    }

    if (solveMaze(row + 1, col, targetRow, targetCol, hasFlag)){
        path[pathLength] = 'D';
        pathLength++;
        return true;
    }

    if (solveMaze(row, col - 1, targetRow, targetCol, hasFlag)){
        path[pathLength] = 'L';
        pathLength++;
        return true;
    }

    if (solveMaze(row, col + 1, targetRow, targetCol, hasFlag)){
        path[pathLength] = 'R';
        pathLength++;
        return true;
    }

    return false;
}


void printPath(){
    for (int pathIndex = pathLength - 1;pathIndex >= 0;pathIndex--){
        cout << path[pathIndex] << ' ';
    }
    cout << endl;
}


void resetSearch(){
    memset(visited,false,sizeof(visited));
    pathLength = 0;
}


void markPath(int startRow,int startCol){
    int currentRow = startRow;
    int currentCol = startCol;

    for (int pathIndex = pathLength - 1;pathIndex >= 0;pathIndex--){
        int nextRow = currentRow;
        int nextCol = currentCol;

        if (path[pathIndex] == 'U'){
            nextRow--;
        }
        else if (path[pathIndex] == 'D'){
            nextRow++;
        }
        else if (path[pathIndex] == 'L'){
            nextCol--;
        }
        else if (path[pathIndex] == 'R'){
            nextCol++;
        }

        if (nextRow >= 0 && nextRow < rows && nextCol >= 0 && nextCol < cols &&Grid[nextRow][nextCol] == '.'){
            Grid[nextRow][nextCol] = 'R';
        }
        currentRow = nextRow;
        currentCol = nextCol;
    }
}


int main()
{

    cout << "======================================" << endl;
    cout << "          MAZE ROBOT PROGRAM          " << endl;
    cout << "======================================" << endl;

    cout << endl;


    cout << "Robot: Voyager" << endl;

    cout << endl;


    int startRow = -1;
    int startCol = -1;

    int flagRow = -1;
    int flagCol = -1;

    int goalRow = -1;
    int goalCol = -1;


    for (int rowIndex = 0; rowIndex < rows; rowIndex++){
        for (int colIndex = 0; colIndex < cols; colIndex++){
            if (Grid[rowIndex][colIndex] == 'S'){
                startRow = rowIndex;
                startCol = colIndex;
            }
            else if (Grid[rowIndex][colIndex] == 'F'){
                flagRow = rowIndex;
                flagCol = colIndex;
            }
            else if (Grid[rowIndex][colIndex] == 'G'){
                goalRow = rowIndex;
                goalCol = colIndex;
            }
        }
    }



    cout << "Initial Maze:" << endl;

    Viz();

    cout << endl;


   bool flagFound = solveMaze(startRow, startCol, flagRow, flagCol,false);


    if (!flagFound){
        cout << endl;
        cout << "No path to FLAG found." << endl;
        return 0;
    }

    int stepsToFlag = pathLength;

    cout << endl;

    cout << "Path S -> F:" << endl;

    printPath();

    cout << endl;

    cout << "FLAG CAPTURED!" << endl;

    markPath(startRow, startCol);
    Viz();
    resetSearch();


    cout << endl;


bool goalFound = solveMaze(flagRow, flagCol, goalRow, goalCol, true);

    if (!goalFound){
        cout << endl;
        cout << "No path to GOAL found." << endl;
        return 0;
    }



    int stepsToGoal = pathLength;

    cout << endl;

    cout << "Path F -> G:" << endl;

    printPath();


    cout << endl;

    cout << "MISSION COMPLETE!" << endl;


    int totalSteps =stepsToFlag + stepsToGoal;


    cout << endl;

    cout << "Steps S -> F: "
         << stepsToFlag
         << endl;

    cout << "Steps F -> G: "
         << stepsToGoal
         << endl;

    cout << "Total Steps: "
         << totalSteps
         << endl;

    markPath(flagRow,flagCol);


    cout << endl;

    cout << "Final Map:" << endl;

    Viz();


    cout << endl;
    cout << "======================================" << endl;
    cout << "              FINISHED                " << endl;
    cout << "======================================" << endl;


    return 0;
}
