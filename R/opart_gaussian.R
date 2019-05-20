
#' compute the optimal changepoint model for a vector of real-valued data
#' and a non-negative real-valued penalty,
#' given the square loss (to minimize) / gaussian likelihood (to maximize)
#'
#' @param n_data A number indicating the number of data points
#' @param data_ptr A list of numbers for which the changepoint model is to be computed
#' @param penalty A non-negative real number indicating penalty
#' @return A pointer to the optimal cost values and a pointer to the optimal segment ends
#' @examples
#' opart_gaussian(3, c(1,2,3), 1)
#' opart_gaussian(4, c(1,2,3,4), 1)


opart_gaussian <- structure(function(n_data, data_ptr, penalty) {
  result <- .C("opart_gaussian_interface", as.integer(n_data),
               as.double(data_ptr), as.double(penalty),
               cost_ptr = as.double(vector("double",length(data_ptr))),
               end_ptr = as.integer(vector("integer",length(data_ptr))), error = integer(1),
               PACKAGE="opart")
  error <- result$error
  cost <- result$cost_ptr
  ends <- result$end_ptr

  print(error)
  print(cost)
  print(ends)
}, ex=function(){})
