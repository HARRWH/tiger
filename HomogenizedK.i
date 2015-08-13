[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 400
  ny = 400
  nz = 0
  xmax = 186.93
  ymax = 186.93
  zmax = 0
[]

[MeshModifiers]
  [./AddExtraNodeset]
    type = AddExtraNodeset
    new_boundary = CenterNode
    coord = '93.465 93.465'
  [../]
[]

[Variables]
  [./T]
    block = 0
  [../]
  [./Chi_X]
    block = 0
  [../]
  [./Chi_Y]
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
  [./CoefConductionChi_X]
    type = CoefConduction
    variable = Chi_X
    block = 0
  [../]
  [./CoefConductionChi_Y]
    type = CoefConduction
    variable = Chi_Y
    block = 0
  [../]
  [./HomogenizationChi_X]
    type = HeatCondHomogenizationKernel
    variable = Chi_X
    component = 0
    block = 0
  [../]
  [./HomogenizationChi_Y]
    type = HeatCondHomogenizationKernel
    variable = Chi_Y
    component = 1
    block = 0
  [../]
  [./CoefConductionT]
    type = CoefConduction
    variable = T
    block = 0
  [../]
[]

[BCs]
  [./Periodic]
    [./PeriodicBCs]
      variable = 'Chi_X Chi_Y'
      auto_direction = 'x y'
    [../]
  [../]
  [./FixChi_X]
    type = PresetBC
    variable = Chi_X
    boundary = CenterNode
    value = 300
  [../]
  [./FixChi_Y]
    type = PresetBC
    variable = Chi_Y
    boundary = CenterNode
    value = 300
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

[Postprocessors]
  [./k_xx]
    # Effective thermal conductivity in x-direction from AEH
    type = WilsHomogenizedThermalConductivity
    variable = Chi_X
    temp_x = Chi_X
    temp_y = Chi_Y
    component = 0
    diffusion_coefficient_name = conductivity
  [../]
  [./k_yy]
    # Effective thermal conductivity in y-direction from AEH
    type = WilsHomogenizedThermalConductivity
    variable = Chi_Y
    temp_x = Chi_X
    temp_y = Chi_Y
    component = 1
    diffusion_coefficient_name = conductivity
  [../]
[]

[Preconditioning]
  [./SMP]
    type = SMP
    off_diag_row = 'Chi_X Chi_Y'
    off_diag_column = 'Chi_Y Chi_X'
  [../]
[]

[Executioner]
  type = Steady
  l_max_its = 15
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value = 'hypre boomeramg 31'
  l_tol = 1e-9
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
    file_base = HomogenizedKMaterialExodus
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

