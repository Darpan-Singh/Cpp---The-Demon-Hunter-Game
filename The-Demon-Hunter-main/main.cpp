#include<bits/stdc++.h>
#include "game.hpp"
//#include "game.cpp"
using namespace std; 
int main(int argc, char ** argv)
{
    Game *game = new Game();
    game->start("The Demon Hunter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, false);
    
    while(game->running()){
        game->display();
        game->event();
    }
    game->end();
    return 0;
}
