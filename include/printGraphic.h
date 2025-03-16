/**
 * @file printGraphic.h
 * @author Cantoni Letizia 882713
 * @brief This file defines functions that are used to display the game implementation
 */
#ifndef PRINT_GRAPHIC_H
#define PRINT_GRAPHIC_H
#include <stdio.h>
#include <stdlib.h>
#include "tile.h"
#include "gameMove.h"

void delay(int seconds);/**Delays the execution for a specified number of seconds. */
void printFirstScreen();/**Prints the first screen of the game. Just the title of the game*/
int endScreen();/**Prints the end screen of the game and returns if the player wants to play again. */
void show_rules();/**Displays the game rules. */
void printTiles(Tile d);/**Prints a tile. [side1|dide2] */
void printSelectedTiles(Tile d);/**Prints a tile but in this function the vertical tile is printed differently from printTiles */
void printTilesPlayer(Tile *playersTiles, int numTiles);/**Prints the player's tiles. */
void printBoardGame(Tile **boardGame, int numTiles);/**Prints the game board with all the tiles in the game. */

#endif 
