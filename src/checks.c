/**
 * @file checks.c
 * @author Cantoni Letizia 882713
 * @brief This file implements all the functions that are used to check the insertion of a tile into the game
 */
#include "../include/checks.h"
#include "../include/printGraphic.h"
#include "../include/gameMove.h"

/**
 * @details Counts the possible rows in which a tile can be added on the game board.
 * That is, look at which rows are occupied by at least one tile
 * @param boardGame The game board.
 * @param numTiles The number of tiles in the game.
 * @return int Returns the number of possible rows.
 */
int possibleRows(Tile **boardGame,int numTiles){
	int res=0;
	for(int i=0; i<numTiles; i++){
		for(int j=0; j<numTiles; j++){
			 if(boardGame[i][j].occupied == 1){/**Move to the next row as soon as we find an occupied cell*/
                res++;
                break; 
            }
		}
	}
	return res;
}

/**
 * @brief Finds the possible left cell in which a tile can be add on the game board in a specific row.
 * @param boardGame The game board.
 * @param numTiles The number of tiles in the game.
 * @return int Returns the index of the possible left cell, or -1 if not found.
 */
int possibleLeftCell(Tile *boardGame, int numTiles){
    int first = -1;
    for(int i = 0; i < numTiles; i++){
        if(boardGame[i].occupied == 1){
            if(i > 0 && boardGame[i-1].occupied == 0){
                first = i-1;
                break;
            }
        }
    }
    return first;
}
/**
 * @brief Finds the possible right cell in which a tile can be add on the game board in a specific row.
 * @param boardGame The game board.
 * @param numTiles The number of tiles in the game.
 * @return int Returns the index of the possible right cell, or -1 if not found.
 */
int possibleRightCell(Tile *boardGame, int numTiles){ 
    int last = -1;
    for(int i = numTiles - 1; i >= 0; i--){
        if(boardGame[i].occupied == 1){
            if(i < numTiles - 1 && boardGame[i+1].occupied == 0){
                last = i+1;
                break;
            }
        }
    }
    return last;
}

/**
 * @brief Checks if a move is valid.
 * @param row The row to check.
 * @param col The column to check.
 * @param selectedtile The selected tile.
 * @param pos The position to check.(left 's' or right 'd')
 * @param boardGame The game board.
 * @param numTiles The number of tiles in the game.
 * @return int Returns 1 if the move is valid, 0 otherwise.
 */
int isValid (int row,int col,Tile selectedtile,char pos,Tile **boardGame,int numTiles){
	if(!boardGame[row][col].occupied){/**I check If where I want to put the tile is not occupied*/
		if(!selectedtile.vertical){/**and if the tile to insert is not vertical*/
			return isValidFlat (row,col,selectedtile,pos,boardGame,numTiles);
		}
		else if(row<numTiles && (!boardGame[row+1][col].occupied)){/**if I want to put the tile vertical I have to look that the cell below is unoccupied*/
			if (selectedtile.special){
				return 1;
			}
			if(pos=='d'){ /**If i want to put the tile right */
				if (isValidFlat (row,col,selectedtile,pos,boardGame,numTiles)){/**If the upper part of the tile can be placed */
					/**here I look to see if the tile I'm placing it next to is NOT vertical and it's compatible with my card*/
					if ((!boardGame[row+1][col-1].vertical) && ((boardGame[row+1][col-1].side2 == selectedtile.side1) || (!boardGame[row+1][col-1].side2))){
						return 1;
					}		
					/**here I look to see if the tile I'm placing it next to is vertical and it's compatible with my card*/
					if ((boardGame[row+1][col-1].vertical) && ((boardGame[row+1][col-1].side1 == selectedtile.side2) || (!boardGame[row+1][col-1].side1))){
						return 1;
					}			
				}
			}
			else{/**If i want to put the tile left */
				if(((boardGame[row][col+1].side1== selectedtile.side1) || (!boardGame[row][col+1].side1)) &&
					((boardGame[row+1][col+1].side1== selectedtile.side2) || (!boardGame[row+1][col+1].side1))){
					return 1;			
				}
				
			}	
		}
	}
	return 0;
}
/**
 * @brief Checks if a flat move is valid (flat move = the tile to insert is not vertical).
 * @param row The row to check.
 * @param col The column to check.
 * @param selectedtile The selected tile.
 * @param pos The position to check.
 * @param boardGame The game board.
 * @param numTiles The number of tiles in the game.
 * @return int Returns 1 if the move is valid, 0 otherwise.
 */
int isValidFlat (int row,int col,Tile selectedtile,char pos,Tile **boardGame,int numTiles){
	if (selectedtile.special){ /**If is special i can place it everywhere*/
		return 1;
	}
	/**If i am trying to put the tile between two other tiles */
	if((col>0 && col<numTiles) && (boardGame[row][col-1].occupied) && (boardGame[row][col+1].occupied)){
		/**all the two tile must be compatible with the one i want to insert, in this case i am trying to insert the tile vertically*/
		if((boardGame[row][col-1].vertical && ((boardGame[row][col-1].side1 == selectedtile.side1 ) || (!boardGame[row][col-1].side1)))
			&&((boardGame[row][col+1].side1 == selectedtile.side2 )||(!boardGame[row][col+1].side1)))
			return 1;
		/**all the two tile must be compatible with the one i want to insert, in this case i am trying to insert the tile horizontally*/
		else if (((!boardGame[row][col-1].vertical) && ((boardGame[row][col-1].side2 == selectedtile.side1 ) || (!boardGame[row][col-1].side2)))
			&&((boardGame[row][col+1].side1 == selectedtile.side2 )||(!boardGame[row][col+1].side1)))
			return 1;
	}
	/**If i am trying to put the tile right */
	else if(col>0 && pos=='d'){
		/**If the adjacent right tile is vertical and compatible with mine */
		if((boardGame[row][col-1].vertical)&&((boardGame[row][col-1].side1 == selectedtile.side1 )||(!(boardGame[row][col-1].side1)))) 
			return 1;
		/**If the adjacent right tile is NOT vertical and compatible with mine */	
		if((!boardGame[row][col-1].vertical)&&((boardGame[row][col-1].side2 == selectedtile.side1 )||!(boardGame[row][col-1].side2)))
			return 1;					
	}
	/**If i am trying to put the tile left*/
	else if(col<numTiles && pos=='s'){
		/**If the adjacent left tile is compatible with mine */
		if((boardGame[row][col+1].side1 == selectedtile.side2)||(!boardGame[row][col+1].side1)){
			return 1;		
		}			
	}
	return 0;
}

/**
 * @brief Checks if there are any available moves or the game is finished. is true when the game is finished.
 * @param playersTiles The player's tiles.
 * @param numTiles The number of tiles the player has.
 * @param boardGame The game board.
 * @return int Returns 1 if there are no available moves, 0 otherwise.
 */
int checkEndgame(Tile *playersTiles, int numTiles, Tile **boardGame){
    int numRow=0,row=0,coldx=0,colsx=0;
    /**  Slides all the possible tile of the player*/
    for (int i = 0; i < numTiles; i++) {
        Tile selectedTiles = playersTiles[i];
        if (selectedTiles.occupied){ /**if a tile is occupied it means that it has not yet been played*/
			numRow = possibleRows(boardGame, numTiles);
			Tile flipped=flipTile(selectedTiles);
			for (row = 0; row < numRow; row++) { /**for every 'possible' row it checks if a certain move is valid right or left*/
				coldx = possibleRightCell(boardGame[row], numTiles);
				colsx = possibleLeftCell(boardGame[row], numTiles);
				/**checks if the move is valid right or left*/
				if ((coldx != -1 && isValid(row, coldx, selectedTiles, 'd', boardGame, numTiles)) ||
					(colsx != -1 && isValid(row, colsx, selectedTiles, 's', boardGame, numTiles)) ||
					(coldx != -1 && isValid(row, coldx, flipped, 'd', boardGame, numTiles)) ||
					(colsx != -1 && isValid(row, colsx, flipped, 's', boardGame, numTiles))){
					return 0;  /**if it finds a possible move it exits*/
				}
			}
		}
    }
    /**if no moves are possible**/
    return 1;
}