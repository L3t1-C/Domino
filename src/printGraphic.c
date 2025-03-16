
/**
 * @file printGraphic.c
 * @author Cantoni Letizia 882713
 * @brief This file implements all the functions that are used to display the game implementation
 */
#include "../include/printGraphic.h"
#include "../include/gameMove.h"

/**
 * @brief Delays the execution for a specified number of seconds.
 * @param seconds The number of seconds to delay.
 */
//https://cplusplus.com/reference/ctime/?kw=time.h
void delay(int seconds){
	clock_t start = clock();
	while(clock()/CLOCKS_PER_SEC<((start/CLOCKS_PER_SEC)+seconds));
}

/**
 * @brief Prints the first screen of the game. Just the title of the game
 */
void printFirstScreen(){
    printf("\033[1;1H\033[2J");
	printf("\x1b[1;32m");/**Color green*/
	printf("\n");
   	printf(" ______   _______  __   __  ___   __    _  _______           \n"); 
    printf("|      | |       ||  |_|  ||   | |  |  | ||       |          \n");
    printf("|  _    ||   _   ||       ||   | |   |_| ||   _   |          \n");
    printf("| | |   ||  | |  ||       ||   | |       ||  | |  |          \n");
    printf("| |_|   ||  |_|  ||       ||   | |  _    ||  |_|  |          \n");
    printf("|       ||       || ||_|| ||   | | | |   ||       |          \n");
    printf("|______| |_______||_|   |_||___| |_|  |__||_______|          \n");
	printf("\x1b[1;34m"); /**Color blue*/
    printf(" ___      ___   __    _  _______  _______  ______    _______ \n");
    printf("|   |    |   | |  |  | ||       ||   _   ||    _ |  |       |\n");
    printf("|   |    |   | |   |_| ||    ___||  |_|  ||   | ||  |    ___|\n");
    printf("|   |    |   | |       ||   |___ |       ||   |_||_ |   |___ \n");
    printf("|   |___ |   | |  _    ||    ___||       ||    __  ||    ___|\n");
    printf("|       ||   | | | |   ||   |___ |   _   ||   |  | ||   |___ \n");
    printf("|_______||___| |_|  |__||_______||__| |__||___|  |_||_______|\n");
	printf("\033(b\033[m");/**reset color*/
	printf("\033[3m");/**cursive*/
	printf("\n882713 Cantoni Letizia\n");
	printf("\033(b\033[m");/**reset color*/
}
/**
 * @brief Prints this screen when the game is over. and asks if the player wants to play again.
 * @return int Returns 1 if the player wants to play another game.
 */
int endScreen(){
    int playAgain=0;
    printf("\x1b[1;33m:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf(" _______  _______  __   __  _______    _______  __   __  _______  ______      \n"); 
    printf("|       ||   _   ||  |_|  ||       |  |       ||  | |  ||       ||    _ |     \n");
    printf("|    ___||  |_|  ||       ||    ___|  |   _   ||  |_|  ||    ___||   | ||     \n");
    printf("|   | __ |       ||       ||   |___   |  | |  ||       ||   |___ |   |_||_    \n");
    printf("|   ||  ||       ||       ||    ___|  |  |_|  ||       ||    ___||    __  |   \n");
    printf("|   |_| ||   _   || ||_|| ||   |___   |       | |     | |   |___ |   |  | |   \n");
    printf("|_______||__| |__||_|   |_||_______|  |_______|  |___|  |_______||___|  |_|   \n");
    printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\033(b\033[m");
    printf("\n");
    
    printf("Vuoi giocare di nuovo? (1 = sì, 2 = no): ");
    do {
    if (scanf("%d", &playAgain) != 1 || (playAgain != 1 && playAgain != 2)) {
        printf("\x1b[1;31mInput non valido. Scegli fra (1 = sì, 2 = no)"); printf("\033(b\033[m \n");
        while (getchar() != '\n'); // clean buffer
    }
    } while (playAgain != 1 && playAgain != 2 );

    return playAgain;
}

/**
 * @brief Displays the game rules.
 */
void show_rules() {
    printf("\033[1;1H\033[2J");printf("\x1b[1;31m"); 
    printf("  _                                                   \n"); 
    printf(" |_)  _   _   _  |  _     _|  _  |    _  o  _   _  _  \n"); 
    printf(" | | (/_ (_| (_) | (/_   (_| (/_ |   (_| | (_) (_ (_) \n"); 
    printf("          _|                          _|              \n"); 
    printf("\033(b\033[m\n");

    printf("\x1b[1;32m"); printf("\nModalità Interattiva:"); printf("\033(b\033[m\n");
    printf("1. La tessera iniziale verrà posizionata di default sul piano di gioco.\n");
    printf("2. Quando posizioni la tessera non puoi posizionarla al di fuori del piano di gioco.\n");
    printf("3. Una tessera (ad eccezione di quella iniziale) dev'essere posizionata per forza vicino ad un'altra tessera.\n");
    printf("4.Lo sviluppo del gioco può avvenire sia a destra che a sinistra ma soltanto agli estremi delle tessere occupate in quella riga e dall’alto in basso.\n");
    printf("\x1b[1;32m"); printf("\nTessere Speciali:"); printf("\033(b\033[m\n");
    printf("Nelle tue tessere ad ogni partita ti potrà capitare al 90 percento di avere fra le tue tessere una speciale:\n");
    printf("[0|0]: Può essere accostata a qualunque altra tessera\n");
    printf("[11|11]: Somma 1 a tutte le cifre di tutte le tessere sul piano di gioco tranne il 6 che diventa 1. \n");
    printf("[12|21]: Copia “a specchio” la tessera adiacente,le sue cifre vegono sostituite con quelle della tessera adiacente in ordine inverso. \n");
    printf("Le tessere speciali possono essere posizionate in qualunque posizione ");
    printf("PERO' le tessere [11|11] e [12|21] dovranno per forza essere accostare ad un'altra tessera per attivare il loro funzionamento.\n");
    printf("Quindi le tessere [11|11] e [12|21] NON potranno essere utilizzate come tessera iniziale.\n");

    printf("\x1b[1;32m");printf("\nModalità AI");printf("\033(b\033[m\n");
    printf("Questa modalità interattiva posiziona la prima tessera che abbia un match nel piano di gioco\nIn aggiunta con una probabilità del 50 percento le tessere potranno anche essere messe in verticale.");
    
    printf("\nPremi il tasto Invio per uscire\n");

    getchar();  /**wait for the player to press a button*/
    while (getchar() != '\n'); /**  clean input buffer */
}


/**
 * @brief Prints a tile. [side1|dide2] 
 * @param d The tile to print.
 */
void printTiles(Tile d) {
	if(d.special==1)
		printf("\x1b[1;33m");
    if(!d.vertical) {
        printf("[%d|%d]", d.side1, d.side2);
    } else {
        printf("{ %d }", d.side1);
    }
	printf("\033(b\033[m");
}

/**
 * @brief Prints the tile selected by the player. in this function the vertical tile is printed differently from printTiles
 * @param d The selected tile.
 */
void printSelectedTiles(Tile d) {
	printf("Tessera selezionata:\n");
	if(d.special==1)
		printf("\x1b[1;33m");
    if(d.vertical == 0) {
        printf("[%d|%d]", d.side1, d.side2);
    } else {
        printf("[%d]\n[%d]", d.side1, d.side2);
    }
	printf("\033(b\033[m\n");
}

/**
 * @brief Prints the player's tiles.
 * @param playersTiles The player's tiles.
 * @param numTiles The number of tiles the player has.
 */
void printTilesPlayer(Tile *playersTiles, int numTiles){
	int num = countTiles(playersTiles, numTiles);
	printf("Tessere Giocatore:\n");
    for (int j = 0; j < num; j++) {
        printf(" %2d  ", j + 1);
    }
    printf("\n");
    for (int i = 0; i < numTiles; i++) {
        if(playersTiles[i].occupied) /**here if a tile is occupied(not already played) it is displayed*/
            printTiles(playersTiles[i]);
    }    
    printf("\n");
}

/**
 * @brief Prints the game board with all the tiles in the game.
 * @param boardGame The game board.
 * @param numTiles The number of tiles in the game.
 */
void printBoardGame(Tile **boardGame, int numTiles){
    printf("\033[1;1H\033[2J");
    for (int j = 0; j < numTiles; j++) { /**this is just for graphic*/
		if(j == numTiles / 2)
			printf("BOARD");
		else
			printf("     ");
	}
	printf("\n***");
    for (int j = 0; j < numTiles; j++) { /**this is just for graphic*/
        printf("*****");
    }
    printf("\n");
    
    for (int i = 0; i < numTiles+1 ; i++) {
        if(i!=numTiles)
		    printf("\x1b[1;32m%2d \033(b\033[m", i + 1);/**prints the number of the rows */
        else
            printf("   ");
        
        for (int j = 0; j < numTiles; j++) { 
            if (!(boardGame[i][j].occupied))/**if a cell of the boardgame is not occupied it print the equivalent of the tile but in spaces*/
                printf("     ");
            else
                printTiles(boardGame[i][j]);/**else if the cell is ocuupied it prints the tile who is in it*/
        }
        printf("\n");
    }
    
    printf("***");
    for (int j = 0; j < numTiles; j++) { /**this is just for graphic*/
        printf("*****");
    }
    printf("\n");
    printf("\x1b[1;36m IL TUO PUNTEGGIO: %d\n",countScore(boardGame,numTiles)); /**here it prints the score= the sum of all the tile score in the game*/
    printf("\033(b\033[m***");
    for (int j = 0; j < numTiles; j++) { /**this is just for graphic*/
        printf("*****");
    }
    printf("\n");
}