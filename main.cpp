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
#include <utility>
#include <algorithm>

using namespace std;

void clear();
vector<int> getRandomPos(int sizeX, int sizeY);

int main(){
    srand(time(NULL));

    cout << "\033[0m" << endl;
    string gameBoard[32][64];

    vector<int> playerPos = getRandomPos(64, 32);
    vector<vector <int>> obstaclePos;

    for (int i = 0; i < 256; i++){
        vector <int> x = getRandomPos(64, 32);
        do {
            x = getRandomPos(64, 32);
        } while (count(obstaclePos.begin(), obstaclePos.end(), x) != 0 && x == playerPos);
    
        obstaclePos.push_back(x);
        cout << obstaclePos.at(i).at(0) << " " << obstaclePos.at(i).at(1) << endl;
    }

    for(int i = 0; i < 32; i++){
        for(int j = 0; j < 64; j++){
            cout << "\033[31m";
            if (count(obstaclePos.begin(), obstaclePos.end(), vector <int> {j, i}) != 0 ){
                cout << "\033[36m";
            }
            if (i == playerPos.at(1) && j == playerPos.at(0)){
                cout << "\033[32m";
                gameBoard[i][j] = "0";
                
            } else {
                gameBoard[i][j] = "#"; 
            }
            
            cout << gameBoard[i][j]; 
        }
        cout<<endl;
    }
  
   

    cout << "\n "<< "\033[0m" << endl;
    return 0;
}

void clear(){
    #if defined _WIN32
        system("CLS");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || defined (__APPLE__) || defined (__posix__)
        system("clear");
    #endif
}


vector<int> getRandomPos(int sizeX, int sizeY){
    vector<int> arr (2);
    arr.at(0) = rand() % sizeX;
    arr.at(1) = rand() % sizeY;
    return arr;
}
