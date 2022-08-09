#include<bits/stdc++.h>
#include "enemy.hpp"



Enemy::Enemy(int xg, int yg, int h, int w){
    destR.h=h; destR.w=w;
    destR.x=xg; destR.y=yg;
    x=xg; y=yg; alive=true;
}
void Enemy::display(SDL_Renderer* renderer){
    //Show enemy on screen
    if(alive){
        SDL_Surface * enemysurf = IMG_Load("images/enemy_new.png");
        enemytex = SDL_CreateTextureFromSurface(renderer, enemysurf);
        SDL_FreeSurface(enemysurf);
        
        SDL_RenderCopy(renderer, enemytex,NULL, &destR);
    }
}

pair<int,int> Enemy::showBullet(int xg,int yg, SDL_Renderer* renderer){
    //Animation to show that enemy is shooting
    if(scount>750){
        scount--;
        px=xg;py=yg;
        SDL_Surface * bulletsurf = IMG_Load("images/bullet2.png");
        bullettex = SDL_CreateTextureFromSurface(renderer, bulletsurf);
        SDL_FreeSurface(bulletsurf);
        bx=x+45; by=y+125;
        destB.h=32; destB.w=32;
        destB.x=bx; destB.y=by;
        SDL_RenderCopy(renderer, bullettex,NULL, &destB);
        return make_pair(bx,by);
    }
    else{
        scount--;
        if(scount==0){
            scount=801;
        }
        float m = (py-y-125)*1.0/(px-x-45);
        int s;
        if(bx-px >0)    s=-1;
        else if(bx-px<0)    s=1;
        else    s=0;
        //if(abs(bx-py)>300)  s*=2;
        bx+=s; by=m*(bx-px) + py;
        destB.x=bx; destB.y=by;
        SDL_Surface * bulletsurf = IMG_Load("images/bullet2.png");
        bullettex = SDL_CreateTextureFromSurface(renderer, bulletsurf);
        SDL_FreeSurface(bulletsurf);
        if(by<=py-20)
            SDL_RenderCopy(renderer, bullettex,NULL, &destB);
        else{
            bx=0; by=0;
        }
        return make_pair(bx,by);
    }
}

bool Enemy::shooted(int xb,int yb){
    //If enemy is killed?
    if(xb>x && xb<x+destR.w && yb>y && yb<y+destR.h){
        alive=false;
        SDL_DestroyTexture(enemytex);
        SDL_DestroyTexture(bullettex);
        return true;
    }
    return false;
}
bool Enemy::isAlive(){
    return alive;
}