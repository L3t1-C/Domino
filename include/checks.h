/**
 * @file checks.h
 * @author Cantoni Letizia 882713
 * @brief This file defines the functions that are used to check the insertion of a tile into the game
 */
#ifndef CHECKS_H
#define CHECKS_H
#include <stdio.h>
#include <stdlib.h>
#include "tile.h"
#include "gameMove.h"

int possibleRows(Tile **boardGame,int numTiles);/**Counts the possible rows in which a tile can be added on the game board. */
int possibleLeftCell(Tile *boardGame, int numTiles);/**Finds the possible left cell in which a tile can be add on the game board in a specific row. */
int possibleRightCell(Tile *boardGame, int numTiles);/**Finds the possible right cell in which a tile can be add on the game board in a specific row. */
int isValid (int row,int col,Tile selectedtile,char pos,Tile **boardGame,int numTiles);/**Checks if a move is valid. */
int isValidFlat (int row,int col,Tile selectedtile,char pos,Tile **boardGame,int numTiles);/**Checks if a flat move is valid (flat move = the tile to insert is not vertical). */
int checkEndgame(Tile *playersTiles, int numTiles, Tile **boardGame);/**Checks if there are any available moves or the game is finished. */

#endif