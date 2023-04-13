#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <thread>
#include <ctime>
#include <functional>
#include <stack>
#include <stdio.h>



const int W = 6; // wiersze
const int K = 7; // kolumny
const int B = 3; // bloczki
const int R = 10;  //stała ruchów
const int N = 8; // losowa z przedziału [0,n)


struct Block {
    std::string look;
    bool has_bonus;
};

class Player {
public:
    int column;

    explicit Player(int col) : column(col){}
};


void wyswietl_plansze( const std::vector<std::queue<Block>>& plansza, const Player& gracz);
void generuj_plansze(std::vector<std::queue<Block>> & plansza);
void game_loop(std::vector<std::queue<Block>> & plansza, Player & gracz);
int losuj();
void dodawanie_bloczkow(std::vector<std::queue<Block>> & plansza);
std::vector<std::queue<Block>> kopiuj_wektor(const std::vector<std::queue<Block>>& plansza);


int main() {
    srand(time(NULL));
    Player gracz(K/2);
    std::vector<std::queue<Block>> plansza(K);
    generuj_plansze(plansza);
    game_loop(plansza, gracz);

    return 0;
}

void wyswietl_plansze( const std::vector<std::queue<Block>>& plansza, const Player& gracz) {

    std::vector<std::queue<Block>> tempVector = kopiuj_wektor(plansza);

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

    char input;
    int col = K/2, r = losuj();
    std::thread druk(std::bind(wyswietl_plansze, plansza, gracz));

    druk.join();


    do{
        std::thread drukuj(std::bind(wyswietl_plansze, plansza, gracz));
        input = std::getchar();

        if(r<=0){
            r = losuj();
            dodawanie_bloczkow(plansza);
        }
        else if(r!=0){
            r--;
        }

        switch (input) {
            case 'd': if(col+1<K) col++; break;
            case 'a': if(col>0) col--; break;
            case 'w': if(!plansza[col].empty())   plansza[col].pop();
        }

        gracz.column = col;

        system("clear");
        if(drukuj.joinable())drukuj.join();
    }while(input != 'q');
}

int losuj() {
    return 2 * (rand() % (N + 1) + R);
}

void dodawanie_bloczkow(std::vector<std::queue<Block>> & plansza){
    int r = rand()%(K+1);
    for(int i = 0; i<K; i++){
        if(i!=r){
            Block blok1 = {"####", false};
            plansza[i].push(blok1);
        }
        else if(i==r){
            Block blok2 = {"#++#", true};
            plansza[i].push(blok2);
        }
    }

}

std::vector<std::queue<Block>> kopiuj_wektor(const std::vector<std::queue<Block>>& plansza){
    std::vector<std::queue<Block>> buffor = plansza, output(K);
    for(int i = 0; i < K; i++){
        std::queue<Block> kolejka;
        std::stack<Block> stos;
        while(!buffor[i].empty()){
            stos.push(buffor[i].front());
            buffor[i].pop();
        }
        while(!stos.empty()){
            kolejka.push(stos.top());
            stos.pop();
        }
        output[i] = kolejka;
    }
    return output;
}
