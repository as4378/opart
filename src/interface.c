#include <R.h>
#include <R_ext/Rdynload.h>
#include "opart_gaussian.h"


void opart_gaussian_interface
  (int* n_data, double *data_ptr, double* penalty, double *cost_ptr, int *end_ptr,
   double* sums, double* sq_sums){

  int status = opart_gaussian(n_data[0], data_ptr, penalty[0], cost_ptr, end_ptr,
                              sums, sq_sums);

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
   (DL_FUNC) &opart_gaussian_interface, 7
    //,{int, double, double, double, int, double, double}
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

