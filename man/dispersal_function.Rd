% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/dispersal_kernel_functions-class.R
\name{exponential_dispersal_kernel}
\alias{exponential_dispersal_kernel}
\title{Create a dispersal function}
\usage{
exponential_dispersal_kernel(distance_decay = 0.5, normalize = FALSE)
}
\arguments{
\item{distance_decay}{(exponential dispersal parameter) controls the rate at which the population disperses with distance}

\item{normalize}{(exponential dispersal parameter) should the normalising constant be used - default is FALSE.}
}
\value{
An object of class \code{dispersal_function}
}
\description{
A dispersal kernal function is a mathematical representation of how species redistribute
across the landscape.
 
A common dispersal kernel is provided in the software for the user to select (see
\link[steps]{exponential_dispersal_kernel}), however, a user may also provide a
custom written dispersal kernel.
}
\examples{

test_dispersal_function <- exponential_dispersal_kernel()
}
