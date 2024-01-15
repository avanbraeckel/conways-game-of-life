/*
* Austin Van Braeckel
* 2019-11-10
* This is a program for CIS1300 Assignment 4 that simulates
* Conway's Game of Life.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXINPUT 200 /*For answering yes/no questions*/ 
#define ROWS 20
#define COLS 40

void deadOrAlive( char*, char*, int, int, int, int );

int main ( int argc, char * argv[] ) {

    int i, c;
    unsigned long int ticks, j, accumulatedTicks = 0;
    bool valid = true;
    bool saysYes = true;
    bool isSame = true; /*default true*/
    bool continuing = true;
    bool rowsAndColsValid = true;
    FILE *fp;
    char input[MAXINPUT];
    char outputChar;
    /*create arrays*/
    char world[ROWS][COLS];
    char futureWorld[ROWS][COLS];
    char line[COLS*2+1];
    char hBorder[COLS+2]; /*horizontal border*/

    /*Check if they put in extra parameters*/
    if (argc == 3) { /*specifies the ticks only*/
        for (i = 0; i < strlen(argv[2]); i++) {
            if ( !(isdigit(argv[2][i])) ) {
                valid = false;
                i = strlen(argv[2]); /*end loop*/
            }
        }
        if ( valid ) {
           ticks = atoi(argv[2]);
           if (ticks < 1){ /*cannot be 0 or lower*/
               valid = false;
           }
           /*Cap it at maximum value for an unsigned int - 32 bits in 4 bytes, which is the size of an unsigned int*/
           if (ticks >= __UINT32_MAX__) {
               ticks =  __UINT32_MAX__;
           }
        } 
    } else if (argc == 2) { /*no arguments (other than the required - seed)*/
        ticks = 50;
    } else {
        valid = false;
    }

    if ( !valid) {
        printf("ERROR: invalid parameters - here are the options: ./cgol (seed)   OR   ./cgol (seed) (ticks)\n");
        exit(-1);
    }

    #define FILENAME argv[1]

    /*Try to open/read file file*/
        /*Read-in data from corresponding file*/
        if ( (fp = fopen( FILENAME, "r")) != NULL ) {

            i = 0, j = 0;
            valid = true;

            /*Fill world 2D array with data from file - maximum number of columns is 40, so with spaces between them and a '\n',
            it is at most 81 if formatted perfectly, so 100 is a good threshold*/
            while ( fgets(line, 100, fp) != NULL && valid && i < ROWS ) {
                
                /*Every other column because there are spaces between needed values*/
                for (c = 0; c < strlen(line); c ++) {
                  
                    if ( line[c] == '1' || line[c] == '0') {
                        world[i][j] = line[c];
                        j++;
                    } else {
                        /*Only spaces allowed, with an exception for newline and null characters*/
                        if (line[c] != '\n' && line[c] != '\0' && line[c] != ' ') {
                            valid = false;
                            rowsAndColsValid = false;
                        }
                    }
                }
                /*Makes sure that the seed and the specified number of columns is the same*/
                if (j != COLS) {
                    valid = false;
                }

                j = 0;
                i++;
            }
            
            if (!valid) {
                if (!rowsAndColsValid) {
                printf ( "ERROR: invalid seed format for %s - the seed must only consist of 0s and 1s separated by spaces\n", FILENAME);
                } else {
                printf ( "ERROR: invalid seed format for %s - the number of rows and columns do not match the default of 20 rows and 40 columns\n", FILENAME);
                }
                exit(-1);
            }

        } else {
            printf ( "ERROR: cannot open \"%s\" for reading\n", FILENAME);
            exit (-1);
        }

        fclose(fp);

        /*Set-up horizontal border*/
        hBorder[0] = ' '; /*off-set so it is centred*/
         for (i = 1; i < COLS+1; i++) {
            hBorder[i] = '-';
        }
        hBorder[i] = '\0'; /*Mark end of the line*/

    /*Display the initial grid/world*/
        printf("%s\n", hBorder);
        /*Values*/
        for (i = 0; i < ROWS; i++) {
            /*Side border*/
            printf("|");
            for ( c = 0; c < COLS; c++ ) {
                
                if (world[i][c] == '0') {
                    outputChar = ' ';
                } else {
                    outputChar = 'X';
                }
                printf("%c", outputChar);
            }
            /*Side border*/
            printf("|\n");
        }
        printf("%s0\n", hBorder); /* Starts at the 0th tick*/

        valid = false; /*default false to run the loop*/

    /*ask if the user wishes to start*/
    /*Error-check Y/y or N/n*/
        while (!valid) {
            printf( "Start? (y or n): ");
            valid = true;

            if ( fgets(input, MAXINPUT, stdin) != NULL ) {
                    /*mark the end of the input to reduce risk of any errors*/
                    input[2] = '\0';
                    /*only need to check first character because the options are y or n*/
                    if ( (input[0] == 'Y' || input[0] == 'y') && (input[1] == '\n' || input[1] == '\0') ) {
                        saysYes = true;
                    } else if ( (input[0] == 'N' || input[0] == 'n') && (input[1] == '\n' || input[1] == '\0') ) {
                        saysYes = false;
                    } else {
                        valid = false;
                    }
            } else {
                valid = false;
            }

            if (!valid) {
                printf("Error: only the single characters 'y' or 'n' are acceptable\n");
            } else if ( saysYes ) {
                system ( "clear" );
            } else { /*says no*/
                exit(-1);
            }
        }

        while (continuing) {
            continuing = false; /*default runs once*/
            /*Start applying the rules of life and death, and count ticks*/
            for ( j = 0; j < ticks; j++ ) {
                system ( "clear" );

                /*Copy curent world into future*/
                for ( i = 0; i < ROWS; i++ ) {
                    for (c = 0; c < COLS; c++ ) {
                        futureWorld[i][c] = world[i][c];
                    }
                } 

                printf("%s\n", hBorder);
                /*Values*/
                for (i = 0; i < ROWS; i++) {
                    /*Side border*/
                    printf("|");
                    for ( c = 0; c < COLS; c++ ) {
                        
                        deadOrAlive(&world[0][0], &futureWorld[0][0], i, c, ROWS, COLS);
                        if (futureWorld[i][c] == '0') {
                            outputChar = ' ';
                        } else {
                            outputChar = 'X';
                        }
                        printf("%c", outputChar);
                    }
                    /*Side border*/
                    printf("|\n");
                }
                printf("%s%lu\n", hBorder, accumulatedTicks + j + 1); /*Since the index begins at 0, add 1 for display*/

                isSame = true;
                /*Make the current world the future world*/
                for ( i = 0; i < ROWS; i++ ) {
                    for (c = 0; c < COLS; c++ ) {
                        if (world[i][c] != futureWorld[i][c]) { /*check to see if the worlds are the same*/
                            isSame = false;
                        }
                        world[i][c] = futureWorld[i][c];
                    }
                } 

                if (isSame) {
                    exit(-1);
                }

                /*delay output*/
                system ( "sleep 0.25" );
                
            } /*end of tick loop*/

            /*Ask if the user wants to continue*/
            valid = false; /*default false to run the loop*/

            /*Error-check Y/y or N/n*/
            while (!valid) {
                printf( "Continue? (y or n): ");
                valid = true;
                continuing = true;

                if ( fgets(input, MAXINPUT, stdin) != NULL ) {
                        /*mark the end of the input to reduce risk of any errors*/
                        input[2] = '\0';
                        /*only need to check first character because the options are y or n*/
                        if ( (input[0] == 'Y' || input[0] == 'y') && (input[1] == '\n' || input[1] == '\0') ) {
                            continuing = true;
                        } else if ( (input[0] == 'N' || input[0] == 'n') && (input[1] == '\n' || input[1] == '\0') ) {
                            continuing = false;
                        } else {
                            valid = false;
                        }
                } else {
                    valid = false;
                }

                if (!valid) {
                    printf("Error: only the single characters 'y' or 'n' are acceptable\n");
                } else if ( continuing ) {
                    accumulatedTicks += ticks; /*start displayed counter from where the user left-off*/
                    system ( "clear" );
                } else { /*says no*/
                    exit(-1);
                }
            } /*End of error-checking*/

        } 

    return 0;
}