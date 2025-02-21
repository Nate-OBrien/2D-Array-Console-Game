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

using namespace std;

void clear();
vector<int> getRandomPos(int sizeX, int sizeY);

int main(){
    srand(time(NULL));

    cout << "\033[31m" << endl;
    string gameBoard[32][64];

    vector<int> playerPos = getRandomPos(64, 32);
    vector<int> minePos = getRandomPos(64, 32); 

    for(int i = 0; i < 32; i++){
        for(int j = 0; j < 64; j++){
            cout << "\033[31m";
            if (i == playerPos.at(1) && j == playerPos.at(0)){
                cout << "\033[32m";
                gameBoard[i][j] = "0";
                
            } else {
                gameBoard[i][j] = "#"; 
            }
            if(i == minePos.at(1) && j == minePos.at(0)){
                cout << "\033[42m";
                gameBoard[i][j] = "M";
            } else {
                gameBoard[i][j] = "#"; 
            }
            
            cout<< gameBoard[i][j] << "\033[0m"; 
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
