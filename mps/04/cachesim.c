#include <stdio.h>
#include <stdlib.h>


//defining line structures
typedef struct line{
  int valid;
  int tag;
  int tstmp;
} line_t; 





int main (int argc, char *argv[]) {
    int num_lines = atoi(argv[1]),
        lines_per_set = atoi(argv[2]),
        bytes_per_block = atoi(argv[3]);
    
    char line[80];
    
    long addr_req;
    //number of sets that will be in cache
    int num_sets=num_lines/lines_per_set;
    /*
    printf("Simulating cache with:\n");
    printf(" - Total lines   = %d\n", num_lines);
    printf(" - Lines per set = %d\n", lines_per_set);
    printf(" - Block size    = %d bytes\n", bytes_per_block);
    printf(" - Number of sets = %d\n", num_sets);
    */
    int n = 0;
    typedef struct set{
      line_t sline[lines_per_set];
    }set_t;
    typedef struct cache{
      set_t cset[num_sets];
    }cache_t;
    int hits=0;
    //intializing the cache, making all the bits validity = 0
    cache_t newcache;
    int i, j, found, lru_spot, lru_diff, tdiff;
    for (i=0; i<num_sets;i++){
      for (j=0; j<lines_per_set; j++){
        newcache.cset[i].sline[j].valid=0;
      }
    }
    while (fgets(line, 80, stdin)) {
      found=0;
      i=0;
      addr_req = strtol(line, NULL, 0);
      int index=(addr_req/bytes_per_block)%num_sets;
      int tagw=(addr_req/bytes_per_block)/num_sets;
      //searching to see if data is in the cache
      while (i<lines_per_set && found == 0){
        if ((newcache.cset[index].sline[i].tag) == tagw && (newcache.cset[index].sline[i].valid == 1)){
          hits++; 
          found=1;
          newcache.cset[index].sline[i].tstmp = n;
        }
        i++;
      }
      //searching for within the set for an empty spot if available.
      i=0;
      if (found==0){
        while (i<lines_per_set && found==0){
          if (newcache.cset[index].sline[i].valid == 0){
            newcache.cset[index].sline[i].tag = tagw;
            newcache.cset[index].sline[i].valid=1;
            newcache.cset[index].sline[i].tstmp=n;
            found=1;
          }
          i++;
        }
      }
      i=0;
      lru_diff=0;
      //no empty spots so we are looking for the least recently used block in the set
      if (found==0){
        for(i=0;i<lines_per_set;i++){
          tdiff=n-newcache.cset[index].sline[i].tstmp;
          if(tdiff>lru_diff){
            lru_spot=i;
            lru_diff=tdiff;
          }
        }
        newcache.cset[index].sline[lru_spot].tag=tagw;
        newcache.cset[index].sline[lru_spot].valid=1;
        newcache.cset[index].sline[lru_spot].tstmp=n;
      }
      n++;
      
        /* simulate cache fetch with address `addr_req` */
      //        printf("Processing request: 0x%lX\n", addr_req);
    }
    printf("The hit rate is: %f | Miss rate is %f\n", (double)hits/n, (double)(n-hits)/n);
    return 0;
}

