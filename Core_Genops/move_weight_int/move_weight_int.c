#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "move_weight_int_pickWeight.h"
Morphism *M_move_weight_int_pickWeight = NULL;
#include "move_weight_int_pickNewTarget.h"
Morphism *M_move_weight_int_pickNewTarget = NULL;
#include "move_weight_int_removeEdge.h"
Morphism *M_move_weight_int_removeEdge = NULL;
#include "move_weight_int_moveEdge.h"
Morphism *M_move_weight_int_moveEdge = NULL;

static void move_weight_int_freeMorphisms(void)
{
   freeMorphism(M_move_weight_int_pickWeight);
   freeMorphism(M_move_weight_int_pickNewTarget);
   freeMorphism(M_move_weight_int_removeEdge);
   freeMorphism(M_move_weight_int_moveEdge);
}

Graph* move_weight_int_host = NULL;
int* move_weight_int_node_map = NULL;
MorphismPot* move_weight_int_pot = NULL;

static void move_weight_int_garbageCollect(void)
{
   move_weight_int_freeMorphisms();
   freePot(move_weight_int_pot);
}

bool move_weight_int_success = true;

int move_weight_int_execute(Graph* host_graph)
{
   move_weight_int_host = host_graph;
   move_weight_int_success = true;
   move_weight_int_pot = makeMorphismPot();
   emptyPot(move_weight_int_pot);
   M_move_weight_int_pickWeight = makeMorphism(2, 1, 3);
   M_move_weight_int_pickNewTarget = makeMorphism(1, 0, 2);
   M_move_weight_int_removeEdge = makeMorphism(2, 1, 3);
   M_move_weight_int_moveEdge = makeMorphism(3, 1, 4);

   /* Try Statement */
   /* Condition */
   int restore_point0 = graph_change_stack == NULL ? 0 : topOfGraphChangeStack();
   do
   {
      /* Rule Call */
      emptyPot(move_weight_int_pot);
      fillpotmove_weight_int_pickWeight(move_weight_int_pot, M_move_weight_int_pickWeight);
      if(potSize(move_weight_int_pot) > 0){
         MorphismHolder *holder = drawFromPot(move_weight_int_pot);
         duplicateMorphism(holder->morphism, M_move_weight_int_pickWeight, move_weight_int_host);
         freeMorphism(holder->morphism);
         free(holder);
         applymove_weight_int_pickWeight(M_move_weight_int_pickWeight, true);
         move_weight_int_success = true;
      }
      else
      {
         move_weight_int_success = false;
         break;
      }
      emptyPot(move_weight_int_pot);
      /* Rule Call */
      emptyPot(move_weight_int_pot);
      fillpotmove_weight_int_pickNewTarget(move_weight_int_pot, M_move_weight_int_pickNewTarget);
      if(potSize(move_weight_int_pot) > 0){
         MorphismHolder *holder = drawFromPot(move_weight_int_pot);
         duplicateMorphism(holder->morphism, M_move_weight_int_pickNewTarget, move_weight_int_host);
         freeMorphism(holder->morphism);
         free(holder);
         applymove_weight_int_pickNewTarget(M_move_weight_int_pickNewTarget, true);
         move_weight_int_success = true;
      }
      else
      {
         move_weight_int_success = false;
         break;
      }
      emptyPot(move_weight_int_pot);
      /* Loop Statement */
      while(move_weight_int_success)
      {
         /* Rule Call */
         if(matchmove_weight_int_removeEdge(M_move_weight_int_removeEdge))
         {
            applymove_weight_int_removeEdge(M_move_weight_int_removeEdge, true);
            move_weight_int_success = true;
         }
         else
         {
            move_weight_int_success = false;
         }
      }
      move_weight_int_success = true;
      /* Rule Call */
      if(matchmove_weight_int_moveEdge(M_move_weight_int_moveEdge))
      {
         applymove_weight_int_moveEdge(M_move_weight_int_moveEdge, true);
         move_weight_int_success = true;
      }
      else
      {
         move_weight_int_success = false;
         break;
      }
   } while(false);

   /* Then Branch */
   if(move_weight_int_success)
   {
      discardChanges(restore_point0);
      /* Skip Statement */
      move_weight_int_success = true;
   }
   /* Else Branch */
   else
   {
      undoChanges(move_weight_int_host, restore_point0);
      move_weight_int_success = true;
      /* Skip Statement */
      move_weight_int_success = true;
   }
   move_weight_int_garbageCollect();
   return 0;
}

