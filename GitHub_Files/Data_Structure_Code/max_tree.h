#include<stdlib.h>
#include<stdio.h>
#include <math.h>
#include<time.h>

/* File created by Nathan Adelgren, Graduate Assisistant at Clemson University on as part of doctoral research
under the advisement of Drs. Pietro Belotti and Akshay Gupte. The goal of this program is to take singleton points and 
line segments as input, treat these input as possible solutions (in the objective space) of a bi-objective maximization 
problem, and create a binary tree that stores the Pareto set.*/

/* This file is designed to be easily converted to a file that can be used for minimization problems. In this file all 
inserted points are reflected about the origin and treated as if the problem is a minimization problem. Then, when 
reporting the Pareto set for the maximization problem, points are simply reflected back to their original position.*/

struct node
{
  	int type;			
	int subtree_size;	
	double slope;
	double nw_x;
	double nw_y;
	double se_x;
	double se_y;
	struct node *parent;
  	struct node *left;	
  	struct node *right;
};

typedef struct node node;

node *find_right_leaf(node *leaf);
node *find_left_leaf(node *leaf);
node *find_rightmost_leaf(node *leaf);
node *find_leftmost_leaf(node *leaf);
node *find_deepest_leaf_right(node *leaf);

void insert(int type, double nw_x, double nw_y, double se_x, double se_y, double slope, struct node **leaf, struct node **leaf2);


