/**
 * @file gameInteractive.h
 * @author Cantoni Letizia 882713
 * @brief This file defines all the functions that are used to play in the Interactive game mode.
 */
#ifndef GAME_INTERACTIVE_H
#define GAME_INTERACTIVE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tile.h"
#include "printGraphic.h"
#include "userInputs.h"
#include "checks.h"

void makeMove(Tile selectedTiles,int numTiles,Tile **boardGame, int choice,Tile *playersTiles);/**Function to get the input from the player to where insert the tile.*/
void tileOrientation(int choice,Tile selectedTiles,Tile *playersTiles,int numTiles,Tile **boardGame, int first);/**Given a tile, take the input of the player to whether to flip it, put it vertical,confirm or exit. */
void gameStartInteractive(Tile *playersTiles,int numTiles,Tile **boardGame);/**Initial function to choose the tile. */


#endif 