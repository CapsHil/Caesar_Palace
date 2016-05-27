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
    char*  name;
};

char symbol[6] = {'x', 'o', 'y', 'v', 'w', 's'};
char result[3] = {0};
Player player;

Player newPlayer(char* name, int balance) {
    Player joueur;
    joueur.balance = balance;
    joueur.name = name;
    return joueur;
}

char getRandChar(){
    return symbol[rand()%6];
}

void getRandArrayFrom(char *result){
    result[0] = getRandChar();
    result[1] = getRandChar();
    result[2] = getRandChar();
}

void betting(int bet, Player player) {
    //player.bet = bet;
}


//Return player's gain or 0 if he loose
int checkResult(char winningArray[6][6], char result[3]){
    int win = 0, tmp = 0;
    for(int i=0; i<6; i++){
        if(win == 0){
            for(int j=0; j<3; j++){
                if(winningArray[i][j] == result[j])
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



int main() {
    srand(time(NULL));
    player = newPlayer("Pierre", 1000);
    int bet = 0;
    scanf("%d", &bet);
    betting(bet, player);
    getRandArrayFrom(result);
    printf("%s: %d", player.name, player.balance);
    return 42;
}
