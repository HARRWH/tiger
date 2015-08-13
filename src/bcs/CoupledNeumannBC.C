/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "CoupledNeumannBC.h"

template<>
InputParameters validParams<CoupledNeumannBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  return params;
}

CoupledNeumannBC::CoupledNeumannBC(const InputParameters & parameters) :
    IntegratedBC(parameters)
{
}

Real
CoupledNeumannBC::computeQpResidual()
{
  _temp_H2O = 355.35;             //K
  _convection_coeff = 0.062452;   //pJ/um^2*K*us
  return -1.0*_test[_i][_qp]*_convection_coeff*(_temp_H2O - _u[_qp]);
}

Real
CoupledNeumannBC::computeQpJacobian()
{
  _temp_H2O = 355.35;             //K
  _convection_coeff = 0.062452;   //pJ/um^2*K*us
  return _test[_i][_qp]*_convection_coeff*_phi[_j][_qp];
}
