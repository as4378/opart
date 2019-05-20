#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include "opart_gaussian.h"


void opart_gaussian_interface
  (int* n_data, double *data_ptr, double* penalty, double *cost_ptr, int *end_ptr, int* error){
    *error = opart_gaussian(n_data[0], data_ptr, penalty[0], cost_ptr, end_ptr);
}
