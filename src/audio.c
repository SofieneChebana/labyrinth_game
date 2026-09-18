#include <stdio.h>
#include <string.h>
#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_mixer.h"
#include "audio.h"
#include <windows.h>
#include <stdio.h>

void getExecutableDir(char* buffer, int maxLen) {
    GetModuleFileName(NULL, buffer, maxLen);

    char* lastSlash = strrchr(buffer, '\\');
    if (lastSlash) *lastSlash = '\0';
}

void walk(){

    char exeDir[512];
    getExecutableDir(exeDir, 512);

    char fullPath[512];
    sprintf(fullPath, "%s\\assets\\sounds\\walk.wav", exeDir);
    printf(fullPath);
    Mix_Chunk* sound = Mix_LoadWAV(fullPath);

    //Mix_Chunk* sound = Mix_LoadWAV("./assets/sounds/walk.wav");
    if (sound == NULL){
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    Mix_VolumeChunk(sound, MIX_MAX_VOLUME);
    /* Play on any free channel and wait until it finishes before freeing/closing
       to avoid the sound being cut off immediately. */
    int channel = Mix_PlayChannel(-1, sound, 0);
    if (channel == -1){
        printf("Failed to play sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    } else {
        while (Mix_Playing(channel)){
            SDL_Delay(50);
        }
    }

    Mix_FreeChunk(sound);
    sound = NULL;
}

void level_start(){
        

    char exeDir[512];
    getExecutableDir(exeDir, 512);

    char fullPath[512];
    sprintf(fullPath, "%s\\assets\\sounds\\start.wav", exeDir);
    printf(fullPath);
    Mix_Chunk* sound = Mix_LoadWAV(fullPath);

    //Mix_Chunk* sound = Mix_LoadWAV("./assets/sounds/start.wav");
    if (sound == NULL){
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    Mix_VolumeChunk(sound, MIX_MAX_VOLUME);
    /* Play on any free channel and wait until it finishes before freeing/closing
       to avoid the sound being cut off immediately. */
    int channel = Mix_PlayChannel(-1, sound, 0);
    if (channel == -1){
        printf("Failed to play sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    } else {
        while (Mix_Playing(channel)){
            SDL_Delay(50);
        }
    }

    Mix_FreeChunk(sound);
    sound = NULL;
        
}

void level_clear(){
    printf("Level cleared sound\n");
}