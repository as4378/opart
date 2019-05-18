# Hello, world!
#
# This is an example function named 'hello'
# which prints 'Hello, world!'.
#
# You can learn more about package authoring with RStudio at:
#
#   http://r-pkgs.had.co.nz/
#
# Some useful keyboard shortcuts for package authoring:
#
#   Build and Reload Package:  'Ctrl + Shift + B'
#   Check Package:             'Ctrl + Shift + E'
#   Test Package:              'Ctrl + Shift + T'

add <- structure(function(x, y) {
  r <- .C("add_interface", as.numeric(x), as.numeric(y), r = double(1),
            PACKAGE="Opart")$r
  r
}, ex=function(){})

