/*
* Name: Nate O'Brien & Shrihan Agarwal
* Program Name: 2D Array Game
* Date: 2/19/25
* Extra: 
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <conio.h>

using namespace std;

void clear();
void instructions();
vector<int> getRandomPos(int sizeX, int sizeY);
void printBoard(string board[32][64], vector<vector<int>> obstaclePos, vector<int> targetPos, vector<int> playerPos);
bool checkMove(vector<vector<int>>, vector<int> playerPos, int changePos[2]);

vector<int> minePos;
int main(){
    srand(time(NULL));
    instructions();
    std::cout << "\033[0m" << endl;
    string gameBoard[32][64];
    char supportedKeys[5] = {'w', 'a', 's', 'd', 'q'};

    vector<int> playerPos = getRandomPos(64, 32);

    vector<vector <int>> obstaclePos;
    for (int i = 0; i < 256; i++){
        vector<int> x;
        do {
            x = getRandomPos(64, 32);
        } while (count(obstaclePos.begin(), obstaclePos.end(), x) != 0 && x == playerPos);
    
        obstaclePos.push_back(x);
    }
  
    vector <int> targetPos;
    do{
        targetPos = getRandomPos(64, 32);
    } while(count(obstaclePos.begin(), obstaclePos.end(), targetPos) != 0 && targetPos == playerPos);
    
    

    while (true){
        cout << endl;

        printBoard(gameBoard, obstaclePos, targetPos, playerPos);
        char input = getch();
        clear();
        int n = sizeof(supportedKeys)/sizeof(supportedKeys[0]);
        auto it = find(supportedKeys, supportedKeys + n, input);
        if (it == supportedKeys + n) continue;
        int changePos[2] {0, 0};
        switch(input){
            case 'w':
                changePos[1] = -1;
                break;
            case 'a':
                changePos[0] = -1;
                break;
            case 's':
                changePos[1] = 1;
                break;
            case 'd':
                changePos[0] = 1;
                break;
            case 'q':
                cout << "Exiting Program" << endl;
                exit(0);
        }
        if (checkMove(obstaclePos, playerPos, changePos)){
            playerPos.at(0) += changePos[0];
            playerPos.at(1) += changePos[1];
        }
        
    }
    if(playerPos.at(0) == minePos.at(0) && playerPos.at(1) == minePos.at(1)){
        exit(0);
    }
    return 0;
}

void clear(){
    cout << "\e[H\e[J";
}

vector<int> getRandomPos(int sizeX, int sizeY){
    vector<int> arr (2);
    arr.at(0) = rand() % sizeX;
    arr.at(1) = rand() % sizeY;
    return arr;
}

void printBoard(string board[][64], vector<vector<int>> obstaclePos, vector<int> targetPos, vector<int> playerPos){
    vector<int> minePos; 
    do{
        minePos = getRandomPos(64, 32);
     }while(count(obstaclePos.begin(), obstaclePos.end(), minePos) != 0 && (minePos == playerPos || minePos == targetPos));
    for(int i = 0; i < 32; i++){
        for(int j = 0; j < 64; j++){
            std::cout << "\033[31m";
            if (count(obstaclePos.begin(), obstaclePos.end(), vector <int> {j, i}) != 0 ){
                std::cout << "\033[36m";
            }
            if (i == targetPos.at(1) && j == targetPos.at(0)){
                cout << "\033[33m";
            }
            if (i == playerPos.at(1) && j == playerPos.at(0)){
                std::cout << "\033[32m";
            }
            if(i == minePos.at(1) && j == minePos.at(0)){
                std::cout << "\033[42m";
                board[i][j] = "M";
            } else {
                board[i][j] = "#"; 
            }
            
            std::cout<< board[i][j] << "\033[0m"; 

        }
        std::cout<<endl;
    }
    
}

void instructions(){
    cout<<"W, A, S, D to move\nQ to quit\nBlue #'s are walls, yellow # is the objective\nGet to the objective without getting hit by the hidden min to win"<<endl; 
    string understand; 
    cin >> understand;
}

bool checkMove(vector<vector<int>> obstaclePos, vector<int> playerPos, int changePos[2]){
    vector<int> check = {playerPos.at(0) + changePos[0], playerPos.at(1) + changePos[1]};
    if (count(obstaclePos.begin(), obstaclePos.end(), check) != 0 || playerPos.at(0) == 0 || playerPos.at(1) == 0 || playerPos.at(0) == 31 || playerPos.at(1) == 63){
        return false;
    }
    return true;
}