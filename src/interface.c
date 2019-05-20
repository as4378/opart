#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include "opart_gaussian.h"

//void add_interface
//  (double *x, double *y, int* l, double *r){
//    *r = add(x, y, l[0]);
//  }

void opart_gaussian_interface
  (int* n_data, double *data_ptr, double* penalty, double *cost_ptr, int *end_ptr, int* error){
    *error = opart_gaussian(n_data[0], data_ptr, penalty[0], cost_ptr, end_ptr);
}
