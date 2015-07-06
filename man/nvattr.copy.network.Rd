\name{nvattr.copy.network}
\alias{nvattr.copy.network}
\title{
Copy network- and vertex-level attributes between two network objects
}
\description{
An internal ergm utility function to copy the network-level attributes and vertex-level attributes from one \code{\link{network}} object to another, ignoring some standard properties by default. 
}
\usage{
nvattr.copy.network(to, from, ignore = c("bipartite", "directed",
                                         "hyper", "loops", "mnext",
                                         "multiple", "n"))
}

\arguments{
  \item{to}{
the \code{\link{network}} that attributes should be copied to 
}
  \item{from}{
the \code{\link{network}} that attributes should be copied to 
}
  \item{ignore}{
vector of charcter names of network attributes that should not be copied. Default is the standard list of network properties created by \code{\link{network.initialize}}
}
}

\value{
returns the \code{to} network, with attributes copied from \code{from}
}

\note{
does not check that networks are of the same size, etc
}


\seealso{
\code{\link{set.vertex.attribute}}, \code{\link{set.network.attribute}}
}