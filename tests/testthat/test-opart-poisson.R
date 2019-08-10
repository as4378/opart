library(testthat)
context("opart-poisson")
library(opart)
data(neuroblastoma, package="neuroblastoma")


#tests for invalid scenarios

test_that("opart gives error for negative penalty", {
  expect_error({
    opart_poisson(c(1,2,3), -2)
  }, "penalty value must be greater than or equal to 0",
  fixed=TRUE)
})


test_that("opart gives error when number of elements in data vector are less than 1", {
  expect_error({
    opart_poisson(c(), 1)
  }, "data vector must have atleast one element",
  fixed=TRUE)
})

test_that("opart gives error when data vector has missing(NA) values", {
  expect_error({
    opart_poisson(c(1,NA,2,3), 1)
  }, "data vector has missing(NA) values",
  fixed=TRUE)
})


test_that("opart gives error when data vector has non-integer values", {
  expect_error({
    opart_poisson(c(1.5,2.5,2.05,3.5), 1)
  }, "data vector must contain integer values",
  fixed=TRUE)
})


test_that("opart gives error when data vector contains non-numeric values", {
  expect_error({
    opart_poisson(c("a", "b", 1, 3), 1)
  }, "data vector must contains finite numeric values",
  fixed=TRUE)
})

test_that("opart gives error when data vector contains infinity", {
  expect_error({
    opart_poisson(c(Inf, 1,2), 1)
  }, "data vector must contains finite numeric values",
  fixed=TRUE)
})

#test for zero penalty
res <- opart_poisson(c(1,2,3,4,5), 0)
test_that("all the data points are segment ends", {
  expect_equal(res$end.vec, c(1,2,3,4,5))
})

#test for large penalty
res <- opart_poisson(c(1,2,3,4,5), 1000000)
test_that("all the data points in one segment", {
  expect_equal(res$end.vec, 5)
})

#test for large data
res <- opart_poisson(c(1:1000), 0)
test_that("all the data points as segment ends", {
  expect_equal(res$end.vec, c(1:1000))
})


#test for correctness
res <- opart_poisson(c(1,2,3), 1)
test_that("cost vector should match manual calculation", {
  expect_equal(round(res$cost.vec, 6), c(1, 1.783605, 1.841117))
})


#test for neuroblastoma data set with profile.id = 1 and chromosome = 1

selProfile <- subset(neuroblastoma$profiles, profile.id=="1" & chromosome=="1")
nrows <- nrow(selProfile)

#test for large penalty
res <- opart_poisson(selProfile$logratio, 10000000)
test_that("all the data points in one segment", {
  expect_equal(res$end.vec, nrows)
})


