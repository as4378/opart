#include <R.h> //error
#include <R_ext/Rdynload.h>//regestiring routines
#include "opart_gaussian.h" // C code


void opart_gaussian_interface
  (int* n_data, double *data_ptr, double* penalty, double *cost_ptr, int *end_ptr, int* error){
    *error = opart_gaussian(n_data[0], data_ptr, penalty[0], cost_ptr, end_ptr);
}
