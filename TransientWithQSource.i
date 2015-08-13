[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 500
  ny = 500
  xmax = 186.93
  ymax = 186.93
  zmax = 2
[]

[Variables]
  [./T]
    block = 0
  [../]
[]

[AuxVariables]
  [./RGB_aux_variable]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  [../]
  [./adapt_aux_variable]
    block = 0
  [../]
[]

[Functions]
  [./image_function]
    type = ImageFunction
    file = WithVoid10.png
    component = 2
  [../]
[]

[Kernels]
  [./CoefConductionT]
    type = CoefConduction
    variable = T
    block = 0
  [../]
  [./QSource]
    type = QSource
    variable = T
    block = 0
  [../]
  [./CoefTimeDerivative]
    type = HeatCondTimeDerivative
    variable = T
    block = 0
  [../]
[]

[Materials]
  [./HafniumAluminum]
    type = HfAlMaterial
    block = 0
    temperature = T
    RGB_aux_variable = RGB_aux_variable
  [../]
[]

[Executioner]
  type = Transient
  dt = 100000
  l_max_its = 15
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value = 'hypre boomeramg 31'
  nl_abs_tol = 1e-8
[]

[Adaptivity]
  cycles_per_step = 0
  marker = marker
  initial_marker = marker
  [./Indicators]
    [./indicator]
      type = GradientJumpIndicator
      variable = adapt_aux_variable
      block = 0
    [../]
  [../]
  [./Markers]
    [./marker]
      type = ErrorFractionMarker
      indicator = indicator
      block = 0
      refine = 0.9
    [../]
  [../]
[]

[Outputs]
  [./MaterialExodus]
    output_material_properties = true
    file_base = TransientWithQSourceExodus
    type = Exodus
  [../]
[]

[ICs]
  [./ConstantIC_T]
    variable = T
    type = ConstantIC
    value = 300
    block = 0
  [../]
  [./ImageFunctionIC_RGB]
    function = image_function
    variable = RGB_aux_variable
    type = FunctionIC
    block = 0
  [../]
  [./ImageFunctionIC_adapt]
    function = image_function
    variable = adapt_aux_variable
    type = FunctionIC
    block = 0
  [../]
[]
