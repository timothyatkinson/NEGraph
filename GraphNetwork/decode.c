#include "decode.h"

bool is_parameter(Node* node){
  HostLabel label = node->label;
  return label.mark == 1;
}

bool is_input(Node* node){
  return strcmp(get_node_identifier(node), "INPUT") == 0;
}

bool is_bias(Node* node){
  return strcmp(get_node_identifier(node), "BIAS") == 0;
}

bool is_neuron(Node* node){
  return strcmp(get_node_identifier(node), "NEURON") == 0;
}

char* get_node_identifier(Node* node){
  HostLabel label = node->label;
  HostListItem* item = label.list->first;
  return item->atom.str;
}

int get_node_value(Node* node){
  HostLabel label = node->label;
  HostListItem* item = label.list->last;
  return item->atom.num;
}

int get_edge_value(Edge* edge){
  HostLabel label = edge->label;
  HostListItem* item = label.list->last;
  return item->atom.num;
}

double get_edge_weight(Edge* edge){
  return (double)get_edge_value(edge) / 1000.0;
}

double get_input_scaling(Graph* graph){
  for(int host_index = 0; host_index < graph->nodes.size; host_index++)
  {
     Node *host_node = getNode(graph, host_index);
     if(host_node == NULL || host_node->index == -1 || !is_parameter(host_node)) continue;
     if(strcmp(get_node_identifier(host_node), "INPUT SCALING") == 0){
       return (double)get_node_value(host_node) / 1000.0;
     }
   }
   return -999;
}

double get_spectral_radius(Graph* graph){
  for(int host_index = 0; host_index < graph->nodes.size; host_index++)
  {
     Node *host_node = getNode(graph, host_index);
     if(host_node == NULL || host_node->index == -1 || !is_parameter(host_node)) continue;
     if(strcmp(get_node_identifier(host_node), "SPECTRAL RADIUS") == 0){
       return (double)get_node_value(host_node) / 1000.0;
     }
   }
   return -999;
}

double get_leak_rate(Graph* graph){
  for(int host_index = 0; host_index < graph->nodes.size; host_index++)
  {
     Node *host_node = getNode(graph, host_index);
     if(host_node == NULL || host_node->index == -1 || !is_parameter(host_node)) continue;
     if(strcmp(get_node_identifier(host_node), "LEAK RATE") == 0){
       return (double)get_node_value(host_node) / 1000.0;
     }
   }
   return -999;
}

li_net* decode_graph(Graph* graph, int inputs){
  //Generate empty LI-ESN
  li_net* empty = gen_li_net(inputs, graph->number_of_nodes - (inputs + 3), 0.0, 0.0, 0.0, 0.0, 0.0);

  //Load parameters
  double input_scaling = get_input_scaling(graph);
  double spectral_radius = get_spectral_radius(graph);
  double leak_rate = get_leak_rate(graph);

  if(input_scaling == -999 || spectral_radius == -999 || leak_rate == -999){
    printf("Exception: missing parameter!\n");
    printfGraph(graph);
    exit(0);
  }

  //Set leak rate
  empty->leak_rate = leak_rate;

  //Cycle through every *edge* in the graph. Identify its source and target and update appropriate entries in matrices.
  for(int i = 0; i < graph->edges.size; i++){
    Edge* e = getEdge(graph, i);
    if(e == NULL || e->index == -1) continue;
    Node* source = getNode(graph, e->source);
    Node* target = getNode(graph, e->target);
    if(!is_neuron(source)){
      printf("Exception: Node %d has an outgoing edge (%d) despite not being a neuron!\n", e->source, i);
      printfGraph(graph);
      exit(0);
    }
    //Get the index of the source.
    int source_index = get_node_value(source);
    if(is_neuron(target)){
      int target_index = get_node_value(target);
      gsl_matrix_set(empty->W_x, source_index, target_index, get_edge_weight(e));
    }
    else if(is_input(target)){
      int target_index = get_node_value(target);
      gsl_matrix_set(empty->W_In, source_index, target_index, get_edge_weight(e) * input_scaling);
    }
    else if(is_bias(target)){
      gsl_matrix_set(empty->W_In, source_index, inputs, get_edge_weight(e));
    }
   }

   if(gsl_matrix_max_eigenvalue(empty->W_x) != 0.0){
     gsl_matrix_scale(empty->W_x, spectral_radius / gsl_matrix_max_eigenvalue(empty->W_x));
   }

  return empty;
}
