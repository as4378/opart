#include <stdlib.h>
#include "opart_gaussian.h"

void InitializeSums(double*, double*, int);
void InitializeSumsSq(double*, double*, int);

int opart_gaussian(int n_data, double *data_ptr, double penalty, double *cost_ptr,
                   int *end_ptr, double* sums, double* sq_sums){

	if(penalty < 0){
	  return NEGATIVE_PENALTY;
	}

	if(n_data <= 0){
	  return NUM_OF_DATA_VALUES_LESS_THAN_ZERO;
	}

  InitializeSums(data_ptr, sums, n_data);
	InitializeSumsSq(data_ptr, sq_sums, n_data);

	int i;
	for(i = 0; i < n_data; i++){
		cost_ptr[i] = data_ptr[i] / penalty;
	}

	for(i = 0; i < n_data; i++){
		end_ptr[i] = i;
	}

	return 0;
}


void InitializeSums(double* data, double* sums, int n_data){
  double total = 0;
  int x;
  for(x = 0; x < n_data + 1; x++){
    sums[x] = 0;
    if(x == 0){
      continue;
    }
    total += data[x - 1];
    sums[x] = total;
  }
}


void InitializeSumsSq(double* data, double* sums_sq, int n_data){
  double total = 0;
  int x;
  for(x = 0; x < n_data + 1; x++){
    sums_sq[x] = 0;
    if(x == 0){
      continue;
    }
    total += data[x - 1] * data[x - 1];
    sums_sq[x] = total;
  }
}
