#include <stdio.h>
#include <stdbool.h>
#include <memory.h>
#define MAXSIZE 10000

int tournament[MAXSIZE+1][MAXSIZE+1];


void newTournament(int index, int newPlayer, int level, int size){
    tournament[level][index] = newPlayer;
    if(size <= 1)
        return;
    
    int competitor = index % 2 == 1 ? index - 1 : index + 1;
    
    if (competitor < 0 || competitor >= size){
        if(size % 2 == 1)
            newTournament(index/2, tournament[level][index], level+1, size / 2 + 1);
        else
            newTournament(index/2, tournament[level][index], level+1, size / 2);
    }
    else if (newPlayer == -1){
        if(size % 2 == 1)
            newTournament(index/2, tournament[level][competitor], level+1, size / 2 + 1);
        else
            newTournament(index/2, tournament[level][competitor], level+1, size / 2);
    }
    else if (tournament[level][competitor] == -1){
        if(size % 2 == 1)
            newTournament(index/2, tournament[level][index], level+1, size / 2 + 1);
        else
            newTournament(index/2, tournament[level][index], level+1, size / 2);
    }
    
    else if(COMPARE(tournament[level][competitor], tournament[level][index]) == 1){
        if(size % 2 == 1)
            newTournament(index/2, tournament[level][competitor], level+1, size / 2 + 1);
        else
            newTournament(index/2, tournament[level][competitor], level+1, size / 2);
    }
    else{
        if(size % 2 == 1)
            newTournament(index/2, tournament[level][index], level+1, size / 2 + 1);
        else
            newTournament(index/2, tournament[level][index], level+1, size / 2);
    }
    
}

int beginTournament(int level, int size){
    if(size % 2 == 0){
        for(int i = 0; i+1 < size; i+=2){
            tournament[level+1][i/2] = COMPARE(tournament[level][i], tournament[level][i+1]) == 1 ? tournament[level][i] : tournament[level][i+1];
        }
        return size / 2;
    }
    else{
        for(int i = 0; i+1 < size; i+=2){
            tournament[level+1][i/2] = COMPARE(tournament[level][i], tournament[level][i+1]) == 1 ? tournament[level][i] : tournament[level][i+1];
        }
        tournament[level+1][size / 2] = tournament[level][size-1];
        return size/ 2 + 1;
    }
}

int doalg(int n, int k, int Best[]){

    if(n < 10 || n > 10000 || k > 100 || k < 1)
        return 0;
    for(int i = 0; i < n; i++)
        tournament[0][i] = i+1;

    
    int size = n-k+1; //n;
    int level = 0;
    
    for(; level < n; level++){
        size = beginTournament(level, size);
        if(size <= 1){
            level += 1;
            break;
        }
    }
    /*
    int winner = tournament[level][0];
    int index = 0;
    for(int i = 0; i < k; i++){
        winner = tournament[level][0];
        Best[i] = winner;
        index = 0;
        while(tournament[0][index] != winner)
            index += 1;
        newTournament(index, -1, 0, n);
    }*/

    int winner = tournament[level][0];
    int index = 0;
    for(int i = 0; i < k-1; i++){
        winner = tournament[level][0];

        if(winner >= n-k+1+i){
            int j = i - 1;
            while(j >= 0 && COMPARE(winner, Best[j]) == 1){
                Best[j+1] = Best[j];
                j --;
            }
            Best[j+1] = winner;
        }
        else
            Best[i] = winner;

        index = 0;
        while(tournament[0][index] != winner)
            index += 1;

        newTournament(index, tournament[0][n-k+1+i], 0, n-k+1);
    }
    
    winner = tournament[level][0];
    if(winner >= n-1){
        int j = k - 2;
        while(j >= 0 && COMPARE(winner, Best[j]) == 1){
            Best[j+1] = Best[j];
            j --;
        }
        Best[j+1] = winner;
    }
    else
        Best[k-1] = winner;


    return 1;
}

