\name{is.dyad.independent}
\alias{is.dyad.independent}
\alias{is.dyad.independent.formula}
\alias{is.dyad.independent.ergm}
\title{
Testing for dyad-independence
}
\description{
These functions test whether an ERGM fit or formula is dyad-independent.
}
\usage{
\method{is.dyad.independent}{ergm}(object, ...)
\method{is.dyad.independent}{formula}(object, basis = NULL, constraints = ~., ...)
}
\arguments{
  \item{object}{
    An \code{\link{ergm}} object or an ERGM formula.
  }
  \item{basis, constraints}{
    See \code{\link{ergm}}.
  }
  \item{\dots}{
    Unused at this time.
}
}
\value{
  \code{TRUE} if the model fit or one implied by the formula is
  dyad-independent; \code{FALSE} otherwise.
}
\author{
  Pavel N. Krivitsky
}
\keyword{ model }