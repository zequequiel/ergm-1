#  File tests/miss_tests.R in package ergm, part of the Statnet suite
#  of packages for network analysis, http://statnet.org .
#
#  This software is distributed under the GPL-3 license.  It is free,
#  open source, and has the attribution requirements (GPL Section 7) at
#  http://statnet.org/attribution
#
#  Copyright 2003-2017 Statnet Commons
#######################################################################
library(statnet.common)
opttest({
library(ergm)
theta0err<- 1 # Perturbation in the initial values
tolerance<-5 # Result must be within 5*MCMCSE. of truth.

n<-20 # Number of nodes
b<-3 # Bipartite split

d<-.1 # Density
m<-.05 # Missingness rate

logit<-function(p) log(p/(1-p))

cat("n=",n,", density=",d,", missing=",m,"\n",sep="")
mk.missnet<-function(n,d,m,directed=TRUE,bipartite=FALSE){
  y<-network.initialize(n, directed=directed, bipartite=bipartite)
  y<-simulate(y~edges, coef=logit(d), control=control.simulate(MCMC.burnin=2*n^2))
  if(m>0){
    y.miss<-simulate(y~edges, coef=logit(m))
    y[as.edgelist(y.miss)]<-NA
  }
  y
}

correct.edges.theta<-function(y){
  e<-network.edgecount(y)
  d<-network.dyadcount(y)

  logit(e/d)
}


run.miss.test<-function(y){
  truth<-correct.edges.theta(y)
  cat("Correct estimate =",truth,"\n")
  
  mplefit<-ergm(y~edges)
  mpleOK<-all.equal(truth,coef(mplefit),check.attributes=FALSE)
  cat("MPLE estimate =", coef(mplefit), if(isTRUE(mpleOK)) "OK" else mpleOK,"\n")

  mcmcfit<-ergm(y~edges, control=control.ergm(force.main=TRUE, init=truth+theta0err),eval.loglik=FALSE, verbose=TRUE)
  mcmc.diagnostics(mcmcfit)
  mcmcOK<-abs(truth-coef(mcmcfit))/sqrt(diag(vcov(mcmcfit, source="estimation"))) 
  cat("MCMCMLE estimate =", coef(mcmcfit), if(mcmcOK<tolerance) "OK" else mcmcOK,"\n")
  
  return(isTRUE(mpleOK) && (mcmcOK<tolerance))
}

# Directed
cat("\n\nDirected Network\n")
set.seed(123)
y<-mk.missnet(n, d, m, TRUE, FALSE)
stopifnot(run.miss.test(y))

# Undirected
cat("\n\nUndirected Network\n")
set.seed(456)
y<-mk.missnet(n, d, m, FALSE, FALSE)
stopifnot(run.miss.test(y))  

# Bipartite Undirected
cat("\n\nBipartite Undirected Network\n")
set.seed(789)
y<-mk.missnet(n, d, m, FALSE, b)
stopifnot(run.miss.test(y))

# Add the curved+missing test here for now

set.seed(321)
n <- 50
y <- network.initialize(n, directed=FALSE) # Create an empty network
y <- simulate(y~edges, coef=logit(0.12), control=control.simulate(MCMC.burnin=2*n^2))
y.miss <- simulate(y~edges, coef=logit(0.01))
y[as.edgelist(y.miss)] <- NA

cat("Network statistics:\n")
print(summary(y~edges+gwesp(0.5)))
truth<-correct.edges.theta(y)
cat("Correct estimate =",truth,"\n")

set.seed(654)
mcmcfit<-ergm(y~edges+gwesp(0.5), control=control.ergm(MCMLE.maxit=5))
summary(mcmcfit)
stopifnot(abs(coef(mcmcfit)[1]-truth)/sqrt(mcmcfit$covar[1])<2)
}, "missing data")
