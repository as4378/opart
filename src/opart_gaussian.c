#include <stdlib.h>
#include "opart_gaussian.h"

int opart_gaussian(int n_data, double *data_ptr, double penalty, double *cost_ptr, int *end_ptr){
	int i;

	//cost_ptr = (double*)malloc(n_data*sizeof(double));
	for(i = 0; i < n_data; i++){
		cost_ptr[i] = data_ptr[i] / penalty;
	}

	//end_ptr = (int*)malloc(n_data*sizeof(int));
	for(i = 0; i < n_data; i++){
		end_ptr[i] = i;
	}

	return 0;
}
