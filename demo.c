#include <time.h>
#include <stdlib.h>
#include "dataset.h"
#include "li_net.h"
#include "ridge_regression.h"

int
main (void)
{
  srand(time(NULL));

  printf("Loading datasets\n");
  dataset* n10 = load_data_set("Datasets/NARMA10/train2000.csv", "Datasets/NARMA10/validation3000.csv", "Datasets/NARMA10/test3000.csv", 1, 1, 2000, 3000, 3000, 100);
  dataset* n20 = load_data_set("Datasets/NARMA20/train2000.csv", "Datasets/NARMA20/validation3000.csv", "Datasets/NARMA20/test3000.csv", 1, 1, 2000, 3000, 3000, 100);
  dataset* n30 = load_data_set("Datasets/NARMA30/train2000.csv", "Datasets/NARMA30/validation3000.csv", "Datasets/NARMA30/test3000.csv", 1, 1, 2000, 3000, 3000, 100);

  li_net* net = gen_li_net(1, 200, 0.1, 1.0, 0.8, 0.1, 0.5);

  t_r_result* resn10 = train_ridge_regression(net, n10);
  printf("NARMA 10\n");
  print_result(resn10);
  t_r_result* resn20 = train_ridge_regression(net, n20);
  printf("NARMA 20\n");
  print_result(resn20);
  t_r_result* resn30 = train_ridge_regression(net, n30);
  printf("NARMA 30\n");
  print_result(resn30);

  free_t_r_result(resn10);
  free_t_r_result(resn20);
  free_t_r_result(resn30);

  free_li_net(net);

  free_dataset(n10);
  free_dataset(n20);
  free_dataset(n30);

}
