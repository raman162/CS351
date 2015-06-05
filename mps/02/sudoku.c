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
  int row;
  int col;
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
  puzzle_t *pzl_ptr=malloc (sizeof(puzzle_t));
  square_t *sq;
  int i, j;
  for (i=0; i<NUM_ROWS; i++){
    for (j=0; j<NUM_COLS; j++){
      sq=&(*pzl_ptr).squares[i][j];
      strcpy((*sq.)vals, DIGITS);
      (*pzl_pt)r.squares[i][j].row = i;
      (*pzl_ptr).squares[i][j].col = j;
    }
  }
  
  for (i=0; i<NUM_ROWS; i++){
    for (j=0; j<NUM_COLS; j++){
      init_peers(pzl_ptr, i, j);
    }
  }
  
  for (i=0; i<NUM_ROWS; i++){
    for (j=0; j<NUM_COLS; j++){
      if(vals[i][j]!='0' || vals[i][j] !='.'){
        (*pzl_ptr).squares[i][j].vals=vals[i][j];//assigning of the values that were given 
        
    }
  }
 

  
  

 
  
  return pzl_ptr;
}

//intiates peers and units
static void init_peers(puzzle_t *puz, int row, int col) {
  int i, k, peer_ctr, row_ctr, col_ctr, mod_row, mod_col;
  peer_ctr=0;
  for (col_ctr=0; col_ctr<NUM_COLS; col_ctr++){
    if(i==(*pzl_ptr.squares[i][j].row) && k!=col_ctr){
      *pzl_ptr.squares[i][j].peers[peer_ctr] = &(*pzl_ptr.squares[i][col_ctr]);
      peer_ctr++;
    }
    *pzl_ptr.squares[i][j].units[0][col_ctr] = &(*pzl_ptr.squares[i][col_ctr]);
  }
  for (row_ctr=0; row_ctr<NUM_ROWS; row_ctr++){
    if (k==(*pzl_ptr.squares[i][j].col) && i!= row_ctr){
      *pzl_ptr.squares[i][j].peers[peer_ctr] = &(*pzl_ptr.squares[row_ctr][k]);
      peer_ctr++;
    }
    *pzl_ptr.squares[i][j].units[1][row_ctr] = &(*pzl_ptr.squares[row_ctr][k]);
  }
  mod_row=row%3;
  mod_col=col%3;
  k=0;
  for (row_ctr=row-mod_row;row_ctr<(row-mod_row+3); row_ctr++){
    for (col_ctr=col-mod_col; col_ctr<(row-mod_col+3); col_ctr++){
      if (ExistInArr(&(*pzl_ptr.squares[i][j])  ), (&(*pzl_ptr.squares[row_ctr][col_ctr]))== false){
        *pzl_ptr.squares[i][j].peers[peer_ctr]=&(*pzl_ptr.squares[row_ctr][col_ctr]);
        peer_ctr++;
      }
      *pzl_ptr.squares[i][j].units[2][k] = &(*pzl_ptr.squares[row_ctr][col_ctr]);
      k++;
        )
      }
    }
  }
  
}

static bool ExistInArr(square_t *sq_or, square_t *sq_add){
  int i;
  for (int i=0; i<20, i++){
    if (*sq_or.peers[i] == sq_add){
      return true;
    }
    else{
      return false;
    }
  }
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
  square_t *sq = &((*puz).squares[row][col]);
  int i;
  strcpy((*sq).vals,"");
  (*sq).vals[0]=val;
  (*sq).vals[1]='\0';
  for (i=0;i<20;i++){
    eliminate(puz, row, col, val);
  }


  return puz;
}

static puzzle_t *eliminate(puzzle_t *puz, int row, int col, char val) {
  int i, k, len, newlen;
  square_t *peer;
  char *target;
 for (i=0;i<20;i++){
   peer = ((*puz).squares[row][col]).peers[i];
   len=strlen((*peer).vals);
   if(len>1){
     target=strchr((*peer).vals, val);
     if (target!=NULL){
       memmove(target++,target,len);
       newlen = (len-1);
       if (newlen==1){
         assign(puz,row,col,(*peer).vals[0]);
       }

     }
   
   }
   else{
     assign(puz,row,col,(*peer).vals[0]);
   }
  }
 return puz;



  
}

/*****************************************/
/* Misc (e.g., utility) functions follow */
/*****************************************/
