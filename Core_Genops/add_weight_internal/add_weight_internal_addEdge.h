#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchadd_weight_internal_addEdge(Morphism *morphism);

void applyadd_weight_internal_addEdge(Morphism *morphism, bool record_changes);
bool fillpotadd_weight_internal_addEdge(MorphismPot *pot, Morphism *morphism);

