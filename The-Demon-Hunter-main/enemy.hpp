#ifndef enemy_hpp
#define enemy_hpp

#include<bits/stdc++.h>
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
using namespace std;
class Enemy{
    private:
        int x,y,px,py,bx,by,scount=801;
        SDL_Texture* enemytex;
        SDL_Texture* shoottex;
        SDL_Texture* bullettex;
        SDL_Rect srcR, destR, destB;
        bool alive;
    public:
        Enemy(int xg, int yg, int h, int w);
        void display(SDL_Renderer*);
        pair<int,int> showBullet(int x,int y, SDL_Renderer* renderer);
        bool shooted(int x, int y);
        bool isAlive();
        //void shoot(int x, int y, SDL_Renderer* renderer);
};


#endif