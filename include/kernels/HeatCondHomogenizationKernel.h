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

#ifndef HEATCONDHOMOGENIZATIONKERNEL_H
#define HEATCONDHOMOGENIZATIONKERNEL_H

#include "Kernel.h"
#include "Material.h"

class HeatCondHomogenizationKernel;

template<>
InputParameters validParams<HeatCondHomogenizationKernel>();

class HeatCondHomogenizationKernel : public Kernel
{
public:
  HeatCondHomogenizationKernel(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  const MaterialProperty<Real> & _conductivity;
  const unsigned int _component;

};

#endif // HEATCONDHOMOGENIZATIONKERNEL_H
