#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "mutate_input_scal_mutate_input_scaling.h"
Morphism *M_mutate_input_scal_mutate_input_scaling = NULL;

static void mutate_input_scal_freeMorphisms(void)
{
   freeMorphism(M_mutate_input_scal_mutate_input_scaling);
}

Graph* mutate_input_scal_host = NULL;
int* mutate_input_scal_node_map = NULL;
MorphismPot* mutate_input_scal_pot = NULL;

static void mutate_input_scal_garbageCollect(void)
{
   mutate_input_scal_freeMorphisms();
   freePot(mutate_input_scal_pot);
}

bool mutate_input_scal_success = true;

int mutate_input_scal_execute(Graph* host_graph)
{
   mutate_input_scal_host = host_graph;
   mutate_input_scal_success = true;
   mutate_input_scal_pot = makeMorphismPot();
   emptyPot(mutate_input_scal_pot);
   M_mutate_input_scal_mutate_input_scaling = makeMorphism(1, 0, 1);

   /* Rule Call */
   if(matchmutate_input_scal_mutate_input_scaling(M_mutate_input_scal_mutate_input_scaling))
   {
      applymutate_input_scal_mutate_input_scaling(M_mutate_input_scal_mutate_input_scaling, false);
      mutate_input_scal_success = true;
   }
   else
   {
      printf("No output graph: rule mutate_input_scal_mutate_input_scaling not applicable.\n");
      mutate_input_scal_garbageCollect();
      return 0;
   }
   mutate_input_scal_garbageCollect();
   return 0;
}

