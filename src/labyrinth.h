#include <stdio.h>
#include <stdlib.h>

char** init_labyrinth();

void load_level(char** labyrinth, char* level);

int* find_player(char** labyrinth);

int* find_goal(char** labyrinth);

char ask_direction();

void move(char** labyrinth, char direction);

int distance( int x1, int y1, int x2, int y2);

void play();
