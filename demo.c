#include <time.h>
#include <stdlib.h>
#include "dataset.h"
#include "li_net.h"
#include "ridge_regression.h"

#include "core_algorithms.h"


int
main (void)
{
  srand(time(NULL));

  printf("Loading dataset(s)\n");
  dataset* n10 = load_data_set("Datasets/NARMA10/train2000.csv", "Datasets/NARMA10/validation3000.csv", "Datasets/NARMA10/test3000.csv", 1, 1, 2000, 3000, 3000, 100);
  //dataset* n20 = load_data_set("Datasets/NARMA20/train2000.csv", "Datasets/NARMA20/validation3000.csv", "Datasets/NARMA20/test3000.csv", 1, 1, 2000, 3000, 3000, 100);
  //dataset* n30 = load_data_set("Datasets/NARMA30/train2000.csv", "Datasets/NARMA30/validation3000.csv", "Datasets/NARMA30/test3000.csv", 1, 1, 2000, 3000, 3000, 100);


  printf("Begin microbial\n");
  double test_score = microbial(15, 200, 1, n10, 2000, 1.0);
  printf("Test NMSE: %lf\n", test_score);

  free_dataset(n10);
  //free_dataset(n20);
  //free_dataset(n30);

}
