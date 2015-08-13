#include "TigerApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "PhaseFieldApp.h"
#include "HeatCondTimeDerivative.h"
#include "CoefConduction.h"
#include "QSource.h"
#include "HeatCondHomogenizationKernel.h"
#include "HfAlMaterial.h"
#include "HfAlBulkMaterial.h"
#include "WilsHomogenizedThermalConductivity.h"
#include "CoupledNeumannBC.h"

template<>
InputParameters validParams<TigerApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  return params;
}

TigerApp::TigerApp(const InputParameters & parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  TigerApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  TigerApp::associateSyntax(_syntax, _action_factory);
}

TigerApp::~TigerApp()
{
}

// External entry point for dynamic application loading
extern "C" void TigerApp__registerApps() { TigerApp::registerApps(); }
void
TigerApp::registerApps()
{
  registerApp(TigerApp);
}

// External entry point for dynamic object registration
extern "C" void TigerApp__registerObjects(Factory & factory) { TigerApp::registerObjects(factory); }
void
TigerApp::registerObjects(Factory & factory)
{
  registerKernel(HeatCondTimeDerivative);
  registerKernel(CoefConduction);
  registerKernel(HeatCondHomogenizationKernel);
  registerKernel(QSource);
  registerMaterial(HfAlMaterial);
  registerMaterial(HfAlBulkMaterial);
  registerPostprocessor(WilsHomogenizedThermalConductivity);
  registerBoundaryCondition(CoupledNeumannBC);
}

// External entry point for dynamic syntax association
extern "C" void TigerApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { TigerApp::associateSyntax(syntax, action_factory); }
void
TigerApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
