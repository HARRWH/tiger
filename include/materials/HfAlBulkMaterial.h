/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef HFALBULKMATERIAL_H
#define HFALBULKMATERIAL_H

#include "Material.h"

class HfAlBulkMaterial;
class Function;

template<>
InputParameters validParams<HfAlBulkMaterial>();

class HfAlBulkMaterial : public Material
{
public:
  HfAlBulkMaterial(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

private:
  VariableValue & _temperature;
  MaterialProperty<Real> & _q_generated;
  MaterialProperty<Real> & _density;
  MaterialProperty<Real> & _conductivity;
  MaterialProperty<Real> & _specific_heat;

};

#endif //HFALBULKMATERIAL_H
