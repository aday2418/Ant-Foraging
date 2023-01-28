cmake_minimum_required(VERSION 3.23)

project(Ants LANGUAGES CXX VERSION 0.1.0)
configure_file(AntsConfig.h.in AntsConfig.h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Create the AntSimulation Library
add_library(AntSimulation STATIC)
target_sources(AntSimulation
    PRIVATE
      world.cpp
      ant.cpp
      food.cpp
      logic.cpp
      pheromone.cpp
    PUBLIC FILE_SET HEADERS
    BASE_DIRS ${PROJECT_SOURCE_DIR}
    FILES
        world.h
        ant.h
        food.h
        logic.h
        pheromone.h
)

install(TARGETS AntSimulation
    EXPORT AntSimulationTargets
    FILE_SET HEADERS
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include)

install(EXPORT AntSimulationTargets
    FILE AntSimulationTargets.cmake
    NAMESPACE AntSimulation::
    DESTINATION lib/cmake/AntSimulation)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "AntSimulationConfigVersion.cmake"
    VERSION ${AntSimulation_VERSION}
    COMPATIBILITY AnyNewerVersion)

install(
    FILES
        "AntSimulationConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/AntSimulationConfigVersion.cmake"
    DESTINATION lib/cmake/${PROJECT_NAME}
)

#Create the ColorTools Library
add_library(ColorTools STATIC)
target_sources(ColorTools
    PRIVATE
      colortools.cpp
      colorgrid.cpp
      colorgridutils.cpp
    PUBLIC
      FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}
        FILES
          colortools.h
          colorgrid.h
          colorgridutils.h
)

install(TARGETS ColorTools
        EXPORT ColorTools
    FILE_SET HEADERS
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include)

install(EXPORT ColorTools
        FILE ColorToolsTargets.cmake
        NAMESPACE ColorTools::
        DESTINATION lib/cmake/ColorTools)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "ColorToolsConfigVersion.cmake"
    VERSION ${ColorTools_VERSION}
    COMPATIBILITY AnyNewerVersion)

install(
    FILES
        "ColorToolsConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/ColorToolsConfigVersion.cmake"
    DESTINATION lib/cmake/ColorTools
)

#Create AntSimulation UnitTests Library
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(AntSimulationUnittests)
target_sources(AntSimulationUnittests
    PRIVATE
    worldunittests.cpp
    antunittests.cpp
    logicunittests.cpp
    pheromoneunittests.cpp
    foodunittests.cpp
    )
target_link_libraries(AntSimulationUnittests PRIVATE
          ${GTEST_LIBRARIES}
     ${GTEST_MAIN_LIBRARIES}
    AntSimulation
    )

#create the Qt GUI Executable
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets Concurrent  REQUIRED)

add_executable(Ants)
target_sources(Ants PRIVATE
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindowform.ui
  renderarea.h
  renderarea.cpp
  )

target_link_libraries(Ants PRIVATE
  Qt6::Widgets
  Qt6::Concurrent
  AntSimulation
  ColorTools
  )
