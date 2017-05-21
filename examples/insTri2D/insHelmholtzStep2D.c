#include "ins2D.h"

// complete a time step using LSERK4
void insHelmholtzStep2D(solver_t *ins, iint tstep,  iint haloBytes,
				               dfloat * sendBuffer, dfloat * recvBuffer,  char   * options){

	mesh2D *mesh = ins->mesh; 

	dfloat t = tstep*ins->dt;


   //Exctract Halo On Device

	// if(mesh->totalHaloPairs>0){
	 
 //    ins->haloExtractKernel(mesh->Nelements,
 //                           mesh->totalHaloPairs,
 //                           mesh->o_haloElementList,
 //                           ins->o_U,
 //                           ins->o_Pr,
 //                           mesh->o_haloBuffer);

 //    // copy extracted halo to HOST 
 //    mesh->o_haloBuffer.copyTo(sendBuffer);            
 //    // start halo exchange
 //    meshHaloExchangeStart(mesh,
 //                          mesh->Np*ins->Nfields*sizeof(dfloat), 
 //                          sendBuffer,
 //                          recvBuffer);
 //  	}

  	// Compute Volume Contribution

   ins->helmholtzRhsVolumeKernel(mesh->Nelements,
                                 mesh->o_vgeo,
                                 mesh->o_DrT,
                                 mesh->o_DsT,
                                 ins->o_U,
                                 ins->o_Pr,
                                 ins->o_NU,   
                                 ins->o_rhsU);


  //   // COMPLETE HALO EXCHANGE
  // if(mesh->totalHaloPairs>0){
  // // wait for halo data to arrive
  //   meshHaloExchangeFinish(mesh);

  //   mesh->o_haloBuffer.copyFrom(recvBuffer); 

  //   ins->haloScatterKernel(mesh->Nelements,
  //                         mesh->totalHaloPairs,
  //                         mesh->o_haloElementList,
  //                         ins->o_U,
  //                         ins->o_Pr,
  //                         mesh->o_haloBuffer);
  // }

 // Compute Surface Conribution
  ins->helmholtzRhsSurfaceKernel(mesh->Nelements,
                              mesh->o_sgeo,
                              mesh->o_LIFTT,
                              mesh->o_vmapM,
                              mesh->o_vmapP,
                              mesh->o_EToB,
                              t,
                              mesh->o_x,
                              mesh->o_y,
                              ins->o_U,
                              ins->o_Pr,
                              ins->o_NU,
                              ins->o_rhsU);
 // Update fields
  ins->helmholtzRhsUpdateKernel(mesh->Nelements,
                              mesh->o_vgeo,
                              mesh->o_MM,
                              ins->dt,	
                              ins->a0,
                              ins->a1,
                              ins->a2,
                              ins->b0,
                              ins->b1,
                              ins->b2,
                              ins->o_U,
                              ins->o_UO,
                              ins->o_UOO,
                              ins->o_NU,
                              ins->o_NUO,
                              ins->o_NUOO,
                              ins->o_rhsU
                              );


  ins->helmholtzRhsIpdgBCKernel(mesh->Nelements,
                                mesh->o_sgeo,
                                mesh->o_vgeo,
                                mesh->o_DrT,
                                mesh->o_DsT,
                                mesh->o_FMMT,
                                mesh->o_vmapM,
                                mesh->o_vmapP,
                                mesh->o_EToB,
                                t,
                                ins->tau,
                                mesh->o_x,
                                mesh->o_y,
                                ins->o_U,
                                ins->o_rhsU
                                );




   
}
