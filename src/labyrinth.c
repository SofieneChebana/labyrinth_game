#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "labyrinth.h"


#define WIDTH 76
#define HEIGTH 75

char** init_labyrinth(){
    char** labyrinth = malloc(HEIGTH * (sizeof(char*) ) );
    for(int i=0 ; i<HEIGTH; i++){
        labyrinth[i] = malloc(WIDTH * (sizeof(char*)));
    }
    return labyrinth;
}

void load_level(char** labyrinth,char* level){
    FILE* file = fopen(level,"r");
    if(file == NULL){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char ch;
    int i=0;
    int j=0;
    while((ch=fgetc(file)) !=EOF){
        
        if(j==WIDTH - 1 && i<HEIGTH - 1){
            j = 0;
            i++;
        }
        else{
            j++;
        }
        labyrinth[i][j] = ch;

    }
    fclose(file);
} 

int* find_player(char** labyrinth){
    int* player = (int*)malloc(2*sizeof(int));
    for (int i=0;i<HEIGTH;i++){
        for(int j=0;j<WIDTH;j++){
            if(labyrinth[i][j]=='x'){
                player[0] = i;
                player[1] = j;                
                return player;
            }
        }
    }
    free(player);
    return NULL;
}

int* find_goal(char** labyrinth){
    int* goal = malloc(2*sizeof(int));

    for (int i=0;i<HEIGTH;i++){
        for(int j=0;j<WIDTH;j++){
            if(labyrinth[i][j]=='1'){
                goal[0] = i;
                goal[1] = j;              
                return goal;
            }
        }
    }
    free(goal);
    return NULL;
}

char ask_direction(){
    char direction;
    printf("choose a direction : ");
    fflush(stdout);
    scanf("%c",&direction);
    return direction;
}

void move(char** labyrinth, char direction){
    int* player = find_player(labyrinth);
    int row = player[0];
    int col = player[1];
    free(player);
    
    fflush(stdout);
    

    if(direction == 'u'){
        if(labyrinth[row-1][col]!='|'){
            labyrinth[row][col] =' ';
            labyrinth[row-1][col] = 'x';
        }
    }
    if(direction == 'd'){
        if(labyrinth[row+1][col]!='|'){
            labyrinth[row][col] =' ';
            labyrinth[row+1][col] = 'x';
        }
    }
    if(direction == 'l'){
        if(labyrinth[row][col-1]!='|'){
            labyrinth[row][col] =' ';
            labyrinth[row][col-1] = 'x';
        }
    }
    if(direction == 'r'){
        if(labyrinth[row][col+1]!='|'){
            labyrinth[row][col] =' ';
            labyrinth[row][col+1] = 'x';
        }
    }

}

int distance(int x1, int y1, int x2, int y2 ){
    
    return (int) sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}


