#include <stdlib.h>
#include "opart_gaussian.h"


//Utility function for storing cumulative sums of given list of values
void InitializeSums(const double* data, double* sums, const int n_data){
  double total = 0;
  int x;
  for(x = 0; x < n_data; x++){
    sums[x] = 0;
    total += data[x];
    sums[x] = total;
  }
}

//Utility function for getting mean of a segment starting at "initial" and ending at "final"
double GetMean(int initial, int final, double* sums){
  double mean = 0;

  int length = final - initial + 1;
  if(initial == 0)
    mean = sums[final] / length;
  else
    mean = (sums[final] - sums[initial - 1]) / length;

  return mean;
}

//Utility function for getting cost of segment starting at "initial" and ending at "final"
double GetSegmentCost(int initial, int final, double* sums){
  double mu = GetMean(initial, final, sums);
  int length = final - initial + 1;
  double total = mu * length;

  return ((-2 * mu * total) + (length * mu * mu));
}


//Recursive function for returning the optimal cost of segmentation upto each data point in the dataset
//This function essentially implements the optimal partitioning algorith described in section 3.1 in:
//https://link.springer.com/article/10.1007/s11222-016-9636-3
//The recursive function is:
//F(t) = min{F(s) + C(Ys+1:t) + B} for all 's' in [0,t) and 'B' is the penalty for segmentation
//We calculate F(t) for each data-point 't' in the given dataset to get the optimal cost
//F(0) = B
void FindOptimalSegments(const double* data_points, double* sums, double* dp,
                         int* positions, const double beta, const int n_data){

  //loop variables
  int i, s, t;

  //temporary variables used in recursive function
  double f_tau;
  double min = 0;
  int pos = -1;


  //initialize the positions with -2 in the positions vector as initially no data-point is segment end
  for(i = 0; i < n_data; i++){
    positions[i] = -2;
  }

  //F(1) = F(0) + Cy1:1 + B
  //F(0) = B
  dp[0] = -1*beta + GetSegmentCost(0, 0, sums) + beta;
  positions[0] = -1;

  //Calculate F(t) for all t in 'data_points'
  //F(t) = min{F(s) + C(Ys+1:t) + B}
  for(t = 1; t < n_data; t++){
    for(s = -1; s < t; s++){
      if(s == -1){
        //F(0) = B
        f_tau = -1*beta + GetSegmentCost(s + 1, t, sums) + beta;
      }
      else{
        f_tau = dp[s] + GetSegmentCost(s + 1, t, sums) + beta;
      }

      if(s == -1){
        min = f_tau;
        pos = s;
      }
      if(f_tau <= min){
        min = f_tau;
        pos = s;
      }
    }
    //update the dynamic programming cost and position buffer with minimum cost
    //and associated position
    dp[t] = min;
    positions[t] = pos;
  }
}

//The interface function that gets called through R
int opart_gaussian(const int n_data, const double *data_ptr, const double penalty,
                   double *cost_ptr, double* sums, double* dp, int *end_ptr, int* positions){

  //test for boundary cases
  if(penalty < 0){
    return NEGATIVE_PENALTY;
  }

  if(n_data <= 0){
    return NUM_OF_DATA_VALUES_LESS_THAN_ZERO;
  }

  //loop variables
  int i;
  int j;

  //temporary variables used in tracing back segment ends
  int temp;
  int maxPos;

  //store cumulative sums for O(1) access to segment cost
  InitializeSums(data_ptr, sums, n_data);

  //Compute optimal cost values and segment ends
  FindOptimalSegments(data_ptr, sums, dp, positions, penalty, n_data);

  //Copy the optimal cost values to cost_ptr for return
  for(i = 0; i < n_data; i++){
    cost_ptr[i] = dp[i];
  }

  //Traceback the optimal segment ends and copy to end_ptr for return
  end_ptr[0] = n_data;
  i = n_data - 1;
  j = 1;
  while(positions[i] >= 0){
    end_ptr[j] = positions[i] + 1;
    i = positions[i];
    j++;
  }
  i = 0;
  maxPos = j;
  j--;
  while(j > i){
    temp = end_ptr[i];
    end_ptr[i] = end_ptr[j];
    end_ptr[j] = temp;
    i++;
    j--;
  }

  //assigning -2 as a placeholder value indicating that segment is not used in the optimal model
  while(maxPos < n_data){
    end_ptr[maxPos] = -2;
    maxPos++;
  }

  //success
  return 0;
}
