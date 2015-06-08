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

typedef struct puzzle {
  square_t squares[NUM_ROWS][NUM_COLS];
} puzzle_t;

void solve(unsigned char grid[9][9]);

// following are static ("private") function declarations --- add as needed

static puzzle_t *create_puzzle(unsigned char grid[9][9]);
static void init_peers(puzzle_t *puz, int row, int col);
static puzzle_t *copy_puzzle(puzzle_t *puz);
static void free_puzzle(puzzle_t *puz);
static void print_puzzle(puzzle_t *);
static int existInArr(square_t *sq_or, square_t *sq_add);
static puzzle_t *search(puzzle_t *puz);
static puzzle_t *assign(puzzle_t *puz, int row, int col, char val);
static puzzle_t *eliminate(puzzle_t *puz, int row, int col, char val);
static int MaxLenInPuz(puzzle_t *puz);

static square_t *Unique(square_t *sq, char val, int unit);
/*************************/
/* Public solve function */
/*************************/

void solve(unsigned char grid[9][9]) {
  puzzle_t *puz = create_puzzle(grid);
  puzzle_t *solved;
  if ((solved = search(puz)) != NULL) {
    print_puzzle(solved);
  }
  free_puzzle(puz);
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
      strcpy((*sq).vals, DIGITS);
      (*sq).row = i;
      (*sq).col = j;
      //printf("the row is:%d the col is:%d\n", (*sq).row, (*sq).col);
    }
  }
  // printf("just assigned all the squares 9 possible digits\n");
  // print_puzzle(pzl_ptr);
  for (i=0; i<NUM_ROWS; i++){
    for (j=0; j<NUM_COLS; j++){
      init_peers(pzl_ptr, i, j);
    }
  }
  //  printf("initiated the peers\n");
  //  printf("%s\n", vals);
  for (i=0; i<NUM_ROWS; i++){
    for (j=0; j<NUM_COLS; j++){
      if (vals[i][j]!='0'&& vals[i][j] != '.'){
        //    printf("%c", vals[i][j]);
      }
      if(vals[i][j]!='0' &&  vals[i][j] !='.'){
        assign(pzl_ptr,i,j, vals[i][j]);//assigning of the values that were given
      }
    }
  }
  // printf("\n\nassigning given values\n");
  // print_puzzle(pzl_ptr);
  // printf("\n\n\n");
  //  printf("create puzzle finished sucessfully!! :)\n");
  return pzl_ptr;

}



//intiates peers and units
static void init_peers(puzzle_t *puz, int row, int col) {
  int   j, peer_ctr, row_ctr, col_ctr, mod_row, mod_col;
  peer_ctr=0;
  if (puz==NULL){
    // printf("Error with pointer, it is null\n");
  }
  //  printf("started the init_peers and units function\n");
  // printf("working on square :%d, %d\n", row , col );
  for (col_ctr=0; col_ctr<NUM_COLS; col_ctr++){
    // printf("working on column: %d\n", col_ctr);
    //printf("row:%d othersquarerow:%d\n", row, (*puz).squares[row][col].row);

    if(col!=col_ctr){//where the segmentation fault is occurring
      ((*puz).squares[row][col]).peers[peer_ctr] = &((*puz).squares[row][col_ctr]);
      // printf("assigned peer from the row%d: %d\n",row, peer_ctr);
      peer_ctr++; 
    }
    
    ((*puz).squares[row][col]).units[0][col_ctr] = &((*puz).squares[row][col_ctr]);
  }
  for (row_ctr=0; row_ctr<NUM_ROWS; row_ctr++){
    if (row!= row_ctr){
      ((*puz).squares[row][col]).peers[peer_ctr] = &((*puz).squares[row_ctr][col]);
      //printf("assigned peer from col%d: %d\n",col, peer_ctr); 
      peer_ctr++;
      
    }
    ((*puz).squares[row][col]).units[1][row_ctr] = &((*puz).squares[row_ctr][col]);
  }
  mod_row=row%3;
  mod_col=col%3;
  j=0;
  
  for (row_ctr=(row-mod_row);row_ctr<(row-mod_row+3); row_ctr++){
    for (col_ctr=(col-mod_col); col_ctr<(col-mod_col+3); col_ctr++){
      if (peer_ctr!=20){
        //  printf("Whether the peer already exists: %d\n", (existInArr(&((*puz).squares[row][col]), &((*puz).squares[row_ctr][col_ctr]))));
        // printf("Target square is: %d %d \n", row_ctr, col_ctr);
        if (existInArr(&((*puz).squares[row][col]), &((*puz).squares[row_ctr][col_ctr])) == 0){
          ((*puz).squares[row][col]).peers[peer_ctr]=&((*puz).squares[row_ctr][col_ctr]);
          // printf("assigned peer from respective box: %d\n", peer_ctr);
          peer_ctr++;
        } 
      }
      ((*puz).squares[row][col]).units[2][j] = &((*puz).squares[row_ctr][col_ctr]);
      j++;
    }
  }
}
  

static int existInArr(square_t *sq_or, square_t *sq_add){
  int i;
  for (i=0; i<16; i++){
    if ((*sq_or).peers[i] == sq_add){
      // printf("%p is the address in peer, %p address of target\n", (*sq_or).peers[i], sq_add);
      return 1;
    }
  }
  return 0;
}

static void free_puzzle(puzzle_t *puz) {
  free(puz);
}

//returns copy of the puzzle
static puzzle_t *copy_puzzle(puzzle_t *puz) {
  puzzle_t *copy_puz=malloc(sizeof(puzzle_t));
  *copy_puz=*puz;
  return copy_puz;
}

void print_puzzle(puzzle_t *p) {
  int i, j;
  for (i=0; i<NUM_ROWS; i++) {
    for (j=0; j<NUM_COLS; j++) {
      // printf(" %9s", p->squares[i][j].vals); // may be useful while debugging
      printf(" %2s", p->squares[i][j].vals);
    }
    printf("\n");
  }
}

/**********/
/* Search */
/**********/

static puzzle_t *search(puzzle_t *puz) {
  int j, k, sq_len, i, minlen, maxlen;
  puzzle_t *copy_puz, *check;
  square_t *sq;
  // printf("The search has started\n");
  if (puz==NULL){
    // printf("the solve failed\n");
    return NULL;//Failed Earlier
  }
  maxlen = (MaxLenInPuz(puz));
  // printf("The max length is %d\n", maxlen);
  if (maxlen==1){
    return puz;
  }
  else{
    for (minlen=2;minlen<(maxlen+1);minlen++){
      for(i=0;i<NUM_ROWS;i++){
        for (j=0;j<NUM_COLS;j++){
          sq=&((*puz).squares[i][j]);
          sq_len = strlen((*sq).vals);
          //  printf("The length of square %d %d is %d\n", i, j, sq_len);
          if (sq_len==minlen){
            // printf("location of min square is: %d %d\n",i,j);
            for (k=0;k<sq_len;k++){
              copy_puz=copy_puzzle(puz);
              //          printf("Copied Puzzle successfully in round %d\n", k);
              // printf("Assigning Value %c\n", (*sq).vals[k]);
              check=assign(copy_puz, i, j, (*sq).vals[k]);
              // printf("Value of check %p\n", check);
              if (check == NULL){
                free_puzzle(copy_puz);
              }
              else{
                search(copy_puz);
              }
            }
          }
        }
      }
    }
  }
}

/**************************/
/* Constraint propagation */
/**************************/

static puzzle_t *assign(puzzle_t *puz, int row, int col, char val) {
  square_t *sq = &((*puz).squares[row][col]);
  printf ("assigning value %c to square %d %d \n", val, row, col);
  //strcpy((*sq).vals,"");
  (*sq).vals[0]=val;
  (*sq).vals[1]='\0';
  // printf("%s\n", (*sq).vals);
  
 
   eliminate(puz, row, col, val);

  return puz;
}



/*****************************************/
/* Misc (e.g., utility) functions follow */
/*****************************************/
//Finds what the maximum length of the puzzle is.
static int MaxLenInPuz(puzzle_t *puz){
  square_t *sq;
  int i, j, maxlen=0, sqlen;
  for (i=0;i<NUM_ROWS;i++){
    for (j=0;j<NUM_COLS;j++){
      sq=&(*puz).squares[i][j];
      sqlen=strlen((*sq).vals);
      if (sqlen>maxlen){
        maxlen=sqlen;
      }
    }
  }
  return maxlen;
}

static puzzle_t *eliminate(puzzle_t *puz, int row, int col, char val) {
  int i,j, len, newlen, uni_row, uni_col, loc_index, sqsa_counter;
  square_t *peer, *sq, *unique_sq, *sqs_to_assign[20];
  char *target;
  char unittester[10];
  strcpy(unittester,DIGITS);
  sqsa_counter=0;
  //elminating all the values from the peers
  for (i=0;i<20;i++){
    peer = ((*puz).squares[row][col]).peers[i];
    len=strlen((*peer).vals);
    if (len > 1){
      target=strchr((*peer).vals, val);
      if (target!=NULL){
        for (j=0;j<len;j++){
          if ((*peer).vals[j]==val){
            loc_index=j;
          }
        }
        if ((*peer).row > 8){
          // printf("this row was made bad before memmove\n");
        }
        memmove(target++,target,(len-loc_index));
        if ((*peer).row>8){
          //  printf("memmove is screwing the row on square %d %d\n", (*peer).row, (*peer).col);
        }
        newlen=strlen((*peer).vals);
        if (newlen==0){
          return NULL;
        }//checking to see if squares are left with final values
        else if (newlen==1){
          sqs_to_assign[sqsa_counter]=peer;
          sqsa_counter++;
          
          //   printf("\nassigning value %c to square %d %d\n", (*peer).vals[0], (*peer).row, (*peer).col);
        }
    
      }
    }
  }
  for (i=0;i<sqsa_counter;i++){
    sq=sqs_to_assign[i];
    eliminate(puz,(*sq).row ,(*sq).col,(*sq).vals[0]);
  }
  //printf("\n\nDoes here even get passed?\n");
  sq=&(*puz).squares[row][col];
  for (i=0; i<3;i++){
    // printf("The unit is :%d\n", i);
    for (j=0; j<9;j++){
      unique_sq=Unique(sq,unittester[j],i);
      // printf("The value we are testing for %c\n", unittester[j]);
      //printf("The Unique value is: %p\n", unique_sq);
        if (unique_sq != NULL){
          //printf("This square is unique: %p\n", unique_sq);
          uni_row=(*unique_sq).row;
          uni_col=(*unique_sq).col;
          assign(puz, uni_row, uni_col, unittester[j]);
          printf("\nUniqueUnit assigning value %c to square %d %d\n", unittester[j]  , uni_row, uni_col);
      }
    }
    }

  return puz;
}




//Unique testing for a unique value in a specefic row
static square_t* Unique(square_t *sq, char val, int unit){
  square_t *sq_u, *sq_tar;
  int i,j, count, len;
  count=0;
  for (i=0;i<9;i++){
    //printf("Is the fault right here?\n");
    sq_u=(*sq).units[unit][i];
    len=strlen((*sq_u).vals);
    //    printf("Location of where in unit is %d %d. The vals are %s and the length is %d\n",unit, i, (*sq_u).vals, len);
    if (len>1){
      for (j=0;j<len;j++){
        if ((*sq_u).vals[j]==val){
          count++;
          sq_tar=sq_u;
          }
      }
    }
  }
  if (count==1){
    return sq_tar;
      }else{
    return NULL;
  }
  
}



