/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "WilsHomogenizedThermalConductivity.h"
//#include "SymmElasticityTensor.h"
//#include <iostream.h>
//#include <fstream.h>
#include "SubProblem.h"

template<>
InputParameters validParams<WilsHomogenizedThermalConductivity>()
{
  InputParameters params = validParams<ElementAverageValue>();
  params.addRequiredCoupledVar("temp_x", "solution in x");
  params.addCoupledVar("temp_y", "solution in y");
  params.addCoupledVar("temp_z", "solution in z");
  params.addRequiredParam<unsigned int>("component", "An integer corresponding to the direction this pp acts in (0 for x, 1 for y, 2 for z)");
  params.addParam<Real>("scale_factor", 1, "Scale factor");
  params.addParam<MaterialPropertyName>("diffusion_coefficient_name", "thermal_conductivity", "Property name of the diffusivity (Default: thermal_conductivity)");
  return params;
}

WilsHomogenizedThermalConductivity::WilsHomogenizedThermalConductivity(const InputParameters & parameters)
  :ElementAverageValue(parameters),
   _grad_temp_x(coupledGradient("temp_x")),
   _grad_temp_y(_subproblem.mesh().dimension() > 1 ? coupledGradient("temp_y") : _grad_zero),
   _grad_temp_z(_subproblem.mesh().dimension() == 3 ? coupledGradient("temp_z") : _grad_zero),
   _component(getParam<unsigned int>("component")),
   _diffusion_coefficient(getMaterialProperty<Real>("diffusion_coefficient_name")),
   _volume(0),
   _integral_value(0),
   _scale(getParam<Real>("scale_factor"))
{
  if (_component > 2)
  {
    mooseError("Component must be 0, 1, or 2 in WilsHeatCondHomogenizationKernel");
  }
}

void
WilsHomogenizedThermalConductivity::initialize()
{
  _integral_value = 0;
  _volume = 0;
}

void
WilsHomogenizedThermalConductivity::execute()
{
  _integral_value += computeIntegral();
  _volume += _current_elem_volume;
}

Real
WilsHomogenizedThermalConductivity::getValue()
{

  gatherSum(_integral_value);
  gatherSum(_volume);

  Real WilsOutputValue = (_integral_value/_volume);

  FILE *fp;
  fp = fopen("./data.txt", "a");
  fprintf(fp, "%f\n", WilsOutputValue);
  fclose(fp);

  return WilsOutputValue;
}

void
WilsHomogenizedThermalConductivity::threadJoin(const UserObject & y)
{
  const WilsHomogenizedThermalConductivity & pps = dynamic_cast<const WilsHomogenizedThermalConductivity &>(y);

  _integral_value += pps._integral_value;
  _volume += pps._volume;
}

Real
WilsHomogenizedThermalConductivity::computeQpIntegral()
{
  Real value(1);
  if (_component == 0)
  {
    value += _grad_temp_x[_qp](0);
  }
  else if (_component == 1)
  {
    value += _grad_temp_y[_qp](1);
  }
  else
  {
    value += _grad_temp_z[_qp](2);
  }

  Real WilsValue;

  WilsValue = _scale * _diffusion_coefficient[_qp] * value;

  return WilsValue;
}
