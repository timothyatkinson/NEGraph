#ifndef DECODE_H
#define DECODE_H

//C Libraries
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <float.h>

//P-GP2 Libraries
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

//Local Libraries
#include "li_net.h"

//Useful functions
bool is_parameter(Node* node);
bool is_input(Node* node);
bool is_bias(Node* node);
char* get_node_identifier(Node* node);
int get_node_value(Node* node);
int get_edge_value(Edge* edge);
double get_edge_weight(Edge* edge);
double get_input_scaling(Graph* graph);
double get_spectral_radius(Graph* graph);
double get_leak_rate(Graph* graph);

//Actual legwork
li_net* decode_graph(Graph* graph, int inputs);
#endif
