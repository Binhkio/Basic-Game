#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

char board[9]={' ',' ',' ',' ',' ',' ',' ',' ',' '};
int index;

void resetBoard(){
    int i;
    for(i=0;i<9;i++){
        board[i]=' ';
    }
}

void showBoard(){
    system("cls");
    printf("\n-------------\t-------------");
    printf("\n| %c | %c | %c |\t| 1 | 2 | 3 |", board[0], board[1], board[2]);
    printf("\n-------------\t-------------");
    printf("\n| %c | %c | %c |\t| 4 | 5 | 6 |", board[3], board[4], board[5]);
    printf("\n-------------\t-------------");
    printf("\n| %c | %c | %c |\t| 7 | 8 | 9 |", board[6], board[7], board[8]);
    printf("\n-------------\t-------------");
}

int checkBoard(){
    int i,n=0;
    for(i=0;i<9;i++){
        if(board[i]==' '){
            n=1;
        }
    }
    if((board[0]=='X' && board[1]=='X' && board[2]=='X') ||
        (board[3]=='X' && board[4]=='X' && board[5]=='X') ||
        (board[6]=='X' && board[7]=='X' && board[8]=='X') ||
          (board[0]=='X' && board[3]=='X' && board[6]=='X') ||
          (board[1]=='X' && board[4]=='X' && board[7]=='X') ||
          (board[2]=='X' && board[5]=='X' && board[8]=='X') ||
        (board[0]=='X' && board[4]=='X' && board[8]=='X') ||
        (board[2]=='X' && board[4]=='X' && board[6]=='X'))
    {
        return 1;
    }
    else if((board[0]=='O' && board[1]=='O' && board[2]=='O') ||
        (board[3]=='O' && board[4]=='O' && board[5]=='O') ||
        (board[6]=='O' && board[7]=='O' && board[8]=='O') ||
          (board[0]=='O' && board[3]=='O' && board[6]=='O') ||
          (board[1]=='O' && board[4]=='O' && board[7]=='O') ||
          (board[2]=='O' && board[5]=='O' && board[8]=='O') ||
        (board[0]=='O' && board[4]=='O' && board[8]=='O') ||
        (board[2]=='O' && board[4]=='O' && board[6]=='O'))
    {
        return 2;
    } 
    else if(n==0){
        return 3;
    }
    else if(n==1){
        return 0;
    }
}

int minimax(bool tf){
    int max_val=-1000, min_val=1000;
    int i,j,value=1;
    int score[9]={1,1,1,1,1,1,1,1,1};
    //check_board
    if(checkBoard()==1){return 10;}
    else if(checkBoard()==2){return -10;}
    else if(checkBoard()==3){return 0;}
    //vong lap
    for(i=0;i<9;i++){
        if(board[i]==' '){
            if(min_val>max_val){
                if(tf==true){
                    board[i]='X';
                    value= minimax(false);
                } else{
                    board[i]='O';
                    value= minimax(true);
                }
                board[i]=' ';
                score[i]=value;
            }
        }
    }
    //xet 2TH
    if(tf== true){
        max_val=-1000;
        for(j=0;j<9;j++){
            if(score[j]>max_val && score[j]!=1){
                max_val=score[j];
                index=j;
            }
        }
        return max_val;
    } else{
        min_val=1000;
        for(j=0;j<9;j++){
            if(score[j]<min_val && score[j]!=1){
                min_val=score[j];
                index=j;
            }
        }
        return min_val;
    }
}

int pvp(int player){
    char point;
    int p;
    if(player%2==0) point='X';
    else point='O';
    showBoard();
    printf("\n>> Player %d's choice: ", (player%2+1)); scanf("%d", &p);
    while(board[p-1]!=' ' || p>9 || p<1){
        printf("Choose another one !");
        printf("\n>> Player %d's choice: ", (player%2+1)); scanf("%d", &p);
    }
    board[p-1]=point; 
    showBoard(); 
    return checkBoard();
}

int pvb(){
    int i, p;
    system("cls");
    printf("\tChoose mode:\n1. Bot first\n2. You first\n>> "); scanf("%d", &i);
    if(i==1){
        board[4]='X';
        showBoard();
        printf("\nYour choice: "); scanf("%d", &p);
        while(board[p-1]!=' ' || p>9 || p<1){
            printf("Choose another one !");
            printf("\nEnter your choice again: "); scanf("%d", &p);
        }
        board[p-1]='O';
        showBoard();
    }
    else if(i==2){
        showBoard();
        printf("\nYour choice: "); scanf("%d", &p);
        while(board[p-1]!=' ' || p>9 || p<1){
            printf("Choose another one !");
            printf("\nEnter your choice again: "); scanf("%d", &p);
        }
        board[p-1]='O';
        showBoard();
    }
    while (true) //Bot now playing.....
    {
        minimax(true);
        board[index]='X';
        showBoard();
        if(checkBoard()==1 || checkBoard()==2 || checkBoard()==3){
            return checkBoard();
            break;
        }
        printf("\nYour choice: "); scanf("%d", &p);
        while(board[p-1]!=' ' || p>9 || p<1){
            printf("Choose another one !");
            printf("\nEnter your choice again: "); scanf("%d", &p);          
        }
        board[p-1]='O';
        showBoard();
    }
}

int main(){
again: system("cls");
    printf("-------Welcome to XO game-------");
    printf("\t\nCHOOSE MODE:\n1. PvP\n2. PvB\n0. Exit\n>> ");
    int choice; scanf("%d", &choice);
    int winner, player =0 ;
    switch (choice)
    {
    case 1:{// PvP
        while(winner==0){
            winner=pvp(player);
            player++;
        }
        if(winner==1){
            printf("\n>> Player 1 win the game !");
        } else if(winner==2){
            printf("\n>> Player 2 win the game !");
        } else if(winner==3){
            printf("\n>> Game draw !");
        }
        Sleep(1000);
        break;
    }
    case 2:{// PvB
        winner= pvb();
        if(winner==1){
            printf("\n>> Bot win the game !");
        } else if(winner==2){
            printf("\n>> Player 2 win the game !");
        } else if(winner==3){
            printf("\n>> Game draw !");
        }
        Sleep(1000);
    }
    case 0:
        break;
    default:{
        printf("\n*Choose 1 or 2 or 0 please !!");
        break;
    } 
    }
    
    printf("\nPress any key to exit..\n(or 0 to play again) >> ");
    int a; scanf("%d", &a);
    switch (a)
    {
    case 0:{
        resetBoard();
        goto again;
        break;
    }
    default:
        break;
    }
    return 0;
}
