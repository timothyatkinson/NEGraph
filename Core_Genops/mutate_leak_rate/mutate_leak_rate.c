#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "mutate_leak_rate_mutate_leak_rate.h"
Morphism *M_mutate_leak_rate_mutate_leak_rate = NULL;

static void mutate_leak_rate_freeMorphisms(void)
{
   freeMorphism(M_mutate_leak_rate_mutate_leak_rate);
}

Graph* mutate_leak_rate_host = NULL;
int* mutate_leak_rate_node_map = NULL;
MorphismPot* mutate_leak_rate_pot = NULL;

static void mutate_leak_rate_garbageCollect(void)
{
   mutate_leak_rate_freeMorphisms();
   freePot(mutate_leak_rate_pot);
}

bool mutate_leak_rate_success = true;

int mutate_leak_rate_execute(Graph* host_graph)
{
   mutate_leak_rate_host = host_graph;
   mutate_leak_rate_success = true;
   mutate_leak_rate_pot = makeMorphismPot();
   emptyPot(mutate_leak_rate_pot);
   M_mutate_leak_rate_mutate_leak_rate = makeMorphism(1, 0, 1);

   /* Rule Call */
   if(matchmutate_leak_rate_mutate_leak_rate(M_mutate_leak_rate_mutate_leak_rate))
   {
      applymutate_leak_rate_mutate_leak_rate(M_mutate_leak_rate_mutate_leak_rate, false);
      mutate_leak_rate_success = true;
   }
   else
   {
      printf("No output graph: rule mutate_leak_rate_mutate_leak_rate not applicable.\n");
      mutate_leak_rate_garbageCollect();
      return 0;
   }
   mutate_leak_rate_garbageCollect();
   return 0;
}

