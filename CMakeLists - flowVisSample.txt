

cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(Assignment_Part2)

find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  CommonDataModel
  FiltersCore
  FiltersGeometry
  FiltersSources
  FiltersModeling
  IOImage
  IOLegacy
  ImagingCore
  InteractionStyle
  InteractionWidgets
  RenderingAnnotation
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingVolumeOpenGL2
  RenderingVolume
  RenderingOpenGL2
  FiltersFlowPaths
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "Assignment_Part2: Unable to find the VTK build folder.")
endif()

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")
add_executable(Assignment_Part2 MACOSX_BUNDLE flowVisSample.cxx )
  target_link_libraries(Assignment_Part2 PRIVATE ${VTK_LIBRARIES}
)
# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS Assignment_Part2
  MODULES ${VTK_LIBRARIES}
)