#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "remove_weight_internal_remove_internal_edge.h"
Morphism *M_remove_weight_internal_remove_internal_edge = NULL;
#include "remove_weight_internal_remove_internal_loop.h"
Morphism *M_remove_weight_internal_remove_internal_loop = NULL;

static void remove_weight_internal_freeMorphisms(void)
{
   freeMorphism(M_remove_weight_internal_remove_internal_edge);
   freeMorphism(M_remove_weight_internal_remove_internal_loop);
}

Graph* remove_weight_internal_host = NULL;
int* remove_weight_internal_node_map = NULL;
MorphismPot* remove_weight_internal_pot = NULL;

static void remove_weight_internal_garbageCollect(void)
{
   remove_weight_internal_freeMorphisms();
   freePot(remove_weight_internal_pot);
}

bool remove_weight_internal_success = true;

int remove_weight_internal_execute(Graph* host_graph)
{
   remove_weight_internal_host = host_graph;
   remove_weight_internal_success = true;
   remove_weight_internal_pot = makeMorphismPot();
   emptyPot(remove_weight_internal_pot);
   M_remove_weight_internal_remove_internal_edge = makeMorphism(2, 1, 3);
   M_remove_weight_internal_remove_internal_loop = makeMorphism(1, 1, 2);

   /* Try Statement */
   /* Condition */
   do
   {
      /* Rule Set Call */
      do
      {
         emptyPot(remove_weight_internal_pot);
         fillpotremove_weight_internal_remove_internal_edge(remove_weight_internal_pot, M_remove_weight_internal_remove_internal_edge);
         fillpotremove_weight_internal_remove_internal_loop(remove_weight_internal_pot, M_remove_weight_internal_remove_internal_loop);
         if(potSize(remove_weight_internal_pot) == 0){
         remove_weight_internal_success = false;
         break;
         } else{
            MorphismHolder *holder = drawFromPot(remove_weight_internal_pot);
            if(strcmp(holder->ruleName, "remove_weight_internal_remove_internal_edge") == 0){
               duplicateMorphism(holder->morphism, M_remove_weight_internal_remove_internal_edge, remove_weight_internal_host);
               freeMorphism(holder->morphism);
               free(holder);
               applyremove_weight_internal_remove_internal_edge(M_remove_weight_internal_remove_internal_edge, false);
               remove_weight_internal_success = true;
               break;
            }
            if(strcmp(holder->ruleName, "remove_weight_internal_remove_internal_loop") == 0){
               duplicateMorphism(holder->morphism, M_remove_weight_internal_remove_internal_loop, remove_weight_internal_host);
               freeMorphism(holder->morphism);
               free(holder);
               applyremove_weight_internal_remove_internal_loop(M_remove_weight_internal_remove_internal_loop, false);
               remove_weight_internal_success = true;
               break;
            }
         }
         emptyPot(remove_weight_internal_pot);
      } while(false);
   } while(false);

   /* Then Branch */
   if(remove_weight_internal_success)
   {
      /* Skip Statement */
      remove_weight_internal_success = true;
   }
   /* Else Branch */
   else
   {
      remove_weight_internal_success = true;
      /* Skip Statement */
      remove_weight_internal_success = true;
   }
   remove_weight_internal_garbageCollect();
   return 0;
}

