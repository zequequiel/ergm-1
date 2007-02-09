ergm.Cprepare <- function(nw, m) 
{
  # Build an object called Clist that contains all the necessary
  # ingredients to be passed to the C function.
  Clist<-list(n=network.size(nw), dir=is.directed(nw))
  bip <- nw$gal$bipartite
  if (is.null(bip)) bip <- 0
  Clist$bipartite <- bip
  e<-as.matrix.network(nw,matrix.type="edgelist")
  if(length(e)==0){
    Clist$nedges<-0
    Clist$heads<-0
    Clist$tails<-0
  }else{
    if(!is.matrix(e)){e <- matrix(e, ncol=2)}
    Clist$nedges<-dim(e)[1]
    Clist$heads<-e[,1]
    Clist$tails<-e[,2]
  }
  Clist$ndyads<-Clist$n * (Clist$n-1)
  if (!Clist$dir) {
    Clist$ndyads <- Clist$ndyads/2
  }
  mo<-m$terms 
  
  Clist$nterms<-length(mo)
  Clist$nparam<-0
  Clist$fnamestring<-""
  Clist$snamestring<-""
  Clist$inputs<-numeric(0)
  if (Clist$nterms>0) {
    for(i in 1:Clist$nterms) {
      Clist$fnamestring <- paste(Clist$fnamestring, mo[[i]]$name)
      Clist$snamestring <- paste(Clist$snamestring, mo[[i]]$soname)
      Clist$inputs <- c(Clist$inputs, mo[[i]]$inputs)
      Clist$nparam <- Clist$nparam + mo[[i]]$inputs[2]
    }
  }
  while (substring(Clist$fnamestring, 1, 1)==" ")
    Clist$fnamestring <- substring(Clist$fnamestring, 2)
  while (substring(Clist$snamestring, 1, 1)==" ")
    Clist$snamestring <- substring(Clist$snamestring, 2)
  Clist
}


