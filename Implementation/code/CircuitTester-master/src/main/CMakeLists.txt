if(APPLE)
    set(SYS "macos")
elseif(UNIX)
    set(SYS "unix")
elseif(WIN32)
    set(SYS "windows")
else()
    set(SYS "unknown")
endif()

set(PROJECT_SOURCES
        main.cc

        ../../resources/resources.qrc

        UI/MainWindow.cc
        UI/MainWindow.h
        UI/Arrow.cc
        UI/Arrow.h
        UI/Scene.cc
        UI/Scene.h
        UI/SceneItem.cc
        UI/SceneItem.h
        UI/SceneText.cc
        UI/SceneText.h

        Analysis/Equation.cc
        Analysis/Equation.h
        Analysis/MNACircuit.cc
        Analysis/MNACircuit.h
        Analysis/MNAComponent.cc
        Analysis/MNAComponent.h
        Analysis/MNASolution.cc
        Analysis/MNASolution.h
        Analysis/MNA.h
        UI/Components/Battery.cc
        UI/Components/Battery.h
        UI/Components/Resistor.cc
        UI/Components/Resistor.h
        Analysis/Unknown.cc
        Analysis/Unknown.h
        Analysis/Term.cc
        Analysis/Term.h
        UI/UIComponent.cc
        UI/UIComponent.h
        UI/AnalysisMapper.cc
        UI/AnalysisMapper.h
        Saves/UserUtils.cpp
        Saves/UserUtils.h Saves/CircuitSaver.cc Saves/CircuitSaver.h)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CircuitTester
            ${PROJECT_SOURCES}
            )
else()
    if(ANDROID)
        add_library(CircuitTester SHARED
                ${PROJECT_SOURCES}
                )
    else()
        add_executable(CircuitTester
                ${PROJECT_SOURCES}
                )
    endif()
endif()

set(EIGEN3_ROOT ${CMAKE_SOURCE_DIR}/lib/eigen)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/lib)

find_package(Eigen3 3.3.9 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

target_link_libraries(CircuitTester PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set(BUILD_DIR ${PROJECT_SOURCE_DIR}/builds/${SYS})

install(TARGETS CircuitTester
        CONFIGURATIONS Debug
        RUNTIME DESTINATION ${BUILD_DIR}/debug/bin)

install(TARGETS CircuitTester
        CONFIGURATIONS Release
        RUNTIME DESTINATION ${BUILD_DIR}/release/bin)


add_custom_target(copy_libs
        COMMAND windeployqt ${BUILD_DIR}/release/bin
        # Output Message
        COMMENT "Copying Qt binaries from '${Qt5Core_DIR}/../../bin/' to '${CMAKE_BINARY_DIR}'" VERBATIM
)
