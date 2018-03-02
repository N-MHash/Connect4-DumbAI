#include <iostream>
#include <cstdlib> // exit(0) && rand()
#include <windows.h> // Sleep() function
#include <time.h> // srand() seed

using namespace std;

//Initializes the board's matrix with empty spaces
char board[6][7] = {
{' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' '}
};

//variable for ASCII codes for symbols (chips)
int ascii;

//the spot (column) which the players picks to play in
short spot;

short cpu_spot;

bool first_round = true;

//whose turn it is
bool p1 = 1, cpu = 0;

//assigns a name to player1
string p_1;

/*=============================================================*/
void drawBoard();

//function to take player's input
void play();

void winnerCheck();

//A counter that when reaches 41, declares the game as a draw.
int draw = -1;

int main()
{
    cout << "PLAYER 1 (" << char(178) << "): Type a name!\n";
    cin >> p_1;

    cout << "\nHello, (" << p_1 << ")! The game begins in 3 seconds.";
    Sleep(3000);
    drawBoard();
    return 0;
}

void drawBoard()
{
    // clears the screen
    cout << string(100, '\n');
    cout << endl;

    //Draws the board
    for (int r = 0; r < 6; r++)
    {
        for (int c = 0; c < 7; c++)
        {
            cout << "[" << board[r][c] << "]\t";
        }
        cout << endl;
    }

    //Prints the number of each respective column
    for (int r = 1; r <= 7; r++)
    {
        cout << " " << r << "\t";
    }

    //Displays where the last move was played
    if (first_round == false)
    {
        if (p1 == 1)
        {
            cout << "\n\n" << p_1 << " (" << char(178) << ") played in column " << spot << "\n";
            cout << "\n\nCPU" << " (" << char(177) << ") played in column " << cpu_spot << "\n";
        }
    }   
    winnerCheck();
    draw++;
    play();
}

void play()
{
    bool error = false;

    //Checks if it is Player 1's turn
    if (p1 == 1)
    {
        ascii = 178;
        cout << "\n\n==== " << p_1 <<"'s TURN " << "[" << char (178) << "] ====\n";
        do
        {
            error = false;
            cout << "Choose a column (1~7) to play in: ";
            cin >> spot;

            if (spot < 1 || spot > 7)
            {
                error = true;
                cout << "\nYou must choose a number between 1 and 7!!\n";
                Sleep(1000);
            }

            if (error == false)
            {
                for (int r = 5; r >= 0;)
                {
                    if (board[r][spot-1] != ' ') //Checks if the row below is empty, if it is not, it picks the row above.
                        r--;
                    else
                    {
                        board[r][spot-1] = ascii; //Plays the chip in the selected column

                        //Alternates between players
                        if (p1 == 1)
                        {
                            p1 = 0;
                            cpu = 1;
                        }
                        else if (cpu == 1)
                        {
                            cpu = 0;
                            p1 = 1;
                        }
                        first_round = false;
                        drawBoard();
                        break;
                    }

                }
            }

        }while(p1 == 1 && (spot < 1 || spot > 7));
    }

    else if (cpu == 1)
    {
        srand(time(NULL));
        ascii = 177;

        cpu_spot = 1 + rand()%7; //Generates a random number from 1 to 7 where the dumb AI will play

        for (int r = 5; r >= 0;)
        {
            if (board[r][cpu_spot-1] != ' ')
                r--;
            else
            {
            board[r][cpu_spot-1] = ascii;
            if (p1 == 1)
            {
                p1 = 0;
                cpu = 1;
            }
            else if (cpu == 1)
            {
                cpu = 0;
                p1 = 1;
            }
            drawBoard();
            break;
            }
        }
    }
}

void winnerCheck()
{
    //Checks all rows for any 4-in-a-row connections
    for (int row = 5; row >= 0; row--)
    {
        for (int col = 0, c_1, c_2, c_3; col < 4;)
        {
            c_1 = 1 + col;
            c_2 = 2 + col;
            c_3 = 3 + col;

            if (board[row][col] == char(178) && board[row][c_1] == char(178) && board[row][c_2] == char(178) && board[row][c_3] == char(178))
            {
                cout << "\n\n" << p_1 << " WON!\n";
                exit(0);
            }
            else if (board[row][col] == char(177) && board[row][c_1] == char(177) && board[row][c_2] == char(177) && board[row][c_3] == char(177))
            {
                cout << "\n\nCPU WON!\n";
                exit(0);
            }
            else col++;
        }
    }

    //Checks all columns for any 4-in-a-row connections
    for (int col = 0; col < 7; col++)
    {
        for (int row = 5, r_1, r_2, r_3; row >= 3;)
        {
            r_1 = row - 1;
            r_2 = row - 2;
            r_3 = row - 3;

            if (board[row][col] == char(178)
                && board[r_1][col] == char(178)
                && board[r_2][col] == char(178)
                && board[r_3][col] == char(178))
            {
                cout << "\n\n" << p_1 << " WON!\n";
                exit(0);
            }
            else if (board[row][col] == char(177)
                     && board[r_1][col] == char(177)
                     && board[r_2][col] == char(177)
                     && board[r_3][col] == char(177))
            {
                cout << "\n\nCPU WON!\n";
                exit(0);
            }
            else row--;
        }
    }

    //Checks all possible diagonal 4-in-a-row connections
    for (int row = 3, r_1, r_2, r_3; row < 6; row++)
    {
        r_1 = row - 1;
        r_2 = row - 2;
        r_3 = row - 3;
        for (int col = 0, c_1, c_2, c_3; col < 4;)
        {
            c_1 = 1 + col;
            c_2 = 2 + col;
            c_3 = 3 + col;

            if (board[row][col] == char(178)
                && board[r_1][c_1] == char(178)
                && board[r_2][c_2] == char(178)
                && board[r_3][c_3] == char(178))
            {
                cout << "\n\n" << p_1 << " WON!\n";
                exit(0);
            }
            else if (board[row][col] == char(177)
                     && board[r_1][c_1] == char(177)
                     && board[r_2][c_2] == char(177)
                     && board[r_3][c_3] == char(177))
            {
                cout << "\n\nCPU WON!\n";
                exit(0);
            }
            else col++;
        }
    }

    //Another one that checks all the other possible diagonal 4-in-a-row connections
    for (int row = 3, r_1, r_2, r_3; row < 6; row++)
    {
        r_1 = row - 1;
        r_2 = row - 2;
        r_3 = row - 3;
        for (int col = 3, c_1, c_2, c_3; col < 7;)
        {
            c_1 = col - 1;
            c_2 = col - 2;
            c_3 = col - 3;

            if (board[row][col] == char(178)
                && board[r_1][c_1] == char(178)
                && board[r_2][c_2] == char(178)
                && board[r_3][c_3] == char(178))
            {
                cout << "\n\n" << p_1 << " WON!\n";
                exit(0);
            }
            else if (board[row][col] == char(177)
                     && board[r_1][c_1] == char(177)
                     && board[r_2][c_2] == char(177)
                     && board[r_3][c_3] == char(177))
            {
                cout << "\n\nCPU WON!\n";
                exit(0);
            }
            else col++;
        }
    }

    if (draw == 41)
    {
        cout << "\nDraw!\n";
        exit(0);
    }
}
