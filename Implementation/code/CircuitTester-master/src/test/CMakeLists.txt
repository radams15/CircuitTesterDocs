set(TEST_FILES
        Test_MNA.cc
        Test_MNACircuit.cc)

set(C_FILES
        ../main/Analysis/Equation.cc
        ../main/Analysis/Equation.h
        ../main/Analysis/MNACircuit.cc
        ../main/Analysis/MNACircuit.h
        ../main/Analysis/MNAComponent.cc
        ../main/Analysis/MNAComponent.h
        ../main/Analysis/MNASolution.cc
        ../main/Analysis/MNASolution.h
        ../main/Analysis/MNA.h
        ../main/Analysis/Unknown.cc ../main/Analysis/Unknown.h Test_MNACircuit.cc ../main/Analysis/Term.cc ../main/Analysis/Term.h)

set(EIGEN3_ROOT ${CMAKE_SOURCE_DIR}/lib/eigen)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/lib)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(test ${TEST_FILES} ${C_FILES})
target_link_libraries(test gtest_main)
