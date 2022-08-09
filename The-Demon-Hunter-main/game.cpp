#include<bits/stdc++.h>
#include<chrono>
#include<thread>
#include "game.hpp"
using namespace std;

SDL_Texture* bgtex;


Game::Game(){}
Game::~Game(){}
void Game::start(const char* title, int x, int y, int w, int h, bool fs){
    int fullscreen = 0;
    if(fs){
        fullscreen=SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING)==0){
        window = SDL_CreateWindow(title, x, y, w, h, fullscreen);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        isRunning = true;

        //Creating  start window

        SDL_Surface * bgsurf = IMG_Load("images/bg4.png");
        bgtex = SDL_CreateTextureFromSurface(renderer, bgsurf);
        SDL_FreeSurface(bgsurf);
        SDL_Surface * titlesurf = IMG_Load("images/title.png");
        SDL_Texture* titletex = SDL_CreateTextureFromSurface(renderer, titlesurf);
        SDL_FreeSurface(titlesurf);
        SDL_Rect title_rect; 
        title_rect.x = 170;  
        title_rect.y = 50; 
        title_rect.w = 662; 
        title_rect.h = 77; 

        SDL_Surface * asknamesurf = IMG_Load("images/askname.png");
        SDL_Texture* asknametex = SDL_CreateTextureFromSurface(renderer, asknamesurf);
        SDL_FreeSurface(asknamesurf);
        SDL_Rect askname_rect; 
        askname_rect.x = 100;  
        askname_rect.y = 350; 
        askname_rect.w = 342; 
        askname_rect.h = 72;

        SDL_Surface * ins1surf = IMG_Load("images/ins1.png");
        SDL_Texture* ins1tex = SDL_CreateTextureFromSurface(renderer, ins1surf);
        SDL_FreeSurface(ins1surf);
        SDL_Rect ins1_rect; 
        ins1_rect.x = 600;  
        ins1_rect.y = 300; 
        ins1_rect.w = 238; 
        ins1_rect.h = 56;

        SDL_Surface * ins2surf = IMG_Load("images/ins2.png");
        SDL_Texture* ins2tex = SDL_CreateTextureFromSurface(renderer, ins2surf);
        SDL_FreeSurface(ins2surf);
        SDL_Rect ins2_rect; 
        ins2_rect.x = 600;  
        ins2_rect.y = 360; 
        ins2_rect.w = 253; 
        ins2_rect.h = 56;

        TTF_Init();
        SDL_Color textColor = { 255, 255, 255};
        TTF_Font* inpfont = TTF_OpenFont("fonts/HandyQuomteRegular-6YLLo.ttf", 40);
        if(inpfont==NULL){
            cout<<"This is wrong"<<endl;
        }
        string inputText="";
        SDL_Texture* input;
        SDL_Rect input_rect; 
        input_rect.x = 150;  
        input_rect.y = 450; 
        input_rect.w = 100; 
        input_rect.h = 30; 


        TTF_Font* instfont = TTF_OpenFont("fonts/HandyQuomteRegular-6YLLo.ttf", 30);
        SDL_Rect inst_rect; 
            
        string pinst = "Left click to shoot and use arrow keys to move left or right";
        SDL_Surface* surfaceinst =TTF_RenderText_Solid(instfont, pinst.c_str(), textColor);
        inst_rect.w=(surfaceinst->w);
        inst_rect.h=surfaceinst->h;
        inst_rect.x = 500 - (inst_rect.w)/2;
        inst_rect.y = 650 - (inst_rect.h)/2;
        SDL_Texture* inst = SDL_CreateTextureFromSurface(renderer, surfaceinst);
        
        SDL_FreeSurface(surfaceinst);


        //Playing sound
        Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT , 2, 2048);
        backgroundSound = Mix_LoadMUS("Sounds/sound.mpeg");
        Mix_PlayMusic(backgroundSound,-1);
        Mix_Volume(-1,5);
        while(true){
            bool renderText=true;
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, bgtex,NULL, NULL);
            SDL_RenderCopy(renderer, titletex, NULL, &title_rect);
            SDL_RenderCopy(renderer, asknametex, NULL, &askname_rect);
            SDL_RenderCopy(renderer, ins1tex, NULL, &ins1_rect);
            SDL_RenderCopy(renderer, ins2tex, NULL, &ins2_rect);
            SDL_RenderCopy(renderer, inst, NULL, &inst_rect);

            SDL_Event event2;
            SDL_PollEvent(&event2);
            if(event2.type==SDL_QUIT){
                isRunning=false;
                SDL_DestroyTexture(input);
                SDL_DestroyTexture(titletex);
                SDL_DestroyTexture(asknametex);
                SDL_DestroyTexture(ins1tex);
                SDL_DestroyTexture(ins2tex);
                SDL_DestroyTexture(inst);
                return;
            }
            //Taking name input
            else if(event2.type==SDL_KEYDOWN){
                if(event2.key.keysym.sym==SDLK_RETURN){
                    SDL_DestroyTexture(input);
                    SDL_DestroyTexture(titletex);
                    SDL_DestroyTexture(asknametex);
                    SDL_DestroyTexture(ins1tex);
                    SDL_DestroyTexture(ins2tex);
                    SDL_DestroyTexture(inst);
                    break;
                }
                else if(event2.key.keysym.sym==SDLK_BACKSPACE){
                    if(!inputText.empty())
                        inputText.pop_back();
                    player_name=inputText;
                    using namespace std::this_thread;
                    using namespace std::chrono;
                    sleep_for(200ms);
                    
                    renderText=true;
                }
            }
            else if(event2.type==SDL_TEXTINPUT){
                
                inputText+=event2.text.text;
                player_name=inputText;
                
                using namespace std::this_thread;
                using namespace std::chrono;
                sleep_for(200ms);
                
                renderText=true;
            }
            if(renderText){
                SDL_Surface* surfaceinput;
                if(inputText=="")
                    surfaceinput =TTF_RenderText_Solid(inpfont, " ", textColor);
                else
                    surfaceinput =TTF_RenderText_Solid(inpfont, inputText.c_str(), textColor);
                input_rect.w=(surfaceinput->w);
                input_rect.h=surfaceinput->h;
                input = SDL_CreateTextureFromSurface(renderer, surfaceinput);
                
                SDL_FreeSurface(surfaceinput);
                SDL_RenderCopy(renderer, input, NULL, &input_rect);
            }

            SDL_RenderPresent(renderer);
            
           
        }

        player = new Player(0,550,250,250);
        hlthfont = TTF_OpenFont("fonts/HandyQuomteRegular-6YLLo.ttf", 30);
        
        showPlayer=true; isShooting=false;
    }
    else{
        isRunning = false;
    }
}
void Game::event(){
    //Checks for closing the window, moving the player, shooting
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning=false;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            if(showPlayer){
                player->move(-1);
                player->display(renderer);
            }
            break;
        case SDLK_RIGHT:
            if(showPlayer){
                player->move(1);
                player->display(renderer);
            }
            break;
        case SDLK_DOWN:
            showPlayer=false;
            break;
    }
        
        break;
    case SDL_MOUSEBUTTONDOWN:
        isShooting=true;
        break;

    case SDL_MOUSEBUTTONUP:
        isShooting=false;
        break;

    default:
        break;
    }
    if(event.type==SDL_QUIT){
        isRunning=false;
    }
}
void Game::display(){
    //Rerendering stuff, checking for shoots, hits, kills, scores, health, creates enemy
    SDL_RenderClear(renderer);
    
    SDL_RenderCopy(renderer, bgtex,NULL, NULL);
    if(showPlayer)
    player->display(renderer);
    secount++;
    secount=secount%901;
    if(secount==900 && ecount<5){
        secount=0;
        ecount++;
        createEnemy();
    }
    
    
     if(isShooting){
         SDL_GetMouseState(&mx,&my);
         player->shoot(mx,my, renderer);
         
         for(auto enemy=enemies.begin();enemy!=enemies.end();enemy++){
            bool shooted = (*enemy)->shooted(mx,my);
            if(shooted){
                ecount--;
                player->setScore(player->getScore()+10);
                free(*enemy);
                *enemy=NULL;
                enemies.erase(enemy--);
            }
         }
     }
    for(auto enemy: enemies){
        if(enemy->isAlive())
            enemy->display(renderer);
    }
    pair<int,int> bullet_pos;

    
    textColor = { 255, 255, 255};
    
    phlth = "Health: "+to_string(player->getHealth());
    surfacehlth =TTF_RenderText_Solid(hlthfont, phlth.c_str(), textColor);
    hlth_rect.w=(surfacehlth->w);
    hlth_rect.h=surfacehlth->h;
    hlth_rect.x = 500 - (hlth_rect.w)/2;
    hlth_rect.y = 0;
    hlth = SDL_CreateTextureFromSurface(renderer, surfacehlth);
    SDL_FreeSurface(surfacehlth);
    SDL_RenderCopy(renderer, hlth, NULL, &hlth_rect);

    for(auto enemy:enemies){
        if(enemy->isAlive()){
            bullet_pos=enemy->showBullet(player->getX()+64,player->getY()+128,renderer);
            if(!player->shooted(bullet_pos.first,bullet_pos.second,renderer)){
                over();
                return;
            }
            
        }
    }
    SDL_RenderPresent(renderer);
    
    
}

bool compare_scores(string a, string b){
    string san,sbn;
    stringstream A(a);
    stringstream B(b);
    getline(A,san,'-');
    getline(B,sbn,'-');
    int an=0,bn=0;
    stringstream sA(san);
    stringstream sB(sbn);
    sA>>an; sB>>bn;
    return (an>bn);
}

void Game::over(){
    //Maintain Scores in a file
    fin.open("ScoreSheet.txt",ios::in);
    string t,row;
    scorelist.clear();
    
    while(fin.peek()!=EOF){
        getline(fin,row);
        scorelist.push_back(row);

    }
    fin.close();
    fout.open("ScoreSheet.txt",ios::out);
    string s1=to_string(player->getScore())+"-"+player_name;
    scorelist.push_back(s1);
    sort(scorelist.begin(), scorelist.end(),compare_scores);
    if(scorelist[0]==s1){
        isHS=true;
    }
    else{
        isHS=false;
    }
    for(auto i:scorelist){
        fout<<i<<endl;
    }
    fout.close();
    //Final Screen
    SDL_Color textColor = { 255, 255, 255};
    TTF_Font* hscorefont = TTF_OpenFont("fonts/HandyQuomteRegular-6YLLo.ttf", 50);
    SDL_Rect hscore_rect; 
        
    string phscore = "New High Score !";
    SDL_Surface* surfacehscore =TTF_RenderText_Solid(hscorefont, phscore.c_str(), textColor);
    hscore_rect.w=(surfacehscore->w);
    hscore_rect.h=surfacehscore->h;
    hscore_rect.x = 500 - (hscore_rect.w)/2;
    hscore_rect.y = 600 - (hscore_rect.h)/2;
    SDL_Texture* hscore = SDL_CreateTextureFromSurface(renderer, surfacehscore);
    
    SDL_FreeSurface(surfacehscore);



    TTF_Font* scorefont = TTF_OpenFont("fonts/HandyQuomteRegular-6YLLo.ttf", 50);
    SDL_Rect score_rect; 
    
    string pscore = "Score: "+to_string(player->getScore());
    SDL_Surface* surfacescore =TTF_RenderText_Solid(scorefont, pscore.c_str(), textColor);
    score_rect.w=(surfacescore->w);
    score_rect.h=surfacescore->h;
    score_rect.x = 500 - (score_rect.w)/2;
    score_rect.y = 200 - (score_rect.h)/2;
    SDL_Texture* score = SDL_CreateTextureFromSurface(renderer, surfacescore);
    
    SDL_FreeSurface(surfacescore);
    free(player);
    player=NULL;
    while(true){
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,bgtex,NULL, NULL);
        if(isHS)
            SDL_RenderCopy(renderer, hscore, NULL, &hscore_rect);
        SDL_RenderCopy(renderer, score, NULL, &score_rect);
        SDL_RenderPresent(renderer);
        SDL_Event event3;
        SDL_PollEvent(&event3);
        if(event3.type==SDL_QUIT){
            isRunning=false;
            return;
        }
    }
}

void Game::createEnemy(){
    int xe,ye;
    srand(time(0));
    xe=rand()%800 + 50;
    ye=rand()%250 + 50;
    Enemy * enemy =new Enemy(xe,ye,150,150);
    enemies.push_back(enemy);
}

void Game::end(){
    Mix_FreeMusic(backgroundSound);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();
}