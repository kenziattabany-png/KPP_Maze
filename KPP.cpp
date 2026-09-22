#include <iostream>
#include <cstring>
using namespace std;

//kita men setting max rows dan collumn yang akan dipakai, sekarang kita mempunyai maze yang paling besar dengan dimensi 11x11
const int MAX_ROWS = 11;
const int MAX_COLS = 11;
//ini adalah batas memori yang bisa disimpan di variabel untuk jumlah step
const int MAX = 100;

//ini adalah rows dan cols yang kita gunakan untuk sementara
int rows = 7;
int cols = 7;

//ini adalah 3 maze kita dalam bentuk array
char mazeSoal1[7][7] = {
    {'#', '#', '#', '#', '#', '#', '#'},
    {'#', 'S', '#', '.', '.', '.', '#'},
    {'#', '.', '#', '.', '#', 'G', '#'},
    {'#', '.', '.', '.', '#', '.', '#'},
    {'#', '#', '#', '.', '.', '.', '#'},
    {'#', 'X', '.', '.', 'F', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#'}
};

char mazeSoal2[9][9] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', 'S', '.', '.', '#', '.', '.', '.', '#'},
    {'#', '.', '#', '.', '#', '.', '#', 'G', '#'},
    {'#', '.', '#', '.', '.', '.', '#', '.', '#'},
    {'#', '.', '.', '.', '#', '.', '.', '.', '#'},
    {'#', '#', '#', '.', '#', '.', '.', '#', '#'},
    {'#', 'X', '.', '.', '#', '.', '.', 'F', '#'},
    {'#', '.', '#', '#', '#', 'X', '.', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

char mazeSoal3[11][11] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', 'S', '.', '.', '#', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '#', '.', '#', '.', '#', '#', '#', '.', '#'},
    {'#', '.', '#', '.', '.', '.', '#', 'G', '#', '.', '#'},
    {'#', '.', '.', '.', '#', '.', '#', '.', '#', '.', '#'},
    {'#', '#', '#', '.', '#', '.', '.', '.', '#', '.', '#'},
    {'#', '.', '.', '.', '#', '#', '#', '.', '#', '.', '#'},
    {'#', '.', '#', '.', '.', 'X', '.', '.', '#', '.', '#'},
    {'#', '.', '#', '.', '#', '#', '#', '.', '#', 'F', '#'},
    {'#', 'X', '.', '.', '.', '.', 'X', '.', '.', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

//untuk menampilkan perjalanan robot entar
char Grid[MAX_ROWS][MAX_COLS];
//untuk mengecek apakah jalan ini sudah pernah dilewati atau belum
bool visited[MAX_ROWS][MAX_COLS] = {};
//ini untuk menyimpan arah-arah yang dilakukan oleh robot nanti
char path[MAX];
//ini adalah jumlah jalan yang dilakukan oleh robot
int pathLength = 0;


//ini untuk mendefinisikan arah-arah robot yang akan dilakukan nanti
const int DR[4]      = {-1, 1, 0, 0};
const int DC[4]      = {0, 0, -1, 1};
const char DCHAR[4]  = {'U', 'D', 'L', 'R'};
const string DNAME[4] = {"UP", "DOWN", "LEFT", "RIGHT"};
int moveIndex(char m) {
    for (int i = 0; i < 4; i++) {
        if (DCHAR[i] == m) return i;
    }
    return -1;
}
string moveName(char c) {
    return DNAME[moveIndex(c)];
}

//untuk mereset memory 
void resetSearch(){
    memset(visited, false, sizeof(visited));
    pathLength = 0;
}

//ini untuk memanggil maze mana yang dipakai
void loadMap(int soal){
    if (soal == 1){
        rows = 7;
        cols = 7;
    }
    else if (soal == 2){
        rows = 9;
        cols = 9;
    }
    else {
        rows = 11;
        cols = 11;
    }

    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++){
            if (soal == 1){
                Grid[row][col] = mazeSoal1[row][col];
            }
            else if (soal == 2){
                Grid[row][col] = mazeSoal2[row][col];
            }
            else {
                Grid[row][col] = mazeSoal3[row][col];
            }
        }
    }
    resetSearch();
}

//ini untuk print maze
void Viz(){
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++){
            cout << Grid[row][col] << ' ';
        }
        cout << endl;
    }
}

//ini seperti aturan-aturan yang saya berikan untuk robot pada maze, seperti tidak boleh menyentuh X dan #, dan sebelum masuk ke G harus dapetin F
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

    //Ini unutk menggerakkan robot
    for (int i = 0; i < 4; i++){
        if (solveMaze(row + DR[i], col + DC[i], targetRow, targetCol, hasFlag)){
            path[pathLength] = DCHAR[i];
            pathLength++;
            return true;
        }
    }

    return false;
}

//ini untuk mengubah tanda '.' pada maze manjadi 'R', sejalan dengan perjalanan robot
void markPath(int startRow, int startCol){
    int row = startRow;
    int col = startCol;

    for (int pathIndex = pathLength - 1; pathIndex >= 0; pathIndex--){
        int i = moveIndex(path[pathIndex]);
        row += DR[i];
        col += DC[i];

        if (Grid[row][col] == '.'){
            Grid[row][col] = 'R';
        }
    }
}

//untuk print koordinat robot
string pos(int row, int col){
    return "(" + to_string(row) + "," + to_string(col) + ")";
}

//untuk mengubah arah-arah robot tadi menjadi text output entar
string pathToText(){
    string text = "";
    for (int pathIndex = pathLength - 1; pathIndex >= 0; pathIndex--){
        text += moveName(path[pathIndex]);
        if (pathIndex > 0) text += ", ";
    }
    return text;
}


int main()
{
    //loop untuk mengerjakan 3 soal maze
    for (int soal = 1; soal <= 3; soal++){
        loadMap(soal);

        cout << "Maze: " << endl;

        int startRow = -1, startCol = -1;
        int flagRow = -1, flagCol = -1;
        int goalRow = -1, goalCol = -1;

        //ini untuk mengetahui koordinat chat 'S', 'F', dan 'G'
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

        //untuk print maze
        Viz();

        //fase ke 1, mencari F dari S
        bool flagFound = solveMaze(startRow, startCol, flagRow, flagCol, false);

        if (!flagFound){
            cout << "MISSION FAILED" << endl;
            if (soal < 3) cout << endl;
            continue;
        }

        //mencatat perjalanan dan reset
        int stepsToFlag = pathLength;
        string pathToFlag = pathToText();
        markPath(startRow, startCol);
        resetSearch();

        // Fase ke 2, mencari G dari F
        bool goalFound = solveMaze(flagRow, flagCol, goalRow, goalCol, true);

        if (!goalFound){
            cout << "MISSION FAILED" << endl;
            if (soal < 3) cout << endl;
            continue;
        }

        //mencatat perjalanan
        int stepsToGoal = pathLength;
        string pathToBase = pathToText();
        markPath(flagRow, flagCol);

        int totalSteps = stepsToFlag + stepsToGoal;

        //output akhir
        cout << "MAP LOADED     : " << rows << " x " << cols << endl;
        cout << "START POSITION : " << pos(startRow, startCol) << endl;
        cout << "PATH TO FLAG   : " << pathToFlag << endl;
        cout << "FLAG CAPTURED  : " << pos(flagRow, flagCol) << endl;
        cout << "PATH TO BASE   : " << pathToBase << endl;
        cout << "BASE REACHED   : " << pos(goalRow, goalCol) << endl;
        cout << "MISSION COMPLETE" << endl;
        cout << "TOTAL MOVES    : " << totalSteps << endl;

        cout << endl << "MAZE WITH PATH MARKED: " << endl;
        Viz();

        if (soal < 3){
            cout << endl;
        }
    }

    return 0;
}
