#ifndef CORE_A_H
#define CORE_A_H
#include <stdlib.h>
#include "dataset.h"
#include "li_net.h"
#include "ridge_regression.h"

#include "../GraphNetwork/initialise.h"
#include "../GraphNetwork/decode.h"
#include "../GraphNetwork/core_genops.h"

double microbial(int pop_size, int neurons, int inputs, dataset* data, int evaluations, double rec_rate);
#endif
