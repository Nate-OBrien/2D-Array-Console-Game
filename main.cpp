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
vector<int> getRandomPos(int size);

int main(){
    srand(time(NULL));

    cout << "\033[31m" << endl;
    string gameBoard[32][64];

    for(int i = 0; i < 32; i++){
        for(int j = 0; j < 64; j++){
            gameBoard[i][j] = "#"; 
            cout<< gameBoard[i][j]; 
        }
        cout<<endl;
    }
  
  vector<int> randPos = getRandomPos(64);
  for (int item : randPos){
        cout << "\n" << item << endl;  
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


vector<int> getRandomPos(int size){
    vector<int> arr (2);
    for (int i = 0; i < 2; i++){
        arr.at(i) = rand() % size;
    }

    return arr;
}
