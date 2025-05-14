/*
  This file has a main function to test a binary search tree
  that stores word count frequencies.  
  
  Pseudocode was taken from ODS - 
   https://opendatastructures.org/ods-python/6_Binary_Trees.html
  and then adapted to this assignment.

  See bst.h and bst.c for how the BST functions.

  Note - for any functions that create nodes or modify the data of a node,
   you should assume that the parameters to the function do not persist past
   the end of the function call. In particular, for strings, you need to 
   strdup them to store into the data struct (and free previous pointer).

  Make sure to free all memory before it is not used any more. Your program
  will not be graded as correct if it has /any/ memory leaks.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

int main(int argc, char *argv[]) {
  // parse the command-line arguments based on the comments above.  
  if (argc > 1 &&
      (strcmp(argv[1], "--help") == 0 || strcmp(argv[1],"-h") == 0)) {
    printf("Usage: ./bst_driver.o [optional_arguments]\n"
	   "reads from stdin\n"
	   "arguments are optional (all default to off if not present):\n"
	   "print_tree      - will cause the entire tree to be printed at the end\n"
	   "print_node=word - will look for \"word\" in the final tree, and print its node if it is found\n"
	   "print_stats     - calls print_stats_bst after the final tree is printed\n"
	   "print_max       - prints the node with maximum count\n"
	   "remove_node=word - after done reading in from stdin, remove the given word\n"
	   "                   from the tree (if it was in the tree) note that you should\n"
	   "                   handle as many of these as are present, possibly more than one node to remove\n"
	   "left_first       - when printing tree, print the left items first (default is right items first)\n"
	   "redblack         - the tree should do the add_fixup and remove_fixup\n"
	   "                   operations after add/remove, so it's a red/black tree.\n"
	   "bigram              - if specified, then the tree is for each pair of consecutive words, rather than a single word\n" // just needs changes in the driver
	   "previous_node=word - look for node just before \"word\" in the final tree and print it\n"        // similar to find_bst, except to the left, and looking for strictly smaller
	   "punctuation         - print statistics about how much punctuation is in the words in the tree\n" // requires full tree traversal, similar to print_stats
	   "\n"
	   // lab7 is to make the following work properly -
	   "count_at_least=f - prints how many nodes have a count that is >= f\n"
	   "next_word=word   - look for node just after \"word\" in the final tree and print it\n"
	   "print_range=word1,word2 - print all words between word1 and word2\n"
	   ""
	   );
    exit(0);
  }

  // call the init function 
  bst_tree_t *t = initialize_bst();
  data_t d;

  int redblack=0, bigram=0;
  for(int i=1; i < argc; i++)
    if (strcmp(argv[i],"redblack") == 0) redblack = 1;
  for(int i=1; i < argc; i++)
    if (strcmp(argv[i],"bigram") == 0) bigram = 1;

  // loop scanf'ing like in h11, adding or updating counts for each word
  char s[100], s_prev[100] = "", s_bigram[200];
  while (scanf("%99s", s) == 1) {
    // before calling find_bst, call wordify_str on s,
    //       save the return value, and call find_bst on that.
    //       if the result is an empty string, though, skip it.
    char *w = wordify_str(s);
    if (w == NULL || strlen(w) == 0) continue;

    if (bigram) {
      if (strcmp(s_prev, "") == 0) {
	// skip the first word, when s_prev isn't anything yet
	sscanf(w, "%99s", s_prev);
	continue;
      }
      s_prev[99] = w[99] = '\0';
      sprintf(s_bigram,"%s %s", s_prev, w);

      // once done with s_prev, copy w for the next time
      sscanf(w, "%99s", s_prev);
      d.word = s_bigram;
    }
    else {
      d.word = w;
    }

    bst_node_t * p = find_eq_bst(&d, t);
    if (p == NULL) {
      //printf("adding new node %s\n", d.word);
      d.count = 1;

      add_bst(&d, t, redblack);
    }
    else {
      //printf("increasing count for %s\n", w);
      // had this word before, increment count
      p->data->count ++;
    }
  }
  
  // after while loop, do as appropriate based on the command-line arguments
  char * word = "";
  int left_first = 0;
  for(int i=1; i < argc; i++) {
    if (strcmp(argv[i], "left_first") == 0) left_first = 1;
    
    if (strcmp(argv[i], "print_tree") == 0) print_bst(t, left_first);
    if (strcmp(argv[i], "print_stats") == 0) print_stats_bst(t);
    if (strcmp(argv[i], "print_max") == 0) print_max_bst(t);
    
    if (strncmp(argv[i], "print_node=", strlen("print_node=")) == 0) {
      word = argv[i]+strlen("print_node=");
      d.word = word;
      bst_node_t *p = find_eq_bst(&d, t);
      if (p != NULL) printf("%s: %d\n", p->data->word, p->data->count);
    }
    
    if (strncmp(argv[i], "remove_node=", strlen("remove_node=")) == 0) {
      word = argv[i]+strlen("remove_node=");
      d.word = word;
      bst_node_t *p = find_eq_bst(&d, t);
      remove_node_bst(p, t, redblack);
    }

    if (strncmp(argv[i], "previous_node=", strlen("previous_node=")) == 0) {
      word = argv[i]+strlen("previous_node=");
      d.word = word;
      bst_node_t *p = find_prev_bst(&d, t);
      if (p != NULL) printf("%s: %d\n", p->data->word, p->data->count);
      else printf("None\n");
    }

    if (strcmp(argv[i], "punctuation") == 0) {
      punctuation_stats_bst(t);
    }

    // lab7 - check for new command-line options here, and handle them

    if (strncmp(argv[i], "next_word=", strlen("next_word=")) == 0) {
      word = argv[i] + strlen("next_word=");
      d.word = word;
      bst_node_t *p = find_next_bst(&d, t);
      if (p != NULL) {
        printf("%s: %d\n", p->data->word, p->data->count);
      }else{
        continue;
      }
    }

    if (strncmp(argv[i], "print_range=", strlen("print_range=")) == 0) {
      word = argv[i] + strlen("print_range=");
      char *word1 = strtok(word, ",");
      char *word2 = strtok(NULL, ",");
      print_bst_range(t, left_first, word1, word2);
    }

    if (strncmp(argv[i], "count_at_least=", strlen("count_at_least=")) == 0) {
      int val = atoi(argv[i] + strlen("count_at_least="));
      int count = count_at_least_bst(t, val);
      printf("%d\n", count);
    }
  }

  free_bst(t); t = NULL;
  return 0;
}
