// Initial conditions : f and g are forcing for exact solution 
// messy manufactured solution
#define mppfFlowField2D(t,x,y,u,v,p) \
  {                         \
    *(u)    =  cos(M_PI*y)*sin(M_PI*x)*sin(t);\
    *(v)    = -sin(M_PI*y)*cos(M_PI*x)*sin(t);\
    *(p)    =  sin(M_PI*y)*sin(M_PI*x)*cos(t);\
  }


#define mppfPhaseField2D(t,h,x,y,phi) \
  {                         \
    *(phi)  =  cos(M_PI*x)*cos(M_PI*y)*sin(t);\
  }


  #define mppfPhaseFieldSource2D(t,x,y,g)\
  {                                    \
    dfloat eta     = 0.1; \
    dfloat lambda  = 0.001; \
    dfloat M       = 0.001; \
    dfloat eta2    = eta*eta;\
    dfloat u = cos(M_PI*y)*sin(M_PI*x)*sin(t);\
    dfloat v = -cos(M_PI*x)*sin(M_PI*y)*sin(t);\
    dfloat phit= cos(M_PI*x)*cos(M_PI*y)*cos(t);\
    dfloat phi = cos(M_PI*x)*cos(M_PI*y)*sin(t);\
    dfloat phix= -M_PI*cos(M_PI*y)*sin(M_PI*x)*sin(t);\
    dfloat phiy= -M_PI*cos(M_PI*x)*sin(M_PI*y)*sin(t);\
    dfloat lapfunc= (2.f*M_PI*M_PI*cos(M_PI*x)*cos(M_PI*y)*sin(t)*(3.f*sin(t)*sin(t) - 6.f*sin(M_PI*x)*sin(M_PI*x)*sin(t)*sin(t) - 6.f*sin(M_PI*y)*sin(M_PI*y)*sin(t)*sin(t) + 2.f*M_PI*M_PI*eta2 + 9.f*sin(M_PI*x)*sin(M_PI*x)*sin(M_PI*y)*sin(M_PI*y)*sin(t)*sin(t) - 1.f))/eta2;\
    *(g)           = phit + u*phix + v*phiy  + lambda*M*lapfunc;\
  } 

  // mu1 = 0.01 // mu2 = 0.02 rho1 = 1 rho2 = 3 are hard coded
  #define mppfVelocitySource2D(t,x,y,fx, fy)\
  {                                    \
    dfloat eta     = 0.1; \
    dfloat lambda  = 0.001; \
    dfloat M       = 0.001; \
    dfloat u = cos(M_PI*y)*sin(M_PI*x)*sin(t);\
    dfloat v = -cos(M_PI*x)*sin(M_PI*y)*sin(t);\
    dfloat ut = cos(M_PI*y)*sin(M_PI*x)*cos(t);\
    dfloat vt = -cos(M_PI*x)*sin(M_PI*y)*cos(t);\
    dfloat ux = M_PI*cos(M_PI*x)*cos(M_PI*y)*sin(t);\
    dfloat uy = -M_PI*sin(M_PI*x)*sin(M_PI*y)*sin(t);\
    dfloat vx = M_PI*sin(M_PI*x)*sin(M_PI*y)*sin(t);\
    dfloat vy = -M_PI*cos(M_PI*x)*cos(M_PI*y)*sin(t);\
    dfloat px = M_PI*cos(M_PI*x)*sin(M_PI*y)*cos(t);\
    dfloat py = M_PI*cos(M_PI*y)*sin(M_PI*x)*cos(t);\
    dfloat rho= 2.f - cos(M_PI*x)*cos(M_PI*y)*sin(t);\
    dfloat mu = 3.f/200.f - (cos(M_PI*x)*cos(M_PI*y)*sin(t))/200.f;\
    dfloat mux= (M_PI*cos(M_PI*y)*sin(M_PI*x)*sin(t))/200.f;\
    dfloat muy= (M_PI*cos(M_PI*x)*sin(M_PI*y)*sin(t))/200.f;\
    dfloat phix= -M_PI*cos(M_PI*y)*sin(M_PI*x)*sin(t);\
    dfloat phiy= -M_PI*cos(M_PI*x)*sin(M_PI*y)*sin(t);\
    dfloat lapphi= -2.f*M_PI*M_PI*cos(M_PI*x)*cos(M_PI*y)*sin(t);\
    dfloat lapu= -2.f*M_PI*M_PI*cos(M_PI*y)*sin(M_PI*x)*sin(t);\
    dfloat lapv= 2*M_PI*M_PI*cos(M_PI*x)*sin(M_PI*y)*sin(t);\
    dfloat gx = rho*(ut + u*ux+ v*uy) + px - mu*lapu - (mux*2.f*ux + muy*(uy + vx)) + lambda*lapphi*phix;\
    dfloat gy = rho*(vt + u*vx+ v*vy) + py - mu*lapv - (muy*2.f*vy + mux*(uy + vx)) + lambda*lapphi*phiy;\
    *(fx)          = gx/rho;\
    *(fy)          = gy/rho;\
  } 

  // dfloat lambda  = 0.001; \
  //   dfloat u       = cos(M_PI*y)*sin(M_PI*x)*sin(t);\
  //   dfloat v       = -cos(M_PI*x)*sin(M_PI*y)*sin(t);\
  //   dfloat ut      = cos(M_PI*y)*sin(M_PI*x)*cos(t);\
  //   dfloat vt      = -cos(M_PI*x)*sin(M_PI*y)*cos(t);\
  //   dfloat ux      = M_PI*cos(M_PI*x)*cos(M_PI*y)*sin(t);\
  //   dfloat uy      = -M_PI*sin(M_PI*x)*sin(M_PI*y)*sin(t);\
  //   dfloat vx      = M_PI*sin(M_PI*x)*sin(M_PI*y)*sin(t);\
  //   dfloat vy      = -M_PI*cos(M_PI*x)*cos(M_PI*y)*sin(t);\
  //   dfloat px      = M_PI*cos(M_PI*x)*sin(M_PI*y)*cos(t);\
  //   dfloat py      = M_PI*cos(M_PI*y)*sin(M_PI*x)*cos(t);\
  //   dfloat DU      =  (M_PI*M_PI*cos(M_PI*y)*sin(M_PI*x)*sin(t)*(2.f*cos(M_PI*x)*cos(M_PI*y)*sin(t) - 3.f))/100.f;\
  //   dfloat DV      = -(M_PI*M_PI*cos(M_PI*x)*sin(M_PI*y)*sin(t)*(2.f*cos(M_PI*x)*cos(M_PI*y)*sin(t) - 3.f))/100.f;\
  //   dfloat Sx      = 2.f*M_PI*M_PI*M_PI*lambda*cos(M_PI*x)*cos(M_PI*y)*cos(M_PI*y)*sin(M_PI*x)*sin(t)*sin(t);\
  //   dfloat Sy      = 2.f*M_PI*M_PI*M_PI*lambda*cos(M_PI*x)*cos(M_PI*x)*cos(M_PI*y)*sin(M_PI*y)*sin(t)*sin(t);\
  //   dfloat rho     = 2.f - cos(M_PI*x)*cos(M_PI*y)*sin(t);\
  //   *(fx)          = rho*(ut + u*ux + v*uy) + px -DU + Sx;\
  //   *(fy)          = rho*(vt + u*vx + v*vy) + py -DV + Sy;\
  
// -2*M_PI*M_PI*cos(M_PI*y)*sin(M_PI*x)*sin(t);\
    // dfloat p_c     = (M_PI*M_PI*lambda*sin(t)*sin(t)*(sin(M_PI*x)*sin(M_PI*x) - 2.f*sin(M_PI*x)*sin(M_PI*x)*sin(M_PI*y)*sin(M_PI*y) + sin(M_PI*y)*sin(M_PI*y)))/2.f;\

// #define mppfPhaseFieldDirichletConditions2D(bc, t, x, y, nx, ny, phiM, phiB) \
// {                                   \
//   if(bc==1){                        \
//     *(phiB) = cos(M_PI*x)*cos(M_PI*y)*sin(t);\
//   } else if(bc==2){                 \
//     *(phiB) = cos(M_PI*x)*cos(M_PI*y)*sin(t);\
//   } else if(bc==3){                 \
//     *(phiB) = cos(M_PI*x)*cos(M_PI*y)*sin(t);\
//   } else if(bc==4){                 \
//     *(phiB) = cos(M_PI*x)*cos(M_PI*y)*sin(t);\
//   } else if(bc==5){                 \
//     *(phiB) = cos(M_PI*x)*cos(M_PI*y)*sin(t);\
//   }                                 \
// }



// #define mppfPhaseFieldNeumannConditions2D(bc, t, x, y, nx, ny, phixM, phiyM, phixB, phiyB) \
// {                                          \
//   if(bc==1 || bc==2){                      \
//     *(phixB) =-M_PI*cos(M_PI*y)*sin(M_PI*x)*sin(t);\
//     *(phiyB) =-M_PI*cos(M_PI*x)*sin(M_PI*y)*sin(t);\
//   } else if(bc==3){                        \
//     *(phixB) = -M_PI*cos(M_PI*y)*sin(M_PI*x)*sin(t);\
//     *(phiyB) = -M_PI*cos(M_PI*x)*sin(M_PI*y)*sin(t);\
//   } else if(bc==4){                        \
//     *(phixB) = -M_PI*cos(M_PI*y)*sin(M_PI*x)*sin(t);\
//     *(phiyB) = -M_PI*cos(M_PI*x)*sin(M_PI*y)*sin(t);\
//   } else if(bc==5){                        \
//     *(phixB) = -M_PI*cos(M_PI*y)*sin(M_PI*x)*sin(t);\
//     *(phiyB) = -M_PI*cos(M_PI*x)*sin(M_PI*y)*sin(t);\
//   }                                        \
// }





#define mppfPhaseFieldDirichletConditions2D(bc, t, x, y, nx, ny, phiM, phiB) \
{                                   \
  if(bc==1){                        \
    *(phiB) = phiM;                 \
  } else if(bc==2){                 \
    *(phiB) = phiM;                 \
  } else if(bc==3){                 \
    *(phiB) = phiM;                 \
  } else if(bc==4){                 \
    *(phiB) = phiM;                 \
  } else if(bc==5){                 \
    *(phiB) = phiM;                 \
  }                                 \
}



#define mppfPhaseFieldNeumannConditions2D(bc, t, x, y, nx, ny, phixM, phiyM, phixB, phiyB) \
{                                          \
  if(bc==1 || bc==2){                      \
    *(phixB) = 0.f;                        \
    *(phiyB) = 0.f;                        \
  } else if(bc==3){                        \
    *(phixB) = 0.f;                        \
    *(phiyB) = 0.f;                        \
  } else if(bc==4){                        \
    *(phixB) = 0.f;                        \
    *(phiyB) = 0.f;                        \
  } else if(bc==5){                        \
    *(phixB) = 0.f;                        \
    *(phiyB) = 0.f;                        \
  }                                        \
}



// Boundary conditions
/* wall 1, inflow 2, outflow 3, x-slip 4, y-slip 5 */
#define mppfVelocityDirichletConditions2D(bc, t, x, y, nx, ny, uM, vM, uB, vB) \
{                                   \
  if(bc==1){                        \
    *(uB) = 0.f;                    \
    *(vB) = 0.f;                    \
  } else if(bc==2){                 \
    *(uB)    =  cos(M_PI*y)*sin(M_PI*x)*sin(t);\
    *(vB)    = -sin(M_PI*y)*cos(M_PI*x)*sin(t);\
  } else if(bc==3){                 \
    *(uB) = uM;                     \
    *(vB) = vM;                     \
  } else if(bc==4){                 \
    *(uB) = 0.f;                    \
    *(vB) = vM;                     \
  } else if(bc==5){                 \
    *(uB) = uM;                     \
    *(vB) = 0.f;                    \
  }                                 \
}

#define mppfVelocityNeumannConditions2D(bc, t, x, y, nx, ny, uxM, uyM, vxM, vyM, uxB, uyB, vxB, vyB) \
{                                          \
  if(bc==1 || bc==2){                      \
    *(uxB) = uxM;                          \
    *(uyB) = uyM;                          \
    *(vxB) = vxM;                          \
    *(vyB) = vyM;                          \
  } else if(bc==3){                        \
    *(uxB) = M_PI*cos(M_PI*x)*cos(M_PI*y)*sin(t);\
    *(uyB) =-M_PI*sin(M_PI*x)*sin(M_PI*y)*sin(t);\
    *(vxB) = M_PI*sin(M_PI*x)*sin(M_PI*y)*sin(t);\
    *(vyB) =-M_PI*cos(M_PI*x)*cos(M_PI*y)*sin(t);\
  } else if(bc==4||bc==5){                  \
    *(uxB) = nx*nx*uxM;                     \
    *(uyB) = nx*nx*uyM;                    \
    *(vxB) = ny*ny*vxM;                    \
    *(vyB) = ny*ny*vyM;                    \
  }                                        \
}


#define mppfPressureDirichletConditions2D(bc, t, x, y, nx, ny, pM, pB) \
{                                   \
  if(bc==1 || bc==2){               \
    *(pB) = pM;                     \
  } else if(bc==3){                 \
    *(pB) = sin(M_PI*y)*sin(M_PI*x)*cos(t);\
  } else if(bc==4|| bc==5){         \
    *(pB) = pM;                     \
  }                                 \
}
// 

#define mppfPressureNeumannConditions2D(bc, t, x, y, nx, ny, pxM, pyM, pxB, pyB) \
{                                          \
  if(bc==1 || bc==2){                      \
    *(pxB) = 0.f;                          \
    *(pyB) = 0.f;                          \
  } else if(bc==3){                             \
    *(pxB) =M_PI*cos(M_PI*x)*sin(M_PI*y)*cos(t);\
    *(pyB) =M_PI*cos(M_PI*y)*sin(M_PI*x)*cos(t);\
  } else if(bc==4|| bc==5){                \
    *(pxB) = 0.f;                          \
    *(pyB) = 0.f;                          \
  }                                        \
}
