#include "mutate_leak_rate_mutate_leak_rate.h"

#include "mutate_leak_rate.h"

static bool match_n0(Morphism *morphism);

bool matchmutate_leak_rate_mutate_leak_rate(Morphism *morphism)
{
   if(1 > mutate_leak_rate_host->number_of_nodes || 0 > mutate_leak_rate_host->number_of_edges) return false;
   if(match_n0(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, mutate_leak_rate_host);
      return false;
   }
}

static bool match_n0(Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < mutate_leak_rate_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(mutate_leak_rate_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 1) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         if(label.length < 1) break;
         /* Matching from the start of the host list. */
         HostListItem *item = label.list->first;
         /* Check if the end of the host list has been reached. */
         if(item == NULL) break;
         /* Matching rule atom 1. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "LEAK RATE") != 0) break;
         item = item->next;

         int result = -1;
         HostListItem *start = item;
         item = label.list->last;
         /* Matching list variable 0. */
         if(start == NULL) result = addListAssignment(morphism, 0, NULL);
         else if(item == start)
         {
            if(item->atom.type == 'i') result = addIntegerAssignment(morphism, 0, item->atom.num);
            else result = addStringAssignment(morphism, 0, item->atom.str);
         }
         else
         {
            /* Assign to variable 0 the unmatched sublist of the host list. */
            HostAtom sublist[label.length - 1];
            int list_index = 0;
            HostListItem *iterator = start;
            while(iterator != item->next)
            {
               sublist[list_index++] = iterator->atom;
               iterator = iterator->next;
            }
            HostList *list = makeHostList(sublist, label.length - 1, false);
            result = addListAssignment(morphism, 0, list);
            freeHostList(list);
         }
         if(result >= 0)
         {
            new_assignments += result;
            match = true;
         }
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         /* All items matched! */
            return true;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

void applymutate_leak_rate_mutate_leak_rate(Morphism *morphism, bool record_changes)
{
   int host_node_index = lookupNode(morphism, 0);
   HostLabel label_n0 = getNodeLabel(mutate_leak_rate_host, host_node_index);
   HostLabel label;
   int list_var_length0 = 0;
   int list_length0 = list_var_length0 + 2;
   HostAtom array0[list_length0];
   int index0 = 0;

   array0[index0].type = 's';
   array0[index0++].str = "LEAK RATE";
   array0[index0].type = 'i';
   array0[index0++].num = rand_int(0, 1000);
   if(list_length0 > 0)
   {
      HostList *list0 = makeHostList(array0, list_length0, false);
      label = makeHostLabel(1, list_length0, list0);
   }
   else label = makeEmptyLabel(1);

   if(equalHostLabels(label_n0, label)) removeHostList(label.list);
   else
   {
      if(record_changes) pushRelabelledNode(host_node_index, label_n0);
      relabelNode(mutate_leak_rate_host, host_node_index, label);
   }
   /* Reset the morphism. */
   initialiseMorphism(morphism, mutate_leak_rate_host);
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);

bool fillpotmutate_leak_rate_mutate_leak_rate(MorphismPot *pot, Morphism *morphism)
{
   if(1 > mutate_leak_rate_host->number_of_nodes || 0 > mutate_leak_rate_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 1.000000;
   fillpot_n0(pot, morphism);
   if(potSize(pot) > oldPotsize){
      initialiseMorphism(morphism, mutate_leak_rate_host);
      return true;
   }
   else
   {
      initialiseMorphism(morphism, mutate_leak_rate_host);
      return false;
   }
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism)
{
   int host_index;
   for(host_index = 0; host_index < mutate_leak_rate_host->nodes.size; host_index++)
   {
      Node *host_node = getNode(mutate_leak_rate_host, host_index);
      if(host_node == NULL || host_node->index == -1) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 1) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         if(label.length < 1) break;
         /* Matching from the start of the host list. */
         HostListItem *item = label.list->first;
         /* Check if the end of the host list has been reached. */
         if(item == NULL) break;
         /* Matching rule atom 1. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "LEAK RATE") != 0) break;
         item = item->next;

         int result = -1;
         HostListItem *start = item;
         item = label.list->last;
         /* Matching list variable 0. */
         if(start == NULL) result = addListAssignment(morphism, 0, NULL);
         else if(item == start)
         {
            if(item->atom.type == 'i') result = addIntegerAssignment(morphism, 0, item->atom.num);
            else result = addStringAssignment(morphism, 0, item->atom.str);
         }
         else
         {
            /* Assign to variable 0 the unmatched sublist of the host list. */
            HostAtom sublist[label.length - 1];
            int list_index = 0;
            HostListItem *iterator = start;
            while(iterator != item->next)
            {
               sublist[list_index++] = iterator->atom;
               iterator = iterator->next;
            }
            HostList *list = makeHostList(sublist, label.length - 1, false);
            result = addListAssignment(morphism, 0, list);
            freeHostList(list);
         }
         if(result >= 0)
         {
            new_assignments += result;
            match = true;
         }
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         /* All items matched! */
            putMorphism(pot, morphism, "mutate_leak_rate_mutate_leak_rate", mutate_leak_rate_host);
            removeNodeMap(morphism, 0);
            host_node->matched = false;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}
