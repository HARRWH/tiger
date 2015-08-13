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

#ifndef COEFCONDUCTION_H
#define COEFCONDUCTION_H

#include "Kernel.h"
#include "Material.h"

class CoefConduction;

template<>
InputParameters validParams<CoefConduction>();

class CoefConduction : public Kernel
{
public:
  CoefConduction(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  const MaterialProperty<Real> & _conductivity;
  //const MaterialProperty<Real> * const _conductivity_dT;

};

#endif // COEFCONDUCTION_H
