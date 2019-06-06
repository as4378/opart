library(testthat)
context("opart-gaussian")
library(opart)

test_that("opart gives error for negative penalty", {
  expect_error({
    opart_gaussian(c(1,2,3), -2)
  }, "penalty value must be greater than 0",
  fixed=TRUE)
})


test_that("opart gives error when data points are less than 1", {
  expect_error({
    opart_gaussian(c(), 1)
  }, "data vector must have atleast one element",
  fixed=TRUE)
})

#test for small penalty
res <- opart_gaussian(c(1,2,3,4,5), 0.0001)
test_that("all the data points are segment ends", {
  expect_equal(res$end.vec, c(1,2,3,4,5))
})

#test for large penalty
res <- opart_gaussian(c(1,2,3,4,5), 1000000)
test_that("all the data points in one segment", {
  expect_equal(res$end.vec, 5)
})
