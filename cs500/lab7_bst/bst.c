// 

#include "bst.h"

/*
  malloc and initialize new bst struct, return the pointer to it
 */
bst_tree_t *initialize_bst() {
  bst_tree_t *t = (bst_tree_t *) malloc(sizeof(bst_tree_t));
  if (t == NULL) return NULL;

  // initialize to be empty: NULL root, n=0
  t->root = NULL; 
  t->n = 0;
  return t;
}

// trim off leading and trailing punctuation, and lowercase everything
char *wordify_str(char *w) {
  if (w == NULL) return NULL;

  // remove leading punctuation
  while (ispunct(*w)) {
    w++;
  }
  char *begin_w = w;

  // remove trailing punctuation
  int i = strlen(begin_w);
  if (i == 0) return begin_w;
  i--;
  while (i >= 0 && ispunct(begin_w[i])) {
    begin_w[i] = '\0';
    i--;
  }

  // convert to lower case
  i = 0;
  while (begin_w[i] != '\0') {
    begin_w[i] = tolower(begin_w[i]);
    i++;
  }

  return begin_w;
}

int print_data_bst(const data_t *d, char color) {
  if (d == NULL) return 0;
  printf("%s: %d", d->word, d->count);
  if (color != ' ')
    printf(" (%s)", color == 'r' ? "red" : "black");
  printf("\n");
  return 1;
}

// create a new BST node with given data, malloc new space and copy the data
bst_node_t *create_node_bst(const data_t *d) {
  if (d == NULL) return NULL;

  // malloc memory for the node
  bst_node_t * p = (bst_node_t *) malloc(sizeof(bst_node_t));
  if (p == NULL) return NULL;

  // init pointers to NULL
  p->left = p->right = p->parent = NULL;
  p->color = ' ';

  // malloc memory for the data
  p->data = (data_t *) malloc(sizeof(data_t));
  if (p->data == NULL) {
    free(p);
    return NULL;
  }

  // set the count, and malloc/copy the word string
  p->data->count = d->count;
  p->data->word = strdup(d->word);

  return p;
}

// return the depth of node u in the tree, from the root to u
int depth_bst(const bst_node_t *u, const bst_tree_t *t) {
  if (u == NULL || t == NULL) return -1;

  // start at u, go to parent, keep going until
  //  get to root node
  int count = 0;
  const bst_node_t *p = u;
  while (p->parent != t->root) {
    count++;
    p = p->parent;
  }
  return count;
}

// return how many nodes in the tree
int size_bst(const bst_tree_t *t) {
  if (t == NULL) return -1;
  return t->n;
}

// return the height of the node in the tree
//  leaves have height 1
//  non-leaves have height 1 + max(height of each left, height of right)
int height_bst(const bst_node_t *u, const bst_tree_t *t) {
  // if we're empty, return 0
  if (u == NULL || t == NULL) return 0;

  // return 1 + the larger of the left or right
  int l = height_bst(u->left, t),
    r = height_bst(u->right, t);
  if (l > r) return l+1;
  else return r+1;
}


// print the bst, from lowest to highest, 2 spaces per level, like this
/*
  3
10
    15
      18
  20
    30
 */
int print_bst_node(const bst_node_t *u, int depth, int left_first) {
  // if NULL pointer, then we reached the end of a leaf, don't do anything
  // base case of recursion
  if (u == NULL) return 1;

  bst_node_t *p_first = u->left,
    *p_second = u->right;
  if (! left_first) {
    p_first = u->right;
    p_second = u->left;
  }
  
  // do the left
  if (!print_bst_node(p_first, depth+1, left_first)) return 0;

  // do this node
  printf("%*s", 2*depth, "");
  if (!print_data_bst(u->data, u->color)) return 0;

  // do the right
  return print_bst_node(p_second, depth+1, left_first);

  // putting things together
}

int print_bst(const bst_tree_t *t, int left_first) {
  if (t == NULL) return 0;
  return print_bst_node(t->root, 0, left_first);
}

// get the node with max count
const bst_node_t *get_max_bst(const bst_node_t *p) {
  if (p == NULL) return NULL;
  
  const bst_node_t *max_left = get_max_bst(p->left),
    *max_right = get_max_bst(p->right);

  const bst_node_t *max = p;
  
  if (max_left != NULL && max_left->data->count > max->data->count)
    max = max_left;
  
  if (max_right != NULL && max_right->data->count > max->data->count)
    max = max_right;

  return max;
}

int print_max_bst(const bst_tree_t *t) {
  if (t == NULL || t->root == NULL) return 0;

  const bst_node_t *max = get_max_bst(t->root);
  if (max == NULL) return 0;
  
  if (!print_data_bst(max->data, max->color)) return 0;

  return 1;
}

int stats_bst(const bst_node_t *u, int *total_count, int *max_depth, int *total_depth, int *curr_depth, int *total_height, int *height, int *max_count) {
  if (u == NULL) {
    *height = -1; // so leaves will be height 0
    return 1;
  }
  
  (*total_count) += u->data->count;
  *total_depth += *curr_depth; // curr_depth should correct when called

  if (*curr_depth > *max_depth) *max_depth = *curr_depth;

  (*curr_depth) ++;
  int left_height = 0, right_height = 0;
  stats_bst(u->left, total_count, max_depth, total_depth, curr_depth, total_height, &left_height, max_count);
  stats_bst(u->right, total_count, max_depth, total_depth, curr_depth, total_height, &right_height, max_count);
  (*curr_depth) --;
  // assuming left_height and right_height are the correct height of left and right children
  // if no left child, left_height will be -1 at this point. same for right

  if (left_height > right_height) {
    *height = left_height + 1;
  }
  else {
    *height = right_height + 1;
  }
  *total_height += *height;

  if (u->data->count > *max_count) *max_count = u->data->count;

  return 1;
}

// print tree stats...
//   # of nodes
//   height of the root
//   average node height
//   average count value
int print_stats_bst(const bst_tree_t *t) {
  if (t == NULL) return 0;
  int total_count = 0, max_depth = 0, total_depth = 0, curr_depth = 0, total_height = 0, height = 0, max_count = 0;
  if (!stats_bst(t->root, &total_count, &max_depth, &total_depth, &curr_depth, &total_height, &height, &max_count)) return 0;
  printf("number of nodes: %d\n", t->n);
  if (t->n > 0) {
    printf("average count:   %2.2f\n", (float) total_count / t->n);
    printf("max count:       %d\n", max_count);
    printf("average depth:   %2.2f\n", (float) total_depth / t->n);
    printf("average height:  %2.2f\n", (float) total_height / t->n);
    printf("root height:     %d\n", max_depth);
  }
  return 1;
}

int punct_stats_bst(const bst_node_t *u, int *n_words_punct, int *punct_count_punct, int *count_words_punct, const bst_node_t **max_p) {
  if (u == NULL) {
    return 1;
  }

  int punct_count = 0;
  for(int i=0; u->data->word[i] != '\0'; i++) {
    punct_count += (ispunct((u->data->word)[i]) != 0);
  }

  if (punct_count > 0) {
    (*n_words_punct) ++;
    (*punct_count_punct) += punct_count;
    (*count_words_punct) += u->data->count;

    if (*max_p == NULL ||
	u->data->count > (*max_p)->data->count)
      *max_p = u;
  }
  
  punct_stats_bst(u->left, n_words_punct, punct_count_punct, count_words_punct, max_p);
  punct_stats_bst(u->right, n_words_punct, punct_count_punct, count_words_punct, max_p);

  return 1;
}

int punctuation_stats_bst(const bst_tree_t *t) {
  if (t == NULL) return 0;
  int n_words_punct = 0, punct_count_punct = 0, count_words_punct = 0;
  const bst_node_t *max_p = NULL;
  if (!punct_stats_bst(t->root, &n_words_punct, &punct_count_punct, &count_words_punct, &max_p)) return 0;
  printf("number of nodes: %d\n", t->n);
  if (t->n > 0) {
    if (n_words_punct == 0) {
      printf("words with punctuation:   0\n");
    }
    else {
      printf("words with punctuation:   %2.2f%%\n", 100.0*(float) n_words_punct / t->n);
      printf(" with average count of:   %2.2f\n", (float) count_words_punct / n_words_punct);
      printf("  and avg # punct/word:   %2.2f\n", (float) punct_count_punct / n_words_punct);
      printf("    max count for word:   %s (count of %d)\n", max_p->data->word, max_p->data->count);
    }
  }
  return 1;
}

// return a pointer to the node that has value d, or NULL if not present
bst_node_t *find_eq_bst(const data_t *d, const bst_tree_t *t) {
  if (d == NULL || t == NULL) return NULL;
  
  bst_node_t *w = t->root; // w = r
  while (w != NULL) {      // NULL instead of Nil
    int value = strcmp(d->word, w->data->word); // w.x == x
    if (value == 0) return w;
    else if (value < 0) w = w->left;
    else w = w->right;
  }
  return w;
}

// return a pointer to the node with value that is smallest and >= d
// and return NULL if d is larger than all items in the tree (or empty tree)
bst_node_t *find_bst(const data_t *d, const bst_tree_t *t) {
  if (d == NULL || t == NULL) return NULL;

  // 
  bst_node_t *w = t->root; // looking for where d would be
  bst_node_t *z = NULL; // something larger than d, if/when we find one
  while (w != NULL) {
    int compare = strcmp(d->word, w->data->word);
    if (compare < 0) { // d would be left of w
      z = w;           // remember z, something larger than d
      w = w->left;
    }
    else if (compare > 0) { // d would be right of w
      w = w->right;
    }
    else { // found d
      return w;
    }
  }
  // if we didn't find d, return the last thing larger that we saved
  return z;
}

// return a pointer to the node with value that is largest and < d
// and return NULL if d is smaller than all items in the tree (or empty tree)
bst_node_t *find_prev_bst(const data_t *d, const bst_tree_t *t) {
  if (d == NULL || t == NULL) return NULL;

  // 
  bst_node_t *w = t->root; // looking for where d would be
  bst_node_t *z = NULL; // something smaller than d, if/when we find one
  while (w != NULL) {
    int compare = strcmp(d->word, w->data->word);
    if (compare > 0) { // d would be right of w
      z = w;           // remember z, something smaller than d
      w = w->right;
    }
    else if (compare < 0) { // d would be left of w
      w = w->left;
    }
    else { // found d
      // looking for next smallest, so go left if we can, and then right as far as we can
      if (w->left != NULL) {
	w = w->left;
	while (w->right != NULL) w = w->right;
	return w;
      }
      else // no left child, so need to go up to parent
	if (w->parent != NULL) {
	  if (w == w->parent->right)
	    return w->parent;
	  else {
	    // go up the tree until something < d
	    w = w->parent;
	    while (w != NULL && strcmp(w->data->word, d->word) > 0)
	      w = w->parent;
	    return w;
	  }
      }
      else // if no parent and no left, no result
	return NULL;

    }
  }
  // if we didn't find d, return the last thing smaller that we saved
  return z;
}

// make a new node, add it to the tree in the right place
// if d is already in the tree, just return that node (without adding)
bst_node_t *add_bst(const data_t *d, bst_tree_t *t, int redblack) {
  if (d == NULL || t == NULL) return NULL;
  
  bst_node_t * p = find_last_bst(d, t);
  
  if (p != NULL && strcmp(p->data->word, d->word) == 0) return p;
  
  bst_node_t * new = create_node_bst(d);
  if (p == NULL) t->root = new;
  else add_child_bst(p, new);
  
  t->n ++;

  if (redblack) {
    new->color = 'r';
    add_fixup(new, t);
  }
      
  return new;
}

// do a search for d, and return the last node that we visited trying to
//  look for it (that would be the parent if we are inserting d into the tree)
bst_node_t *find_last_bst(const data_t *d, const bst_tree_t *t) {
  bst_node_t *w = t->root;
  bst_node_t *prev = NULL;
  while (w != NULL) {
    prev = w;
    int value = strcmp(d->word, w->data->word);
    if (value == 0) return w;
    else if (value < 0) w = w->left;
    else w = w->right;
  }
  // note: if the tree is empty, then NULL will be returned
  return prev;
}

// add node u as a child of node p, we can assume this is the right place to put u
//   return NULL if there is a problem, else return u
// note: a helper function that add_bst uses
bst_node_t *add_child_bst(bst_node_t *p, bst_node_t *u) {
  assert(p != NULL); assert(u != NULL);

  int val = strcmp(u->data->word, p->data->word);
  if (val < 0) p->left = u;
  else if (val > 0) p->right = u;
  else return NULL;
  
  u->parent = p;

  return u;
}

// remove the node from the tree
//  cases: u is a leaf, u has only one child, u has two children
//  if u has two children, replace it with the node that has smallest value
//   greater than u (the left-most thing on the right side of u)
// free u's memory when done
int remove_node_bst(bst_node_t *u, bst_tree_t *t, int redblack) {
  if (u == NULL || t == NULL) return 0;
  
  // if either left or right is NULL, we can just remove this node
  if (u->left == NULL || u->right == NULL) {
    splice_bst(u, t); 
    return 1;
  }
  else {
    // otherwise, find the smallest in the right half, and swap
    //  that in to this node.
    bst_node_t *w = u->right;
    while (w->left != NULL) {
      w = w->left;
    }
    // put w's data here in u's, then splice out w
    data_t tmp = *(u->data); // need to remember so we can free the word
    *(u->data) = *(w->data); 
    *(w->data) = tmp;
    splice_bst(w, t);
  }
  return 1;
}

int free_node(bst_node_t *u);

// remove u from the tree, assuming it has only one child
// return u's parent
// free u's memory when done
bst_node_t *splice_bst(bst_node_t *u, bst_tree_t *t) {
  if (u == NULL || t == NULL)
    return NULL;

  // u will be replaced with its child, either left or right
  bst_node_t *s = NULL, *p = NULL;
  if (u->left != NULL)
    s = u->left;
  else
    s = u->right;

  // note that if s is NULL that means u didn't have any children

  if (u == t->root) {     // if we're removing the root
    t->root = s;
    p = NULL;
  }
  else {
    // not removing the root, so we have a parent
    p = u->parent;
    // update p's pointer to u to point to s instead
    if (p->left == u) p->left = s;
    else p->right = s;
  }
  // update s's parent pointer to be p
  if (s != NULL) s->parent = p;

  // subtract 1 from how many nodes in the tree
  t->n -= 1;

  // free memory no longer needed
  free_node(u);
  
  return p;
}

int free_node(bst_node_t *u) {
  if (u != NULL) {
    if (u->data != NULL) {
      if (u->data->word != NULL)
	free(u->data->word);
      free(u->data);
    }
    free(u);
  }
  return 1;
}

int free_node_and_descendants(bst_node_t *u) {
  if (u != NULL) {
    free_node_and_descendants(u->left);
    free_node_and_descendants(u->right);
    free_node(u);
  }
  return 1;
}

int free_bst(bst_tree_t *t) {
  if (t != NULL) {
    free_node_and_descendants(t->root);
    free(t);
  }
  return 1;
}

char flip_color(char c) {
  if (c == 'r') return 'b';
  else return 'r';
}

void push_black(bst_node_t *u) {
  if (u == NULL) return;
  
  u->color = flip_color(u->color);
  if (u->left != NULL)
    u->left->color = flip_color(u->left->color);
  if (u->right != NULL)
    u->right->color = flip_color(u->right->color);
}

void pull_black(bst_node_t *u) {
  push_black(u);
}

void swap_colors(bst_node_t *u, bst_node_t *v) {
  if (u == NULL || v == NULL) return;
  
  char tmp = u->color;
  u->color = v->color;
  v->color = tmp;
}


/*
       p
       u
    l    r
       rl  rr
-->
      p
      r
   u    rr
 l  rl
 */
void rotate_left(bst_node_t *u, bst_tree_t *t) {
  if (u == NULL || t == NULL) return;
  
  bst_node_t *p = u->parent,
    *r = u->right,
    *rl = r->left;
  
  u->right = rl;
  if (rl != NULL)
    rl->parent = u;

  if (r != NULL)
    r->left = u;
  u->parent = r;

  if (p == NULL)
    t->root = r;
  else if (p->left == u)
    p->left = r;
  else 
    p->right = r;
  if (r != NULL)
    r->parent = p;
}

void flip_left(bst_node_t *u, bst_tree_t *t) {
  swap_colors(u, u->right);
  rotate_left(u, t);
}

/*
       p
       u
     l   r
   ll lr
-->
       p
       l
    ll   u
       lr  r
 */
void rotate_right(bst_node_t *u, bst_tree_t *t) {
  if (u == NULL || t == NULL) return;
  
  bst_node_t *p = u->parent,
    *l = u->left,
    *lr = l->right;

  if (p == NULL)
    t->root = l;
  else if (u == p->left)
    p->left = l;
  else
    p->right = l;
  if (l != NULL)
    l->parent = p;

  if (l != NULL)
    l->right = u;
  u->parent = l;

  u->left = lr;
  if (lr != NULL)
    lr->parent = u;
}

void flip_right(bst_node_t *u, bst_tree_t *t) {
  swap_colors(u, u->left);
  rotate_right(u, t);
}


// redblack tree
// return 1 if successful, 0 if failed
int add_fixup(bst_node_t *u, bst_tree_t *t) {
  if (u == NULL || t == NULL) return 0;

  bst_node_t *w = NULL, *g = NULL;
  
  while (u->color == 'r') {
    if (u == t->root) {
      u->color = 'b';
    }
    else {
      w = u->parent;
      
      if (w->left == NULL || w->left->color == 'b') { // ?? or w->left == NULL || w->left->color == 'b'
	flip_left(w, t);
	u = w;
	w = u->parent;
      }
      if (w->color == 'b') {
	return 1; // red-red edge eliminated, done
      }
      g = w->parent;
      if (g->right == NULL || g->right->color == 'b') { // ?? or g->right != NULL && g->right->color == 'b'
	flip_right(g, t);
	return 1;
      }
      push_black(g);
      u = g;
    }
  }
  return 1;
}


// redblack tree
// return 1 if successful, 0 if failed
int remove_fixup(bst_node_t *u, bst_tree_t *t) {
  return 0;
}

// Helper function to count nodes with count >= val
int count_at_least_bst_helper(const bst_node_t *u, int val) {
    if (u == NULL) return 0;

    int count = 0;

    // Check the current node's count
    if (u->data->count >= val) count++;

    // Recurse for left and right subtrees
    count += count_at_least_bst_helper(u->left, val);
    count += count_at_least_bst_helper(u->right, val);

    return count;
}

// Return the number of nodes in the tree with count >= val
int count_at_least_bst(const bst_tree_t *t, int val) {
    if (t == NULL || t->root == NULL) return 0;
    return count_at_least_bst_helper(t->root, val);
}

// Find the node with the smallest value greater than d
bst_node_t *find_next_bst(const data_t *d, const bst_tree_t *t) {
    if (d == NULL || t == NULL || t->root == NULL) return NULL;

    bst_node_t *w = t->root; // Start from the root
    bst_node_t *z = NULL;    // Candidate for the next largest node

    while (w != NULL) {
        int compare = strcmp(d->word, w->data->word);
        if (compare < 0) { // d would be to the left of w
            z = w;        // Update z as a potential candidate
            w = w->left;
        } else { // d would be to the right or equal
            w = w->right;
        }
    }

    return z;
}

// Helper function to print nodes within a range
int print_bst_node_helper(const bst_node_t *u, int depth, int left_first, char *word1, char *word2) {
    if (u == NULL) return 1;

    bst_node_t *p_first = u->left, *p_second = u->right;

    // Determine traversal order
    if (!left_first) {
        p_first = u->right;
        p_second = u->left;
    }

    // Traverse the first subtree
    if (!print_bst_node_helper(p_first, depth + 1, left_first, word1, word2)) return 0;

    // Check if the current node is within range
    if (strcmp(u->data->word, word1) >= 0 && strcmp(u->data->word, word2) <= 0) {
        printf("%*s", 2 * depth, ""); // Indentation for depth
        if (!print_data_bst(u->data, u->color)) return 0;
    }

    // Traverse the second subtree
    return print_bst_node_helper(p_second, depth + 1, left_first, word1, word2);
}

// Print nodes in the tree that are >= word1 and <= word2
int print_bst_range(const bst_tree_t *t, int left_first, char *word1, char *word2) {
    if (t == NULL || t->root == NULL || word1 == NULL || word2 == NULL) return 0;
    return print_bst_node_helper(t->root, 0, left_first, word1, word2);
}
