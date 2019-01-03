#include "li_net.h"

li_net* gen_li_net(int inputs, int nodes, double x_sparsity, double in_sparsity, double spectral_radius, double input_scaling, double leak_rate){
  gsl_matrix* W_In = gsl_matrix_calloc(nodes, inputs + 1);
  gsl_matrix* W_x = gsl_matrix_calloc(nodes, nodes);
  gsl_matrix* W_Out = gsl_matrix_calloc(1, nodes + inputs + 1);

  for(int i = 0; i < nodes; i++){
    for(int j = 0; j < inputs + 1; j++){
      if(random_bool(in_sparsity) && j != inputs){
        gsl_matrix_set(W_In, i, j, random_range(-1.0, 1.0) * input_scaling);
      }
      if(j == inputs && in_sparsity != 0.0){
        gsl_matrix_set(W_In, i, j, random_range(-1.0, 1.0));
      }
    }
  }

  for(int i = 0; i < nodes; i++){
    for(int j = 0; j < nodes; j++){
      if(random_bool(x_sparsity)){
        gsl_matrix_set(W_x, i, j, random_range(-0.5, 0.5));
      }
    }
  }
  if(gsl_matrix_max_eigenvalue(W_x) != 0.0){
    gsl_matrix_scale(W_x, spectral_radius / gsl_matrix_max_eigenvalue(W_x));
  }

  return make_li_net(W_In, W_x, W_Out, leak_rate);
}

li_net* make_li_net(gsl_matrix* W_In, gsl_matrix* W_x, gsl_matrix* W_Out, double leak_rate){
  li_net* net = malloc(sizeof(li_net));
  net->inputs = W_In->size2;
  net->nodes = W_x->size1;
  net->outputs = W_Out->size1;
  net->W_In = W_In;
  net->W_x = W_x;
  net->W_Out = W_Out;
  net->leak_rate = leak_rate;
  net->state = gsl_matrix_calloc(1, 1);
  return net;
}

void free_li_net(li_net* net){
  gsl_matrix_free(net->W_In);
  gsl_matrix_free(net->W_x);
  gsl_matrix_free(net->W_Out);
  gsl_matrix_free(net->state);
  free(net);
}

gsl_matrix** execute_li_net(li_net* net, gsl_matrix** input_sequence, int input_sequence_length, int warmups, int output_skip){

  //If the warmup param is >=0, we reset the network and run it on blank inputs for |warmups| steps to reset the network and converge it.
  if(warmups >= 0){

    //Reset state to zero
    gsl_matrix_free(net->state);
    net->state = gsl_matrix_calloc(net->nodes, 1);

    //Make blank input sequence
    gsl_matrix* zero = gsl_matrix_calloc(net->inputs, 1);
    gsl_matrix** zero_seq = malloc(warmups * sizeof(zero));
    for(int i = 0; i < warmups; i++){
      zero_seq[i] = zero;
    }

    //Run the network on the zero sequence
    free(execute_li_net(net, zero_seq, warmups, -1, warmups));

    //free the blank input sequence
    gsl_matrix_free(zero);
    free(zero_seq);

    //up-scale the new state.
    gsl_matrix* new_state = gsl_matrix_calloc(net->nodes, input_sequence[0]->size2);
    for(int i = 0; i < net->nodes; i++){
      for(int j = 0; j < input_sequence[0]->size2; j++){
        gsl_matrix_set(new_state, i, j, gsl_matrix_get(net->state, i, 0));
      }
    }
    gsl_matrix_free(net->state);
    net->state = new_state;
  }

  gsl_matrix** output_sequence = malloc((input_sequence_length - output_skip) * sizeof(gsl_matrix*));

  for(int i = 0; i < input_sequence_length; i++){

    gsl_matrix* win = gsl_matrix_multiply(net->W_In, input_sequence[i]);
    gsl_matrix* wx = gsl_matrix_multiply(net->W_x, net->state);

    gsl_matrix* sum = gsl_matrix_sum(win, wx);
    gsl_matrix* fx = apply_function(sum, tanh);
    gsl_matrix_free(win);
    gsl_matrix_free(wx);
    gsl_matrix_free(sum);
    gsl_matrix_scale(fx, net->leak_rate);
    gsl_matrix_scale(net->state, 1.0 - net->leak_rate);

    gsl_matrix* res = gsl_matrix_sum(fx, net->state);
    gsl_matrix_free(net->state);
    gsl_matrix_free(fx);
    net->state = res;

    if(i >= output_skip){
      gsl_matrix* out = gsl_matrix_calloc(net->inputs + net->nodes, input_sequence[0]->size2);
      for(int i = 0; i < net->inputs; i++){
        for(int j = 0; j < input_sequence[0]->size2; j++){
          gsl_matrix_set(out, i, j, gsl_matrix_get(input_sequence[i], i, j));
        }
      }
      for(int i = 0; i < net->nodes; i++){
        for(int j = 0; j < input_sequence[0]->size2; j++){
          gsl_matrix_set(out, i + net->inputs, j, gsl_matrix_get(net->state, i, j));
        }
      }

      output_sequence[i - output_skip] = out;
    }
  }

  return output_sequence;
}

gsl_matrix* get_output_matrix(gsl_matrix** output_sequence, int output_sequence_length){
  gsl_matrix* out = gsl_matrix_calloc(output_sequence[0]->size1, output_sequence_length);
  for(int i = 0; i < output_sequence_length; i++){
    assert(output_sequence[i]->size2 == 1);
    for(int j = 0; j < output_sequence[0]->size1; j++){
      gsl_matrix_set(out, j, i, gsl_matrix_get(output_sequence[i], j, 0));
    }
  }
  return out;
}

gsl_matrix* get_linear_output(li_net* net, gsl_matrix** input_sequence, int input_sequence_length, int warmup){
  gsl_matrix** output_sequence = execute_li_net(net, input_sequence, input_sequence_length, warmup, 0);
  gsl_matrix* out = get_output_matrix(output_sequence, input_sequence_length);
  gsl_matrix* true_out = gsl_matrix_multiply(net->W_Out, out);
  for(int i = 0; i < input_sequence_length; i++){
    gsl_matrix_free(output_sequence[i]);
  }
  free(output_sequence);
  gsl_matrix_free(out);
  return true_out;
}

gsl_matrix* get_node_outputs(li_net* net, gsl_matrix** input_sequence, int input_sequence_length, int warmup, int output_nodes){
  gsl_matrix** output_sequence = execute_li_net(net, input_sequence, input_sequence_length, warmup, input_sequence_length - 1);
  gsl_matrix* out = output_sequence[0];
  free(output_sequence);
  gsl_matrix* true_out = gsl_matrix_calloc(output_nodes, out->size2);
  for(int i = 0; i < output_nodes; i++){
      for(int j = 0; j < out->size2; j++){
        gsl_matrix_set(true_out, i, j, gsl_matrix_get(out, (out->size1 - output_nodes) + i, j));
      }
  }
  gsl_matrix_free(out);
  return true_out;
}
