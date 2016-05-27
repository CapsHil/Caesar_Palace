/*
 *
 * Created by Sublime Text
 * Pierre RABY
 * 21/05/2016
 *
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct Player Player;
struct Player {
    int balance;
    char name[256];
};

typedef struct Game Game;
struct Game {
    char result[3];
    Player player;
    short int isPlaying;
    int bet;
};

Game game;
char symbol[6] = {'x', 'o', 'y', 'v', 'w', 's'};

void newPlayer() {
    printf("Create your player !\nEnter your name: ");
    scanf("%s", game.player.name);
    printf("Enter your starting balance: ");
    scanf("%d", &game.player.balance);
}

char getRandChar(){
    return symbol[rand()%6];
}

void getRandArrayFrom(){
    game.result[0] = getRandChar();
    game.result[1] = getRandChar();
    game.result[2] = getRandChar();
}

void betting() {
    printf("Bet: ");
    scanf("%d", &game.bet);
}


//Return player's gain or 0 if he loose
int checkResult(char winningArray[6][6]){
    int win = 0, tmp = 0;
    for(int i=0; i<6; i++){
        if(win == 0){
            for(int j=0; j<3; j++){
                if(winningArray[i][j] == game.result[j])
                    tmp++;
            }
            if(tmp == 3)
                win = 1;
            tmp = 0;
        } else
            return i;
    }
    return 0;
}

void newGame() {
    newPlayer();
    game.isPlaying = 1;
    betting();
}

int main() {
    srand(time(NULL));
    newGame();
    //int bet = 0;
    //scanf("%d", &bet);
    //betting(bet, player);
    //getRandArrayFrom(result);
    printf("%s: %d\n", game.player.name, game.player.balance);
    return 42;
}
