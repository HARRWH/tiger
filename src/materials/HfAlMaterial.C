/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "HfAlMaterial.h"

template<>
InputParameters validParams<HfAlMaterial>()
{
  InputParameters params = validParams<Material>();
  params.addCoupledVar("temperature", "temperature");
  params.addCoupledVar("RGB_aux_variable", "RGB_aux_variable");
  return params;
}

HfAlMaterial::HfAlMaterial(const InputParameters & parameters) :
  Material(parameters),
  _temperature(coupledValue("temperature")),
  _RGB_aux_variable(coupledValue("RGB_aux_variable")),
  _RGB(declareProperty<Real>("RGB")),
  _q_generated(declareProperty<Real>("q_generated")),
  _density(declareProperty<Real>("density")),
  _conductivity(declareProperty<Real>("conductivity")),
  _specific_heat(declareProperty<Real>("specific_heat"))
{
}

void
HfAlMaterial::computeQpProperties()
{
  Real qp_temperature = _temperature[_qp];

  _RGB[_qp] = _RGB_aux_variable[_qp];

  if (_RGB[_qp] > 6.0 && _RGB[_qp] < 8.0)
  {
    //Al3HF INTERMETALLIC PARTICLE
    _q_generated[_qp] = 0.000052;        // pJ/um^3-us
    _conductivity[_qp] = 35.8;           // pJ/um-K-us
    _specific_heat[_qp] = 0.38;          // pJ/pg-K
    _density[_qp] = 6.03;                // pg/um^3
  }
  else if (_RGB[_qp] > 99.0 && _RGB[_qp] < 101.0)
  {
    //VOID
    _q_generated[_qp] = 0.0;             // pJ/um^3-us
    _conductivity[_qp] = 0.0515;         // pJ/um-K-us
    _specific_heat[_qp] = 1.068;         // pJ/pg-K
    _density[_qp] = 0.000524;            // pg/um^3
  }
  else
  {
    //ALUMINUM MATRIX

    _q_generated[_qp] = 0.0;

    double A1 = 165.84;
    double B1 = 0.49305;
    double C1 = -0.0011114;
    double D1 = 0.00000098024;
    double E1 = -0.00000000032368;
    _conductivity[_qp] = A1 + B1*qp_temperature + C1*pow(qp_temperature,2) + D1*pow(qp_temperature,3) + E1*pow(qp_temperature,4);
    // pJ/um-K-us

    double A2 = -0.16344013600464341;
    double B2 = 0.00911622249501409;
    double C2 = -0.00003229894514634;
    double D2 = 0.00000006292936835;
    double E2 = -0.00000000006845269;
    double F2 = 0.00000000000003952;
    double G2 = -0.00000000000000001;
    _specific_heat[_qp] = A2 + B2*qp_temperature + C2*pow(qp_temperature,2) + D2*pow(qp_temperature,3) + E2*pow(qp_temperature,4) + F2*pow(qp_temperature,5) + G2*pow(qp_temperature,6);
    // pJ/pg-K

    double A3 = 2.74861945326103;
    double B3 = -0.000117931002997983;
    double C3 = -1.03677250057976E-07;
    double D3 = 1.19297576142395E-11;
    _density[_qp] = A3 + B3*qp_temperature + C3*pow(qp_temperature,2) + D3*pow(qp_temperature,3);
    // pg/um^3
  }
}
