/**
 * @file tile.c
 * @author Cantoni Letizia 882713
 * @brief This file implements all the functions that initialize the player tiles (with the special tiles) and the boardgame
 */
#include "../include/tile.h"
#define SPECIAL_TILE_1_SIDE1 11
#define SPECIAL_TILE_1_SIDE2 11
#define SPECIAL_TILE_2_SIDE1 12
#define SPECIAL_TILE_2_SIDE2 21

/**
 * @brief Initializes the game board.
 * @param numTiles The number of tiles in the game. used to create the 'matrix' of boardgame
 * @return Tile** Returns the initialized  board game.
 */
Tile **initializationBoard(int numTiles){
	int numCols=numTiles;
    int numRows = numTiles + 1; /**if a vertical tile is added on the last row */
	/**  Allocate memory for rows array */
	Tile **boardGame = malloc(numRows * sizeof(Tile *));
	if (boardGame == NULL) {
		printf("Allocazione memoria fallita!\n");
        return NULL;
    }
	for (int i = 0; i < numRows; i++) {
		/**Allocate memory for each column in the current row*/
		boardGame[i] = malloc(numCols * sizeof(Tile));
		if (boardGame[i] == NULL) {
			printf("Allocazione memoria fallita!\n");
        	return NULL;
		}
		for (int j = 0; j < numCols; j++) {
			boardGame[i][j].side1 = 0;
            boardGame[i][j].side2 = 0;
            boardGame[i][j].occupied = 0; 
            boardGame[i][j].vertical = 0;
            boardGame[i][j].special = 0;
		}
	}
	return boardGame;
}

/**
 * @brief Initializes the player's tiles.
 * @param numTiles The number of tiles the player has.
 * @param specialTiles The array of special tiles in the game.
 * @return Tile* Returns the initialized  player's Tiles.
 */
Tile *initializationPlayerTiles(int numTiles,Tile *specialTiles){	
	int randVar=0,randTileIndex=0;
	srand(time(NULL));  /**Initialize the random number generator with the current time*/
	Tile * playersTiles = malloc(numTiles * sizeof(Tile));
	if (playersTiles == NULL) {
		printf("Allocazione memoria fallita!\n");
        return NULL;
    }
	randVar=rand() % 10; /**Generates a random number between 0 and 9*/
	if(randVar!=1){ /**90% chance of randVar being different from 1*/
		randTileIndex = rand() % 3; /**Generates a random index between 0 and 2*/
       	playersTiles[numTiles-1] = specialTiles[randTileIndex];
		numTiles=numTiles-1;
	}
		
	for (int i = 0; i < numTiles; i++) {
		playersTiles[i].side1 = rand() % 6 + 1;  /**Generate a casual number from 1 to 6*/
		playersTiles[i].side2 = rand() % 6 + 1;
		playersTiles[i].occupied=1;
		playersTiles[i].vertical=0;
		playersTiles[i].special = 0;
	}
	return playersTiles;
}
/**
 * @brief Initializes the special tiles.
 * @param specialTiles The special tiles to initialize. Tile *
 * @param numSpecial The number of special tiles.
 * @return Tile* Returns the initialized special tiles.
 */
void initializationSpecialTiles(Tile *specialTiles, int numSpecial) {
    for (int i = 0; i < numSpecial; i++) {
        specialTiles[i].side1 = 0;
        specialTiles[i].side2 = 0;
        specialTiles[i].occupied = 1;
        specialTiles[i].vertical = 0;
        specialTiles[i].special = 1;
    }
    specialTiles[1].side1 = SPECIAL_TILE_1_SIDE1;
    specialTiles[1].side2 = SPECIAL_TILE_1_SIDE2;
    specialTiles[2].side1 = SPECIAL_TILE_2_SIDE1;
    specialTiles[2].side2 = SPECIAL_TILE_2_SIDE2;
}
