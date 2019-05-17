#include <R.h>
#include <Rinternals.h>
#include "add.h"

void add_interface
  (double *a,double *b, double *r){
    *r = add(a,b);
  }
