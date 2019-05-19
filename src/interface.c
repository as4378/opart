#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include "add.h"

void add_interface
  (double *a,double *b, double *r){
    *r = add(a,b);
  }
