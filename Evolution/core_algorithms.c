#include "core_algorithms.h"

double microbial(int pop_size, int neurons, int inputs, dataset* data, int evaluations, double rec_rate){
  Graph** population = malloc(pop_size * sizeof(Graph*));
  double* scores = malloc(pop_size * sizeof(double));
  int evals = 0;
  for(int i = 0; i < pop_size; i++){
    population[i] = gen_graph_network(neurons, inputs);
    li_net* net = decode_graph(population[i], inputs);
    t_r_result* res = train_ridge_regression(net, data);
    free_li_net(net);
    scores[i] = res->validation_nmse;
    free_t_r_result(res);
    evals++;
  }

  while (evals < evaluations){
    int p1 = random_integer(0, pop_size);
    int p2 = random_integer(0, pop_size - 1);
    if(p2 >= p1){
      p2++;
    }
    int winner = p1;
    int loser = p2;
    if(scores[p1] > scores[p2]){
      winner = p2;
      loser = p1;
    }
    if(random_bool(rec_rate)){
      freeGraph(population[loser]);
      population[loser] = duplicate_graph(population[winner]);
    }
    Graph* mutated = mutate_graph(population[loser]);
    freeGraph(population[loser]);
    population[loser] = mutated;
    li_net* net = decode_graph(population[loser], inputs);
    t_r_result* res = train_ridge_regression(net, data);
    free_li_net(net);
    scores[loser] = res->validation_nmse;
    free_t_r_result(res);
    evals++;
    printf("Evaluations: %d. Scores: [", evals);
    for(int i = 0; i < pop_size; i++){
      printf("%.2e", scores[i]);
      if(i != pop_size - 1){
        printf(", ");
      }
    }
    printf("]\n");
  }

  double best_score = 1000.0;
  int best = -1;
  for(int i = 0; i < pop_size; i++){
    if(scores[i] < best_score){
      best_score = scores[i];
      best = i;
    }
  }

  li_net* best_net = decode_graph(population[best], inputs);
  t_r_result* res = train_ridge_regression(best_net, data);
  double test = res->test_nmse;
  free_li_net(best_net);
  free_t_r_result(res);
  for(int i = 0; i < pop_size; i++){
    freeGraph(population[i]);
  }
  return test;
}
