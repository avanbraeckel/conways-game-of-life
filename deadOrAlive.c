/* Austin Van Braeckel
 * 2019-11-10
 * A function that determines whether a cell in the "world" grid is 
 * dead or live for Conway's game of life. For CIS1300 Assignment 4.
 * Returns a 'X' character if it is alive, and a ' ' character if it is not.
 */

#include <stdbool.h>
#include <stdio.h>

void deadOrAlive ( char*world, char*futureWorld, int row, int col, int ROWS, int COLS ) {
    /*set initial position of the value in regards to the array in memory*/
    int position = COLS * row + col;
    bool original, isAlive;
    int numAlive = 0;

    if ( *(world+position) == '0' ) {
        original = false;
    } else {
        original = true;
    }

    if ( col > 0 ) { /*left*/
        if ( *(world+position-1) == '1') { /*left - same row*/
            numAlive++;
        }
        if ( row > 0 && *(world+position-COLS-1) == '1' ) { /*top-left*/
            numAlive++;
        }
        if ( row < ROWS-1 && *(world+position+COLS-1) == '1' ) { /*bottom-left*/
            numAlive++;
        }
    }
    if ( col < COLS-1 ) { /*right*/
        if ( *(world+position+1) == '1' ) { /*right - same row*/
            numAlive++;
        }
        if ( row > 0 && *(world+position-COLS+1) == '1' ) { /*top-right*/
            numAlive++;
        }
        if ( row < ROWS-1 && *(world+position+COLS+1) == '1' ) { /*bottom-right*/
            numAlive++;
        }
    }
    if ( row > 0 && *(world+position-COLS) == '1' ) { /*top*/
        numAlive++;
    }
    if ( row < ROWS-1 && *(world+position+COLS) == '1' ) { /*bottom*/
        numAlive++;
    }
    
    /*Determine if dead or alive*/
    if ( numAlive < 2 ) { /*dies*/
        isAlive = false;
    } else if ( numAlive == 2 ) { /*lives if already alive*/
        if (original == true) {
            isAlive = true;
        } else {
            isAlive = false;
        }
    } else if ( numAlive == 3 ) { /*becomes alive*/
        isAlive = true;
    } else if ( numAlive > 3 ) { /*dies*/
        isAlive = false;
    }

    /*Change value depending on dead or alive*/
    if ( isAlive ) {
        *(futureWorld+position) = '1';
    } else {
        *(futureWorld+position) = '0';
    }
}