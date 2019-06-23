library(testthat)
context("opart-gaussian")
library(opart)
data(neuroblastoma, package="neuroblastoma")

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

#test for zero penalty
res <- opart_gaussian(c(1,2,3,4,5), 0)
test_that("all the data points are segment ends", {
  expect_equal(res$end.vec, c(1,2,3,4,5))
})

#test for large penalty
res <- opart_gaussian(c(1,2,3,4,5), 1000000)
test_that("all the data points in one segment", {
  expect_equal(res$end.vec, 5)
})

#test for large data
res <- opart_gaussian(c(1:1000), 0)
test_that("all the data points in one segment", {
  expect_equal(res$end.vec, c(1:1000))
})


#test for neuroblastoma data set with profile.id = 1 and chromosome = 1

selProfile <- subset(neuroblastoma$profiles, profile.id=="1" & chromosome=="1")
nrows <- nrow(selProfile)

#test for large penalty
res <- opart_gaussian(selProfile$logratio, 10000000)
test_that("all the data points in one segment", {
  expect_equal(res$end.vec, nrows)
})

#test for zero penalty
res <- opart_gaussian(selProfile$logratio, 0)
test_that("all the data points are segment ends", {
  expect_equal(nrow(as.data.frame(res$end.vec)), nrows - 2)
})
