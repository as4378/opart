#define NEGATIVE_PENALTY 1
#define NUM_OF_DATA_VALUES_LESS_THAN_ZERO 2

int opart_poisson
(const int n_data, const double *data_ptr, const double penalty, double *cost_ptr,
 double* sums, double* dp, int *end_ptr, int* positions);
