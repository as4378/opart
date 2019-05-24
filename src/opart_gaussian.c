#include <stdlib.h>
#include "opart_gaussian.h"

int opart_gaussian(int n_data, double *data_ptr, double penalty, double *cost_ptr, int *end_ptr, double* sums, double* sq_sums){

	if(penalty < 0){
	  return NEGATIVE_PENALTY;
	}

	if(n_data <= 0){
	  return NUM_OF_DATA_VALUES_LESS_THAN_ZERO;
	}

	int i;

	for(i = 0; i < n_data; i++){
		cost_ptr[i] = data_ptr[i] / penalty;
	}

	for(i = 0; i < n_data; i++){
		end_ptr[i] = i;
	}

	return 0;
}
