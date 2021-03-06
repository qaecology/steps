% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/data.R
\docType{data}
\name{egk}
\alias{egk}
\alias{egk_hab}
\alias{egk_pop}
\alias{egk_k}
\alias{egk_mat}
\alias{egk_mat_stoch}
\alias{egk_sf}
\alias{egk_fire}
\alias{egk_source}
\alias{egk_sink}
\alias{egk_road}
\title{Eastern Grey Kangaroo example data}
\format{Misc data}
\usage{
egk_hab

egk_pop

egk_k

egk_mat

egk_mat_stoch

egk_sf

egk_fire

egk_source

egk_sink

egk_road
}
\description{
Example data for simulating spatial population dynamics of Eastern Grey
Kangaroos in a hypothetical landscape.
}
\details{
\describe{
  \item{egk_hab}{A raster layer containing the predicted relative habitat
  suitability for the Eastern Grey Kangaroo.}
  \item{egk_pop}{A raster stack containing intital populations for each
  life-stage of the Eastern Grey Kangaroo.}
  \item{egk_k}{A raster layer containing the total number of Eastern Grey
  Kangaroos each grid cell can support.}
  \item{egk_mat}{A matrix containing the survival and fecundity of Eastern
  Grey Kangaroos at each of three life-stages - juvenile, subadult, and adult.}
  \item{egk_mat_stoch}{A matrix containing the uncertainty around survival
  and fecundity of Eastern Grey Kangaroos at each of three life-stages -
  juvenile, subadult, and adult.}
  \item{egk_sf}{A raster stack containing values for modifying survival and
  fecundities - each is raster is named according to the timestep and position
  of the life-stage matrix to be modified.}
  \item{egk_fire}{A raster stack containing values for modifying the habitat
  - in this case the proportion of landscape remaining after fire.}
  \item{egk_source}{A raster stack containing locations and counts of where
  to move individual kangaroos from.}
  \item{egk_sink}{A raster stack containing locations and counts of where to
  move individual kangaroos to.}
  \item{egk_road}{A raster stack containing values for modifying the habitat
  - in this case the proportion of habitat remaining after the construction of a road.}
}
}
\keyword{datasets}
