#include "add_weight_internal_addEdge.h"

#include "add_weight_internal.h"

static bool match_n0(Morphism *morphism);
static bool match_n1(Morphism *morphism);

bool matchadd_weight_internal_addEdge(Morphism *morphism)
{
   if(2 > add_weight_internal_host->number_of_nodes || 0 > add_weight_internal_host->number_of_edges) return false;
   if(match_n0(morphism)) return true;
   else
   {
      initialiseMorphism(morphism, add_weight_internal_host);
      return false;
   }
}

static bool match_n0(Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(add_weight_internal_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(add_weight_internal_host, nodes->index);
      if(host_node == NULL) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 3) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "NEURON") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 0. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 0, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->next;

         /* Matching rule atom 3. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "SOURCE") != 0) break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         if(match_n1(morphism)) return true;
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

static bool match_n1(Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(add_weight_internal_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(add_weight_internal_host, nodes->index);
      if(host_node == NULL) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 3) break;
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
         item = item->next;

         /* Matching rule atom 3. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "TARGET") != 0) break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 1, host_node->index, new_assignments);
         host_node->matched = true;
         /* All items matched! */
            return true;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

void applyadd_weight_internal_addEdge(Morphism *morphism, bool record_changes)
{
   int var_0 = getIntegerValue(morphism, 0);
   int var_1 = getIntegerValue(morphism, 1);
   int host_node_index = lookupNode(morphism, 0);
   HostLabel label_n0 = getNodeLabel(add_weight_internal_host, host_node_index);
   HostLabel label;
   int list_var_length0 = 0;
   int list_length0 = list_var_length0 + 2;
   HostAtom array0[list_length0];
   int index0 = 0;

   array0[index0].type = 's';
   array0[index0++].str = "NEURON";
   array0[index0].type = 'i';
   array0[index0++].num = var_0;
   if(list_length0 > 0)
   {
      HostList *list0 = makeHostList(array0, list_length0, false);
      label = makeHostLabel(0, list_length0, list0);
   }
   else label = makeEmptyLabel(0);

   if(equalHostLabels(label_n0, label)) removeHostList(label.list);
   else
   {
      if(record_changes) pushRelabelledNode(host_node_index, label_n0);
      relabelNode(add_weight_internal_host, host_node_index, label);
   }
   host_node_index = lookupNode(morphism, 0);
   if(record_changes) pushChangedRootNode(host_node_index);
   changeRoot(add_weight_internal_host, host_node_index);
   host_node_index = lookupNode(morphism, 1);
   HostLabel label_n1 = getNodeLabel(add_weight_internal_host, host_node_index);
   int list_var_length1 = 0;
   int list_length1 = list_var_length1 + 2;
   HostAtom array1[list_length1];
   int index1 = 0;

   array1[index1].type = 's';
   array1[index1++].str = "NEURON";
   array1[index1].type = 'i';
   array1[index1++].num = var_1;
   if(list_length1 > 0)
   {
      HostList *list1 = makeHostList(array1, list_length1, false);
      label = makeHostLabel(0, list_length1, list1);
   }
   else label = makeEmptyLabel(0);

   if(equalHostLabels(label_n1, label)) removeHostList(label.list);
   else
   {
      if(record_changes) pushRelabelledNode(host_node_index, label_n1);
      relabelNode(add_weight_internal_host, host_node_index, label);
   }
   host_node_index = lookupNode(morphism, 1);
   if(record_changes) pushChangedRootNode(host_node_index);
   changeRoot(add_weight_internal_host, host_node_index);
   int host_edge_index;
   int source, target;
   int edge_array_size0 = add_weight_internal_host->edges.size;
   source = lookupNode(morphism, 0);
   target = lookupNode(morphism, 1);
   int list_var_length2 = 0;
   int list_length2 = list_var_length2 + 1;
   HostAtom array2[list_length2];
   int index2 = 0;

   array2[index2].type = 'i';
   array2[index2++].num = rand_int(-500, 500);
   if(list_length2 > 0)
   {
      HostList *list2 = makeHostList(array2, list_length2, false);
      label = makeHostLabel(0, list_length2, list2);
   }
   else label = makeEmptyLabel(0);

   host_edge_index = addEdge(add_weight_internal_host, label, source, target);
   /* If the edge array size has not increased after the edge addition, then
      the edge was added to a hole in the array. */
   if(record_changes)
      pushAddedEdge(host_edge_index, edge_array_size0 == add_weight_internal_host->edges.size);
   /* Reset the morphism. */
   initialiseMorphism(morphism, add_weight_internal_host);
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism);
static bool fillpot_n1(MorphismPot *pot, Morphism *morphism);

bool fillpotadd_weight_internal_addEdge(MorphismPot *pot, Morphism *morphism)
{
   if(2 > add_weight_internal_host->number_of_nodes || 0 > add_weight_internal_host->number_of_edges) return false;
   int oldPotsize = potSize(pot);
   morphism->weight = 1.000000;
   fillpot_n0(pot, morphism);
   if(potSize(pot) > oldPotsize){
      initialiseMorphism(morphism, add_weight_internal_host);
      return true;
   }
   else
   {
      initialiseMorphism(morphism, add_weight_internal_host);
      return false;
   }
}

static bool fillpot_n0(MorphismPot *pot, Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(add_weight_internal_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(add_weight_internal_host, nodes->index);
      if(host_node == NULL) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 3) break;
         HostListItem *item = label.list->first;
         /* Matching rule atom 1. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "NEURON") != 0) break;
         item = item->next;

         /* Matching rule atom 2. */
         int result = -1;
         /* Matching integer variable 0. */
         if(item->atom.type != 'i') break;
         result = addIntegerAssignment(morphism, 0, item->atom.num);
         if(result >= 0)
         {
            new_assignments += result;
         }
         else break;
         item = item->next;

         /* Matching rule atom 3. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "SOURCE") != 0) break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 0, host_node->index, new_assignments);
         host_node->matched = true;
         if(fillpot_n1(pot, morphism)) return true;
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

static bool fillpot_n1(MorphismPot *pot, Morphism *morphism)
{
   RootNodes *nodes;
   for(nodes = getRootNodeList(add_weight_internal_host); nodes != NULL; nodes = nodes->next)
   {
      Node *host_node = getNode(add_weight_internal_host, nodes->index);
      if(host_node == NULL) continue;
      if(host_node->matched) continue;
      if(host_node->label.mark != 0) continue;
      if(host_node->indegree < 0 || host_node->outdegree < 0 ||
         ((host_node->outdegree + host_node->indegree - 0 - 0 - 0) < 0)) continue;

      HostLabel label = host_node->label;
      bool match = false;
      /* Label Matching */
      int new_assignments = 0;
      do
      {
         /* The rule list does not contain a list variable, so there is no
          * match if the host list has a different length. */
         if(label.length != 3) break;
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
         item = item->next;

         /* Matching rule atom 3. */
         if(item->atom.type != 's') break;
         else if(strcmp(item->atom.str, "TARGET") != 0) break;
         match = true;
      } while(false);

      if(match)
      {
         addNodeMap(morphism, 1, host_node->index, new_assignments);
         host_node->matched = true;
         /* All items matched! */
            putMorphism(pot, morphism, "add_weight_internal_addEdge", add_weight_internal_host);
            removeNodeMap(morphism, 1);
            host_node->matched = false;
      }
      else removeAssignments(morphism, new_assignments);
   }
   return false;
}

