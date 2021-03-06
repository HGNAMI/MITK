find_package(VTK COMPONENTS ${VTK_REQUIRED_COMPONENTS_BY_MODULE} REQUIRED)

foreach(vtk_module ${VTK_REQUIRED_COMPONENTS_BY_MODULE})
  list(APPEND ALL_LIBRARIES "VTK::${vtk_module}")
endforeach()

if(ALL_LIBRARIES)
  vtk_module_autoinit(TARGETS ${MODULE_NAME} MODULES ${ALL_LIBRARIES})
endif()
