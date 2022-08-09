#ifndef player_hpp
#define player_hpp
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;
class Player{
    private:
        int x,y, health=100,score=0;;
        SDL_Texture* playertex;
        SDL_Texture* shoottex;
        SDL_Rect srcR, destR;
    public:
        Player(int xg, int yg, int h, int w);
        void display(SDL_Renderer*);
        void move(int dir);
        void shoot(int x, int y, SDL_Renderer* renderer);
        bool shooted(int x, int y, SDL_Renderer* renderer);
        int getX();
        int getY();
        int getHealth();
        void setScore(int s);
        int getScore();
};
#endif