#include "graph_net.h"

li_net* decode_graph(Graph* graph, int inputs){
  li_net* empty = gen_li_net(inputs, graph->number_of_nodes - inputs, 0.0, 0.0, 0.0, 0.0, 0.0);
}
