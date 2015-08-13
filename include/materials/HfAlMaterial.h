/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef HFALMATERIAL_H
#define HFALMATERIAL_H

#include "Material.h"

class HfAlMaterial;
class Function;

template<>
InputParameters validParams<HfAlMaterial>();

class HfAlMaterial : public Material
{
public:
  HfAlMaterial(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

private:
  VariableValue & _temperature;
  VariableValue & _RGB_aux_variable;
  MaterialProperty<Real> & _RGB;
  MaterialProperty<Real> & _q_generated;
  MaterialProperty<Real> & _density;
  MaterialProperty<Real> & _conductivity;
  MaterialProperty<Real> & _specific_heat;

};

#endif //HFALMATERIAL_H
