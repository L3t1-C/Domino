/**
 * @file gameMove.h
 * @author Cantoni Letizia 882713
 * @brief This file defines all the functions that are used to move and insert the tiles in the game.
 */
#ifndef GAME_MOVE_H
#define GAME_MOVE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tile.h"
#include "printGraphic.h"
#include "userInputs.h"
#include "checks.h"
#include "gameInteractive.h"
#include "gameAi.h"


void swapTiles(Tile *tile1, Tile *tile2);/**Function to swap two tiles.*/
void removePlayerTile(Tile *playersTiles,int numTiles,int choice);/**Removes a choosen tile from the player's tiles. */
Tile flipTile(Tile d);/**Flips a tile: flips the number of side1 with the number of side2. */
int scoreTile(Tile tile);/**Calculate the  score of a tile which is the sum of side1+side2 of the tile */
int countScore(Tile **boardGame, int numTiles);/**Counts the total score of the tiles on the game board.  */
int countTiles(Tile *playersTiles, int numTiles);/**Counts the number of tiles the player has left to play.*/
void addTile(Tile d, int row, int col,Tile **boardGame,int numTiles);/**Adds the chosen tile to the game board. */
void gameStart(Tile *playersTiles,int numTiles,Tile **boardGame);/**Initial function to start the game. */
void free_game(Tile **boardGame, int numTiles);/**Frees the memory allocated for the game board. */

#endif 
