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

#ifndef HEATCONDTIMEDERIVATIVE_H
#define HEATCONDTIMEDERIVATIVE_H

#include "TimeDerivative.h"

class HeatCondTimeDerivative;

template<>
InputParameters validParams<HeatCondTimeDerivative>();

class HeatCondTimeDerivative : public TimeDerivative
{
public:
  HeatCondTimeDerivative(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

//private:
  const MaterialProperty<Real> & _density;
  const MaterialProperty<Real> & _specific_heat;
};

#endif // HEATCONDTIMEDERIVATIVE_H
