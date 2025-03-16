/**
 * @file userInputs.c
 * @author Cantoni Letizia 882713
 * @brief This file implements all the functions that are used to get the user's input to make the moves in the game
 */
#include "../include/userInputs.h"

/**
 * @brief Asks the player with how many tiles he wants to play with.
 * @return int return the user's choice of tiles number he wants to play with.
 */
int getTilesNumber(){
    int choice=0;
    do {
        printf("\033[1;1H\033[2J");
        printf("\nCon quante tessere vuoi giocare?\n\x1b[1;35m");
        printf("Puoi scegliere da 6 a 12 tessere\x1b[0m \n");
        if((scanf(" %d", &choice)!= 1)||(choice< 6 || choice > 12)){
            printf("\x1b[1;31mInput non valido. Scegli fra le opzioni 6-7-8-9-10-11-12");printf("\033(b\033[m \n");
            while (getchar() != '\n'); // Pulizia del buffer di input
            choice = 0; // Reset the choice
        }
    } while (choice< 6 || choice > 12);
    return choice;
}
/**
 * @brief Displays the game mode menu and returns the user's choice of game mode.(Singleplayer,AI or Game Rules)
 * @return int return the user's choice of game mode.
 */
int getMenuMode(){
    int choice=0;
    do {
        printf("\033[1;1H\033[2J");
        printf("\nIn Che modalità vuoi giocare?\n\x1b[1;35m");
        printf("1. Giocatore singolo \n");
        printf("2. Modalità AI \n");
        printf("3. Regole - Informazioni aggiuntive \x1b[0m \n");
        
        if((scanf(" %d", &choice) != 1) || (choice<1 || choice > 3)){
            printf("\x1b[1;31mInput non valido. Scegli fra le opzioni 1-2-3");printf("\033(b\033[m \n");
            while (getchar() != '\n'); /** clean the input buffer  */
            choice = 0; /** Reset the choice*/ 
        }
    } while (choice != 1 && choice != 2 && choice != 3);
    
    return choice;
}
/**
 * @brief Asks the player and then returns the tile to play chosen by the player.
 * @param currenTiles The current number of tiles.
 * @return int Returns the chosen tile.
 */
int getMoveTiles(int currenTiles){
	int choice=0;
	do{
		printf("\nQuale tessera vuoi selezionare?(1-%d)\n",currenTiles);
		if ((scanf(" %d",&choice) != 1)||(choice<1 || choice>currenTiles)){
            printf("\x1b[1;31mInput non valido. Scegli una tessera tra quelle indicate.");printf("\033(b\033[m \n");
            while (getchar() != '\n');  /** clean the input buffer  */
            continue;
        }
	}while(choice<1||choice>currenTiles);
	return choice;
}
/**
 * @brief Asks and returns the action that the player wants to do with the chosen tile.
 * for example flip it, put it vertical, confirm or exit
 * @return char Returns the chosen action.
 */
char getOrientation(){
	char selection=' ';
	do {
		printf("\nChe mossa vuoi fare?\x1b[1;35m f=flip\x1b[0m,\x1b[1;35m v=vertical\x1b[0m,\x1b[1;35m c=conferma\x1b[0m,\x1b[1;35m a=annulla\x1b[0m\n");
        if ((scanf(" %c", &selection) != 1)||(selection != 'f' && selection != 'v' && selection != 'c' && selection != 'a')) {
			printf("\x1b[1;31mInput non valido. scegli fra le mosse elencate");printf("\033(b\033[m \n");
            while (getchar() != '\n'); /** clean the input buffer  */
            continue;
		}
	} while (selection != 'f' && selection != 'v' && selection != 'c' && selection != 'a');
	return selection;
}
/**
 * @brief Asks and returns the row where the player wants to insert the tile.
 * @param numRows The number of rows.
 * @return int Returns the chosen row.
 */
int getRow(int numRows){
	int row=0;
	do {
        printf("\nDove vuoi inserire la tessera?\nRIGA: 1 - %d.\n", numRows);
        if ((scanf(" %d", &row) != 1) ||(row < 1 || row > numRows)) {
            printf("\x1b[1;31mInput non valido. Inserisci un numero compreso tra 1 e %d.", numRows);printf("\033(b\033[m \n");
            while (getchar() != '\n'); /** clean the input buffer  */
            continue;
        }
    }while(row < 1 || row > numRows);
    row = row - 1;
	return row;
}
/**
 * @brief Asks and returns the position where the player wants to insert the tile. (right or left)
 * @param numTiles The number of tiles.
 * @return char Returns the chosen position.
 */
char getPosition(int numTiles) {
    char pos=' ';
    while (pos!= 'd' && pos != 's'){
        printf("\nDove vuoi inserire la tessera? DESTRA (d) oppure SINISTRA (s) \n");
        if ((scanf(" %c", &pos) != 1)||(pos != 'd' && pos != 's')) {
            printf("\x1b[1;31mInput non valido per la posizione. Inserisci d per destra s per sinistra");printf("\033(b\033[m \n");
            while (getchar() != '\n'); /** clean the input buffer  */
            continue;
        }
        while (getchar() != '\n');
    }
    return pos;
}
