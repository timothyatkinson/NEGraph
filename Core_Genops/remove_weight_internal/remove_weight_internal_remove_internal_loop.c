#include "remove_weight_internal_remove_internal_loop.h"

#include "remove_weight_internal.h"

static bool match_n0(Morphism *morphism);
static bool match_e0(Morphism *morphism);

bool matchremove_weight_internal_remove_internal_loop(Morphism *morphism)
{
   if(1 > remove_weight_internal_host->number_of_nodes || 1 > remove_weight_internal_host->number_of_edges) return false;
   if(match_n0(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, remove_weight_internal_host);
      return false;
   }
}

static bool match_n0(Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < remove_weight_internal_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(remove_weight_internal_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 1 || host_node->outdegree < 1 ||
         ((host_node->outdegree + host_node->indegree - 1 - 1 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 2) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "NEURON") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 1. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 1, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         if(match_e0(morphism)) return true;
         else
         {
         removeNodeMap(morphism, 0);
         host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool match_e0(Morphism *morphism)
{
   /* Matching a loop. */
   int node_index = lookupNode(morphism, 0);
   if(node_index < 0) return false;
   Node *host_node = getNode(remove_weight_internal_host, node_index);

   int counter;
   for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
   {
      Edge *host_edge = getNthOutEdge(remove_weight_internal_host, host_node, counter);
      if(host_edge == NULL) continue;
      if(host_edge->matched) continue;
      if(host_edge->source != host_edge->target) continue;
      if(host_edge->label.mark != 0) continue;

      HostLabel label = host_edge->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Match list variable 0 against the whole host list. */
      int result = -1;
      if(label.length == 1)
      {
         if(label.list->first->atom.type == 'i')
            result = addIntegerAssignment(morphism, 0, label.list->first->atom.num);
         else result = addStringAssignment(morphism, 0, label.list->first->atom.str);
      }
      else result = addListAssignment(morphism, 0, label.list);
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
      if(match)
      {
         addEdgeMap(morphism, 0, host_edge->index, new_assignments);
         host_edge->matched = true;
      /* All items matched! */
            return true;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

void applyremove_weight_internal_remove_internal_loop(Morphism *morphism, bool record_changes)
{
   int host_edge_index = lookupEdge(morphism, 0);
   if(record_changes)
   {
      Edge *edge = getEdge(remove_weight_internal_host, host_edge_index);
      /* A hole is created if the edge is not at the right-most index of the array. */
      pushRemovedEdge(edge->label, edge->source, edge->target, edge->index,
                      edge->index < remove_weight_internal_host->edges.size - 1);
   }
   removeEdge(remove_weight_internal_host, host_edge_index);

   /* Reset the morphism. */
   initialiseMorphism(morphism, remove_weight_internal_host);
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_e0(MorphismPot *pot, Morphism *morphism);

bool fillpotremove_weight_internal_remove_internal_loop(MorphismPot *pot, Morphism *morphism)
{
   if(1 > remove_weight_internal_host->number_of_nodes || 1 > remove_weight_internal_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 1.000000;
   fillpot_n0(pot, morphism);
   if(potSize(pot) > oldPotsize){
      initialiseMorphism(morphism, remove_weight_internal_host);
      return true;
   }
   else
   {
      initialiseMorphism(morphism, remove_weight_internal_host);
      return false;
   }
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < remove_weight_internal_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(remove_weight_internal_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 1 || host_node->outdegree < 1 ||
         ((host_node->outdegree + host_node->indegree - 1 - 1 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 2) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "NEURON") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 1. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 1, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         if(fillpot_e0(pot, morphism)) return true;
         else
         {
         removeNodeMap(morphism, 0);
         host_node->matched = false;
         }
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

static bool fillpot_e0(MorphismPot *pot, Morphism *morphism)
{
   /* Matching a loop. */
   int node_index = lookupNode(morphism, 0);
   if(node_index < 0) return false;
   Node *host_node = getNode(remove_weight_internal_host, node_index);

   int counter;
   for(counter = 0; counter < host_node->out_edges.size + 2; counter++)
   {
      Edge *host_edge = getNthOutEdge(remove_weight_internal_host, host_node, counter);
      if(host_edge == NULL) continue;
      if(host_edge->matched) continue;
      if(host_edge->source != host_edge->target) continue;
      if(host_edge->label.mark != 0) continue;

      HostLabel label = host_edge->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      /* Match list variable 0 against the whole host list. */
      int result = -1;
      if(label.length == 1)
      {
         if(label.list->first->atom.type == 'i')
            result = addIntegerAssignment(morphism, 0, label.list->first->atom.num);
         else result = addStringAssignment(morphism, 0, label.list->first->atom.str);
      }
      else result = addListAssignment(morphism, 0, label.list);
      if(result >= 0)
      {
         new_assignments += result;
         match = true;
      }
      if(match)
      {
         addEdgeMap(morphism, 0, host_edge->index, new_assignments);
         host_edge->matched = true;
      /* All items matched! */
            putMorphism(pot, morphism, "remove_weight_internal_remove_internal_loop", remove_weight_internal_host);
            removeEdgeMap(morphism, 0);
            host_edge->matched = false;
            return false;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

