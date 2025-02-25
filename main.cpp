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
vector<int> getRandomPos(int sizeX, int sizeY);
void printBoard(string board[32][64], vector<vector<int>> obstaclePos, vector<int> targetPos, vector<int> playerPos, vector<int> minePos);

int main(){
    srand(time(NULL));

    std::cout << "\033[0m" << endl;
    string gameBoard[32][64];

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
    
    vector<int> minePos; 
    do{
        minePos = getRandomPos(64, 32);
     }while(count(obstaclePos.begin(), obstaclePos.end(), minePos) != 0 && (minePos == playerPos || minePos == targetPos));

    while (true){
        printBoard(gameBoard, obstaclePos, targetPos, playerPos, minePos);

        char input = getch();
        clear();
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

void printBoard(string board[][64], vector<vector<int>> obstaclePos, vector<int> targetPos, vector<int> playerPos, vector<int> minePos){
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