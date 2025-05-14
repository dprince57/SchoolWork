#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct DATA {
  // will store a word, will be malloc or strdup'ed and need to be free'd
  char *word;
  // count of frequency of the word
  int count;
} data_t;


typedef struct BST_NODE {
  data_t *data;
  struct BST_NODE *parent;
  struct BST_NODE *left;
  struct BST_NODE *right;
  char color;              // for red black tree, will be 'r' or 'b'
} bst_node_t;


typedef struct BST_TREE {
  int n;
  bst_node_t *root;
} bst_tree_t;

// remove leading/trailing punctuation, make lower case
char *wordify_str(char *w);

// print like this:
// the 12345\n
// return 1 on success, 0 on error
int print_data_bst(const data_t *d, char color);

// create a new BST with no data, return a pointer to it or NULL if error
bst_tree_t *initialize_bst();

// create a new BST node with given data, malloc new space and copy the data
// return NULL if error, and if so free any malloc'ed memory as well
bst_node_t *create_node_bst(const data_t *d);

// return the depth of node u in the tree, from the root to u
// return -1 on error
int depth_bst(const bst_node_t *u, const bst_tree_t *t);

// return how many nodes in the tree
// return -1 on error
int size_bst(const bst_tree_t *t);

// return the height of the node in the tree
//  leaves have height 1
//  non-leaves have height 1 + max(height of each left, height of right)
// return -1 on error
int height_bst(const bst_node_t *u, const bst_tree_t *t);


// print the bst, from lowest to highest, 2 spaces per level, like this
/*
  3
10
    15
      18
  20
    30
 */
// return 1 on success, 0 on error
// you likely will want to create a helper function that is recursive
int print_bst(const bst_tree_t *t, int left_first);

// print the node with max count
// return 1 on success, 0 on error
int print_max_bst(const bst_tree_t *t);

// print tree stats...
//   # of nodes
//   height of the root
//   average node height
//   average count value
// return 1 on success, 0 on error
int print_stats_bst(const bst_tree_t *t);

int punctuation_stats_bst(const bst_tree_t *t);

// return a pointer to the node that has value d, or NULL if not present
bst_node_t *find_eq_bst(const data_t *d, const bst_tree_t *t);

// return a pointer to the node with value that is smallest and >= d
// and return NULL if d is larger than all items in the tree (or empty tree)
bst_node_t *find_bst(const data_t *d, const bst_tree_t *t);

bst_node_t *find_prev_bst(const data_t *d, const bst_tree_t *t);

// make a new node, add it to the tree in the right place
// if d is already in the tree, just return that node (without adding)
// return NULL on error
// redblack - 0 or 1 to indicate whether this should be a redblack tree
bst_node_t *add_bst(const data_t *d, bst_tree_t *t, int redblack);


// redblack tree
// return 1 if successful, 0 if failed
int add_fixup(bst_node_t *u, bst_tree_t *t);

// redblack tree
// return 1 if successful, 0 if failed
int remove_fixup(bst_node_t *u, bst_tree_t *t);


// do a search for d, and return the last node that we visited trying to
//  look for it (that would be the parent if we are inserting d into the tree)
// return NULL on error
bst_node_t *find_last_bst(const data_t *d, const bst_tree_t *t);

// add node u as a child of node p, we can assume this is the right place to put u
//   return NULL if there is a problem
// note: a helper function that add_bst uses
bst_node_t *add_child_bst(bst_node_t *p, bst_node_t *u);

// remove the node from the tree
//  cases: u is a leaf, u has only one child, u has two children
//  if u has two children, replace it with the node that has smallest value
//   greater than u (the left-most thing on the right side of u)
// free u's memory when done
// return 1 on success, 0 on error
// redblack - 0 or 1 to indicate whether this should be a redblack tree
int remove_node_bst(bst_node_t *u, bst_tree_t *t, int redblack);

// remove u from the tree, assuming it has only one child
// return u's parent
// free u's memory when done
// return NULL on error
bst_node_t *splice_bst(bst_node_t *u, bst_tree_t *t);


// free all memory
// return 1 on success, 0 on error
int free_bst(bst_tree_t *t);


// lab7 functions
// you should create these in bst.c

// return the number of nodes in the tree that have a count that is at least val
// return 0 if t or t->root is NULL
int count_at_least_bst(const bst_tree_t *t, int val);
int count_at_least_bst_helper(const bst_node_t *u, int val);

// return a pointer to the node with value that is smallest and > d
// and return NULL if d is larger than all items in the tree (or empty tree)
bst_node_t *find_next_bst(const data_t *d, const bst_tree_t *t);

// print nodes in the tree that are >= word1 and <= word2
// return 1 on success, 0 on error.
int print_bst_range(const bst_tree_t *t, int left_first, char *word1, char *word2);
int print_bst_node_helper(const bst_node_t *u, int depth, int left_first, char *word1, char *word2);

#endif
