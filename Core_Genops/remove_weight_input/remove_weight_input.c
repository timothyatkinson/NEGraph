#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "remove_weight_input_remove_input_edge.h"
Morphism *M_remove_weight_input_remove_input_edge = NULL;

static void remove_weight_input_freeMorphisms(void)
{
   freeMorphism(M_remove_weight_input_remove_input_edge);
}

Graph* remove_weight_input_host = NULL;
int* remove_weight_input_node_map = NULL;
MorphismPot* remove_weight_input_pot = NULL;

static void remove_weight_input_garbageCollect(void)
{
   remove_weight_input_freeMorphisms();
   freePot(remove_weight_input_pot);
}

bool remove_weight_input_success = true;

int remove_weight_input_execute(Graph* host_graph)
{
   remove_weight_input_host = host_graph;
   remove_weight_input_success = true;
   remove_weight_input_pot = makeMorphismPot();
   emptyPot(remove_weight_input_pot);
   M_remove_weight_input_remove_input_edge = makeMorphism(2, 1, 2);

   /* Try Statement */
   /* Condition */
   do
   {
      /* Rule Call */
      emptyPot(remove_weight_input_pot);
      fillpotremove_weight_input_remove_input_edge(remove_weight_input_pot, M_remove_weight_input_remove_input_edge);
      if(potSize(remove_weight_input_pot) > 0){
         MorphismHolder *holder = drawFromPot(remove_weight_input_pot);
         duplicateMorphism(holder->morphism, M_remove_weight_input_remove_input_edge, remove_weight_input_host);
         freeMorphism(holder->morphism);
         free(holder);
         applyremove_weight_input_remove_input_edge(M_remove_weight_input_remove_input_edge, false);
         remove_weight_input_success = true;
      }
      else
      {
         remove_weight_input_success = false;
         break;
      }
      emptyPot(remove_weight_input_pot);
   } while(false);

   /* Then Branch */
   if(remove_weight_input_success)
   {
      /* Skip Statement */
      remove_weight_input_success = true;
   }
   /* Else Branch */
   else
   {
      remove_weight_input_success = true;
      /* Skip Statement */
      remove_weight_input_success = true;
   }
   remove_weight_input_garbageCollect();
   return 0;
}

