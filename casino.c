/*
 *
 * Created with Sublime Text
 * Pierre RABY
 * 21/05/2016
 *
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define winningArraySize 4
#define winningArraySize2 6

typedef struct Player Player;
struct Player {
    int balance;
    char name[256];
    short int wantToPlay;
    int bet;
    int profit;
};

typedef struct Game Game;
struct Game {
    char randomResult[3];
    Player player;
    int isGodMode;
    int mode; 	// 1 -> letter
    			// 2 -> symbol 
    int jackpot;
};

Game game;
char symbol[6] = {'B', 'D', 'E', 'S', 'A', 'P'};
char symbol2[6] = {'$', '#', '*', '!', '^', '+'};
char winningCharArray[winningArraySize][3] = {
	{'B','D','E'},
	{'B','D','S'},
	{'B','D','P'},
	{'B','D','A'}
};
char winningSymboleArray[winningArraySize2][3] = {
	{'$','$','$'},
	{'#','#','#'},
	{'!','!','!'},
	{'^','^','^'},
	{'*','*','*'},
	{'+','+','+'}
};
int winningProfitArray[winningArraySize] = {200, 100, 50, 25};
int winningProfitArray2[winningArraySize2] = {200, 100, 50, 25, 10, 5};

void clearScreen() {
	system("clear");
}

void printJackpot() {
	clearScreen();
	if(game.mode == 1) {
		printf("	 	 /$$$$$$$        /$$$$$$$        /$$$$$$$$                \n");
		printf("		| $$__  $$      | $$__  $$      | $$_____/                \n");
	    printf("	        | $$  \\ $$      | $$  \\ $$      | $$                      \n");
	    printf("	        | $$$$$$$       | $$  | $$      | $$$$$                   \n");
	    printf("	        | $$__  $$      | $$  | $$      | $$__/                   \n");
	    printf("	        | $$  \\ $$      | $$  | $$      | $$                      \n");
	    printf("	        | $$$$$$$/      | $$$$$$$/      | $$$$$$$$                \n");
	    printf("	        |_______/       |_______/       |________/                \n");
	    printf("	                                                                  \n");
	    printf("	                                                                  \n");
	    printf("	                                                                  \n");
	    printf("    /$$$$$  /$$$$$$   /$$$$$$  /$$   /$$ /$$$$$$$   /$$$$$$  /$$$$$$$$\n");
		printf("   |__  $$ /$$__  $$ /$$__  $$| $$  /$$/| $$__  $$ /$$__  $$|__  $$__/\n");
		printf("      | $$| $$  \\ $$| $$  \\__/| $$ /$$/ | $$  \\ $$| $$  \\ $$   | $$   \n");
		printf("      | $$| $$$$$$$$| $$      | $$$$$/  | $$$$$$$/| $$  | $$   | $$   \n");
		printf(" /$$  | $$| $$__  $$| $$      | $$  $$  | $$____/ | $$  | $$   | $$   \n");
		printf("| $$  | $$| $$  | $$| $$    $$| $$\\  $$ | $$      | $$  | $$   | $$   \n");
		printf("|  $$$$$$/| $$  | $$|  $$$$$$/| $$ \\  $$| $$      |  $$$$$$/   | $$   \n");
		printf(" \\______/ |__/  |__/ \\______/ |__/  \\__/|__/       \\______/    |__/   \n");
	} else {
		printf("    /$$             /$$             /$$   \n"); 
		printf("  /$$$$$$         /$$$$$$         /$$$$$$ \n");
		printf(" /$$__  $$       /$$__  $$       /$$__  $$\n");
		printf("| $$  \\__/      | $$  \\__/      | $$  \\__/\n");
		printf("|  $$$$$$       |  $$$$$$       |  $$$$$$ \n");
		printf(" \\____  $$       \\____  $$       \\____  $$\n");
		printf(" /$$  \\ $$       /$$  \\ $$       /$$  \\ $$\n");
		printf("|  $$$$$$/      |  $$$$$$/      |  $$$$$$/\n");
		printf(" \\_  $$_/        \\_  $$_/        \\_  $$_/ \n");
		printf("   \\__/            \\__/            \\__/   \n");
	}
}

void clearInputBuffer() {    
 	while(getchar() != '\n');
}

void printBlinkingJackpotFor(int seconds) {
	while(1) {
		printJackpot();
		sleep(1);
		clearScreen();
		sleep(1);
	}
}

void resetGame() {
    game.player.profit = 0;
    game.player.bet = 0;
    game.jackpot = 0;
}

void printResult() {
	if(game.isGodMode != 1)
		printf("Result: %c %c %c\n", game.randomResult[0], game.randomResult[1], game.randomResult[2]);
	printf("You bet: %d\n", game.player.bet);
	if(game.player.profit > 0) {
		if(game.jackpot == 1) {
			printJackpot();
		}
		printf("You win %d, Congratulations !\nYour new balance is %d\n", game.player.profit, game.player.balance);
	}
	else
		printf("Sorry, you lost the game bitch ! Your balance is %d\n", game.player.balance);
}

void replay() {
    printf("Do you want to continue ? (y/n)\n");
    char answer;
    //	clearInputBuffer();
    scanf("%c", &answer);
    if(answer == 'n')
        game.player.wantToPlay = 0;
    else if(game.player.balance <= 0){
    	printf("Sorry dude, your out of money !\n");
        game.player.wantToPlay = 0;
    }
    resetGame();
}

void updatePlayerBalance() {
    game.player.balance = game.player.balance+game.player.profit;
}

int getProfitFromResult(int result) {
	if(result == 0)
		game.jackpot = 0;
	if(result >= 0)
		return winningProfitArray[result]*game.player.bet;
	else
		return 0;
}

//Return player's gain or 0 if he loose
int getResult(){
    int win = 0, tmp = 0;
    if(game.mode == 1) {
    	for(int i=0; i<winningArraySize; i++){
	        if(win == 0){
	            for(int j=0; j<3; j++){
	                if(winningCharArray[i][j] == game.randomResult[j])
	                    tmp++;
	            }
	            if(tmp == 3)
	                win = 1;
	            tmp = 0;
	        } else {
	            return i;
	        }
	    }
    }
    else if(game.mode == 2) {
    	for(int i=0; i<winningArraySize2; i++){
	        if(win == 0){
	            for(int j=0; j<3; j++){
	                if(winningSymboleArray[i][j] == game.randomResult[j])
	                    tmp++;
	            }
	            if(tmp == 3)
	                win = 1;
	            tmp = 0;
	        } else {
	            return i;
	        }
        }
    }
    return -1;
}

char getRandChar(){
	if(game.mode == 1)
    	return symbol[rand()%6];
    else
    	return symbol2[rand()%6];
}

void getRandArray(){
    game.randomResult[0] = getRandChar();
    game.randomResult[1] = getRandChar();
    game.randomResult[2] = getRandChar();
}

void launchGambling() {
    getRandArray();
}

int getIntegerLesserThan(int max) {
	int number = 0;
	do{
		scanf("%d", &number);
		if(number > max || number <= 0)
			printf("Please enter a number between 1 & %d\n", max);
		clearInputBuffer();
	}while(number > max || number <= 0);
	return number;
}

void betting() {
	int betIsOk = 0;
	while(betIsOk == 0) {
	    printf("Bet: ");
	    game.player.bet = getIntegerLesserThan(3);
	    if(game.player.bet > game.player.balance) 
	    	printf("Sorry you don't have enought money, your balance is %d\n", game.player.balance);
	    else
	    	betIsOk = 1;
	}

    game.player.balance = game.player.balance-game.player.bet;
}

void newPlayer() {
    printf("Create your player !\nEnter your name: ");
    scanf("%s", game.player.name);
    printf("Enter your starting balance: ");
    scanf("%d", &game.player.balance);
    printf("Welcome %s, your balance is %d\n", game.player.name, game.player.balance);
    game.player.profit = 0;
    game.player.wantToPlay = 1;
}

void newGame() {
	game.jackpot = 0;
	printf("Choose your game mode :\n1 - Chararacter mode\n2 - Symbole mode\n");
	game.mode = getIntegerLesserThan(2);
    newPlayer();
    while(game.player.wantToPlay == 1) {
	    betting();
	    if(game.isGodMode == 1) {
	    	game.player.profit = getProfitFromResult(0);
	    }
	    else {
	    	launchGambling();
	    	game.player.profit = getProfitFromResult(getResult());
	    }
	    updatePlayerBalance();
	    printResult();
	    replay();
	}
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    if(argc > 1) {
    	if(strcmp("god_mode",argv[1]) == 0) {
    		printf("God Mode activated !\n");
    		game.isGodMode = 1;
    	} else {
    		game.isGodMode = 0;
    	}
    }
    newGame();
    return 42;
}