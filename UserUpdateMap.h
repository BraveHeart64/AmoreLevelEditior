#include "Platforms.h"
int landmass;
int enemey;
int player;

void UserUpdateMap(int x, int y,struct Platforms p);

int DetermineLandMass(int landtype);
void RenderGameMap(int x , int y, struct Platforms p);
int gamelevel[20][80];
// int gamelevel[10][60];
