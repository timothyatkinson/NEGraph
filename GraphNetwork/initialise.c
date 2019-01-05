#include "initialise.h"

Graph* gen_graph_network(int neurons, int inputs){
  double sparsity = random_double() * 0.1;
  int input_scaling_int = random_integer(0, 2001);
  int spectral_radius_int = random_integer(-1000, 1001);
  int leak_rate_int = random_integer(0, 1001);

  //Start by making an empty host graph.
  Graph* empty = build_empty_host_graph();

  //Insert nodes for parameters.
  do {
    HostAtom array[2];
    HostLabel label;
    array[0].type = 's';
    array[0].str = "INPUT SCALING";
    array[1].type = 'i';
    array[1].num = input_scaling_int;
    HostList *list = makeHostList(array, 2, false);
    label = makeHostLabel(1, 2, list);
    addNode(empty, 0, label);
  } while(false);
  do {
    HostAtom array[2];
    HostLabel label;
    array[0].type = 's';
    array[0].str = "SPECTRAL RADIUS";
    array[1].type = 'i';
    array[1].num = spectral_radius_int;
    HostList *list = makeHostList(array, 2, false);
    label = makeHostLabel(1, 2, list);
    addNode(empty, 0, label);
  } while(false);
  do {
    HostAtom array[2];
    HostLabel label;
    array[0].type = 's';
    array[0].str = "LEAK RATE";
    array[1].type = 'i';
    array[1].num = leak_rate_int;
    HostList *list = makeHostList(array, 2, false);
    label = makeHostLabel(1, 2, list);
    addNode(empty, 0, label);
  } while(false);

  //Insert nodes for inputs.
  int* input_index = malloc((inputs + 1) * sizeof(int));

  //Insert node for bias.
  do {
    HostAtom array[1];
    HostLabel label;
    array[0].type = 's';
    array[0].str = "BIAS";
    HostList *list = makeHostList(array, 1, false);
    label = makeHostLabel(0, 1, list);
    input_index[inputs] = addNode(empty, 0, label);
  } while(false);

  for(int i = 0; i < inputs; i++){
    //Add a node for each input labelled "INPUT":i where i is the number of the input and "INPUT" indicates that it is indeed an input
    HostAtom array[2];
    HostLabel label;
    array[0].type = 's';
    array[0].str = "INPUT";
    array[1].type = 'i';
    array[1].num = i;
    HostList *list = makeHostList(array, 2, false);
    label = makeHostLabel(0, 2, list);
    input_index[i] = addNode(empty, 0, label);
  }

  //Insert nodes for neurons.
  int* neuron_index = malloc(neurons * sizeof(int));
  for(int i = 0; i < neurons; i++){
    //Add a node for each neuron labelled "NEURON":i where i is the number of the neuron and "NEURON" indicates that it is indeed a neuron
    HostAtom array[2];
    HostLabel label;
    array[0].type = 's';
    array[0].str = "NEURON";
    array[1].type = 'i';
    array[1].num = i;
    HostList *list = makeHostList(array, 2, false);
    label = makeHostLabel(0, 2, list);
    neuron_index[i] = addNode(empty, 0, label);
  }

  //Insert neuron-neuron edges according to the sparsity parameter. Includes self loops.
  for(int i = 0; i < neurons; i++){
    for(int j = 0; j < neurons; j++){
      if(random_bool(sparsity)){
        int weight_int = random_integer(-500, 501);
        HostAtom array[1];
        HostLabel label;
        array[0].type = 'i';
        array[0].num = weight_int;
        HostList *list = makeHostList(array, 1, false);
        label = makeHostLabel(0, 1, list);
        addEdge(empty, label, neuron_index[i], neuron_index[j]);
      }
    }
  }

  //Insert neuron-input edges. All are initially connected to all inputs and the bias.
  for(int i = 0; i < neurons; i++){
    for(int j = 0; j < inputs + 1; j++){
      int weight_int = random_integer(-1000, 1001);
      HostAtom array[1];
      HostLabel label;
      array[0].type = 'i';
      array[0].num = weight_int;
      HostList *list = makeHostList(array, 1, false);
      label = makeHostLabel(0, 1, list);
      addEdge(empty, label, neuron_index[i], input_index[j]);
    }
  }

  free(neuron_index);
  free(input_index);
  
  //The generated graph now has the appropriate number of neurons, inputs, bias, parameters and connections according to a random ([0, 0.1]) sparsity.
  return empty;
}
