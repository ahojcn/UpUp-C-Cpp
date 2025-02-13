#include "game.h"

void game_menu()
{
    printf("*********************\n");
    printf("*** 1.play 0.exit ***\n");
    printf("*********************\n");
}

// 初始化地图
void board_init(char board[ROW][COL], int row, int col)
{
    memset(&board[0][0], ' ', row*col*sizeof(board[0][0]));
}

// 展示地图信息
void board_print(char board[ROW][COL], int row, int col)
{
    system("clear");
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            printf(" %c ",board[i][j]);
            if (j<row-1)
            {
                printf("|");
            }
        }
        printf("\n");
        if (i<row-1)
        {
            for (int j=0; j<col; j++)
            {
                printf("---");
                if (j<row-1)
                {
                    printf("|");
                }
            }
            printf("\n");
        }
    }
}

// 玩家走
void player_move(char board[ROW][COL], int row, int col)
{
    Point p;
    printf("your turn:\n");
    while (true)
    {
        printf(">");
        scanf("%d%d", &p.x, &p.y);
        if (p.x>0&&p.x<=row && p.y>0&&p.y<=col)
        {
            if (board[p.x-1][p.y-1] == ' ')
            {
                board[p.x-1][p.y-1] = 'X';
                break;
            }
            else
            {
                printf("illegal!\n");
            }
        }
        else
        {
            printf("illegal!\n");
        }
    }
}

// 电脑走
void computer_move(char board[ROW][COL], int row, int col)
{
    Point p;
    while (true)
    {
        p = scan_row(board, ROW, COL);
        if (p.x == -1)
        {
            p = scan_col(board, ROW, COL);
            if (p.x == -1)
            {
                p.x = rand()%row;
                p.y = rand()%col;
                if (board[p.x][p.y] == ' ')
                {
                    board[p.x][p.y] = 'O';
                    break;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                if (board[p.x][p.y] == ' ')
                {
                    board[p.x][p.y] = 'O';
                    break;
                }
                else
                {
                    continue;
                }
            }
        }
        else
        {
            if (board[p.x][p.y] == ' ')
            {
                board[p.x][p.y] = 'O';
                break;
            }
            else
            {
                continue;
            }
        }
    }
}

// 胜利判断
char is_win(char board[ROW][COL], int row, int col)
{
    int i = 0;
    for(i=0; i<row; i++)
    {
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][0] != ' ')
        {
            return board[i][0];
        }
    }
    for(i=0; i<col; i++)
    {
        if(board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[1][i] != ' ')
        {
            return board[1][i];
        }
    }
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[1][1] != ' ')
        return board[1][1];
    if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[1][1] != ' ')
        return board[1][1];
    
    //判断平局
    if(is_full(board, row, col) == 1)
    {
        return 'Q';
    }
    //继续
    return ' ';
}

int is_full(char board[ROW][COL], int row, int col)
{
    int i = 0;
    int j = 0;
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            if(board[i][j] == ' ')
                return 0;
        }
    }
    return 1;
}

// 扫描行 如果玩家即将胜利，返回一个他下一步的棋子位置，如果没有，返回(-1，-1)点
Point scan_row(char board[ROW][COL], int row, int col)
{
    Point p;
    p.x = -1;
    p.y = -1;
    for (int i=0; i<row; i++)
    {
        if (board[i][0]==board[i][1]&&board[i][0]=='X'&&board[i][2]==' ')
        {
            p.x = i;
            p.y = 2;
            return p;
        }
        else if(board[i][1]==board[i][2]&&board[i][1]=='X'&&board[i][0]==' ')
        {
            p.x = i;
            p.y = 0;
            return p;
        }
        else
        {
            return p;
        }
    }
    return p;
}

// 扫描列 如果玩家即将胜利，返回一个他下一步的棋子位置，如果没有，返回(-1，-1)点
Point scan_col(char board[ROW][COL], int row, int col)
{
    Point p;
    p.x = -1;
    p.y = -1;
    for (int i=0; i<row; i++)
    {
        if (board[0][i]==board[1][i]&&board[0][i]=='X'&&board[2][i]==' ')
        {
            p.x = 2;
            p.y = i;
            return p;
        }
        else if(board[1][i]==board[2][i]&&board[1][i]=='X'&&board[0][i]==' ')
        {
            p.x = 0;
            p.y = i;
            return p;
        }
        else
        {
            return p;
        }
    }
    return p;
}
