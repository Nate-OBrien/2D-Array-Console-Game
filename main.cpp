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
//methods
void clear();
void instructions();
vector<int> getRandomPos(int sizeX, int sizeY);
void printBoard(string board[32][64], vector<vector<int>> obstaclePos, vector<int> targetPos, vector<int> playerPos);
bool checkMove(vector<vector<int>>, vector<int> playerPos, int changePos[2]);

//defined outside to be accessed easier
vector<int> minePos = getRandomPos(64, 32);

int main(){
    srand(time(NULL));
    instructions();
    std::cout << "\033[0m" << endl;
    string gameBoard[32][64];
    char supportedKeys[5] = {'w', 'a', 's', 'd', 'q'};
    //gets positions of everything to start off
    vector<int> playerPos = getRandomPos(64, 32);

    vector<vector <int>> obstaclePos;
    for (int i = 0; i < 256; i++){
        vector<int> x;
        do {
            x = getRandomPos(64, 32);
        } while (count(obstaclePos.begin(), obstaclePos.end(), x) != 0 && x == playerPos); //count gets the number of times x appears
    
        obstaclePos.push_back(x);
    }
  
    vector <int> targetPos;
    do{
        targetPos = getRandomPos(64, 32);
    } while(count(obstaclePos.begin(), obstaclePos.end(), targetPos) != 0 && targetPos == playerPos);
    
    while (true){
        cout << endl;
        //prints board
        printBoard(gameBoard, obstaclePos, targetPos, playerPos);
        //extra - uses getch to get input
        char input = getch();
        clear();
        //checks to see if inputed character is in supported characters
        int n = sizeof(supportedKeys)/sizeof(supportedKeys[0]);
        auto it = find(supportedKeys, supportedKeys + n, input);
        if (it == supportedKeys + n) continue;
        //uses arr of 2 to get movement direction
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
            // if q is entered, quits
            case 'q':
                cout << "Exiting Program" << endl;
                exit(0);
        }
        //moves player
        if (checkMove(obstaclePos, playerPos, changePos)){
            playerPos.at(0) += changePos[0];
            playerPos.at(1) += changePos[1];
        } else {
            changePos[0] = 0;
            changePos[1] = 0;
        }
        // win/loss criteria
        if(playerPos.at(0) == minePos.at(0) && playerPos.at(1) == minePos.at(1)){
            cout << "You lose!" << endl;
            exit(0);
        } else if (playerPos.at(0) == targetPos.at(0) && playerPos.at(1) == targetPos.at(1)){
            cout << "You win!" << endl;
            exit(0);
        }    
    }
    
    return 0;
}

//ascii code to clear screen
void clear(){
    cout << "\e[H\e[J";
}

//returns a vector with a random amount
vector<int> getRandomPos(int sizeX, int sizeY){
    vector<int> arr (2);
    arr.at(0) = rand() % sizeX;
    arr.at(1) = rand() % sizeY;
    return arr;
}

void printBoard(string board[][64], vector<vector<int>> obstaclePos, vector<int> targetPos, vector<int> playerPos){
    //determines mine position randomly each time
    vector<int> minePos; 
    do{
        minePos = getRandomPos(64, 32);
     }while(count(obstaclePos.begin(), obstaclePos.end(), minePos) != 0 && (minePos == playerPos || minePos == targetPos));
    //prints board with certain colors based on if i/j is on the right coordinates
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
            } else {
                board[i][j] = "#"; 
            }
            
            std::cout<< board[i][j] << "\033[0m"; 

        }
        std::cout<<endl;
    }
    
}

//prints instructions, and gets input to start
void instructions(){
    cout<<"W, A, S, D to move\nQ to quit\n\033[36mBlue #'s \033[0m are walls, \033[42myellow # \033[0mis the objective\n\033[32mGreen # \033[0mis the player\nGet to the objective without getting hit by the hidden mine to win"<<endl; 
    char understand; 
    cin >> understand;
    clear();
}

//checks to see if moving would hit an obstacle or hit the side of the program
bool checkMove(vector<vector<int>> obstaclePos, vector<int> playerPos, int changePos[2]){
    vector<int> check = {playerPos.at(0) + changePos[0], playerPos.at(1) + changePos[1]};
    if (count(obstaclePos.begin(), obstaclePos.end(), check) != 0 || check.at(0) < 0 || check.at(1) < 0 || check.at(1) >= 32 || check.at(0) >= 64){
        return false;
    }
    return true;
}
