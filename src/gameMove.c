/**
 * @file gameMove.c
 * @author Cantoni Letizia 882713
 * @brief This file implements the functions used to move and insert the tiles in the game
 */

#include "../include/gameMove.h"
#include "../include/tile.h"
#include "../include/printGraphic.h"
#include "../include/userInputs.h"
#include "../include/checks.h"

/**
 * @brief Function to swap two tiles.
 * @param tile1 The tile to swap.
 * @param tile2 The other tile to swap.
 */
void swapTiles(Tile *tile1, Tile *tile2) {
    Tile temp = *tile1;
    *tile1 = *tile2;
    *tile2 = temp;
}

/**
 * @brief Removes a choosen tile from the player's tiles.
 * @param playersTiles The player's tiles.
 * @param numTiles The number of tiles the player has.
 * @param choice The index of the tile to remove.
 */
void removePlayerTile(Tile *playersTiles,int numTiles,int choice){
    for (int i = choice; i < numTiles - 1; i++) {
        swapTiles(&playersTiles[i], &playersTiles[i + 1]);
    }
	playersTiles[numTiles - 1].occupied=0;
	playersTiles[numTiles - 1].special=0;
}

/**
 * @brief Flips a tile: flips the number of side1 with the number of side2.
 * @param d The tile to flip.
 * @return Tile Returns the flipped tile.
 */
Tile flipTile(Tile d){
	Tile swapped = d;	
    swapped.side1 = d.side2; 
    swapped.side2 = d.side1;
    return swapped; 
}
/**
 * @brief Calculate the  score of a tile which is the sum of side1+side2 of the tile
 * @param tile The tile to calculate the score.
 * @return int Returns the score of the tile.
 */
int scoreTile(Tile tile) {
    return tile.side1 + tile.side2;
}

/**
 * @brief Counts the total score of the tiles on the game board.
 * @param boardGame The game board.
 * @param numTiles The number of tiles in the game.
 * @return int Returns the total score in the board.
 */
int countScore(Tile **boardGame, int numTiles){
	int res=0;
	for (int i = 0; i < numTiles; i++) {
		for (int j = 0; j < numTiles; j++) 
			res+=scoreTile(boardGame[i][j]); 
	}
	return res;
}
/**
 * @brief Counts the number of tiles the player has left to play.
 * @param playersTiles The player's tiles.
 * @param numTiles The number of tiles the player has.
 * @return int Returns the number of tiles left.
 */
int countTiles(Tile *playersTiles, int numTiles){
	int res=0;
	for (int i = 0; i < numTiles; i++) {
		if(playersTiles[i].occupied){
			res++;
		}
	}
	return res;
}

/**
 * @brief Adds the chosen tile to the game board.
 * @param d The chosen tile.
 * @param row The row to insert the tile.
 * @param col The column to insert the tile.
 * @param boardGame The game board.
 * @param numTiles The number of tiles in the game.
 */
void addTile(Tile d, int row, int col,Tile **boardGame,int numTiles){
	boardGame[row][col]=d;/**Add the tile to the board*/
	/** Handle special tiles*/
	if(d.special && d.side1 != 0 && d.side2 != 0){
		/** Check if the tile is adjacent to another tile left*/
		if (col > 0 && boardGame[row][col - 1].occupied) {
			boardGame[row][col].side1 = boardGame[row][col - 1].side2;/**Insert the tile mirroring the left tile */
			boardGame[row][col].side2 = boardGame[row][col - 1].side1;
			/** Check if the tile to insert is vertical and if the tile left below is free*/
			if(d.vertical && (row < numTiles) && (!boardGame[row+1][col - 1].occupied)){ 
				/**Insert the tile below(vertical) copying the left tile up */
				boardGame[row + 1][col] = d;
				boardGame[row + 1][col].side1 = boardGame[row][col - 1].side1;
				boardGame[row + 1][col].side2 = boardGame[row][col - 1].side2;
			}
			else if((d.vertical) && (row < numTiles) && (boardGame[row+1][col - 1].occupied)){
				/**Insert the tile below(vertical) copying the adjacent left tile */
				boardGame[row + 1][col]= d;
				boardGame[row + 1][col].side1 = boardGame[row + 1][col - 1].side2;
				boardGame[row + 1][col].side2 = boardGame[row + 1][col - 1].side1;
			}
			/** if the adjacent tile is vertical i need to flip the tile, otherwhise it will be:
			 *  [2]{3} instead of  [2]{2}
			 *  [3]{2}             [3]{3}
			*/
			if(boardGame[row][col - 1].vertical){
				boardGame[row][col]=flipTile(boardGame[row][col]);
				boardGame[row+1][col]=flipTile(boardGame[row+1][col]);
			}
		} 
		/**Check if the tile is adjacent to another tile right*/
		else if (col < numTiles  && boardGame[row][col + 1].occupied) {
			boardGame[row][col].side1 = boardGame[row][col + 1].side2;/**Insert the tile mirroring the right tile */
			boardGame[row][col].side2 = boardGame[row][col + 1].side1;
			/** Check if the tile to insert is vertical and if the tile right below is free*/
			if((d.vertical) && (row < numTiles) && (!boardGame[row+1][col + 1].occupied)){
				/**Insert the tile below(vertical) copying the right tile up */
				boardGame[row + 1][col]= d;
				boardGame[row + 1][col].side1 = boardGame[row][col + 1].side1;
				boardGame[row + 1][col].side2 = boardGame[row][col + 1].side2;
			}
			else if((d.vertical) && (row < numTiles) && (boardGame[row+1][col + 1].occupied)){
				/**Insert the tile below(vertical) copying the adjacent right tile */
				boardGame[row + 1][col]= d;
				boardGame[row + 1][col].side1 = boardGame[row + 1][col + 1].side2;
				boardGame[row + 1][col].side2 = boardGame[row + 1][col + 1].side1;
			}
			/** if the adjacent tile is vertical i need to flip the tile, otherwhise it will be:
			 *  {3}[2] instead of  [2]{2}
			 *  {2}[3]             [3]{3}
			*/
			if(d.vertical){
				boardGame[row][col]=flipTile(boardGame[row][col]);
				boardGame[row + 1][col]=flipTile(boardGame[row+1][col]);
			}
		}
		/** Special tile [11|11] Increment digits of all tiles by 1, except 6 which becomes 1*/
		if (d.side1 == 11 && d.side2 == 11) {
			for (int i = 0; i < numTiles; i++) {
				for (int j = 0; j < numTiles; j++) {
					if (boardGame[i][j].occupied) {
						boardGame[i][j].side1= (boardGame[i][j].side1 % 6)+1;
						boardGame[i][j].side2= (boardGame[i][j].side2 % 6)+1;
					}
				}
			}
		}
	}
	else{/** if the tile is not special and is vertical Add the tile also to the next row*/
		if(d.vertical){
			boardGame[row+1][col]= d;
			boardGame[row+1][col].side1=d.side2;
			boardGame[row+1][col].side2=d.side1;
		}
	}
}
/**
 * @brief Initial function to choose the game mode and start the game.
 * @param playersTiles The player's tiles.
 * @param numTiles The number of tiles in the game.
 * @param boardGame The game board.
 */
void gameStart(Tile *playersTiles,int numTiles,Tile **boardGame){
	int mode=0;
	/** Loop to decide the game mode, it's a loop because that way if the user decides
     *  to read the rules then he can always go back and decide what mode to play. 
     */
	do {
		mode = getMenuMode();
		if(mode == 1){
			/** Start of the game in single-player mode*/
			gameStartInteractive(playersTiles, numTiles, boardGame);
		}
		else if(mode == 2){
			/** Start of the game in AI mode*/
			gameStartAi(playersTiles, numTiles, boardGame);
		}
		else{
			/** Printing of the Information-Rules*/
			show_rules();
		}
	}while (mode == 3);
	
}

/**
 * @brief Frees the memory allocated for the game board.
 * @param boardGame The game board.
 * @param numTiles The number of tiles in the game.
 */
void free_game(Tile **boardGame, int numTiles){
	for (int i = 0; i < numTiles; i++) {
        free(boardGame[i]);
    }
    free(boardGame);
}
