#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "add_weight_input_pick_source.h"
Morphism *M_add_weight_input_pick_source = NULL;
#include "add_weight_input_pick_target.h"
Morphism *M_add_weight_input_pick_target = NULL;
#include "add_weight_input_removeEdge.h"
Morphism *M_add_weight_input_removeEdge = NULL;
#include "add_weight_input_addEdge.h"
Morphism *M_add_weight_input_addEdge = NULL;

static void add_weight_input_freeMorphisms(void)
{
   freeMorphism(M_add_weight_input_pick_source);
   freeMorphism(M_add_weight_input_pick_target);
   freeMorphism(M_add_weight_input_removeEdge);
   freeMorphism(M_add_weight_input_addEdge);
}

Graph* add_weight_input_host = NULL;
int* add_weight_input_node_map = NULL;
MorphismPot* add_weight_input_pot = NULL;

static void add_weight_input_garbageCollect(void)
{
   add_weight_input_freeMorphisms();
   freePot(add_weight_input_pot);
}

bool add_weight_input_success = true;

int add_weight_input_execute(Graph* host_graph)
{
   add_weight_input_host = host_graph;
   add_weight_input_success = true;
   add_weight_input_pot = makeMorphismPot();
   emptyPot(add_weight_input_pot);
   M_add_weight_input_pick_source = makeMorphism(1, 0, 1);
   M_add_weight_input_pick_target = makeMorphism(1, 0, 2);
   M_add_weight_input_removeEdge = makeMorphism(2, 1, 3);
   M_add_weight_input_addEdge = makeMorphism(2, 0, 2);

   /* Rule Call */
   emptyPot(add_weight_input_pot);
   fillpotadd_weight_input_pick_source(add_weight_input_pot, M_add_weight_input_pick_source);
   if(potSize(add_weight_input_pot) > 0){
      MorphismHolder *holder = drawFromPot(add_weight_input_pot);
      duplicateMorphism(holder->morphism, M_add_weight_input_pick_source, add_weight_input_host);
      freeMorphism(holder->morphism);
      free(holder);
      applyadd_weight_input_pick_source(M_add_weight_input_pick_source, false);
      add_weight_input_success = true;
   }
   else
   {
      printf("No output graph: rule add_weight_input_pick_source not applicable.\n");
      add_weight_input_garbageCollect();
      return 0;
   }
   emptyPot(add_weight_input_pot);
   /* Rule Call */
   emptyPot(add_weight_input_pot);
   fillpotadd_weight_input_pick_target(add_weight_input_pot, M_add_weight_input_pick_target);
   if(potSize(add_weight_input_pot) > 0){
      MorphismHolder *holder = drawFromPot(add_weight_input_pot);
      duplicateMorphism(holder->morphism, M_add_weight_input_pick_target, add_weight_input_host);
      freeMorphism(holder->morphism);
      free(holder);
      applyadd_weight_input_pick_target(M_add_weight_input_pick_target, false);
      add_weight_input_success = true;
   }
   else
   {
      printf("No output graph: rule add_weight_input_pick_target not applicable.\n");
      add_weight_input_garbageCollect();
      return 0;
   }
   emptyPot(add_weight_input_pot);
   /* Loop Statement */
   while(add_weight_input_success)
   {
      /* Rule Call */
      if(matchadd_weight_input_removeEdge(M_add_weight_input_removeEdge))
      {
         applyadd_weight_input_removeEdge(M_add_weight_input_removeEdge, false);
         add_weight_input_success = true;
      }
      else
      {
         add_weight_input_success = false;
      }
   }
   add_weight_input_success = true;
   /* Rule Call */
   if(matchadd_weight_input_addEdge(M_add_weight_input_addEdge))
   {
      applyadd_weight_input_addEdge(M_add_weight_input_addEdge, false);
      add_weight_input_success = true;
   }
   else
   {
      printf("No output graph: rule add_weight_input_addEdge not applicable.\n");
      add_weight_input_garbageCollect();
      return 0;
   }
   add_weight_input_garbageCollect();
   return 0;
}

