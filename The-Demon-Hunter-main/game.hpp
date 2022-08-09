#ifndef game_hpp
#define game_hpp

#include<bits/stdc++.h>
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>
#include "player.hpp"
#include "enemy.hpp"
using namespace std;
class Game{
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture* hlth;
        SDL_Rect hlth_rect;
        SDL_Color textColor;
        SDL_Surface* surfacehlth;
        Mix_Music *backgroundSound;
        TTF_Font* hlthfont;
        Player* player;
        string player_name,phlth;
        vector<Enemy*> enemies;
        vector<string> scorelist;
        fstream fin,fout;
        bool isRunning, showPlayer, isShooting, isHS;
        int mx,my,ecount=0;
        long secount=0;
    public:
        Game();
        ~Game();
        void start(const char* title,int x, int y, int w, int h, bool fs);
        void event();
        void display();
        void createEnemy();
        void end();
        void over();
        bool running(){ return isRunning;};
};



#endif