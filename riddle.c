//The following code is of Number Riddle game.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int row, col,i,j,k,x,y,c,r;
int p[64];
int prow,pcol,erow,ecol,emptyPosition;

void random1()
{
  p[0] = rand() % (row*col-1) + 1;
   i = 1;
    while (i<row*col-1) {
      k =  rand() % (row*col-1) + 1;

      // Check the uniqueness of the randomly generated number
       j = 0;
      for (; j<i; j++) {
        if (p[j] == k) {
          break;
        }
      }

      // Generated number is unique
      if (j == i) {
        p[i] = k;
        i++;
      }
    }
}
void validity()
{
  p[emptyPosition] = p[i];
  p[i] = 0;
  emptyPosition = i;
}
void show()
{
    // Show the elements of Array as two dimensional table format.
    for ( r = 0; r < row; r++) {
      printf("| ");
      for ( c = 0; c < col; c++) {
        if (p[r*col+c]==0) {
          printf("   | ");
        }
        else {
          printf("%2d | ", p[r*col+c]);
        }
      }
      puts("");
    }
}

int main() {

  puts("**************************");
  puts("******* Welcome to *******");
  puts("*** Number Riddle Game ***");
    puts("**************************");
  puts("");

  srand(time(NULL));

  do {

    // Variables for number of rows and columns


    // Get the number of rows and columns from the user
    do {
      printf("Enter number of rows (3 - 8):\n");
      scanf("%d",&row);
    } while (row <3 || row > 8);

    do {
      printf("Enter number of columns (3 - 8):\n");
      scanf("%d",&col);
    } while (col < 3 || col > 8);

    // Create a one-dimensional array for the game board, and initialize the elements with zero
     p[row*col];
    for (i = 0; i < row*col; i++) {
      p[i] = 0;
    }

    // Generate random numbers and put in the board cells

    random1();

    // Randomize the location of the empty cell
    i = rand() % (row*col-1);
    emptyPosition = i;
    p[row*col-1] = p[i];
    p[i] = 0;

    puts("");

    show();

    int won = 0;

    time_t start, end;    // Record the time taken in each round of play
    time(&start);
    int counter = 0;
    // Loop for one game:
    do {

      // get the player's move
      int answer;
      do {
        printf("(#Move %d), Enter the number you want to move ( 0 to exit):\n", counter);
        scanf("%d",&answer);
        if (answer >= 0 && answer < row*col)
          break;
        else
          printf("Invalid number.\n");
      } while (1);
      if (answer == 0) {
        break;
      }

      for ( i=0; i<row*col; i++) {
        if (p[i] == answer) {

          // Convert the one-dimensional values to two-dimensional values
           prow = i / col;
             pcol = i % col;
           erow = emptyPosition / col;
           ecol = emptyPosition % col;

          // Check the validity of the movement
          if (abs(prow-erow) + abs(pcol - ecol) == 1)
          {
            validity();

            show();

            // Check if the game is over
             j = 0;
            for (; j<row*col-1;j++) {
              if (p[j] != j+1) {
                counter++;
                break;
              }
            }

            // Game is over and the player wins
            if (j == row*col-1) {
              time(&end);
              double t = difftime(end,start);
              printf("Excellent!!! you solved it with %d guesses, in %3.0f seconds.\n",counter, t);
              won = 1;
              break;
            }
          }

          // Invalid movement
          else {
            printf("This cell can't move!\n");
          }
          break;
        }
      }

    } while (!won);

    // Ask the user to play again or not
    printf("To play again, enter 1:\n");
    int answer;
    scanf("%d",&answer);
    if (answer != 1) {
      break;
    }
  } while (1);

  printf("GoodBye!\n");

  return 0;

}
