/**
 * @file gameInteractive.c
 * @author Cantoni Letizia 882713
 * @brief This file implements the functions used to play the game in the Interactive Mode
 */

#include "../include/gameInteractive.h"
#include "../include/tile.h"
#include "../include/gameMove.h"
#include "../include/printGraphic.h"
#include "../include/userInputs.h"
#include "../include/checks.h"


/**
 * @brief Function to get the input from the player to where insert the tile.
 * @param selectedTiles The tile selected ti insert.
 * @param numTiles The number of tiles in the game.
 * @param boardGame The game board.
 * @param choice The chosen tile.
 * @param playersTiles The player's tiles.
 */
void makeMove(Tile selectedTiles,int numTiles,Tile **boardGame, int choice,Tile *playersTiles){
	int numRow=0,row=0,col=0;
	char pos=' ';
	printBoardGame(boardGame,numTiles); 
	printSelectedTiles(selectedTiles);
	numRow=possibleRows(boardGame,numTiles);/**the number of the row a tile can be placed */
	if(numRow>1){/** if the number of rows>1 asks the player which row he wants to put it in*/
		row=getRow(numRow);
		printBoardGame(boardGame,numTiles); 
		printSelectedTiles(selectedTiles);
	}
	pos=getPosition(numTiles);/** Ask the player where he wants to put the tile, left or right*/
	if(pos=='d')
		col=possibleRightCell(boardGame[row],numTiles);/**retrieve the right column where to put the tile*/
	else
		col=possibleLeftCell(boardGame[row],numTiles);/**retrieve the left column where to put the tile*/

	if(col!=-1){ /**if there is a column for the move*/
		if(isValid (row,col,selectedTiles,pos,boardGame,numTiles)){/**if the move is valid*/
			addTile(selectedTiles,row,col,boardGame,numTiles);/**makes the move*/
			removePlayerTile(playersTiles,numTiles,choice);
		}
		else{ 
			printf("\x1b[1;31m");printf("Mossa non Valida!\n");printf("\033(b\033[m");delay(1);
		}
	}
	else{ 
		printf("\x1b[1;31m");printf("Mossa non Valida!\n");printf("\033(b\033[m");delay(1);
	}
}

/**
 * @brief Given a tile, take the input of the player to whether to flip it, put it vertical,confirm or exit.
 * @param choice The chosen tile.
 * @param selectedTiles The selected tile.
 * @param playersTiles The player's tiles.
 * @param numTiles The number of tiles in the game.
 * @param boardGame The game board.
 * @param first Whether it's the first move.
 */
void tileOrientation(int choice,Tile selectedTiles,Tile *playersTiles,int numTiles,Tile **boardGame,int first){
	char selection=' ';
	do{
		printBoardGame(boardGame,numTiles); 
		printSelectedTiles(selectedTiles);
		selection=getOrientation(); /**choose what to do with the tile: flip it, put it vertical, confirm or exit*/
		if(selection=='f'){
			selectedTiles=flipTile(selectedTiles);
		}
		if(selection=='v'){
			selectedTiles.vertical=1;
		}
	}while(selection!='c' && selection!='a');
	if(selection=='c'){
		if(first){
			addTile(selectedTiles,0,0,boardGame,numTiles);
			removePlayerTile(playersTiles,numTiles,choice);
		}
		else{
			makeMove(selectedTiles,numTiles,boardGame,choice,playersTiles);/**if confirmed go to makeMove*/
		}
	}
	else{
		printf("\x1b[1;31m");printf("Operazione annullata!\n");printf("\033(b\033[m");
	}
}

/**
 * @brief Initial function to choose the tile (interactive mode).
 * @param playersTiles The player's tiles.
 * @param numTiles The number of tiles in the game.
 * @param boardGame The game board.
 */
void gameStartInteractive(Tile *playersTiles,int numTiles,Tile **boardGame){
	int choice=0,tilesNumber=0;

	printBoardGame(boardGame,numTiles); 
    printTilesPlayer(playersTiles, numTiles);   
	/**Get the tile the player wants to play*/
	choice=getMoveTiles(numTiles);
	/**This happens only for the first move*/
	while(playersTiles[choice-1].special && playersTiles[choice-1].side1!=0){
		/**The special tiles [11|11] and [12|21] cannot be placed in the first position*/
		printf("\x1b[1;31m");printf("Mossa non Valida, questa tessera speciale non può essere inserita lì!\n");printf("\033(b\033[m");
		delay(1);
		choice=getMoveTiles(tilesNumber);
	}
	tileOrientation(choice-1,playersTiles[choice-1],playersTiles,numTiles,boardGame,1);
	do
	{
		tilesNumber=countTiles(playersTiles,numTiles);
		printBoardGame(boardGame,numTiles); 
		printTilesPlayer(playersTiles, numTiles);   
		/**Get the tile the player wants to play*/
		choice=getMoveTiles(tilesNumber);
		tileOrientation(choice-1,playersTiles[choice-1],playersTiles,numTiles,boardGame,0);
	} while (!checkEndgame(playersTiles, numTiles, boardGame));

	printBoardGame(boardGame,numTiles); 
	if(countTiles(playersTiles,numTiles)==0){/**If all the tiles have been inserted print */
		printf("\n\x1b[1;36mTutte le tessere sono state inserite!");printf("\033(b\033[m \n");
	}
	else{
		printTilesPlayer(playersTiles, numTiles);/**else print the remaining tiles*/
	}
	delay(1);
	printf("\n\x1b[1;33m:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	printf("\x1b[1;32m PUNTEGGIO TOTALIZZATO: %d\n",countScore(boardGame,numTiles));  
}