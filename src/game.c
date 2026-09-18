#define SDL_MAIN_HANDLED
#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_mixer.h"
#include <stdio.h>
#include "labyrinth.h"
#include "audio.h"

#define WIDTH 76
#define HEIGHT 75
#define WINDOW_WIDTH 650
#define WINDOW_HEIGHT 620
#define CELL_WIDTH WINDOW_WIDTH / WIDTH
#define CELL_HEIGHT WINDOW_HEIGHT / HEIGHT

void playUI(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0 ){
	printf("Error : %s ", SDL_GetError() );
    return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Window * window = SDL_CreateWindow("Labyrinthe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_Event event;
    int run = 1;
    
    //Creation du labyrinthe
    char** labyrinth = init_labyrinth();

    char level_path[20];
    char level_str[20];
    int level = 0;
    snprintf(level_path, 20, "levels/%d.txt", level);
    load_level(labyrinth, level_path);

    int* goal = find_goal(labyrinth);
    int goal_x = goal[0];
    int goal_y = goal[1];

    level_start();
    //Boucle principale
    while(run){

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //make_label(renderer, level, level_path);
            
        // Dessiner le labyrinthe
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                SDL_Rect rect;
                rect.x = j * CELL_WIDTH;
                rect.y = i * CELL_HEIGHT;
                rect.w = CELL_WIDTH;
                rect.h = CELL_HEIGHT;

                int* player = find_player(labyrinth);
                int x = player[0];
                int y = player[1];
                int d = distance(x,y,i,j);
                
                //make_shadows(renderer, rect, labyrinth, d, i, j, goal_x, goal_y);

                //else{
                    switch (labyrinth[i][j]) {
                        case '|': // Mur
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir
                            SDL_RenderFillRect(renderer, &rect);
                            break;
                        case 'x': // Joueur
                            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rouge
                            SDL_RenderFillRect(renderer, &rect);
                            break;
                        case '1': // But
                            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Vert
                            SDL_RenderFillRect(renderer, &rect);
                            break;
                        case ' ': // Espace vide
                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Blanc
                            SDL_RenderFillRect(renderer, &rect);
                            break;
                    }
                //}
            }
        }

        if (labyrinth[goal_x][goal_y] != '1'){
            level++;
            snprintf(level_path, 20, "levels/%d.txt", level);
            load_level(labyrinth, level_path);

            goal = find_goal(labyrinth);
            goal_x = goal[0];
            goal_y = goal[1];

            //level_clear();

            SDL_Delay(200);
            level_start();
        }


        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT){
                run = 0; // Marquer pour quitter la boucle
            }

            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        move(labyrinth, 'u');
                        //walk();
                        break;
                    case SDLK_DOWN:
                        move(labyrinth, 'd');
                        //walk();
                        break;
                    case SDLK_LEFT:
                        move(labyrinth, 'l');
                        //walk();
                        break;
                    case SDLK_RIGHT:
                        move(labyrinth, 'r');
                        //walk();
                        break;
                    case SDLK_r:
                        snprintf(level_path, 20, "levels/%d.txt", level);
                        load_level(labyrinth, level_path);
                }
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();

    SDL_Quit();

    
    
}

/*void make_label(SDL_Renderer renderer, int level, char level_str){
    if(TTF_Init()==-1){
                SDL_Quit();
            }
            TTF_Font* font = TTF_OpenFont("./assets/fonts/regular.ttf", 24);
                if (font == NULL) {
                    fprintf(stderr, "error: font not found\n");
                    exit(EXIT_FAILURE);
                }
            
                SDL_Color Green = {0, 255, 0};

                // as TTF_RenderText_Solid could only be used on
                // SDL_Surface then you have to create the surface first
                snprintf(level_str,20, "level", level);
                SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, level_str, Green);
                SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
                
                SDL_Rect Message_rect;
                Message_rect.x = 100;  
                Message_rect.y = 100; 
                Message_rect.w = 250; 
                Message_rect.h = 250;
                SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

                TTF_CloseFont(font);
                SDL_FreeSurface(surfaceMessage);
                SDL_DestroyTexture(Message);

    }
*/
void make_shadows(SDL_Renderer* renderer, SDL_Rect rect, char** labyrinth, int d, int i, int j, int x, int y){

    if (d > 1 && labyrinth[x][y] =='1'){
                    
        if (labyrinth[i][j] == '1'){
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Vert
            SDL_RenderFillRect(renderer, &rect);
        }
        else{
         
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir
        SDL_RenderFillRect(renderer, &rect);
        }
    }
}