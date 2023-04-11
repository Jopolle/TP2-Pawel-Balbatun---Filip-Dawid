#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <thread>


/*
#include <functional> ???????
#include <pthread.h> ??????
*/



const int W = 6; // wiersze
const int K = 6; // kolumny
const int B = 3; // bloczki
const int R = 5;  //stała ruchów
const int N = 5; // losowa z przedziału [0,n)


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
void generuj_plansze(std::vector<std::queue<Block>> & plansza);
void game_loop(std::vector<std::queue<Block>> & plansza, Player & gracz);



int main() {

    Player gracz(K/2);
    std::vector<std::queue<Block>> plansza(K);
    generuj_plansze(plansza);
    game_loop(plansza, gracz);

/*
    std::thread druk(std::bind(wyswietl_plansze, plansza, gracz));
    druk.join();
*/

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




void generuj_plansze(std::vector<std::queue<Block>> & plansza){
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < B; j++) {
            Block blok = {"####", false};
            plansza[i].push(blok);
        }
    }
}

void game_loop(std::vector<std::queue<Block>> & plansza, Player & gracz){

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
    
}

