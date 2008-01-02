#ifndef MHproposals_formdiss_IHS_H
#define MHproposals_formdiss_IHS_H

#include "edgeTree.h"
#include "changestats.h"
#include "model.h"
#include "MCMC.h"
#include "MHproposals.h"

void MH_Formation(MHproposal *MHp, DegreeBound *bd, Network *nwp);
void MH_FormationTNT(MHproposal *MHp, DegreeBound *bd, Network *nwp);
/*void MH_DissolutionTNT(MHproposal *MHp, DegreeBound *bd, Network *nwp); */
void MH_Dissolution(MHproposal *MHp, DegreeBound *bd, Network *nwp);

void MH_BipartiteFormation (MHproposal *MHp,  DegreeBound *bd, Network *nwp);
void MH_BipartiteFormationTNT (MHproposal *MHp,  DegreeBound *bd, Network *nwp);
void MH_BipartiteDissolution (MHproposal *MHp,  DegreeBound *bd, Network *nwp);

#endif 
