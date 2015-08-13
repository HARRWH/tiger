/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "HfAlBulkMaterial.h"

template<>
InputParameters validParams<HfAlBulkMaterial>()
{
  InputParameters params = validParams<Material>();
  params.addCoupledVar("temperature", "temperature");
  return params;
}

HfAlBulkMaterial::HfAlBulkMaterial(const InputParameters & parameters) :
  Material(parameters),
  _temperature(coupledValue("temperature")),
  _q_generated(declareProperty<Real>("q_generated")),
  _density(declareProperty<Real>("density")),
  _conductivity(declareProperty<Real>("conductivity")),
  _specific_heat(declareProperty<Real>("specific_heat"))
{
}

void
HfAlBulkMaterial::computeQpProperties()
{
  Real qp_temperature = _temperature[_qp];

  //Currently just inputting 28.4 vol% Al3Hf data

  _q_generated[_qp] = 0.000014768;                        // pJ/um^3-us
  _conductivity[_qp] = 147.0;                             // pJ/um-K-us
  _specific_heat[_qp] = 0.7;                              // pJ/pg-K             (although not needed for steady state simulation, as actual Cp value is T-dependent - 0.7 is an average)
  _density[_qp] = 3.68;                                   // pg/um^3             (although not needed for steady state simulation)
}
