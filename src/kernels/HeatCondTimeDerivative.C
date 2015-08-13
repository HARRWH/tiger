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

#include "HeatCondTimeDerivative.h"

template<>
InputParameters validParams<HeatCondTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  return params;
}

HeatCondTimeDerivative::HeatCondTimeDerivative(const InputParameters & parameters) :
    TimeDerivative(parameters),
    _density(getMaterialProperty<Real>("density")),
    _specific_heat(getMaterialProperty<Real>("specific_heat"))
{
}

Real
HeatCondTimeDerivative::computeQpResidual()
{
  return _density[_qp] * _specific_heat[_qp] * TimeDerivative::computeQpResidual();
}

Real
HeatCondTimeDerivative::computeQpJacobian()
{
  return _density[_qp] * _specific_heat[_qp] * TimeDerivative::computeQpJacobian();
}
