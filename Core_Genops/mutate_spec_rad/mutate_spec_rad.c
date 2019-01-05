#include <time.h>
#include "common.h"
#include "debug.h"
#include "graph.h"
#include "graphStacks.h"
#include "parser.h"
#include "morphism.h"

#include "mutate_spec_rad_mutate_spectral_radius.h"
Morphism *M_mutate_spec_rad_mutate_spectral_radius = NULL;

static void mutate_spec_rad_freeMorphisms(void)
{
   freeMorphism(M_mutate_spec_rad_mutate_spectral_radius);
}

Graph* mutate_spec_rad_host = NULL;
int* mutate_spec_rad_node_map = NULL;
MorphismPot* mutate_spec_rad_pot = NULL;

static void mutate_spec_rad_garbageCollect(void)
{
   mutate_spec_rad_freeMorphisms();
   freePot(mutate_spec_rad_pot);
}

bool mutate_spec_rad_success = true;

int mutate_spec_rad_execute(Graph* host_graph)
{
   mutate_spec_rad_host = host_graph;
   mutate_spec_rad_success = true;
   mutate_spec_rad_pot = makeMorphismPot();
   emptyPot(mutate_spec_rad_pot);
   M_mutate_spec_rad_mutate_spectral_radius = makeMorphism(1, 0, 1);

   /* Rule Call */
   if(matchmutate_spec_rad_mutate_spectral_radius(M_mutate_spec_rad_mutate_spectral_radius))
   {
      applymutate_spec_rad_mutate_spectral_radius(M_mutate_spec_rad_mutate_spectral_radius, false);
      mutate_spec_rad_success = true;
   }
   else
   {
      printf("No output graph: rule mutate_spec_rad_mutate_spectral_radius not applicable.\n");
      mutate_spec_rad_garbageCollect();
      return 0;
   }
   mutate_spec_rad_garbageCollect();
   return 0;
}

