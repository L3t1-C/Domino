/**
 * @file gameAi.c
 * @author Cantoni Letizia 882713
 * @brief This file implements all the functions that are used to play the game in AI mode. 
 */
#include "../include/gameAi.h"
#include "../include/checks.h"
#include "../include/gameMove.h"
#include "../include/printGraphic.h"

/**
 * @brief Function to sort the player tiles based on their score (es.[3|2] has a score=5).
 * @param tiles The array of tiles to sort(the player tiles).
 * @param numTiles The number of tiles available to the AI.
 */
void sortTiles(Tile *tiles, int numTiles) {
    for (int i = 0; i < numTiles - 1; i++) {
        for (int j = 0; j < numTiles - i - 1; j++) {
            if (scoreTile(tiles[j]) < scoreTile(tiles[j + 1])) {
                swapTiles(&tiles[j], &tiles[j + 1]);
            }
        }
    }
	/**  Move special tiles to the second position so it's likely it mirrores the tile with the highest score*/
    for (int i = 0; i < numTiles; i++) {
        if (tiles[i].special) {
            swapTiles(&tiles[i], &tiles[1]);
            break;
        }
    }
}

/**
 * @brief Function to make a move for the AI.
 * @param choice The index of the tile chosen by the AI.
 * @param selectedTiles The tile chosen by the AI.
 * @param playersTiles The array of tiles available to the AI.
 * @param numTiles The number of tiles available to the AI.
 * @param boardGame The current state of the game board.
 * @return int Returns 1 if the move was successful, 0 otherwise.
 */
int MoveAi(int choice, Tile selectedTiles, Tile *playersTiles, int numTiles, Tile **boardGame) {
	srand(time(NULL));  /**Initialize the random number generator with the current time*/
    int vertical = rand() % 5;/**Generates a random number between 0 and 4 that give us a probability of 80% that is != 0*/
    int numRow = possibleRows(boardGame, numTiles);/**Possible row where to insert the tile*/
	Tile flipped=flipTile(selectedTiles);
	/**I will try for every row if there is a match*/
    for (int row = 0; row < numRow; row++) {
        int coldx = possibleRightCell(boardGame[row], numTiles);/**Possible right column where to insert the tile*/
        int colsx = possibleLeftCell(boardGame[row], numTiles);/**Possible left column where to insert the tile*/
        /**If there is a possible right cell*/ 
        if (coldx!= -1 && colsx== -1){
			if(vertical){/**If the randon number is !=0 the vertical is true, so we try to place it vertical*/ 
				selectedTiles.vertical=1;
				/**If the moveis not valid with the vertical tile, we try with the horizonal tile*/ 
				if((!isValid (row,coldx,selectedTiles,'d',boardGame,numTiles)) && (!isValid (row,coldx,flipped,'d',boardGame,numTiles)))
					selectedTiles.vertical=0;
			}
			/**if the move is valid we add it*/
			if (isValid (row,coldx,selectedTiles,'d',boardGame,numTiles)) {
				addTile(selectedTiles, row, coldx, boardGame, numTiles);
				removePlayerTile(playersTiles, numTiles, choice);
				return 1;
			}
			/**else we try with the flipped tile and if the move is valid we add it*/
			else if (isValid (row,coldx,flipped,'d',boardGame,numTiles)) {
				addTile(flipped, row, coldx, boardGame, numTiles);
				removePlayerTile(playersTiles, numTiles, choice);
				return 1;
			}
        }
        /**If there is a possible left cell*/ 
        if (colsx!= -1 && coldx== -1){
			if(vertical){ /**If the randon number is !=0 the vertical is true, so we try to place it vertical*/ 
				selectedTiles.vertical=1;
				/**If the move is not valid with the vertical tile, we try with the horizonal tile*/ 
				if((!isValid (row,colsx,selectedTiles,'s',boardGame,numTiles)) && (!isValid (row,colsx,flipped,'s',boardGame,numTiles)))
					selectedTiles.vertical=0;
			}
			/**if the move is valid we add it*/
			if (isValid (row,colsx,selectedTiles,'s',boardGame,numTiles)) {
				addTile(selectedTiles, row, colsx, boardGame, numTiles);
				removePlayerTile(playersTiles, numTiles, choice);
				return 1;
			}
			/**else we try with the flipped tile and if the move is valid we add it*/
			else if (isValid (row,colsx,flipped,'s',boardGame,numTiles)) {
				addTile(flipped, row, colsx, boardGame, numTiles);
				removePlayerTile(playersTiles, numTiles, choice);
				return 1;
			}
        }
		/**If there is a possible right AND left cell*/ 
        if (coldx!= -1 && colsx!= -1) {
			if(vertical){
				selectedTiles.vertical=1;
				/**If the move is not valid on either left or right with the vertical tile, we try with the horizonal tile*/ 
				if((!isValid (row,colsx,selectedTiles,'s',boardGame,numTiles)) && (!isValid (row,colsx,flipped,'s',boardGame,numTiles)) && 
				(!isValid (row,coldx,selectedTiles,'d',boardGame,numTiles) && (!isValid (row,coldx,flipped,'d',boardGame,numTiles))))
					selectedTiles.vertical=0;
			}
			/**if the move is valid left we add it*/
			if (isValid (row,colsx,selectedTiles,'s',boardGame,numTiles)) {
				addTile(selectedTiles, row, colsx, boardGame, numTiles);
				removePlayerTile(playersTiles, numTiles, choice);
				return 1;
			}
			/**else if the move is valid with the flipped tile left we add it*/
			else if (isValid (row,colsx,flipped,'s',boardGame,numTiles)) {
				addTile(flipped, row, colsx, boardGame, numTiles);
				removePlayerTile(playersTiles, numTiles, choice);
				return 1;
			}
			/**if the move is valid right we add it*/
			else if (isValid (row,coldx,selectedTiles,'d',boardGame,numTiles)) {
				addTile(selectedTiles, row, coldx, boardGame, numTiles);
				removePlayerTile(playersTiles, numTiles, choice);
				return 1;
			}
			/**else if the move is valid with the flipped tile right we add it*/
			else if (isValid (row,coldx,flipped,'d',boardGame,numTiles)) {
				addTile(flipped, row, coldx, boardGame, numTiles);
				removePlayerTile(playersTiles, numTiles, choice);
				return 1;
			}
        }
    }
    return 0;
}

/**
 * @brief Initial function for the AI to choose a tile.
 * @param playersTiles The array of tiles available to the AI.
 * @param numTiles The number of tiles available to the AI.
 * @param boardGame The current state of the game board.
 */
void gameStartAi(Tile *playersTiles,int numTiles,Tile **boardGame){
	int i=0,resultOp=0;
	printBoardGame(boardGame,numTiles); 
    printTilesPlayer(playersTiles, numTiles); 
	delay(1);
	/**it sorts the tiles so the first match you find is the one with the highest score*/
	sortTiles(playersTiles,numTiles);
	addTile(playersTiles[0],0,0,boardGame,numTiles);
	removePlayerTile(playersTiles,numTiles,0);
	
	do{	
		i = 0;
		while (i < numTiles) {
			if (playersTiles[i].occupied) {/**if the tile is not already played*/
				printBoardGame(boardGame,numTiles); 
				printTilesPlayer(playersTiles, numTiles);
				printSelectedTiles(playersTiles[i]);
				resultOp=MoveAi(i,playersTiles[i],playersTiles,numTiles,boardGame);
				if(!resultOp) /**if the tile was not inserted i carry on*/
					i++;
				else{/**else i wait just for the user to see the move and then i start checking the tiles from the start*/
					delay(1);
					i=0;
				}
			}
			else {/**if the tile has already been played i go to the next*/
        		i++; 
    		}
		}
		if(checkEndgame(playersTiles, numTiles, boardGame)){/**if there are no avaiable moves exit*/
			break;
		}
	}while (countTiles(playersTiles, numTiles) > 0 && i<numTiles);
	
	printBoardGame(boardGame,numTiles);
	/**if all the tiles have been played print the phrase below else print the remaining tiles*/
	if(countTiles(playersTiles,numTiles)==0){
		printf("\n\x1b[1;36mTutte le tessere sono state inserite!");printf("\033(b\033[m \n");
	}else{
		printTilesPlayer(playersTiles, numTiles);
	}
	delay(1);
	printf("\n\x1b[1;33m:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	printf("\x1b[1;32m PUNTEGGIO TOTALIZZATO: %d\n",countScore(boardGame,numTiles)); 
	
}
