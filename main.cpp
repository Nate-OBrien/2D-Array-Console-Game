#include <iostream>

using namespace std;

void clear();

int main(){
    cout << "\033[31m" << endl;
    string gameBoard[16] = {"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#",};
    for (string piece : gameBoard){
        cout << piece;
    }

    cout << "\033[0m" << endl;
    return 0;
}

void clear(){
    #if defined _WIN32
        system("CLS");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
    #elif defined (__APPLE__)
        system("clear");
    #endif
}