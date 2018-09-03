//
//#define _XOPEN_SOURCE 500

#include<ctype.h>
#include<stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes

void greet(void);
void init(void);
void draw(void);
int move(int tile);
int won(void);

int main()
{  char choice;
    do{int n;
       system("cls");
       printf("***********************************************************WELCOME TO GAME OF FIFTEEN!**********************************\n");
       printf("\nINSTRUCTIONS FOR USAGE!\n\n1)THE OBJECTIVE: The grid of numbers is to be arranged in ascending order.\n\n2)THE CONTROLS: Simply press the number of the tile to be moved. Game allows only those tiles to be moved which are :\n\na)Horizontally adjacent or\n\nb)Vertically adjacent\n\nto the blank tile!");
       printf("\n\n3)NOTE: In case of improper usage, you'll be notified and asked for the proper move. \n\n\nALL THE BEST!!!\n\n\n");
       printf("Enter Difficulty: \n\n1)Easy(3x3)\n\n2)Medium(4x4)\n\n3)Difficult(5x5)\n");
       scanf("%d",&n);
       if(n==1)
         d=3;
       else if(n==2)
         d=4;
       else if(n==3)
         d=5;
       else
       {printf("Please enter correct choice.");return 2;}





    // ensure valid dimensions

    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (1)
    {
        // clear the screen
//        clear();
      system("cls");

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {         for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("\n\n!!!!!!!!!!!!!!!!!!!!!!CONGRATULATIONS!!!!!!!!!!!!!!!!!!!\n\nYOU HAVE SOLVED THE PUZZLE!!\n\nPress Y to play again, N to exit! \n\n");
            fflush(stdin);scanf(" %c",&choice);
            break;
        }

        // prompt for move
        printf("\n\nTile to move: ");
        int tile;
        scanf("%d",&tile);
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {   printf("\n\nYou have successfully left the previous game! \n\nPress Y to restart the game or N to exit! ");
            fflush(stdin);scanf(" %c",&choice);
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);
}while(choice=='Y' || choice=='y');
    // success
    return 0;
}


/**
 * Greets player.
 */
void greet(void)
{
//    clear();
    system("cls");
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    // TODO
    int p=d*d;
    for(int i=0;i<d;i++)
    {
        for(int j=0;j<d;j++)
        {
            board[i][j]=--p;
        }
    }
    if(d%2==0)
       {

        board[d-1][d-3]=1;
        board[d-1][d-2]=2;
       }
    board[d-1][d-1]='_';
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{   printf("!!!!!!!!!!!!PRESS 0 TO QUIT!!!!!!!!!!!");
    printf("\n");for(int i=0;i<=(d*16);i++)printf("-");
    for(int i=0; i<d; i++)
    {   char ch='_';printf("\n");
        for(int j=0; j<d; j++)
        {


            if(board[i][j]!='_')
               printf("\t%3i\t|",board[i][j]);


           else
              printf("\t%3c\t|",ch);
        }
        printf("\n");for(int i=0;i<=(d*16);i++)printf("-");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
int move(int tile)
{   int br,bc;
    for(int i=0;i<d;i++)
    {
        for(int j=0;j<d;j++)
        {
            if(board[i][j]=='_')
            {
                br=i;
                bc=j;
            }
        }
    }
    for(int i=0;i<d;i++)
    {
        for(int j=0;j<d;j++)
        {
            if(board[i][j]==tile)
            {
                if(br==i)
                {
                 if(bc==j-1)
                   {
                     int tmp = board[i][j];
                     board[i][j]=board[br][bc];
                     board[br][bc]=tmp;
                     return 1;
                   }
                 else if(bc==j+1)
                 {
                     int tmp = board[i][j];
                     board[i][j]=board[br][bc];
                     board[br][bc]=tmp;
                     return 1;
                   }
                 else
                    return 0;


                }
                else if(bc==j)
                {
                    if(br==i-1)
                    {

                     int tmp = board[i][j];
                     board[i][j]=board[br][bc];
                     board[br][bc]=tmp;
                     return 1;
                    }
                    else if(br==i+1)
                    {
                     int tmp = board[i][j];
                     board[i][j]=board[br][bc];
                     board[br][bc]=tmp;
                     return 1;
                   }
                   else
                     return 0;
                }

            }


        }
    }
return 0;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else
.
 */
int won(void)
{
    int arr[d*d],k=1;
    for(int i=1;i<=(d*d);i++)
        arr[i]=i;arr[(d*d)]='_';



     for(int i=0;i<d;i++)
     {
         for(int j=0;j<d;j++)
         {
             if(board[i][j]!=arr[k++])
                return 0;
         }
     }
    return 1;



}
