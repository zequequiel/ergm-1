check.ErgmTerm <- function(arglist, directed=NULL, bipartite=NULL,
                           varnames=NULL, vartypes=NULL,
                           defaultvalues=list(), required=NULL) {
  ## This function (called by InitErgmTerm.xxx functions) will
  ## (a) check to make sure that the network has the correct "directed"
  ##     and "bipartite" attributes, if applicable, i.e., if either directed
  ##     of bipartite is non-NULL.
  ## (b) check that the inputs to the model term are of the correct type
  ## (c) assign default values if applicable
  ## (d) return a list with elements (var1=var1value, var2=var2value, etc.)
  ## Note that the list returned will contain the maximum possible number of
  ## arguments; any arguments without values are returned as NULL.
  ##
  ##   Inputs:  arglist (required) is the list of arguments passed from ergm.getmodel
  ##            directed is logical if directed=T or F is required, NULL o/w
  ##            bipartite is logical if bipartite=T or F is required, NULL o/w
  ##            varnames is a vector of variable names
  ##            vartypes is a vector of corresponding variable types
  ##            defaultvalues is a list of default values (NULL means no default)
  ##            required is a vector of logicals:  Is this var required or not?
  sc <- sys.calls()
  fname <- ifelse(length(sc)>1, as.character(sc[[length(sc)-1]]), NULL)
  fname <- substring(fname,14) # get rid of leading "InitErgmTerm."
  message <- NULL
  if (!is.null(directed) && directed != is.directed(nw)) {
    message <- paste("networks with directed==",is.directed(nw),sep="")
  }
  if (!is.null(bipartite) && bipartite != (nw %v% "bipartite" > 0)) {
    message <- paste("networks with bipartite", 
                     ifelse(nw %v% "bipartite">0,"!= FALSE", " > 0"))
  }
  if (!is.null(message)) {
    stop(paste("The ERGM term",fnames,"may not be used with",message))
  }

  sr=sum(required)
  lv=length(varnames)
  la=length(arglist)
  if(la < sr || la > lv) {
    if (sr < lv)
      expected = paste("from",sr,"to",lv,"arguments,")
    else if(sr==1)
      expected = "1 argument,"
    else
      expected = paste(sr,"arguments,")
    stop(paste(fname,"model term expected", expected, "got", la), call.=FALSE)
  }
# The correctness of what the user typed is checked, but it is assumed
# that each InitErgmTerm function faithfully passes in what the user typed;
# thus, the correctness of input from the InitErgmTerm function isn't checked.
  out = defaultvalues
  names(out)=varnames
  m=NULL
  if (la>0) {
    for(i in 1:la) { # check each arglist entry
      if (!is.null(names(arglist)) && (name <- names(arglist)[i]) != "") {
        m = pmatch(name, varnames)# try to match user-typed name if applicable
        if(is.na(m)) { # User typed an unrecognizable name
          stop(paste(fname,"model term does not recognize",
                     name, "argument"), call.=FALSE)
        }
        # valid name match with mth variable if we got to here
        if (!eval(call(paste("is.",vartypes[m],sep=""),arglist[[i]]))) {
          # Wrong type
          stop(paste(name, "argument to", fname, "model term is not of",
                     "the expected", vartypes[m], "type"), call.=FALSE)
        }
        # correct type if we got to here
        out[[m]]=arglist[[i]]
      } else { # no user-typed name for this argument
        if (!is.null(m)) {
          stop(paste("unnamed argument follows named argument in",
                     fname,"model term"), call.=FALSE)
        }
        if (!eval(call(paste("is.",vartypes[i],sep=""),arglist[[i]]))) {
          # Wrong type
          stop(paste("argument number", i, "to", fname, "model term is not",
                     "of the expected", vartypes[i], "type"), call.=FALSE)
        }
        # correct type if we got to here
        out[[i]]=arglist[[i]]
      }
    }
  }
  c(.conflicts.OK=TRUE,out)
}
