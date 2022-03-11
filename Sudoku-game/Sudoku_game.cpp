#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

char a[9][9]; //a[row][column] array of '.'
char x[9][9]; //array of answer...
int level, STEP=1;


void reset(){
    int i,j;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            a[i][j]='.';
            x[i][j]='.';
        }
    }
}
void showBoard(){
    system("cls");
    printf("\n\t>>>>>>   SUDOKU GAME   <<<<<<");
    printf("\n\t  C 1 2 3   4 5 6   7 8 9");
    printf("\n\tR -------------------------");
    printf("\n\t1 | %c %c %c | %c %c %c | %c %c %c |",a[0][0],a[0][1],a[0][2],a[0][3],a[0][4],a[0][5],a[0][6],a[0][7],a[0][8]);
    printf("\n\t2 | %c %c %c | %c %c %c | %c %c %c |",a[1][0],a[1][1],a[1][2],a[1][3],a[1][4],a[1][5],a[1][6],a[1][7],a[1][8]);
    printf("\n\t3 | %c %c %c | %c %c %c | %c %c %c |",a[2][0],a[2][1],a[2][2],a[2][3],a[2][4],a[2][5],a[2][6],a[2][7],a[2][8]);
    printf("\n\t  -------------------------");/////////////////////////////////////////////////////////////////////////////////
    printf("\n\t4 | %c %c %c | %c %c %c | %c %c %c |",a[3][0],a[3][1],a[3][2],a[3][3],a[3][4],a[3][5],a[3][6],a[3][7],a[3][8]);
    printf("\n\t5 | %c %c %c | %c %c %c | %c %c %c |",a[4][0],a[4][1],a[4][2],a[4][3],a[4][4],a[4][5],a[4][6],a[4][7],a[4][8]);
    printf("\n\t6 | %c %c %c | %c %c %c | %c %c %c |",a[5][0],a[5][1],a[5][2],a[5][3],a[5][4],a[5][5],a[5][6],a[5][7],a[5][8]);
    printf("\n\t  -------------------------");/////////////////////////////////////////////////////////////////////////////////
    printf("\n\t7 | %c %c %c | %c %c %c | %c %c %c |",a[6][0],a[6][1],a[6][2],a[6][3],a[6][4],a[6][5],a[6][6],a[6][7],a[6][8]);
    printf("\n\t8 | %c %c %c | %c %c %c | %c %c %c |",a[7][0],a[7][1],a[7][2],a[7][3],a[7][4],a[7][5],a[7][6],a[7][7],a[7][8]);
    printf("\n\t9 | %c %c %c | %c %c %c | %c %c %c |",a[8][0],a[8][1],a[8][2],a[8][3],a[8][4],a[8][5],a[8][6],a[8][7],a[8][8]);
    printf("\n\t  -------------------------\n");///////////////////////////////////////////////////////////////////////////////

}
int checkBoard(int row, int column){
    if(a[row][column]==x[row][column]) return 1;
    else return 0;
}
void congrate(){
    printf("\n\n\tCongratulations !! You won the game (UwU)");
    printf("\n         ------------------------------------------------");
}
void playGame(){
    int row, column;
    char value;
    showBoard();
    printf("\n");
chooseRC: fflush(stdin);
    printf("  Choose the cell (row,column):\n\t>> "); scanf("%d%d",&row,&column);
    if((row<1||row>9) || (column<1||column>9)) goto chooseRC;
chooseV: fflush(stdin);
    printf("  Choose the value (1~9 and 0 to exit):\n\t>> "); scanf("%c",&value);
    if(value=='0') goto end;
    if(value<'1'||value>'9') goto chooseV;
    row--; column--;
    a[row][column]=value;
    if( checkBoard(row,column) == 1 ){
        printf("\n>> Correct answer !!");
        STEP++;
        if(STEP==81) congrate();
        fflush(stdin); getch();
        playGame();
    } else {
        a[row][column]='.';
        printf("\n>> Incorrect answer !! We'll delete your last answer.");
        fflush(stdin); getch();
        playGame();
    }
    end: fflush(stdin);
    printf("\n --- Thanks for playing!! --- "); Sleep(1500);
}
void showMenu(){
    system("cls");
    printf(" ----- SUDOKU GAME -----\n");
    printf(" 1. New game\n 2. How to play\n 3. Exit\n>> ");
}
void howtoplay(){
    system("cls");
    printf(" ---- HOW TO PLAY ----"); 
    printf("\n 1 - Choose the cell to fill by typing:\n\tNumber of row _ space _ Number of column");
    printf("\n 2 - Then write down the value (1~9) that you want.");
    printf("\n (If you write more than 1 number, we just take the first one)");
    printf("\n 3 - You can write '0' in value to stop and exit the game.");
    printf("\n----- Good luck!! ----- ");
    fflush(stdin); getch();
}

//Thuat toan tim bang SUDOKU
void saveSolution(){
    int i,numOfHints;
    if(level==1) numOfHints=50;
    else if(level==2) numOfHints=35;
    else if(level==3) numOfHints=20;
    else if(level==4) numOfHints=10;
    STEP+=numOfHints;
    for(i=0;i<numOfHints;i++){
        int r=rand()%9;
        int c=rand()%9;
        if(a[r][c]!='.'){
            i--;
            continue;
        } else{
            a[r][c]=x[r][c];
        }
    }
}
bool check(char v, int r, int c)
{
    for (int i = 0; i <= r - 1; i++)
        if (x[i][c] == v)
            return false;
    for (int j = 0; j <= c - 1; j++)
        if (x[r][j] == v)
            return false;
    int I = r / 3;
    int J = c / 3;
    int i = r - 3 * I;
    int j = c - 3 * J;
    int i1, j1;
    for (i1 = 0; i1 <= i - 1; i1++)
        for (int j1 = 0; j1 <= 2; j1++)
            if (x[3 * I + i1][3 * J + j1] == v)
                return false;
    for (j1 = 0; j1 <= j - 1; j1++)
        if (x[3 * I + i][3 * J + j1] == v)
            return false;
    return true;
}
void createBoard(int row, int column){
    char value;
    for(value='1';value<='9';value++){
        if(check(value,row,column)){
            x[row][column]=value;
            if(row==8 && column==8){
                saveSolution();
                playGame();
            } else{
                if(column==8) createBoard(row+1,0);
                else createBoard(row,column+1);
            }
        }
    }
}


int main(){
    int choice;
    while (choice!=3)
    {
    begin: showMenu();
        fflush(stdin); scanf("%d",&choice);
        switch (choice)
        {
        case 1:{
            system("cls");
        lv: printf("\tCHOOSE LEVEL\n 1. Easy\n 2. Normal\n 3. Hard\n 4. Ultra Hard\n>> "); scanf("%d",&level);
            if(level<1 || level>4) goto lv;
            reset();
            srand((char) time(0));
        //Khoi tao 3 gia tri dau tien ngau nhien
            x[0][0]=rand()%9+49;
            x[0][1]=rand()%9+49;
            while(x[0][1]==x[0][0]) x[0][1]=rand()%9+49;
            x[0][2]=rand()%9+49;
            while(x[0][2]==x[0][0]) x[0][2]=rand()%9+49;
        //---------------------------------------
            createBoard(0,3);
            break;
        }
        case 2:{
            howtoplay();
            break;
        }
        case 3:{
            printf(" --- Thanks for playing!! --- ");
            fflush(stdin); getch();
            break;
        }
        default:
            goto begin;
        }
    }
    return 0;
}