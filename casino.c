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
    int solde;
    int bet;
    char*  name;
};

Player newPlayer(char* name, int solde) {
    Player joueur;
    joueur.solde = solde;
    joueur.name = name;
    return joueur;
}

char getRandCharFrom(char symbol[6]){
    return symbol[rand()%6];
}

void getRandArrayFrom(char symbol[6], char *result){
    result[0] = getRandCharFrom(symbol);
    result[1] = getRandCharFrom(symbol);
    result[2] = getRandCharFrom(symbol);
}

void bet(int bet, Player player) {
    player.bet = bet;
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
    char symbol[6] = {'x', 'o', 'y', 'v', 'w', 's'};
    char result[3] = {0};
    Player player = newPlayer("Pierre", 1000);
    int bet = 0;
    scanf("%d", *bet);
    bet(bet, player);
    getRandArrayFrom(symbol, result);
    return 42;
}
