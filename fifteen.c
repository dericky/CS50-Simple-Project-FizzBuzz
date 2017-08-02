/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
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
void clear(void);
void greet(void);
void init(int board[][DIM_MAX], int d);
void draw(int board[][DIM_MAX], int d);
bool move(int tile, int board[][DIM_MAX], int d);
bool won(int board[][DIM_MAX], int d);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
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
    init(board, d);

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw(board, d);

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
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
        if (won(board, d))
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile, board, d))
        {
            printf("\nIllegal move.\n");
            usleep(50000);
        }

        // sleep thread for animation's sake
        usleep(50000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(20000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(int board[][DIM_MAX], int d)
{
    bool evenTiles = true;
    int numbers = (d*d);
    if((numbers)%2 == 1){
        evenTiles = false;
    }
    numbers--;
    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            board[j][i] = numbers;
            numbers--;
        }
    }
    if(!evenTiles){
        int temp = board[d-2][d-1];
        board[d-2][d-1] = board[d-3][d-1];
        board[d-3][d-1] = temp;
    }
    printf("The board dimensions are %i by %i", d, d);
}

/**
 * Prints the board in its current state.
 */
void draw(int board[][DIM_MAX], int d)
{
    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            if(board[j][i] == 0){
                printf("__");
            }
            else
                printf("%2i ", board[j][i]);
        }
        printf("\n");
    }}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile, int board[][DIM_MAX], int d)
{
    int width = 0;
    int height = 0;
    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            if (board[j][i] == tile){
                width = j;
                height = i;
            }
        }
    }
    //check tile above
    if(height-1>=0){
        if(board[width][height-1] == 0){
        board[width][height-1] = board[width][height];
        board[width][height] = 0;
        return true;
        }
    }
    
    //check tile below
    if(height+1< d){
       if(board[width][height+1] == 0){
        board[width][height+1] = board[width][height];
        board[width][height] = 0;
        return true;
        } 
    }
    
    //check tile right
    if(width+1 < d){
        if(board[width+1][height] == 0){
        board[width+1][height] = board[width][height];
        board[width][height] = 0;
        return true;
        }
    }

    //check tile left
    if(width-1 >= 0){
            if(board[width-1][height] == 0){
        board[width-1][height] = board[width][height];
        board[width][height] = 0;
        return true;
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(int board[][DIM_MAX], int d)
{
    int numbers = 1;
    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            if (board[j][i] != numbers)
                return false;
            numbers++;
        }
    }

    return true;
}
