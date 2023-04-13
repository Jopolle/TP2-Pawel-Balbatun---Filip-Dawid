#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <thread>
#include <ctime>
#include <functional>
#include <stack>





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
    bool bonus;
    Player(int col, bool b) : column(col), bonus(b) {}
};


void wyswietl_plansze( const std::vector<std::queue<Block>>& plansza, const Player& gracz, const int punkty);
void generuj_plansze(std::vector<std::queue<Block>> & plansza);
void game_loop(std::vector<std::queue<Block>> & plansza, Player & gracz);
int losuj();
void dodawanie_bloczkow(std::vector<std::queue<Block>> & plansza);
std::vector<std::queue<Block>> kopiuj_wektor(const std::vector<std::queue<Block>>& plansza);
void strzelanie( std::vector<std::queue<Block>> & plansza, Player & gracz, int col, int & punkty);
bool koniec_gry(const std::vector<std::queue<Block>> & plansza);


int main() {
    Player gracz(K/2, false);
    std::vector<std::queue<Block>> plansza(K);
    generuj_plansze(plansza);
    game_loop(plansza, gracz);

    return 0;
}

void wyswietl_plansze( const std::vector<std::queue<Block>>& plansza, const Player& gracz, const int punkty) {

    std::vector<std::queue<Block>> tempVector = kopiuj_wektor(plansza);
    std::cout<< "Punkty: " <<punkty<<std::endl;
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
    int col = K/2, r = losuj(), punkty = 0;
    bool koniec;

    do{
        std::thread drukuj(std::bind(wyswietl_plansze, plansza, gracz, punkty));
        input = std::getchar();
        if(r<=0){
            r = losuj();
            dodawanie_bloczkow(plansza);
        }
        else{
            r--;
        }
        switch (input) {
            case 'd': if(col+1<K) col++; break;
            case 'a': if(col>0) col--; break;
            case 'w': strzelanie(plansza, gracz, col, punkty); break;

        }
        gracz.column = col;
        system("clear");
        if(drukuj.joinable())drukuj.join();
        koniec = koniec_gry(plansza);
        if(koniec) break;

    }while(input != 'q');
    if(koniec){
        system("clear");
        std::cout<< "Koniec gry" << std::endl << "Zdobyta liczba punktów: " << punkty<< std::endl;
    }

}

int losuj() {
    srand(time(NULL));
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


void strzelanie(  std::vector<std::queue<Block>> & plansza, Player & gracz, const int col, int & punkty){

    if(!plansza[col].empty() && !gracz.bonus) {
        if(plansza[col].front().has_bonus) gracz.bonus = true;
        plansza[col].pop();
        punkty++;
    }else if(!plansza[col].empty() && plansza[col].size() >= 2 &&  gracz.bonus) {
        plansza[col].pop();
        plansza[col].pop();
        gracz.bonus = false;
        punkty = punkty + 2;
    }else if(!plansza[col].empty() && plansza[col].size() < 2 &&  gracz.bonus) {
        plansza[col].pop();
        gracz.bonus = false;
        punkty++;
    }
}

bool koniec_gry(const std::vector<std::queue<Block>> & plansza){
    for(int i = 0; i < K; i++){
        if(plansza[i].size() == (W+1)) return true;
    }
    return false;
}
