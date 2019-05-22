#' compute the optimal changepoint model for a vector of real-valued data
#' and a non-negative real-valued penalty,
#' given the square loss (to minimize) / gaussian likelihood (to maximize)
#'
#' @param data A list of numbers for which the changepoint model is to be computed
#' @param penalty A non-negative real number indicating penalty parameter
#' @return An error status code with a pointer to the optimal cost values and a pointer to the optimal segment ends
#' @examples
#' opart_gaussian(c(1,2,3), 1)
#' opart_gaussian(c(1,2,3,4), 2)


opart_gaussian <- structure(function(data, penalty) {
  result <- .C("opart_gaussian_interface",
               as.integer(length(data)),
               as.double(data),
               as.double(penalty),
               cost_ptr = as.double(vector("double", length(data))),
               end_ptr = as.integer(vector("integer", length(data))),
               PACKAGE="opart")

  print(result)
})
