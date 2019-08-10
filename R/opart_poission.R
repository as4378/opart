#' compute the optimal changepoint model for a vector of real-valued data
#' and a non-negative real-valued penalty,
#' given the poisson loss (to minimize) / log likelihood (to maximize)
#'
#' @param data A list of numbers for which the changepoint model is to be computed
#' @param penalty A non-negative real number indicating penalty parameter
#' @return An error status code with a pointer to the optimal cost values and a pointer to the optimal segment ends
#' @examples
#' opart_poisson(c(1,2,3), 1)
#' opart_poisson(c(1,2,3,4), 2)
#' @export


opart_poisson <- function(data, penalty) {

  #check for positive length of data
  if(!(length(data) > 0)){
    stop("data vector must have atleast one element")
  }

  #check if there are any missing values in data vector
  if(any(is.na(data))){
    stop("data vector has missing(NA) values")
  }

  #check if data vector has all finite numeric values
  if(!(all(is.numeric(data)) && all(is.finite(data)))){
    stop("data vector must contains finite numeric values")
  }

  #check if the penalty value is numeric
  if(!is.numeric(penalty)){
    stop("penalty value should be numeric")
  }

  #check if penalty is finite and of length 1
  if(!(is.finite(penalty) && (length(penalty) == 1))){
    stop("penalty must be a finite numeric value")
  }

  #check if penalty if non-negative
  if(penalty < 0){
    stop("penalty value must be greater than or equal to 0")
  }

  #check if data vector has all integer values
  if(!all(data == floor(data))){
    stop("data vector must contain integer values")
  }
  result <- .C("opart_poisson_interface",
               n_data = as.integer(length(data)),
               data.vec = as.double(data),
               penalty = as.double(penalty),
               cost.vec = double(length(data)),
               sums = double(length(data)),
               dp = double(length(data)),
               end.vec = integer(length(data)),
               positions = integer(length(data)),
               PACKAGE="opart")

  seg_ends <- (result$end.vec)

  #remove the -2 from the output
  result$end.vec <- seg_ends[seg_ends != -2]

  #remove the columns used for internal calculations as they don't need to be displayed
  #result <- result[-c(5,6,8)]
  result <- result[!(names(result) %in% c("sums","dp","positions"))]

  #display the result
  result
}
