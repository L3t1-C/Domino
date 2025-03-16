/**
 * @file userInputs.h
 * @author Cantoni Letizia 882713
 * @brief This file defines the functions that are used to get the user's input to make the moves in the game
 */

#ifndef USERINPUTS_H
#define USERINPUTS_H
#include <stdio.h>
#include <stdlib.h>

int getTilesNumber(); /**Returns the player's choice of tiles number he wants to play with. */
int getMenuMode(); /**Returns the player's choice of game mode he want to play in Singleplayer,AI or view the Game Rules */
int getMoveTiles(int currenTiles);/**Returns the tile to play chosen by the player. */
char getOrientation();/**Returns the action that the player wants to do with the chosen tile. flip it, put it vertical,confirm or exit*/
int getRow(int numRows);/**Returns the row where the player wants to insert the tile.*/
char getPosition(int numTiles);/**Returns the position where the player wants to insert the tile. (right or left) */

#endif 