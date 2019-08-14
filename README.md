# opart

[![Foo](https://api.travis-ci.org/as4378/opart.png?branch=master)](https://travis-ci.org/as4378/opart)

[![Coverage Status](https://coveralls.io/repos/github/as4378/opart/badge.svg?branch=C_interface_poisson)](https://coveralls.io/github/as4378/opart?branch=C_interface_poisson)

The Optimal partitioning algorithm (https://arxiv.org/abs/math/0309285) computes the solution to the penalized changepoint problem (best model for a given non-negative real-valued penalty parameter) in quadratic time. It is relatively straightforward to code in C, but there is no R package that provides a reference implementation.

There are many other R packages that compute optimal changepoint models.

(i) changepoint: provides the cpt.mean, … functions which compute the optimal solution to the penalized problem via the PELT algorithm, which is log-linear time complexity.

(ii) Fpop::fpop computes the optimal solution to the penalized problem via the FPOP algorithm, which is also log-linear time complexity.

This R package will benefit the changepoint community by providing an efficient C reference implementation of the standard Optimal Partitioning algorithm that has been missing in R. Its simplicity makes it easy to modify (which is not true of other algorithms such as FPOP), which will be useful when developing other changepoint models/algorithms.
