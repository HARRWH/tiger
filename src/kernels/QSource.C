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

#include "QSource.h"

template<>
InputParameters validParams<QSource>()
{
  InputParameters params = validParams<Kernel>();
  return params;
}

QSource::QSource(const InputParameters & parameters)
  :Kernel(parameters),
  _q_generated(getMaterialProperty<Real>("q_generated"))
{
}

Real
QSource::computeQpResidual()
{
  return -1.0*_test[_i][_qp]*_q_generated[_qp];
}

Real
QSource::computeQpJacobian()
{
  return 0;
}
