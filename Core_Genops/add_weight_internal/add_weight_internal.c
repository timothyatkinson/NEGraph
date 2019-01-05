#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "add_weight_internal_pick_source.h"
Morphism *M_add_weight_internal_pick_source = NULL;
#include "add_weight_internal_pick_target.h"
Morphism *M_add_weight_internal_pick_target = NULL;
#include "add_weight_internal_removeEdge.h"
Morphism *M_add_weight_internal_removeEdge = NULL;
#include "add_weight_internal_removeLoop.h"
Morphism *M_add_weight_internal_removeLoop = NULL;
#include "add_weight_internal_addEdge.h"
Morphism *M_add_weight_internal_addEdge = NULL;
#include "add_weight_internal_addLoop.h"
Morphism *M_add_weight_internal_addLoop = NULL;

static void add_weight_internal_freeMorphisms(void)
{
   freeMorphism(M_add_weight_internal_pick_source);
   freeMorphism(M_add_weight_internal_pick_target);
   freeMorphism(M_add_weight_internal_removeEdge);
   freeMorphism(M_add_weight_internal_removeLoop);
   freeMorphism(M_add_weight_internal_addEdge);
   freeMorphism(M_add_weight_internal_addLoop);
}

Graph* add_weight_internal_host = NULL;
int* add_weight_internal_node_map = NULL;
MorphismPot* add_weight_internal_pot = NULL;

static void add_weight_internal_garbageCollect(void)
{
   add_weight_internal_freeMorphisms();
   freePot(add_weight_internal_pot);
}

bool add_weight_internal_success = true;

int add_weight_internal_execute(Graph* host_graph)
{
   add_weight_internal_host = host_graph;
   add_weight_internal_success = true;
   add_weight_internal_pot = makeMorphismPot();
   emptyPot(add_weight_internal_pot);
   M_add_weight_internal_pick_source = makeMorphism(1, 0, 1);
   M_add_weight_internal_pick_target = makeMorphism(1, 0, 2);
   M_add_weight_internal_removeEdge = makeMorphism(2, 1, 3);
   M_add_weight_internal_removeLoop = makeMorphism(1, 1, 2);
   M_add_weight_internal_addEdge = makeMorphism(2, 0, 2);
   M_add_weight_internal_addLoop = makeMorphism(1, 0, 1);

   /* Rule Call */
   emptyPot(add_weight_internal_pot);
   fillpotadd_weight_internal_pick_source(add_weight_internal_pot, M_add_weight_internal_pick_source);
   if(potSize(add_weight_internal_pot) > 0){
      MorphismHolder *holder = drawFromPot(add_weight_internal_pot);
      duplicateMorphism(holder->morphism, M_add_weight_internal_pick_source, add_weight_internal_host);
      freeMorphism(holder->morphism);
      free(holder);
      applyadd_weight_internal_pick_source(M_add_weight_internal_pick_source, false);
      add_weight_internal_success = true;
   }
   else
   {
      printf("No output graph: rule add_weight_internal_pick_source not applicable.\n");
      add_weight_internal_garbageCollect();
      return 0;
   }
   emptyPot(add_weight_internal_pot);
   /* Rule Call */
   emptyPot(add_weight_internal_pot);
   fillpotadd_weight_internal_pick_target(add_weight_internal_pot, M_add_weight_internal_pick_target);
   if(potSize(add_weight_internal_pot) > 0){
      MorphismHolder *holder = drawFromPot(add_weight_internal_pot);
      duplicateMorphism(holder->morphism, M_add_weight_internal_pick_target, add_weight_internal_host);
      freeMorphism(holder->morphism);
      free(holder);
      applyadd_weight_internal_pick_target(M_add_weight_internal_pick_target, false);
      add_weight_internal_success = true;
   }
   else
   {
      printf("No output graph: rule add_weight_internal_pick_target not applicable.\n");
      add_weight_internal_garbageCollect();
      return 0;
   }
   emptyPot(add_weight_internal_pot);
   /* Loop Statement */
   while(add_weight_internal_success)
   {
      /* Rule Set Call */
      do
      {
         if(matchadd_weight_internal_removeEdge(M_add_weight_internal_removeEdge))
         {
            applyadd_weight_internal_removeEdge(M_add_weight_internal_removeEdge, false);
            add_weight_internal_success = true;
            break;
         }
         if(matchadd_weight_internal_removeLoop(M_add_weight_internal_removeLoop))
         {
            applyadd_weight_internal_removeLoop(M_add_weight_internal_removeLoop, false);
            add_weight_internal_success = true;
         }
         else
         {
            add_weight_internal_success = false;
         }
      } while(false);
   }
   add_weight_internal_success = true;
   /* Rule Set Call */
   do
   {
      if(matchadd_weight_internal_addEdge(M_add_weight_internal_addEdge))
      {
         applyadd_weight_internal_addEdge(M_add_weight_internal_addEdge, false);
         add_weight_internal_success = true;
         break;
      }
      if(matchadd_weight_internal_addLoop(M_add_weight_internal_addLoop))
      {
         applyadd_weight_internal_addLoop(M_add_weight_internal_addLoop, false);
         add_weight_internal_success = true;
      }
      else
      {
         printf("No output graph: rule add_weight_internal_addLoop not applicable.\n");
         add_weight_internal_garbageCollect();
         return 0;
      }
   } while(false);
   add_weight_internal_garbageCollect();
   return 0;
}

