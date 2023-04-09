#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <thread>


/*
#include <functional> ???????
#include <pthread.h> ??????
*/
const int W = 6; // liczba wierszy
const int K = 5; // liczba kolumn
const int B = 3; // liczba bloczków w każdej kolumnie na początku
const int R = 3; // liczba ruchów do dodania nowego bloczka
const int N = 5; // wartość losowa z przedziału [0,n)

struct Block {
    std::string look;
    bool has_bonus;
};

class Player {
public:
    int column;
    int row;

    Player(int col) : column(col), row(W - 1) {}
};

void wyswietl_plansze( std::vector<std::queue<Block>>& plansza, const Player& gracz) {
    std::cout << " +";
    for (int i = 0; i < K; i++) {
        std::cout << "----+";
    }
    std::cout << std::endl;


    for (int i = 0; i < W; i++) {
        std::cout<<"| ";
        for (int j = 0; j < K; j++) {
            std::cout << plansza[j].front().look << " ";
            plansza[j].pop();
        }
        std::cout << "|" << std::endl;
    }
    std::cout << " +";
    for (int j = 0; j < K; j++) {
        std::cout << "----+";
    }
    std::cout << std::endl;

//TU WYSWIETLIMY GRACZA, JESZCZE ZOBACZYMY JAK

}

int main() {
    std::vector<std::queue<Block>> plansza(K);

    // wstępna generacja wektora planszy
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < B; j++) {
            Block blok = {"####", false};
            plansza[i].push(blok);
        }
    }
    for (int ii = 0; ii < K; ii++) {
        for (int jj = 0; jj < W; jj++) {
            Block blok = {"    ", false};
            plansza[ii].push(blok);
        }
    }
    Player gracz(K / 2);
/*
    std::thread druk(std::bind(wyswietl_plansze, plansza, gracz));

    druk.join();
*/
    wyswietl_plansze(plansza, gracz);

    return 0;
}
