#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COMPUTER 1
#define HUMAN 2
#define SIDE 3
#define COMPUTERMOVE  'O'
#define HUMANMOVE 'X'

struct move{
int row,col;
};

char player = 'x',opponent =  'o';

bool ismovesleft(char board[3][3]) {
    for (int i = 0; i< 3; i++)
      for (int j = 0; j<3; j++ )
          if (board[i][j]=='_')
              return true;
    return false;
}

int evaluate(char b[3][3]) {
    for (int row = 0; row < 3; row++) {
        if (b[row][0]== b[row][1] && b[row][1] == b[row][2]){
        if (b[row][0] == player)
            return +10;
        else if (b[row][0] == opponent)
            return -10;
    }
    }
    for (int col = 0; col<3; col++) {
        if (b[0][col] == b[1][col]
            && b[1][col] == b[2][col]) {
            if (b[0][col] == player)
                return +10;
            else if (b[0][col] == opponent)
                return -10;
        }
    }
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        if (b[0][0] == player)
            return +10;
        else if (b[0][0] == opponent)
            return -10;
    }
    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == player)
            return +10;
        else if (b[0][2] == opponent)
            return -10;
    }
    return 0;
}

int minimax (char board[3][3],int depth, bool ismax) {
    int score = evaluate(board);
    if (score == 10)
        return score;
    if (score == -10)
        return score;

    if (ismovesleft(board)==false)
        return 0;

    if (ismax) {
        int best = -1000;

        for (int i=0; i<3; i++) {
            for (int j =0; j<3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = player;
                    int val = minimax(board,depth+1,!ismax);
                    if (val >   best) {
                        best = val;
                    }
                    board[i][j]='_';
                }
            }
        }
        return best;
    }
    else {
        int best = 1000;
        for (int i =0; i<3; i++) {
            for (int j =0; j<3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = opponent;

                    int val =  minimax(board,depth+1,!ismax);
                    if (val < best) {
                        best = val;
                    }
                    board[i][j]='_';
                }
            }
        }
        return best;
    }
}

struct move findbestmove(char board[3][3]) {
    int bestval = -1000;
    struct move bestmove;
    bestmove.row = -1;
    bestmove.col = -1;

    for (int i =0; i<3; i++) {
        for (int j =0; j<3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = player;
                int moveval = minimax(board,0,false);
                board[i][j] = '_';
                if (moveval > bestval) {
                    bestmove.row = i;
                    bestmove.col = j;
                    bestval = moveval;
                }
            }
        }
    }
    return bestmove;
}

void showboard(char board[][SIDE]) {
    printf("\n\n");
    printf("\t\t\t %c | %c | %c \n",board[0][0],board[0][1],board[0][2]);
    printf("\t\t\t--------------------\n");
    printf("\t\t\t %c | %c | %c \n",board[1][0],board[1][1],board[1][2]);
    printf("\t\t\t--------------------\n");
    printf("\t\t\t %c | %c | %c \n",board[2][0],board[2][1],board[2][2]);

}

void showinstructions() {
    printf("\t\t\t Tic-Tac-Toe\n\n");
    printf("Hamle yapmak icin 1-9 arasi bir sayi seciniz\n\n");

    printf("\t\t\t 1 | 2 | 3 \n");
    printf("\t\t\t--------------\n");
    printf("\t\t\t 4 | 5 | 6 \n");
    printf("\t\t\t--------------\n");
    printf("\t\t\t 7 | 8 | 9 \n\n");

    printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");
}
void initialise(char board[0][SIDE],int moves[]) {
    srand(time(NULL));
    for (int i = 0; i<SIDE; i++) {
        for (int j = 0; j<SIDE; j++ )
            board[i][j] = ' ';

        }
        for (int i = 0; i<SIDE*SIDE; i++)
            moves[i]=i;

        for (int i =0; i<SIDE*SIDE; i++) {
            int randIndex = rand() % (SIDE*SIDE);
            int temp = moves[i];
            moves[i] = moves[randIndex];
            moves[randIndex] = temp;
        }
    }

void declarewinner(int whoseturn) {
    if (whoseturn == COMPUTER)
        printf("Bilgisiyar kazandi\n");
    else
        printf("İnsan kazandi\n");
}

int rowcrossed(char board[][SIDE]) {
    for (int i = 0; i<SIDE; i++) {
        if (board[i][0]== board[i][1] && board[i][1]== board[i][2] && board[i][0] != ' ')
            return 1;
    }
    return 0;
}

int columcrossed(char board[][SIDE]) {
    for (int i = 0; i<SIDE; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return 1;
    }
    return 0;
}
int diagonalcrossed(char board[][SIDE])
{
    if ((board[0][0] == board[1][1]
         && board[1][1] == board[2][2]
         && board[0][0] != ' ')
        || (board[0][2] == board[1][1]
            && board[1][1] == board[2][0]
            && board[0][2] != ' '))
        return 1;

    return 0;
}

int gameover(char board[][SIDE]) {
    return (rowcrossed(board) || columcrossed(board) || diagonalcrossed(board));

}

void playtictactoe(int whoseturn) {
    char board[SIDE][SIDE];
    int moves[SIDE*SIDE];
    initialise(board,moves);
    showinstructions();

    int moveIndex =0,x,y;
    while (!gameover(board) && moveIndex !=  SIDE*SIDE) {
        if (whoseturn == COMPUTER) {
            char  tempboard[3][3];
            for (int i = 0; i<3; i++) {
                for (int j = 0; j<3; j++) {
                    if (board[i][j] == 'X') {
                        tempboard[i][j] = 'x';
                    }
                    else if (board[i][j] == 'O') {
                        tempboard[i][j] = 'o';
                    }
                    else {
                        tempboard[i][j] = '_';
                    }
                }
            }
            struct move thismove = findbestmove(tempboard);
            x = thismove.row;
            y = thismove.col;
            board[x][y] = COMPUTERMOVE;
            printf("Bilgisiyar %d %d hucresine %c koydu\n",x,y,COMPUTERMOVE);
            showboard(board);
            moveIndex++;
            whoseturn = HUMAN;
        }
        else  if (whoseturn == HUMAN) {
            int move;
            printf("Hamle giriniz (1-9):");
            scanf("%d",&move);
            if (move  < 1 || move  > 9) {
                printf("Gecersiz bir hamle girdiniz  hamle 1-9 hucreleri arasinda olmalidir..\n");
                continue;
            }
            x = (move-1) / SIDE;
            y =  (move-1) % SIDE;
            if (board[x][y] == ' ') {
                board[x][y] = HUMANMOVE;
                showboard(board);
                moveIndex++;
                if (gameover(board)) {
                    declarewinner(HUMAN);
                    return;
                }
                whoseturn = COMPUTER;
            }
            else {
                printf("%d hucresi zaten dolu tekrar deneyiniz..\n",move);
            }
        }
    }
    if (!gameover(board) && moveIndex== SIDE*SIDE)
        printf("BERABERLİK\n");
    else {
        if (whoseturn == COMPUTER)
            whoseturn = HUMAN;
        else if (whoseturn == HUMAN)
            whoseturn = COMPUTER;
        declarewinner(whoseturn);
    }
}

int main() {
    playtictactoe(COMPUTER);
    return 0;
}
