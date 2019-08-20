# opart

[![Foo](https://api.travis-ci.org/as4378/opart.png?branch=master)](https://travis-ci.org/as4378/opart) [![Coverage Status](https://coveralls.io/repos/github/as4378/opart/badge.svg)](https://coveralls.io/github/as4378/opart)

This repository is for Google Summer of Code 2019 project [Optimal partitioning algorithm for changepoint detection](https://github.com/rstats-gsoc/gsoc2019/wiki/Optimal-partitioning-algorithm-for-changepoint-detection) under organization [R project for statistical computing](https://summerofcode.withgoogle.com/organizations/4934391420157952/).



## Installation

The package can be installed from github as follows:

```R
install.packages("devtools") #if not already installed

devtools::install_github("as4378/opart")
```

Alternatively, you can use remotes which is a lighter-weight package that has the install_github functionality that devtools provides, but not all the “development” parts of devtools.


```R
install.packages("remotes") #if not already installed

remotes::install_github("as4378/opart")
```

## Introduction

There are several applications where we need to work with ordered data (e.g. Time-series). This includes financial data, climate data, radio signals, genome data in bioinformatics etc. Often it is of interest to find patterns or structure in this data and to detect abrupt changes in structure to model the data effectively. There are a class of dynamic programming algorithms that can solve the optimal partitioning problem and find optimal segments given a statistical criteria.

A quadratic time algorithm described in https://link.springer.com/article/10.1007/s11222-016-9636-3 is one such algorithm that solves the optimal partitioning problem given square error loss function.
Currently there are no R packages available that provide a reference implementation to this algorithm.


This project provides an efficient C reference implementation to the standard optimal partitioning algorithm in an R package (opart) using square error loss function and poisson loss. Its simplicity makes it easy to modify (which is not true of other algorithms such as FPOP), which will be useful when developing other changepoint models/algorithms.


## Features

This package provides 2 functions:

(i) **opart_gaussian**: This function computes the optimal changepoint model for a vector of real-valued data and a non-negative real-valued penalty, given the square loss (to minimize) / gaussian likelihood (to maximize).

```R
library(opart)
sample_data <- rnorm(100, mean=50)
opart::opart_gaussian(data=sample_data, penalty=1)
```

The execution returns a cost vector (cost.vec) which contains the optimal cost values for partitioning the data and end vector (end.vec) which contains the optimal segment ends.

Complete documentation including results with neuroblastoma dataset in package neuroblastoma and model and runtime comparison with other algorithms(fpop and cpt.mean) is described in detail in vignettes.



(ii) **opart_poisson**: This function computes the optimal changepoint model for a vector of count data and a non-negative real-valued penalty, given the poisson loss (to minimize) / log likelihood (to maximize).


```R
library(opart)
sample_data <- rpois(100, 10.5)
opart::opart_poisson(data=sample_data, penalty=1)
```

The execution returns a cost vector (cost.vec) which contains the optimal cost values for partitioning the data and end vector (end.vec) which contains the optimal segment ends.

The vignettes describe in detail about poisson loss and model comparison with Segmentor3IsBack which provides several options for loss functions including poisson loss.



## Documentation

All the vignettes can be accessed in R envirnment after package installation. Use build_opts argument as follows with install_github to install vignettes as by default manuals are not installed. 

```R
devtools::install_github("as4378/opart", build_opts = c("--no-resave-data"))
```

A quick reference to all vignettes in pdf format can be found [here](https://drive.google.com/open?id=1N9OSTHAGaH_ZrOeRNcNc5eXFEDkJWbjY)


## Future Work

In future we would like to extend this package by supporting different loss functions and move this to CRAN so that it is available to wide community of R users. If possible, extend this further to provide a generic option for supporting user specified loss function as an input argument.

## Acknowledgements

* The Google Summer of Code team for funding and motivating open source development

* My mentors Guillem Rigaill, Rebecca Killick and Toby Hocking

* Members of R Project for Statistical Computing community

* A special thanks to [Toby Hocking](https://github.com/tdhock) for his support and insights throughout the entire GSoC. His experience working with R packages helped in efficient implementation of this package and making it a reality

## Link to commits

All the commits made throughout the entire GSoC program can be accessed by this [link](https://github.com/as4378/opart/commits/master)

