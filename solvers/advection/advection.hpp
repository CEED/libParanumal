/*

The MIT License (MIT)

Copyright (c) 2017 Tim Warburton, Noel Chalmers, Jesse Chan, Ali Karakus

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef ADVECTION_HPP
#define ADVECTION_HPP 1

#include "core.hpp"
#include "platform.hpp"
#include "mesh.hpp"
#include "solver.hpp"
#include "timeStepper.hpp"
#include "linAlg.hpp"

#define DADVECTION LIBP_DIR"/solvers/advection/"

class advectionSettings_t: public settings_t {
public:
  advectionSettings_t(MPI_Comm& _comm);
  void report();
  void parseFromFile(platformSettings_t& platformSettings,
                     meshSettings_t& meshSettings,
                     const string filename);
};

class advection_t: public solver_t {
public:
  mesh_t &mesh;
  TimeStepper::timeStepper_t* timeStepper;

  halo_t* traceHalo;

  dfloat *q;
  occa::memory o_q;

  occa::memory o_Mq;

  occa::kernel volumeKernel;
  occa::kernel surfaceKernel;

  occa::kernel initialConditionKernel;
  occa::kernel maxWaveSpeedKernel;

  advection_t() = delete;
  advection_t(platform_t &_platform, mesh_t &_mesh,
              advectionSettings_t& _settings):
    solver_t(_platform, _settings), mesh(_mesh) {}

  ~advection_t();

  //setup
  static advection_t& Setup(platform_t& platform, mesh_t& mesh,
                            advectionSettings_t& settings);

  void Run();

  void Report(dfloat time, int tstep);

  void PlotFields(dfloat* Q, char *fileName);

  void rhsf(occa::memory& o_q, occa::memory& o_rhs, const dfloat time);

  dfloat MaxWaveSpeed(occa::memory& o_Q, const dfloat T);
};

#endif
