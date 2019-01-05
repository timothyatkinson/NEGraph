#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "move_weight_input_pickWeight.h"
Morphism *M_move_weight_input_pickWeight = NULL;
#include "move_weight_input_pickNewTarget.h"
Morphism *M_move_weight_input_pickNewTarget = NULL;
#include "move_weight_input_removeEdge.h"
Morphism *M_move_weight_input_removeEdge = NULL;
#include "move_weight_input_moveEdge.h"
Morphism *M_move_weight_input_moveEdge = NULL;

static void move_weight_input_freeMorphisms(void)
{
   freeMorphism(M_move_weight_input_pickWeight);
   freeMorphism(M_move_weight_input_pickNewTarget);
   freeMorphism(M_move_weight_input_removeEdge);
   freeMorphism(M_move_weight_input_moveEdge);
}

Graph* move_weight_input_host = NULL;
int* move_weight_input_node_map = NULL;
MorphismPot* move_weight_input_pot = NULL;

static void move_weight_input_garbageCollect(void)
{
   move_weight_input_freeMorphisms();
   freePot(move_weight_input_pot);
}

bool move_weight_input_success = true;

int move_weight_input_execute(Graph* host_graph)
{
   move_weight_input_host = host_graph;
   move_weight_input_success = true;
   move_weight_input_pot = makeMorphismPot();
   emptyPot(move_weight_input_pot);
   M_move_weight_input_pickWeight = makeMorphism(2, 1, 3);
   M_move_weight_input_pickNewTarget = makeMorphism(1, 0, 1);
   M_move_weight_input_removeEdge = makeMorphism(2, 1, 3);
   M_move_weight_input_moveEdge = makeMorphism(3, 1, 4);

   /* Try Statement */
   /* Condition */
   int restore_point0 = graph_change_stack == NULL ? 0 : topOfGraphChangeStack();
   do
   {
      /* Rule Call */
      emptyPot(move_weight_input_pot);
      fillpotmove_weight_input_pickWeight(move_weight_input_pot, M_move_weight_input_pickWeight);
      if(potSize(move_weight_input_pot) > 0){
         MorphismHolder *holder = drawFromPot(move_weight_input_pot);
         duplicateMorphism(holder->morphism, M_move_weight_input_pickWeight, move_weight_input_host);
         freeMorphism(holder->morphism);
         free(holder);
         applymove_weight_input_pickWeight(M_move_weight_input_pickWeight, true);
         move_weight_input_success = true;
      }
      else
      {
         move_weight_input_success = false;
         break;
      }
      emptyPot(move_weight_input_pot);
      /* Rule Call */
      emptyPot(move_weight_input_pot);
      fillpotmove_weight_input_pickNewTarget(move_weight_input_pot, M_move_weight_input_pickNewTarget);
      if(potSize(move_weight_input_pot) > 0){
         MorphismHolder *holder = drawFromPot(move_weight_input_pot);
         duplicateMorphism(holder->morphism, M_move_weight_input_pickNewTarget, move_weight_input_host);
         freeMorphism(holder->morphism);
         free(holder);
         applymove_weight_input_pickNewTarget(M_move_weight_input_pickNewTarget, true);
         move_weight_input_success = true;
      }
      else
      {
         move_weight_input_success = false;
         break;
      }
      emptyPot(move_weight_input_pot);
      /* Loop Statement */
      while(move_weight_input_success)
      {
         /* Rule Call */
         if(matchmove_weight_input_removeEdge(M_move_weight_input_removeEdge))
         {
            applymove_weight_input_removeEdge(M_move_weight_input_removeEdge, true);
            move_weight_input_success = true;
         }
         else
         {
            move_weight_input_success = false;
         }
      }
      move_weight_input_success = true;
      /* Rule Call */
      if(matchmove_weight_input_moveEdge(M_move_weight_input_moveEdge))
      {
         applymove_weight_input_moveEdge(M_move_weight_input_moveEdge, true);
         move_weight_input_success = true;
      }
      else
      {
         move_weight_input_success = false;
         break;
      }
   } while(false);

   /* Then Branch */
   if(move_weight_input_success)
   {
      discardChanges(restore_point0);
      /* Skip Statement */
      move_weight_input_success = true;
   }
   /* Else Branch */
   else
   {
      undoChanges(move_weight_input_host, restore_point0);
      move_weight_input_success = true;
      /* Skip Statement */
      move_weight_input_success = true;
   }
   move_weight_input_garbageCollect();
   return 0;
}

