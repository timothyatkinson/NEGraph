#ifndef CORE_GENOPS_H
#define CORE_GENOPS_H

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

#include "rand_util.h"
#include "../util.h"

static double P_MUTATE_PARAM = 0.3;
static double P_CORE_MUTATE = 0.25;

Graph* mutate_graph(Graph* graph);

#endif
