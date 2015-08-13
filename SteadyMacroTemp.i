[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 200
  ny = 200
  xmax = 5e4
  ymax = 5e4
  zmax = 1e2
[]

[Variables]
  [./T]
    block = 0
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
[]

[BCs]
  [./Periodic]
    [./PeriodicBC]
      variable = T
      auto_direction = 'y z'
    [../]
  [../]
  [./right_CoupledNeumannBC]
    type = CoupledNeumannBC
    variable = T
    boundary = right
  [../]
  [./left_NeumannBC]
    type = NeumannBC
    variable = T
    boundary = left
    value = 0.58
  [../]
[]

[Materials]
  [./HafniumAluminum]
    type = HfAlBulkMaterial
    block = 0
    temperature = T
  [../]
[]

[Executioner]
  type = Steady
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
      variable = T
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
    file_base = SteadyMacroTempExodus
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
[]

