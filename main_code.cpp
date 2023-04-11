#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <thread>


/*
#include <functional> ???????
#include <pthread.h> ??????
*/



const int W = 5; // liczba wierszy
const int K = 8; // liczba kolumn
const int B = 3; // liczba bloczków w każdej kolumnie na początku
const int R = K/2; // liczba ruchów do dodania nowego bloczka
const int N = 5; // wartość losowa z przedziału [0,n)


struct Block {
    std::string look;
    bool has_bonus;
};

class Player {
public:
    int column;

    Player(int col) : column(col) {}
};


void wyswietl_plansze( std::vector<std::queue<Block>>& plansza, const Player& gracz);





int main() {
    std::vector<std::queue<Block>> plansza(K);

    // wstępna generacja wektora planszy
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < B; j++) {
            Block blok = {"####", false};
            plansza[i].push(blok);
        }
    }

    Player gracz(K/2);



    wyswietl_plansze(plansza, gracz);
    char input;
    int col = K/2;
    do{
        input = std::getchar();
        if(input == 'd' && col+1<K) col++;
        else if(input == 'a' && col-1>-1) col--;
        else if(input == 'w'){
            if(!plansza[col].empty())   plansza[col].pop();
        }
        gracz.column = col;
        system("clear");
        wyswietl_plansze(plansza, gracz);

    }while(input != 'q');


/*
    std::thread druk(std::bind(wyswietl_plansze, plansza, gracz));
    druk.join();
*/
    wyswietl_plansze(plansza, gracz);

    return 0;
}

void wyswietl_plansze( std::vector<std::queue<Block>>& plansza, const Player& gracz) {

    std::vector<std::queue<Block>> tempVector = plansza;

    std::cout << " +";
    for (int i = 0; i < K; i++) {
        std::cout << "----+";
    }
    std::cout << std::endl;
    for (int i = 0; i < W; i++) {
        std::cout<<"| ";
        for (int j = 0; j < K; j++) {
            if(!tempVector[j].empty()) {
                std::cout << tempVector[j].front().look << " ";
                tempVector[j].pop();
            }
            else{
                std::cout << "     ";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout<<"| ";
    for (int i = 0; i < K; i++){
        if(gracz.column == i){ std::cout << "=[]= ";}
        else{
            std::cout << "     ";
        }


    }

    std::cout << "|" << std::endl;


    std::cout << " +";
    for (int j = 0; j < K; j++) {
        std::cout << "----+";
    }
    std::cout << std::endl;
}

