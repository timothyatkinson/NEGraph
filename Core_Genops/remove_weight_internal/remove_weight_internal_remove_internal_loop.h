#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchremove_weight_internal_remove_internal_loop(Morphism *morphism);

void applyremove_weight_internal_remove_internal_loop(Morphism *morphism, bool record_changes);
bool fillpotremove_weight_internal_remove_internal_loop(MorphismPot *pot, Morphism *morphism);

