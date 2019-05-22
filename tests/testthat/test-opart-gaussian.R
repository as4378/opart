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
  }, "the data vector must have more than 0 elements",
  fixed=TRUE)
})
