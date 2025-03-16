/**
 * @file main.c
 * @author Cantoni Letizia 882713
 * @brief This project implements the Domino Game with it's own set of rules
 * @date 24/06/2024
 */
#include <stdio.h>

#include "include/tile.h"
#include "include/userInputs.h"
#include "include/printGraphic.h"
#include "include/gameMove.h"
#include "include/gameInteractive.h"
#include "include/gameAi.h"
#include "include/checks.h"

/**
 * @details Initial function to start the game, in which the game structures are defined and initialized 
 * @return int
 */

int main(){	
	int numTiles=0,playAgain=0; 
    Tile **boardGame= NULL;
    Tile *playersTiles = NULL;
    Tile specialTiles[3];

    /** print the first screen of the game, just for graphic*/
	printFirstScreen();
    /** Wait 2 seconds*/
	delay(2); 
    do
    {
        numTiles=getTilesNumber();
        /** Initialization of special tiles */
        initializationSpecialTiles(specialTiles,3);
        /** Initialization of player tiles */
        playersTiles=initializationPlayerTiles(numTiles,specialTiles);
        /** Board game initialization */
        boardGame=initializationBoard(numTiles);
        if (boardGame == NULL || playersTiles == NULL) {
            printf("Error: Allocazione memoria fallita!\n");
            return 1; 
        }
        /**Function to start the game*/
        gameStart(playersTiles,numTiles,boardGame);
        /**Print the 'game over' screen and return if the player wants to play again*/
		playAgain = endScreen();
        /**Frees the memory allocated*/
        free_game(boardGame,numTiles);
        free(playersTiles);

    } while (playAgain==1);
    
    
    return 0;
}    

