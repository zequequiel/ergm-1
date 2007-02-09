#include "basechangeStats.h"
 
/*****************
 void d_triadcensus
*****************/
void d_triadcensus (int ntoggles, Vertex *heads, Vertex *tails, 
	            ModelTerm *mtp, Network *nwp) 
{
  int i, j, edgeflag, a, b, c, d, e, edgecount, t300, 
  t210, t120C, t120U, t120D, t201, t030C, t030T, t111U, 
  t111D, t021C, t021U, t021D, t102, t012, t003;
  Vertex triadtype, node3, h, t;

  for (i=0; i < mtp->nstats; i++) 
    mtp->dstats[i] = 0.0;

  if (nwp->directed_flag) {
// directed version
   for (i=0; i<ntoggles; i++) 
    {      
      edgeflag = (EdgetreeSearch(h=heads[i], t=tails[i], nwp->outedges) != 0);
      t300 = 0;
      t210 = 0;
      t120C = 0;  t120U = 0;   t120D = 0;  t201 = 0;
      t030C = 0;  t030T = 0;   t111U = 0;  t111D = 0;
      t021C = 0;  t021U = 0;   t021D = 0;  t102 = 0;
      t012 = 0;

      if ((EdgetreeMinimum(nwp->outedges, t) != 0) || 
          (EdgetreeMinimum(nwp->inedges, t) != 0) || 
          (EdgetreeMinimum(nwp->outedges, h) != 0) ||
          (EdgetreeMinimum(nwp->inedges, h) != 0)) {      

          /* ****** loop through node3 ****** */
          for (node3=1; node3 <= nwp->nnodes; node3++)
             { 
             if (node3 != h && node3 != t)
               {   
               a = (EdgetreeSearch(t, h, nwp->outedges) != 0); 
               b = (EdgetreeSearch(t, node3, nwp->outedges) != 0);
               c = (EdgetreeSearch(node3, t, nwp->outedges) != 0);
               d = (EdgetreeSearch(node3, h, nwp->outedges) != 0);
               e = (EdgetreeSearch(h, node3, nwp->outedges) != 0);
               edgecount = (a + b + c + d + e);

               switch(edgecount)
               {  
               case 0:   /* 012 */
                 ++t012;

               case 1:   /* 021C, 021U, 021D, 102 */
                 {
                     if ((b == 1) || (d == 1))
                       ++t021C;
                     if (c == 1)
                       ++t021U;
                     if (e == 1)
                       ++t021D;
                     if (a == 1)
                       ++t102;
                 }
                 break;
          
               case 2:   /* 030C, 030T, 111U, 111D */
                 {
                     if ((b + d) == 2)       
                       ++t030C;
                     if (((b + e) == 2) || ((c + d) == 2) || ((c + e) == 2))
                       ++t030T;
                     if (((a + b) == 2) || ((a + e) == 2) || ((d + e) == 2))
                       ++t111U;
                     if (((a + c) == 2) || ((a + d) == 2) || ((b + c) == 2))
                       ++t111D;
                 }
                 break;
            
               case 3:   /* 120C, 120U, 120D, 201 */
                 {
                     if (a == 1)
                         {
                            if (((b + d) == 2) || ((c + e) == 2))
                              ++t120C;
                            if ((b + e) == 2)
                              ++t120U;
                            if ((c + d) == 2)
                              ++t120D;
                            if (((b + c) == 2) || ((d + e) == 2))
                              ++t201;
                         }
                     else 
                         {
                            if (b == 1)
                                {
                                    if (((c + d) == 2) || ((d + e) == 2))
                                      ++t120C;
                                    if ((c + e) == 2)
                                      ++t120D;
                                } 
                            else 
                                {
                                    ++t120U;
                                }
                         } 
                 }
                 break;
             
               case 4:   /* 210 */
                 ++t210;
                 break;
             
               case 5:   /* 300 */            
                 ++t300;
                 break;
               }

               switch(edgecount)
               {  
               case 1:   /* 102, 021D, 021U, 021C */
                 --t012;
                 break;
           
               case 2:   /* 030C, 030T, 111U, 111D */ 
                 {
                     if (((a + c) == 2) || ((a + e) == 2) || ((b + d) == 2) || 
                        ((c + e) == 2)) 
                       --t021C;
                     if (((a + d) == 2) || ((b + e) == 2))
                       --t021U;
                     if (((a + b) == 2) || ((c + d) == 2))
                       --t021D;
                     if (((b + c) == 2) || ((d + e) == 2))
                       --t102;
                 } 
                 break;

               case 3:   /* 201, 120D, 120U, 120C */
                 {
                     if (a == 1)
	    	           {
	    	           if ((c + e) == 2)       
                             --t030C;
                           if (((c + d) == 2) || ((b + e) == 2) || ((b + d) == 2))
                             --t030T;
                           if ((b + c) == 2)
                             --t111U;
                           if ((d + e) == 2)
	                      --t111D;
	 	               }
 		             else
 		               {
 		                   if (b == 1)
 		 	                 {
 		 	                   if ((c + d) == 2)
 			                     --t111U;
 			                   if (((c + e) == 2) || ((d + e) == 2))
			                     --t111D;
 		 	                 }
    	    	                   else
		    	                 --t111U;
    		               }
                   }
                   break;
          
               case 4:   /* 210 */
                 {
                     if (a == 1)
                         {
                            if (((b + c + e) == 3) || ((c + d + e) == 3))
                              --t120C;
                            if ((b + c + d) == 3)
                              --t120U;
                            if ((b + d + e) == 3)
                              --t120D;
                         }
                     else 
                         {
                            if ((b + c + d + e) == 4)
                              --t201;
                         } 
                 }
                 break;
              
               case 5:   /* 300 */            
                 --t210;
                 break;
               }
               }
             }    /* ******  move to next node3 ******** */
        }
        else 
          t012 = t012 + (nwp->nnodes - 2);  

      for(j = 0; j < mtp->nstats; j++)
        { 
	    triadtype = (Vertex)mtp->inputparams[j]; 

            switch(triadtype)
            {
                case 1:  t003 = (t300+t210+t120C+t120U+t120D+t201+t030C+t030T);
			 t003 = t003+(t111U+t111D+t021C+t021U+t021D+t102+t012);
 	                 mtp->dstats[j] += edgeflag ? -(double)t003 : (double)t003;
		      break;
 	        case 2:   mtp->dstats[j] += edgeflag ? -(double)t012 : (double)t012;
	              break;
	        case 3:   mtp->dstats[j] += edgeflag ? -(double)t102 : (double)t102;
                      break;
	        case 4:   mtp->dstats[j] += edgeflag ? -(double)t021D : (double)t021D;
                      break;
	        case 5:   mtp->dstats[j] += edgeflag ? -(double)t021U : (double)t021U;
                      break;
 	        case 6:   mtp->dstats[j] += edgeflag ? -(double)t021C : (double)t021C;
                      break;
	        case 7:	  mtp->dstats[j] += edgeflag ? -(double)t111D : (double)t111D;
                      break;
	        case 8:	  mtp->dstats[j] += edgeflag ? -(double)t111U : (double)t111U;
                      break;
	        case 9:	  mtp->dstats[j] += edgeflag ? -(double)t030T : (double)t030T;
                      break;
	        case 10:   mtp->dstats[j] += edgeflag ? -(double)t030C : (double)t030C;
                      break;
	        case 11:  mtp->dstats[j] += edgeflag ? -(double)t201 : (double)t201;
                      break;
	        case 12:  mtp->dstats[j] += edgeflag ? -(double)t120D : (double)t120D;
                      break;
	        case 13:  mtp->dstats[j] += edgeflag ? -(double)t120U : (double)t120U;
                      break;
	        case 14:  mtp->dstats[j] += edgeflag ? -(double)t120C : (double)t120C;
                      break;
	        case 15:  mtp->dstats[j] += edgeflag ? -(double)t210 : (double)t210;
                      break;
  	        case 16:  mtp->dstats[j] += edgeflag ? -(double)t300 : (double)t300;
		      break;
            }
        }
      if (i+1 < ntoggles)
	  ToggleEdge(heads[i], tails[i], nwp);  /* Toggle this edge if more to come */ 
    }
    }else{
//  undirected
    for (i=0; i<ntoggles; i++) 
     {      
      edgeflag = (EdgetreeSearch(h=heads[i], t=tails[i], nwp->outedges) != 0);
      t300 = 0; t201 = 0; t102 = 0; t012 = 0;

      if ((EdgetreeMinimum(nwp->outedges, t) != 0) || 
          (EdgetreeMinimum(nwp->inedges, t) != 0) || 
          (EdgetreeMinimum(nwp->outedges, h) != 0) ||
          (EdgetreeMinimum(nwp->inedges, h) != 0)) {      

          /* ****** loop through node3 ****** */
          for (node3=1; node3 <= nwp->nnodes; node3++)
             { 
             if (node3 != h && node3 != t)
               {   
               a = (EdgetreeSearch(MIN(node3,t), MAX(node3,t), nwp->outedges) != 0);
               b = (EdgetreeSearch(MIN(node3,h), MAX(node3,h), nwp->outedges) != 0);
               edgecount = (a + b);

               switch(edgecount)
               {  
               case 0:   /* 012 */
		{
                 ++t102;
                 --t012;
		}
                break;

               case 1:   /* 021C, 021U, 021D, 102 */
		{
                 ++t201;
                 --t102;
		}
                break;
          
               case 2:   /* 030C, 030T, 111U, 111D */
		{
                 ++t300;
                 --t201;
		}
                break;
            
               }
	       }

             }    /* ******  move to next node3 ******** */
        }
        else 
          t102 = t102 + (nwp->nnodes - 2);  

      for(j = 0; j < mtp->nstats; j++)
        { 
	    triadtype = (Vertex)mtp->inputparams[j]; 

            switch(triadtype)
            {
                case 1:  t003 = (t102+t201+t300);
 	                 mtp->dstats[j] += edgeflag ? -(double)t003 : (double)t003;
		      break;
 	        case 2:  mtp->dstats[j] += edgeflag ? -(double)t102 : (double)t102;
		      break;
	        case 3:  mtp->dstats[j] += edgeflag ? -(double)t201 : (double)t201;
                      break;
	        case 4:  mtp->dstats[j] += edgeflag ? -(double)t300 : (double)t300;
                      break;
            }
        }
     if (i+1 < ntoggles)
	  ToggleEdge(heads[i], tails[i], nwp);  /* Toggle this edge if more to come */ 
     } // i loop
    }
    
  i--; 
  while (--i>=0)  /*  Undo all previous toggles. */
    ToggleEdge(heads[i], tails[i], nwp); 
}

/*****************
 void d_balance
*****************/
void d_balance (int ntoggles, Vertex *heads, Vertex *tails, 
	            ModelTerm *mtp, Network *nwp) 
{
  int i, edgeflag, a, b, c, d, e, edgecount, t300, 
  t210, t120C, t120U, t120D, t201, t030C, t030T, t111U, 
  t111D, t021C, t021U, t021D, t102, t012, t003;
  Vertex node3, h, t;

  *(mtp->dstats) = 0.0;

  if (nwp->directed_flag) {
// directed version
   for (i=0; i<ntoggles; i++) 
    {      
      edgeflag = (EdgetreeSearch(h=heads[i], t=tails[i], nwp->outedges) != 0);
      t300 = 0;
      t210 = 0;
      t120C = 0;  t120U = 0;   t120D = 0;  t201 = 0;
      t030C = 0;  t030T = 0;   t111U = 0;  t111D = 0;
      t021C = 0;  t021U = 0;   t021D = 0;  t102 = 0;
      t012 = 0;

      if ((EdgetreeMinimum(nwp->outedges, t) != 0) || 
          (EdgetreeMinimum(nwp->inedges, t) != 0) || 
          (EdgetreeMinimum(nwp->outedges, h) != 0) ||
          (EdgetreeMinimum(nwp->inedges, h) != 0)) {      

          /* ****** loop through node3 ****** */
          for (node3=1; node3 <= nwp->nnodes; node3++)
             { 
             if (node3 != h && node3 != t)
               {   
               a = (EdgetreeSearch(t, h, nwp->outedges) != 0); 
               b = (EdgetreeSearch(t, node3, nwp->outedges) != 0);
               c = (EdgetreeSearch(node3, t, nwp->outedges) != 0);
               d = (EdgetreeSearch(node3, h, nwp->outedges) != 0);
               e = (EdgetreeSearch(h, node3, nwp->outedges) != 0);
               edgecount = (a + b + c + d + e);

               switch(edgecount)
               {  
               case 0:   /* 012 */
                 ++t012;

               case 1:   /* 021C, 021U, 021D, 102 */
                 {
                     if ((b == 1) || (d == 1))
                       ++t021C;
                     if (c == 1)
                       ++t021U;
                     if (e == 1)
                       ++t021D;
                     if (a == 1)
                       ++t102;
                 }
                 break;
          
               case 2:   /* 030C, 030T, 111U, 111D */
                 {
                     if ((b + d) == 2)       
                       ++t030C;
                     if (((b + e) == 2) || ((c + d) == 2) || ((c + e) == 2))
                       ++t030T;
                     if (((a + b) == 2) || ((a + e) == 2) || ((d + e) == 2))
                       ++t111U;
                     if (((a + c) == 2) || ((a + d) == 2) || ((b + c) == 2))
                       ++t111D;
                 }
                 break;
            
               case 3:   /* 120C, 120U, 120D, 201 */
                 {
                     if (a == 1)
                         {
                            if (((b + d) == 2) || ((c + e) == 2))
                              ++t120C;
                            if ((b + e) == 2)
                              ++t120U;
                            if ((c + d) == 2)
                              ++t120D;
                            if (((b + c) == 2) || ((d + e) == 2))
                              ++t201;
                         }
                     else 
                         {
                            if (b == 1)
                                {
                                    if (((c + d) == 2) || ((d + e) == 2))
                                      ++t120C;
                                    if ((c + e) == 2)
                                      ++t120D;
                                } 
                            else 
                                {
                                    ++t120U;
                                }
                         } 
                 }
                 break;
             
               case 4:   /* 210 */
                 ++t210;
                 break;
             
               case 5:   /* 300 */            
                 ++t300;
                 break;
               }

               switch(edgecount)
               {  
               case 1:   /* 102, 021D, 021U, 021C */
                 --t012;
                 break;
           
               case 2:   /* 030C, 030T, 111U, 111D */ 
                 {
                     if (((a + c) == 2) || ((a + e) == 2) || ((b + d) == 2) || 
                        ((c + e) == 2)) 
                       --t021C;
                     if (((a + d) == 2) || ((b + e) == 2))
                       --t021U;
                     if (((a + b) == 2) || ((c + d) == 2))
                       --t021D;
                     if (((b + c) == 2) || ((d + e) == 2))
                       --t102;
                 } 
                 break;

               case 3:   /* 201, 120D, 120U, 120C */
                 {
                     if (a == 1)
	    	           {
	    	           if ((c + e) == 2)       
                             --t030C;
                           if (((c + d) == 2) || ((b + e) == 2) || ((b + d) == 2))
                             --t030T;
                           if ((b + c) == 2)
                             --t111U;
                           if ((d + e) == 2)
	                      --t111D;
	 	               }
 		             else
 		               {
 		                   if (b == 1)
 		 	                 {
 		 	                   if ((c + d) == 2)
 			                     --t111U;
 			                   if (((c + e) == 2) || ((d + e) == 2))
			                     --t111D;
 		 	                 }
    	    	                   else
		    	                 --t111U;
    		               }
                   }
                   break;
          
               case 4:   /* 210 */
                 {
                     if (a == 1)
                         {
                            if (((b + c + e) == 3) || ((c + d + e) == 3))
                              --t120C;
                            if ((b + c + d) == 3)
                              --t120U;
                            if ((b + d + e) == 3)
                              --t120D;
                         }
                     else 
                         {
                            if ((b + c + d + e) == 4)
                              --t201;
                         } 
                 }
                 break;
              
               case 5:   /* 300 */            
                 --t210;
                 break;
               }
               }
             }    /* ******  move to next node3 ******** */
        }
        else 
          t012 = t012 + (nwp->nnodes - 2);  

//        t003 = (t300+t210+t120C+t120U+t120D+t201+t030C+t030T);
//        t003 = t003+(t111U+t111D+t021C+t021U+t021D+t102+t012);
	b = t102 + t300; 
	*(mtp->dstats) += edgeflag ? -(double)b : (double)b;

      if (i+1 < ntoggles)
	  ToggleEdge(heads[i], tails[i], nwp);  /* Toggle this edge if more to come */ 
    }
    }else{
//  undirected
    for (i=0; i<ntoggles; i++) 
     {      
      edgeflag = (EdgetreeSearch(h=heads[i], t=tails[i], nwp->outedges) != 0);
      t300 = 0; t201 = 0; t102 = 0; t012 = 0;

      if ((EdgetreeMinimum(nwp->outedges, t) != 0) || 
          (EdgetreeMinimum(nwp->inedges, t) != 0) || 
          (EdgetreeMinimum(nwp->outedges, h) != 0) ||
          (EdgetreeMinimum(nwp->inedges, h) != 0)) {      

          /* ****** loop through node3 ****** */
          for (node3=1; node3 <= nwp->nnodes; node3++)
             { 
             if (node3 != h && node3 != t)
               {   
               a = (EdgetreeSearch(MIN(node3,t), MAX(node3,t), nwp->outedges) != 0);
               b = (EdgetreeSearch(MIN(node3,h), MAX(node3,h), nwp->outedges) != 0);
               edgecount = (a + b);

               switch(edgecount)
               {  
               case 0:   /* 012 */
		{
                 ++t102;
                 --t012;
		}
                break;

               case 1:   /* 021C, 021U, 021D, 102 */
		{
                 ++t201;
                 --t102;
		}
                break;
          
               case 2:   /* 030C, 030T, 111U, 111D */
		{
                 ++t300;
                 --t201;
		}
                break;
            
               }
	       }

             }    /* ******  move to next node3 ******** */
        }
        else 
          t102 = t102 + (nwp->nnodes - 2);  

        t003 = (t102+t201+t300);
	b = t102 + t300; 
	*(mtp->dstats) += edgeflag ? -(double)b : (double)b;
  
     if (i+1 < ntoggles)
	  ToggleEdge(heads[i], tails[i], nwp);  /* Toggle this edge if more to come */ 
     } // i loop
    }
    
  i--; 
  while (--i>=0)  /*  Undo all previous toggles. */
    ToggleEdge(heads[i], tails[i], nwp); 
}

/*****************
 void d_intransitivity
*****************/
void d_intransitivity (int ntoggles, Vertex *heads, Vertex *tails, 
	             ModelTerm *mtp, Network *nwp) 
{
  int i, edgeflag, a, b, c, d, e, edgecount, t300, 
  t210, t120C, t120U, t120D, t201, t030C, t030T, t111U, 
  t111D, t021C, t021U, t021D, t102, t012, t003;
  Vertex node3, h, t;

  *(mtp->dstats) = 0.0;

  if (nwp->directed_flag) {
// directed version
   for (i=0; i<ntoggles; i++) 
    {      
      edgeflag = (EdgetreeSearch(h=heads[i], t=tails[i], nwp->outedges) != 0);
      t300 = 0;
      t210 = 0;
      t120C = 0;  t120U = 0;   t120D = 0;  t201 = 0;
      t030C = 0;  t030T = 0;   t111U = 0;  t111D = 0;
      t021C = 0;  t021U = 0;   t021D = 0;  t102 = 0;
      t012 = 0;

      if ((EdgetreeMinimum(nwp->outedges, t) != 0) || 
          (EdgetreeMinimum(nwp->inedges, t) != 0) || 
          (EdgetreeMinimum(nwp->outedges, h) != 0) ||
          (EdgetreeMinimum(nwp->inedges, h) != 0)) {      

          /* ****** loop through node3 ****** */
          for (node3=1; node3 <= nwp->nnodes; node3++)
             { 
             if (node3 != h && node3 != t)
               {   
               a = (EdgetreeSearch(t, h, nwp->outedges) != 0); 
               b = (EdgetreeSearch(t, node3, nwp->outedges) != 0);
               c = (EdgetreeSearch(node3, t, nwp->outedges) != 0);
               d = (EdgetreeSearch(node3, h, nwp->outedges) != 0);
               e = (EdgetreeSearch(h, node3, nwp->outedges) != 0);
               edgecount = (a + b + c + d + e);

               switch(edgecount)
               {  
               case 0:   /* 012 */
                 ++t012;

               case 1:   /* 021C, 021U, 021D, 102 */
                 {
                     if ((b == 1) || (d == 1))
                       ++t021C;
                     if (c == 1)
                       ++t021U;
                     if (e == 1)
                       ++t021D;
                     if (a == 1)
                       ++t102;
                 }
                 break;
          
               case 2:   /* 030C, 030T, 111U, 111D */
                 {
                     if ((b + d) == 2)       
                       ++t030C;
                     if (((b + e) == 2) || ((c + d) == 2) || ((c + e) == 2))
                       ++t030T;
                     if (((a + b) == 2) || ((a + e) == 2) || ((d + e) == 2))
                       ++t111U;
                     if (((a + c) == 2) || ((a + d) == 2) || ((b + c) == 2))
                       ++t111D;
                 }
                 break;
            
               case 3:   /* 120C, 120U, 120D, 201 */
                 {
                     if (a == 1)
                         {
                            if (((b + d) == 2) || ((c + e) == 2))
                              ++t120C;
                            if ((b + e) == 2)
                              ++t120U;
                            if ((c + d) == 2)
                              ++t120D;
                            if (((b + c) == 2) || ((d + e) == 2))
                              ++t201;
                         }
                     else 
                         {
                            if (b == 1)
                                {
                                    if (((c + d) == 2) || ((d + e) == 2))
                                      ++t120C;
                                    if ((c + e) == 2)
                                      ++t120D;
                                } 
                            else 
                                {
                                    ++t120U;
                                }
                         } 
                 }
                 break;
             
               case 4:   /* 210 */
                 ++t210;
                 break;
             
               case 5:   /* 300 */            
                 ++t300;
                 break;
               }

               switch(edgecount)
               {  
               case 1:   /* 102, 021D, 021U, 021C */
                 --t012;
                 break;
           
               case 2:   /* 030C, 030T, 111U, 111D */ 
                 {
                     if (((a + c) == 2) || ((a + e) == 2) || ((b + d) == 2) || 
                        ((c + e) == 2)) 
                       --t021C;
                     if (((a + d) == 2) || ((b + e) == 2))
                       --t021U;
                     if (((a + b) == 2) || ((c + d) == 2))
                       --t021D;
                     if (((b + c) == 2) || ((d + e) == 2))
                       --t102;
                 } 
                 break;

               case 3:   /* 201, 120D, 120U, 120C */
                 {
                     if (a == 1)
	    	           {
	    	           if ((c + e) == 2)       
                             --t030C;
                           if (((c + d) == 2) || ((b + e) == 2) || ((b + d) == 2))
                             --t030T;
                           if ((b + c) == 2)
                             --t111U;
                           if ((d + e) == 2)
	                      --t111D;
	 	               }
 		             else
 		               {
 		                   if (b == 1)
 		 	                 {
 		 	                   if ((c + d) == 2)
 			                     --t111U;
 			                   if (((c + e) == 2) || ((d + e) == 2))
			                     --t111D;
 		 	                 }
    	    	                   else
		    	                 --t111U;
    		               }
                   }
                   break;
          
               case 4:   /* 210 */
                 {
                     if (a == 1)
                         {
                            if (((b + c + e) == 3) || ((c + d + e) == 3))
                              --t120C;
                            if ((b + c + d) == 3)
                              --t120U;
                            if ((b + d + e) == 3)
                              --t120D;
                         }
                     else 
                         {
                            if ((b + c + d + e) == 4)
                              --t201;
                         } 
                 }
                 break;
              
               case 5:   /* 300 */            
                 --t210;
                 break;
               }
               }
             }    /* ******  move to next node3 ******** */
        }
        else 
          t012 = t012 + (nwp->nnodes - 2);  

//        t003 = -(t300+t210+t120C+t120U+t120D+t201+t030C+t030T);
//        t003 = t003-(t111U+t111D+t021C+t021U+t021D+t102+t012);
	b = t021C+t030C+t111D+t111U+t120C+t201+t210;
	*(mtp->dstats) += edgeflag ? -(double)b : (double)b;

      if (i+1 < ntoggles)
	  ToggleEdge(heads[i], tails[i], nwp);  /* Toggle this edge if more to come */ 
    }
    }else{
//  undirected
    for (i=0; i<ntoggles; i++) 
     {      
      edgeflag = (EdgetreeSearch(h=heads[i], t=tails[i], nwp->outedges) != 0);
      t300 = 0; t201 = 0; t102 = 0; t012 = 0;

      if ((EdgetreeMinimum(nwp->outedges, t) != 0) || 
          (EdgetreeMinimum(nwp->inedges, t) != 0) || 
          (EdgetreeMinimum(nwp->outedges, h) != 0) ||
          (EdgetreeMinimum(nwp->inedges, h) != 0)) {      

          /* ****** loop through node3 ****** */
          for (node3=1; node3 <= nwp->nnodes; node3++)
             { 
             if (node3 != h && node3 != t)
               {   
               a = (EdgetreeSearch(MIN(node3,t), MAX(node3,t), nwp->outedges) != 0);
               b = (EdgetreeSearch(MIN(node3,h), MAX(node3,h), nwp->outedges) != 0);
               edgecount = (a + b);

               switch(edgecount)
               {  
               case 0:   /* 012 */
		{
                 ++t102;
                 --t012;
		}
                break;

               case 1:   /* 021C, 021U, 021D, 102 */
		{
                 ++t201;
                 --t102;
		}
                break;
          
               case 2:   /* 030C, 030T, 111U, 111D */
		{
                 ++t300;
                 --t201;
		}
                break;
            
               }
	       }

             }    /* ******  move to next node3 ******** */
        }
        else 
          t102 = t102 + (nwp->nnodes - 2);  

        t003 = -(t102+t201+t300);
	b = t300; 
	*(mtp->dstats) += edgeflag ? -(double)b : (double)b;
  
     if (i+1 < ntoggles)
	  ToggleEdge(heads[i], tails[i], nwp);  /* Toggle this edge if more to come */ 
     } // i loop
    }
    
  i--; 
  while (--i>=0)  /*  Undo all previous toggles. */
    ToggleEdge(heads[i], tails[i], nwp); 
}
/*****************
 void d_transitivity
*****************/
void d_transitivity (int ntoggles, Vertex *heads, Vertex *tails, 
	             ModelTerm *mtp, Network *nwp) 
{
  int i, edgeflag, a, b, c, d, e, edgecount, t300, 
  t210, t120C, t120U, t120D, t201, t030C, t030T, t111U, 
  t111D, t021C, t021U, t021D, t102, t012, t003;
  Vertex node3, h, t;

  *(mtp->dstats) = 0.0;

  if (nwp->directed_flag) {
// directed version
   for (i=0; i<ntoggles; i++) 
    {      
      edgeflag = (EdgetreeSearch(h=heads[i], t=tails[i], nwp->outedges) != 0);
      t300 = 0;
      t210 = 0;
      t120C = 0;  t120U = 0;   t120D = 0;  t201 = 0;
      t030C = 0;  t030T = 0;   t111U = 0;  t111D = 0;
      t021C = 0;  t021U = 0;   t021D = 0;  t102 = 0;
      t012 = 0;

      if ((EdgetreeMinimum(nwp->outedges, t) != 0) || 
          (EdgetreeMinimum(nwp->inedges, t) != 0) || 
          (EdgetreeMinimum(nwp->outedges, h) != 0) ||
          (EdgetreeMinimum(nwp->inedges, h) != 0)) {      

          /* ****** loop through node3 ****** */
          for (node3=1; node3 <= nwp->nnodes; node3++)
             { 
             if (node3 != h && node3 != t)
               {   
               a = (EdgetreeSearch(t, h, nwp->outedges) != 0); 
               b = (EdgetreeSearch(t, node3, nwp->outedges) != 0);
               c = (EdgetreeSearch(node3, t, nwp->outedges) != 0);
               d = (EdgetreeSearch(node3, h, nwp->outedges) != 0);
               e = (EdgetreeSearch(h, node3, nwp->outedges) != 0);
               edgecount = (a + b + c + d + e);

               switch(edgecount)
               {  
               case 0:   /* 012 */
                 ++t012;

               case 1:   /* 021C, 021U, 021D, 102 */
                 {
                     if ((b == 1) || (d == 1))
                       ++t021C;
                     if (c == 1)
                       ++t021U;
                     if (e == 1)
                       ++t021D;
                     if (a == 1)
                       ++t102;
                 }
                 break;
          
               case 2:   /* 030C, 030T, 111U, 111D */
                 {
                     if ((b + d) == 2)       
                       ++t030C;
                     if (((b + e) == 2) || ((c + d) == 2) || ((c + e) == 2))
                       ++t030T;
                     if (((a + b) == 2) || ((a + e) == 2) || ((d + e) == 2))
                       ++t111U;
                     if (((a + c) == 2) || ((a + d) == 2) || ((b + c) == 2))
                       ++t111D;
                 }
                 break;
            
               case 3:   /* 120C, 120U, 120D, 201 */
                 {
                     if (a == 1)
                         {
                            if (((b + d) == 2) || ((c + e) == 2))
                              ++t120C;
                            if ((b + e) == 2)
                              ++t120U;
                            if ((c + d) == 2)
                              ++t120D;
                            if (((b + c) == 2) || ((d + e) == 2))
                              ++t201;
                         }
                     else 
                         {
                            if (b == 1)
                                {
                                    if (((c + d) == 2) || ((d + e) == 2))
                                      ++t120C;
                                    if ((c + e) == 2)
                                      ++t120D;
                                } 
                            else 
                                {
                                    ++t120U;
                                }
                         } 
                 }
                 break;
             
               case 4:   /* 210 */
                 ++t210;
                 break;
             
               case 5:   /* 300 */            
                 ++t300;
                 break;
               }

               switch(edgecount)
               {  
               case 1:   /* 102, 021D, 021U, 021C */
                 --t012;
                 break;
           
               case 2:   /* 030C, 030T, 111U, 111D */ 
                 {
                     if (((a + c) == 2) || ((a + e) == 2) || ((b + d) == 2) || 
                        ((c + e) == 2)) 
                       --t021C;
                     if (((a + d) == 2) || ((b + e) == 2))
                       --t021U;
                     if (((a + b) == 2) || ((c + d) == 2))
                       --t021D;
                     if (((b + c) == 2) || ((d + e) == 2))
                       --t102;
                 } 
                 break;

               case 3:   /* 201, 120D, 120U, 120C */
                 {
                     if (a == 1)
	    	           {
	    	           if ((c + e) == 2)       
                             --t030C;
                           if (((c + d) == 2) || ((b + e) == 2) || ((b + d) == 2))
                             --t030T;
                           if ((b + c) == 2)
                             --t111U;
                           if ((d + e) == 2)
	                      --t111D;
	 	               }
 		             else
 		               {
 		                   if (b == 1)
 		 	                 {
 		 	                   if ((c + d) == 2)
 			                     --t111U;
 			                   if (((c + e) == 2) || ((d + e) == 2))
			                     --t111D;
 		 	                 }
    	    	                   else
		    	                 --t111U;
    		               }
                   }
                   break;
          
               case 4:   /* 210 */
                 {
                     if (a == 1)
                         {
                            if (((b + c + e) == 3) || ((c + d + e) == 3))
                              --t120C;
                            if ((b + c + d) == 3)
                              --t120U;
                            if ((b + d + e) == 3)
                              --t120D;
                         }
                     else 
                         {
                            if ((b + c + d + e) == 4)
                              --t201;
                         } 
                 }
                 break;
              
               case 5:   /* 300 */            
                 --t210;
                 break;
               }
               }
             }    /* ******  move to next node3 ******** */
        }
        else 
          t012 = t012 + (nwp->nnodes - 2);  

        t003 = -(t300+t210+t120C+t120U+t120D+t201+t030C+t030T);
        t003 = t003-(t111U+t111D+t021C+t021U+t021D+t102+t012);
	b = t003+t012+t021U+t021D+t102+t030T+t120U+t120D+t300;
	*(mtp->dstats) += edgeflag ? -(double)b : (double)b;

      if (i+1 < ntoggles)
	  ToggleEdge(heads[i], tails[i], nwp);  /* Toggle this edge if more to come */ 
    }
    }else{
//  undirected
    for (i=0; i<ntoggles; i++) 
     {      
      edgeflag = (EdgetreeSearch(h=heads[i], t=tails[i], nwp->outedges) != 0);
      t300 = 0; t201 = 0; t102 = 0; t012 = 0;

      if ((EdgetreeMinimum(nwp->outedges, t) != 0) || 
          (EdgetreeMinimum(nwp->inedges, t) != 0) || 
          (EdgetreeMinimum(nwp->outedges, h) != 0) ||
          (EdgetreeMinimum(nwp->inedges, h) != 0)) {      

          /* ****** loop through node3 ****** */
          for (node3=1; node3 <= nwp->nnodes; node3++)
             { 
             if (node3 != h && node3 != t)
               {   
               a = (EdgetreeSearch(MIN(node3,t), MAX(node3,t), nwp->outedges) != 0);
               b = (EdgetreeSearch(MIN(node3,h), MAX(node3,h), nwp->outedges) != 0);
               edgecount = (a + b);

               switch(edgecount)
               {  
               case 0:   /* 012 */
		{
                 ++t102;
                 --t012;
		}
                break;

               case 1:   /* 021C, 021U, 021D, 102 */
		{
                 ++t201;
                 --t102;
		}
                break;
          
               case 2:   /* 030C, 030T, 111U, 111D */
		{
                 ++t300;
                 --t201;
		}
                break;
            
               }
	       }

             }    /* ******  move to next node3 ******** */
        }
        else 
          t102 = t102 + (nwp->nnodes - 2);  

        t003 = (t102+t201+t300);
	b = -t300; 
	*(mtp->dstats) += edgeflag ? -(double)b : (double)b;
  
     if (i+1 < ntoggles)
	  ToggleEdge(heads[i], tails[i], nwp);  /* Toggle this edge if more to come */ 
     } // i loop
    }
    
  i--; 
  while (--i>=0)  /*  Undo all previous toggles. */
    ToggleEdge(heads[i], tails[i], nwp); 
}
