#ifndef LI_NET
#define LI_NET

#include <gsl/gsl_linalg.h>
#include "activation_functions.h"
#include <stdbool.h>
#include "matrix_util.h"
#include "rand_util.h"

typedef struct li_net{
  int inputs;
  int nodes;
  int outputs;
  gsl_matrix* W_In;
  gsl_matrix* W_x;
  gsl_matrix* W_Out;
  double leak_rate;

  gsl_matrix* state;
} li_net;

li_net* gen_li_net(int inputs, int nodes, double x_sparsity, double in_sparsity, double spectral_radius, double input_scaling, double leak_rate);
li_net* make_li_net(gsl_matrix* W_In, gsl_matrix* W_x, gsl_matrix* W_Out, double leak_rate);
void free_li_net(li_net* net);

gsl_matrix** execute_li_net(li_net* net, gsl_matrix** input_sequence, int input_sequence_length, int warmup, int output_skip);

gsl_matrix* get_output_matrix(gsl_matrix** output_sequence, int output_sequence_length);
gsl_matrix* get_linear_output(li_net* net, gsl_matrix** input_sequence, int input_sequence_length, int warmup);
gsl_matrix* get_node_outputs(li_net* net, gsl_matrix** input_sequence, int input_sequence_length, int warmup, int output_nodes);

#endif
