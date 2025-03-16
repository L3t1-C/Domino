/**
 * @file gameAi.h
 * @author Cantoni Letizia 882713
 * @brief This file defines the functions that are used to play the game in AI mode. 
 */
#ifndef GAME_AI_H
#define GAME_AI_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gameMove.h"
#include "checks.h"
#include "printGraphic.h"

void sortTiles(Tile *tiles, int numTiles);/**Function to sort the player tiles based on their score (es.[3|2] has a score=5). */
int MoveAi(int choice,Tile selectedTiles,Tile *playersTiles,int numTiles,Tile **boardGame);/**Function to make a move for the AI. */
void gameStartAi(Tile *playersTiles,int numTiles,Tile **boardGame);/**Initial function for the AI to choose a tile. */

#endif 
