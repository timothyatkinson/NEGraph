#include "core_genops.h"
#include "add_weight_input.h"
#include "add_weight_internal.h"
#include "move_weight_input.h"
#include "move_weight_int.h"
#include "mutate_input_scal.h"
#include "mutate_leak_rate.h"
#include "mutate_spec_rad.h"
#include "remove_weight_input.h"
#include "remove_weight_internal.h"


Graph* mutate_graph(Graph* parent){
  //Copy first
  Graph* graph = duplicate_graph(parent);
  if(random_bool(P_MUTATE_PARAM)){
    mutate_leak_rate_execute(graph);
  }
  if(random_bool(P_MUTATE_PARAM)){
    mutate_input_scal_execute(graph);
  }
  if(random_bool(P_MUTATE_PARAM)){
    mutate_spec_rad_execute(graph);
  }
  if(random_bool(P_CORE_MUTATE)){
    remove_weight_input_execute(graph);
  }
  if(random_bool(P_CORE_MUTATE)){
    remove_weight_internal_execute(graph);
  }
  if(random_bool(P_CORE_MUTATE)){
    move_weight_input_execute(graph);
  }
  if(random_bool(P_CORE_MUTATE)){
    move_weight_int_execute(graph);
  }
  if(random_bool(P_CORE_MUTATE)){
    add_weight_input_execute(graph);
  }
  if(random_bool(P_CORE_MUTATE)){
    add_weight_internal_execute(graph);
  }

  return graph;

}
