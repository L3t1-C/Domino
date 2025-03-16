/**
 * @file tile.h
 * @author Cantoni Letizia 882713
 * @brief This file defines the game structures and the functions that initialize the player tiles and the boardgame
 */
#ifndef TILE_H
#define TILE_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/** 
 * @details Tile is the chosen structure to represent the tile in the game
 * side1 is the number left in the tile and side2 is the number right [side1|side2] [2|6]
 * occupied is used to mark a tile not yet played in the player tiles, And in the board game it mark a tile that is the board.
 * vertical is used to see if a tile is vertical [2] or using the graphic in the boardgame: {2}
 *                                               [6]                                        {6}
 * special is used to see if the tile is special, like [0|0] or [11|11] or [12|21]
 */
typedef struct {
    int side1; 
    int side2;
    int occupied;
    int vertical;
    int special;
} Tile;

Tile **initializationBoard(int numTiles);/**Initializes the game board.*/
Tile *initializationPlayerTiles(int numTiles,Tile *specialTiles);/**Initializes the player's tiles. */
void initializationSpecialTiles(Tile *specialTiles, int numSpecial);/**Initializes the special tiles*/

#endif 