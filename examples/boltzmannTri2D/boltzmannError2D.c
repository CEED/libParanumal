#include "boltzmann2D.h"

// currently maximum
void boltzmannError2D(mesh2D *mesh, dfloat time){


  #if 1
  // Coutte Flow exact solution for U velocity

 dfloat maxerr = 0;
 dfloat maxQ1 = 0, minQ1 = 1e9;
 iint fid = 1; //U velocity

dfloat nu = mesh->sqrtRT*mesh->sqrtRT/mesh->tauInv;
 
  for(iint e=0;e<mesh->Nelements;++e){
    for(iint n=0;n<mesh->Np;++n){
      dfloat q1=0;
      iint id = n+e*mesh->Np;
      dfloat x = mesh->x[id];
      dfloat y = mesh->y[id];
      // U = sqrt(RT)*Q2/Q1; 
      dfloat u   = mesh->sqrtRT*mesh->q[id*mesh->Nfields + 1]/mesh->q[id*mesh->Nfields];

      
      dfloat uex = 2. * y ; 
      maxerr = mymax(maxerr, fabs(u-uex));

      maxQ1 = mymax(maxQ1, fabs(mesh->q[id*mesh->Nfields]));
      minQ1 = mymin(minQ1, fabs(mesh->q[id*mesh->Nfields]));
      
    }
  }

  // compute maximum over all processes
  dfloat globalMaxQ1, globalMinQ1, globalMaxErr;
  MPI_Allreduce(&maxQ1, &globalMaxQ1, 1,
     MPI_DFLOAT, MPI_MAX, MPI_COMM_WORLD);
  MPI_Allreduce(&minQ1, &globalMinQ1, 1,
    MPI_DFLOAT, MPI_MIN, MPI_COMM_WORLD);
  MPI_Allreduce(&maxerr, &globalMaxErr, 1,
     MPI_DFLOAT, MPI_MAX, MPI_COMM_WORLD);



  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if(rank==0){
    printf("%g %g %g %g (time,min(density),max(density),max(error)\n",
     time, globalMinQ1, globalMaxQ1, globalMaxErr);
    mesh->maxErrorBoltzmann = globalMaxErr; 
  }


  if(isnan(globalMaxErr))
    exit(EXIT_FAILURE);

#else




  dfloat maxQ1 = 0, minQ1 = 1e9;
  for(iint e=0;e<mesh->Nelements;++e){
    for(int n=0;n<mesh->Np;++n){
      dfloat q1=0;
      iint id = n+e*mesh->Np;
      dfloat x = mesh->x[id];
      dfloat y = mesh->y[id];

      maxQ1 = mymax(maxQ1, fabs(mesh->q[id*mesh->Nfields]));
      minQ1 = mymin(minQ1, fabs(mesh->q[id*mesh->Nfields]));
    }
  }
  
 
  // compute maximum over all processes
  dfloat globalMaxQ1, globalMinQ1;
  MPI_Allreduce(&maxQ1, &globalMaxQ1, 1,
		 MPI_DFLOAT, MPI_MAX, MPI_COMM_WORLD);
  MPI_Allreduce(&minQ1, &globalMinQ1, 1,
		MPI_DFLOAT, MPI_MIN, MPI_COMM_WORLD);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if(rank==0)
    printf("%g %g %g (time,min(density),max(density)\n",
	   time, globalMinQ1, globalMaxQ1);

  if(isnan(globalMinQ1) || isnan(globalMaxQ1))
    exit(EXIT_FAILURE);

#endif

  
}
