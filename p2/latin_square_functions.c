/******************************************************************************
 * @file: latin_square_functions.c
 *
 * WISC NETID       lmdinh
 * CANVAS USERNAME  lmdinh
 * WISC ID NUMBER   908 066 0948
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: Laura Dinh (lmdinh@wisc.edu)
 * @modified: 11/13/2021
 *****************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "latin_square_functions.h"

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0 
// before submitting!
#define DEBUG               0 
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }
#define dbgprint_latin_square(n, LS) if (DEBUG) { Print_Latin_Square(n, LS); }

/******************************************************************************
 * Data Types and Structures
 *****************************************************************************/

// ADD ANY ADDITIONAL DATA TYPES OR STRUCTSvHERE 

/******************************************************************************
 * Globals
 *****************************************************************************/
extern void Print_Latin_Square(const size_t n, char **latin_square);

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE

/*
 * Counts how many times c appears in the latin square
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square A pointer to the latin square variable in main
 * @param c A pointer the character we are counting
 */
int Count_Char(const size_t n, char **latin_square, char *c) {
    int count = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            if (*(*(latin_square + i) + j) == *c) {
                count++;
            }
        }
    }
    return count;
}
/*
 * Transposes the latin_square
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square A pointer to the latin square variable in main
 */
char** Transpose(const size_t n, char ***transpose, char ***latin_square) {
    // allocates memory for transpose
    *transpose = (char **)malloc(n * sizeof(char*));
    for(int i = 0; i <n; i++) {
        *((*transpose) + i) = (char *)malloc(n * sizeof(char));
    }

    for(size_t i = 0; i < n; i++) {
        for(size_t j = 0; j < n; j++) {
            *(*(*(transpose) + i) + j) = *(*(*(latin_square) + j) + i);
        }
    }
    return *transpose;
}

/*
 * Checks if there is a duplicate in a row
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square A pointer to the latin square variable in main
 */
int Check_Duplicates(const size_t n, char *latin_square) {
    for (size_t i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if(*(latin_square + i) == *(latin_square + j))
                return 1;
        }
    }
    return 0;
}

/******************************************************************************
 * Verificaiton functions
 *****************************************************************************/

/* 
 * This function takes the name of the file containing the latin square
 * and reads in the data to the the latin_square parameter.  
 *
 * There are many approaches that will work to read in the latin square data.
 * In any approach you choose, you will need to do at least the following:
 *     1) open the file 
 *     2) read in the text from the file
 *     3) figure out the dimensions of the latin square (n)
 *     4) reserve memory for the latin_square. This requires 2 steps
 *         4a) reserve an array of pointers to the rows
 *         4b) reserve an array of characters for each row
 *     5) fill in the latin_square data structure 
 *     6) close the file
 *
 * @param filename The name of the file to read in
 * @param latin_square_in A pointer to the latin square variable in main
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 */
void Read_Latin_Square_File(const char *filename, 
                            char ***latin_square_in,
                            size_t *n) {
    /* BEGIN MODIFYING CODE HERE */
    // open the file
    FILE *fp;
    fp = fopen(filename, "r");

    // read text and find dimension
    int c = getc(fp);
    size_t count = 0;
    while(c != '\n') {
        count++;
        c = getc(fp);
    }
    *n = count;

    // reserve memory for latin_square
    *latin_square_in = (char **)malloc(*n * sizeof(char*));
    for(size_t  i = 0; i < *n; i++) {
        *((*latin_square_in) + i) = (char *)malloc(*n * sizeof(char));
    }
    // filling in latin_square
    rewind(fp); // starts at the top of the file
    for(size_t  i = 0; i < count; i++) {
        for (size_t  j = 0; j < count; j++) {
            c = getc(fp);
            if (c == EOF)
                break;
            if ( (char) c == '\n') {
                j--;
                continue;
            } else {
                *(*(*(latin_square_in) + i) + j) = (char) c;
            }
        }
    }
    fclose(fp);
    /* END MODIFYING CODE HERE */
}

/* 
 * This function checks to see that exactly n symbols are used and that 
 * each symbol is used exactly n times.
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
int Verify_Alphabet(const size_t n, char **latin_square) {
    if (latin_square == NULL) {
        printf("Verify_Alphabet - latin_square is NULL\n"); 
        return 0;
    }
    /* BEGIN MODIFYING CODE HERE */
    char *c = (char *)malloc(n*n*sizeof(char)); // list of each character in latin_square
    int k = 0; // increment c in memory
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            *(c+k) =  *(*(latin_square + i) + j);
            k++;
        }
    }
    size_t size = n;
    for(size_t i = 0; i < size; i++) {
        for(size_t j = i + 1; j < size; j++) {
            if (*(c+i) == *(c+j)) {
                for (size_t l = j; l < size - 1; l++) {
                    *(c+l) = *(c+l+1);
                }
                size--;
                j--;
            }
        }
    }

    for (size_t i = 0; i < size; i++) {
        char symbol = *(c + i);
        int count = Count_Char(n, latin_square, &symbol);
        if (count == n) {
            continue;
        } else {
            free(c);
            return 0;
        }
    }
    /* END MODIFYING CODE HERE */
    free(c);
    return 1;
}

/* 
 * This function verifies that no symbol is used twice in a row or column.
 * It prints an error message alerting the user which rows or columns have 
 * duplicate symbols. This means that you will have at most n row error prints
 * and n column error prints.
 *
 * Note: Test all rows first then test all columns.
 * 
 * Error messages have been included for you. Do not change the format out the 
 * print statements, as our grading scripts will use exact string matching. You
 * change the variable passed as the formatting argument to printf.
 * 
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
 int Verify_Rows_and_Columns(const size_t n, char **latin_square){
    if (latin_square == NULL) {
        printf("Verify_Rows_and_Columns - latin_square is NULL\n"); 
        return 0;
    }
    int count = 0;
    /* BEGIN MODIFYING CODE HERE */
    //Testing rows
    for(size_t i = 0; i < n; i++) {
        if(Check_Duplicates(n, *(latin_square + i))) {
            printf("Error in row %d\n", i);
            count++;
        }
    }

    // Testing Columns
    char ** transpose = Transpose(n, &transpose, &latin_square);
    for(size_t i = 0; i < n; i++) {
        if(Check_Duplicates(n, *(transpose  + i))) {
            printf("Error in column %d\n", i);
            count++;
        }
    }
    Free_Memory(n, transpose);
    if (count > 0) {
        return 0;
    }
    /* END MODIFYING CODE HERE */
    return 1;
}

/* 
 * This function calls free to allow all memory used by the latin_square 
 * verification program to be reclaimed.
 *
 * Note: you will have n+1 calls to free
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 */ 
void Free_Memory(const size_t n, char **latin_square) {
    /* BEGIN MODIFYING CODE HERE */
    for (int i = 0; i < n; i++) {
        free(*(latin_square+i));
    }
    free(latin_square);
    /* END MODIFYING CODE HERE */
}

