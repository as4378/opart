# opart

[![Foo](https://api.travis-ci.org/as4378/opart.png?branch=master)](https://travis-ci.org/as4378/opart) [![Coverage Status](https://coveralls.io/repos/github/as4378/opart/badge.svg)](https://coveralls.io/github/as4378/opart)

This repository is for Google Summer of Code 2019 project [Optimal partitioning algorithm for changepoint detection](https://github.com/rstats-gsoc/gsoc2019/wiki/Optimal-partitioning-algorithm-for-changepoint-detection) under organization [R project for statistical computing](https://summerofcode.withgoogle.com/organizations/4934391420157952/).



## Installation

The package can be installed from github as follows:

```R
install.packages("devtools") #if not already installed
library(devtools)

devtools::install_github("as4378/opart")
```

## Introduction

There are several applications where we need to work with ordered data (e.g. Time-series). This includes financial data, climate data, radio signals, genome data in bioinformatics etc. Often it is of interest to find patterns or structure in this data and to detect abrupt changes in structure to model the data effectively. There are a class of dynamic programming algorithms that can solve the optimal partitioning problem and find optimal segments given a statistical criteria.

A quadratic time algorithm described in https://link.springer.com/article/10.1007/s11222-016-9636-3 is one such algorithm that solves the optimal partitioning problem given square error loss function.
Currently there are no R packages available that provide a reference implementation to this algorithm.


This project provides an efficient C++ reference implementation to the standard optimal partitioning algorithm in an R package (opart) using square error loss function and poisson loss. Its simplicity makes it easy to modify (which is not true of other algorithms such as FPOP), which will be useful when developing other changepoint models/algorithms.



