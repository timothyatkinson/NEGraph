#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchadd_weight_internal_removeLoop(Morphism *morphism);

void applyadd_weight_internal_removeLoop(Morphism *morphism, bool record_changes);
bool fillpotadd_weight_internal_removeLoop(MorphismPot *pot, Morphism *morphism);

