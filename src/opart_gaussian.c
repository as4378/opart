#include <stdlib.h>
#include "opart_gaussian.h"


/******************************************Function declarations**********************************/
void InitializeSums(const double* data, double* sums, const int n_data); //stores cumulative sums
double GetMean(int start, int end, double* sums); //gets mean of the segment between start and end point in constant time
double GetSegmentCost(int start, int end, double* sums); // gets the cost of segment between start and end point in constant time
void FindOptimalSegments(const double* data, double* sums, double* dp,
                         int* positions, const double beta, int n_data); //finds the optimal cost values upto a data point in data vector
/**************************************************************************************************/


int opart_gaussian(const int n_data, const double *data_ptr, const double penalty, double *cost_ptr,
                   int *end_ptr){

	if(penalty < 0){
	  return NEGATIVE_PENALTY;
	}

	if(n_data <= 0){
	  return NUM_OF_DATA_VALUES_LESS_THAN_ZERO;
	}

	int i;
	int j;
	int temp;
	int maxPos;

	//allocate dynamic memory for storing sums, cost values and segment ends
	double* sums = (double*)malloc((n_data + 1)*(sizeof(double)));
	double* dp = (double*)malloc((n_data + 1)*(sizeof(double)));
	int* positions = (int*)malloc((n_data + 1)*(sizeof(int)));

  //store cumulative sums for O(1) access to segment cost
  InitializeSums(data_ptr, sums, n_data);

	//Compute optimal cost values and segment ends
  FindOptimalSegments(data_ptr, sums, dp, positions, penalty, n_data);

  //Copy the optimal cost values to cost_ptr for return
	for(i = 1; i <= n_data; i++){
		cost_ptr[i - 1] = dp[i];
	}

	//Traceback the optimal segment ends and copy to end_ptr for return
	end_ptr[0] = n_data;
	i = n_data;
	j = 1;
	while(positions[i] > 1){
		end_ptr[j++] = positions[i] - 1;
	  i = positions[i] - 1;
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
	  end_ptr[maxPos++] = -2;
	}

	//free the allocated memory
  free(sums);
	free(dp);
	free(positions);

	//success
	return 0;
}

void FindOptimalSegments(const double* data_points, double* sums, double* dp,
                         int* positions, const double beta, const int n_data){

  int i, j;
  double val;

  dp[0] = beta;
  positions[0] = 0;
  double min;
  int pos;

  for(i = 0; i < n_data + 1; i++){
    positions[i] = -2;
  }

  for(i = 1; i < n_data + 1; i++){
    for(j = 0; j < i; j++){
       val = dp[j] + GetSegmentCost(j + 1, i, sums) + beta;
       if(j == 0){
         min = val;
         pos = j + 1;
       }
       if(val < min){
         min = val;
         pos = j + 1;
       }
    }
    dp[i] = min;
    positions[i] = pos;
  }
}


void InitializeSums(const double* data, double* sums, const int n_data){
  double total = 0;
  int x;
  for(x = 0; x < n_data + 1; x++){
    sums[x] = 0;
    if(x == 0){
      continue;
    }
    total += data[x - 1];
    sums[x] = total;
  }
}

double GetMean(int initial, int final, double* sums){
  double mean = 0;

  int length = final - initial + 1;
  if(initial == 0)
    mean = sums[final] / length;
  else
    mean = (sums[final] - sums[initial - 1]) / length;

  return mean;
}

double GetSegmentCost(int initial, int final, double* sums){
  double mu = GetMean(initial, final, sums);
  int length = final - initial + 1;
  double total = mu * length;

  return ((-2 * mu * total) + (length * mu * mu));
}
