#  get.node.attr takes the network.and a vertex attribute name, as
#  well as the name of the function calling get.node.attr, as arguments.
#  If there is a vertex attribute by that name, it returns the vector
#  of covariates; otherwise, it aborts and prints an error message.

# This is a kludge, which has been patched to bring it in line with the
# corrected class definitions.  -CTB

get.node.attr <- function(nw, attrname, functionname)
{
  if (!is.character(attrname) || length(attrname)>1)
    stop(paste("The argument", attrname, "passed to", functionname,
               "must be a single character string naming a nodal attribute."),
         call.=FALSE)
  #We'll assume that every vertex must have a value, so checking the 
  #first is reasonable.
  if (!any(attrname==names(nw$val[[1]])))
    stop(paste("Attribute", attrname, "named in", functionname,
               "model term is not contained in vertex attribute list."),
         call.=FALSE)
  #"[["(nw$val,attrname)
  unlist(get.vertex.attribute(nw,attrname))
}
