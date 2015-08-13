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

#include "HeatCondHomogenizationKernel.h"

template<>
InputParameters validParams<HeatCondHomogenizationKernel>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<unsigned int>("component", "component");
  return params;
}

HeatCondHomogenizationKernel::HeatCondHomogenizationKernel(const InputParameters & parameters)
  :Kernel(parameters),
  _conductivity(getMaterialProperty<Real>("conductivity")),
  _component(getParam<unsigned int>("component"))
{
}

Real
HeatCondHomogenizationKernel::computeQpResidual()
{
  return _conductivity[_qp] * _grad_test[_i][_qp](_component);
}

Real
HeatCondHomogenizationKernel::computeQpJacobian()
{
  return 0.0;
}
