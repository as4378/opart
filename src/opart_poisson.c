#include <stdlib.h>
#include "opart_poisson.h"

//The interface function that gets called through R
int opart_poisson(const int n_data, const double *data_ptr, const double penalty,
                   double *cost_ptr, double* sums, double* dp, int *end_ptr, int* positions){

  //test for boundary cases
  if(penalty < 0){
    return NEGATIVE_PENALTY;
  }

  if(n_data <= 0){
    return NUM_OF_DATA_VALUES_LESS_THAN_ZERO;
  }

  //success
  return 0;
}
