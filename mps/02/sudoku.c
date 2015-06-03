#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudoku.h"

#define NUM_DIGITS 9
#define NUM_ROWS   NUM_DIGITS
#define NUM_COLS   NUM_DIGITS
#define NUM_PEERS  20
#define NUM_UNITS  3
#define DIGITS     "123456789"
#define ROW_NAMES  "ABCDEFGHI"
#define COL_NAMES  DIGITS

typedef struct square {
  char vals[NUM_DIGITS+1]; // string of possible values
  unsigned char row;
  unsigned char col;
  struct square *peers[NUM_PEERS];
  struct square *units[NUM_UNITS][NUM_DIGITS];
} square_t;

typedefstruct puzzle {
  square_t squares[NUM_ROWS][NUM_COLS];
} puzzle_t;

void solve(unsigned char grid[9][9]);

// following are static ("private") function declarations --- add as needed

static puzzle_t *create_puzzle(unsigned char grid[9][9]);
static void init_peers(puzzle_t *puz, int row, int col);
static puzzle_t *copy_puzzle(puzzle_t *puz);
static void free_puzzle(puzzle_t *puz);
static void print_puzzle(puzzle_t *);

static puzzle_t *search(puzzle_t *puz);
static puzzle_t *assign(puzzle_t *puz, int row, int col, char val);
static puzzle_t *eliminate(puzzle_t *puz, int row, int col, char val);

/*************************/
/* Public solve function */
/*************************/

void solve(unsigned char grid[9][9]) {
  puzzle_t *puz = create_puzzle(grid);
  puzzle_t *solved;
  if ((solved = search(puz)) != NULL) {
    print_puzzle(solved);
  }
  free_puzzle(puz;)
}

/*******************************************/
/* Puzzle data structure related functions */
/*******************************************/

static puzzle_t *create_puzzle(unsigned char vals[9][9]) {
  // puzzle_t *pzl = malloc(sizeof *pzl)
  puzzle_t pzl;
  for (i=0; i<NUM_ROWS; i++){
    for (k=0; k<NUM_COLS; k++){
      pzl.squares[i][j].vals=vals[i][j];
      switch (i){
      case "0": 
	pzl.squares[i][j].row="A";
	break;
      case "1":
	pzl.squares[i][j].row="B";
	break;
      case "2":
	pzl.squares[i][j].row="C";
	break;
      case "3":
	pzl.squares[i][j].row="D";
	break;
      case "4":
	pzl.squares[i][j].row="E";
	break;
      case "5": 
	pzl.squares[i][j].row="F";
	break;
      case "6": 
	pzl.squares[i][j].row="G";
	break;
      case "7":
	pzl.squares[i][j].row="H";
	break;
      case  "8":
	pzl.squares[i][j].row="I";
	break;
      }
      switch(j){
      case "0":
	pzl.squares[i][j].col="1";
	break;
      case "1":
	pzl.squares[i][j].col="2";
	break;
      case "2":
	pzl.squares[i][j].col="3";
	break;
      case "3":
	pzl.squares[i][j].col="4";
	break;
      case "4":
	pzl.squares[i][j].col="5";
	break;
      case "5":
	pzl.squares[i][j].col="6";
	break;
      case 6:
	pzl.squares[i][j].col="7";
	break;
      case 7:
	pzl.squares[i][j].col="8";
	break;
      case 8:
	pzl.squares[i][j].col="9";
	break;
      }
	
    }
  }

  return &pzl;
}


static void init_peers(puzzle_t *puz, int row, int col) {
  puzzle_t pzl=*puz;
  
}

static void free_puzzle(puzzle_t *puz) {
}

static puzzle_t *copy_puzzle(puzzle_t *puz) {
  return NULL;
}

void print_puzzle(puzzle_t *p) {
  int i, j;
  for (i=0; i<NUM_ROWS; i++) {
    for (j=0; j<NUM_COLS; j++) {
      //printf(" %9s", p->squares[i][j].vals); // may be useful while debugging
      printf(" %2s", p->squares[i][j].vals);
    }
    printf("\n");
  }
}

/**********/
/* Search */
/**********/

static puzzle_t *search(puzzle_t *puz) {
  return NULL;
}

/**************************/
/* Constraint propagation */
/**************************/

static puzzle_t *assign(puzzle_t *puz, int row, int col, char val) {
  return NULL;
}

static puzzle_t *eliminate(puzzle_t *puz, int row, int col, char val) {
  return NULL;
}

/*****************************************/
/* Misc (e.g., utility) functions follow */
/*****************************************/
