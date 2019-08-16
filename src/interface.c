#include <R.h>
#include <R_ext/Rdynload.h>
#include "opart_gaussian.h"
#include "opart_poisson.h"


void opart_gaussian_interface
  (const int* n_data, const double *data_ptr, const double* penalty, double *cost_ptr,
   double* sums, double* dp, int *end_ptr, int* positions){

  int status = opart_gaussian(n_data[0], data_ptr, penalty[0], cost_ptr, sums, dp, end_ptr, positions);

  if(status == NEGATIVE_PENALTY){
    error("penalty value must be greater than 0");
  }

  if(status == NUM_OF_DATA_VALUES_LESS_THAN_ZERO){
    error("the data vector must have more than 0 elements");
  }

  if(status != 0){
    error("error code %d", status);
  }
}

void opart_poisson_interface
  (const int* n_data, const double *data_ptr, const double* penalty, double *cost_ptr,
   double* sums, double* dp, int *end_ptr, int* positions){

  int status = opart_poisson(n_data[0], data_ptr, penalty[0], cost_ptr, sums, dp, end_ptr, positions);

  if(status == NEGATIVE_PENALTY){
    error("penalty value must be greater than 0");
  }

  if(status == NUM_OF_DATA_VALUES_LESS_THAN_ZERO){
    error("the data vector must have more than 0 elements");
  }

  if(status != 0){
    error("error code %d", status);
  }
}

R_CMethodDef cMethods[] = {
  {"opart_gaussian_interface",
   (DL_FUNC) &opart_gaussian_interface, 8
    //,{int, double, double, double, double, double, int, int}
  },
  {"opart_poisson_interface",
   (DL_FUNC) &opart_poisson_interface, 8
    //,{int, double, double, double, double, double, int, int}
  },
  {NULL, NULL, 0}
};


void R_init_opart(DllInfo *info) {
  R_registerRoutines(info, cMethods, NULL, NULL, NULL);
  //R_useDynamicSymbols call says the DLL is not to be searched for
  //entry points specified by character strings so .C etc calls will
  //only find registered symbols.
  R_useDynamicSymbols(info, FALSE);
}

