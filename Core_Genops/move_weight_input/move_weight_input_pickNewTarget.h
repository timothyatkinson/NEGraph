#include "graph.h"
#include "label.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"
#include "common.h"

bool matchmove_weight_input_pickNewTarget(Morphism *morphism);

void applymove_weight_input_pickNewTarget(Morphism *morphism, bool record_changes);
bool fillpotmove_weight_input_pickNewTarget(MorphismPot *pot, Morphism *morphism);

