cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_VERBOSE_MAKEFILE ON)

project(fast)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp-simd -march=native -O1")

find_package(OpenCL REQUIRED)

if ( NOT OpenCL_FOUND)
	message(WARNING "Missing OpenCL support.")
    return()

endif()


find_package(OpenMP REQUIRED)

if(NOT OpenMP_FOUND)
	message( WARNING "Missing OpenMP Support")
	return()
endif()

find_package(Eigen3 REQUIRED)

if(NOT Eigen3_FOUND)
	message(WARNING "Missing Eigen3 Support")
	return()
endif()

set(SOURCE_DIR "src/")

include_directories(fast ${SOURCE_DIR} ${OpenCL_INCLUDE_DIRS} ${OpenMP_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIRS} )
link_directories(${OpenCL_LIBRARY_DIRS} ${OpenMP_LIBRARY_DIRS})

# Add Pybind11 as sub directory (MUST HAVE A CMAKE FILE)
add_subdirectory(pybind11)
pybind11_add_module(fast "${SOURCE_DIR}/module.cpp")

target_link_libraries(fast PRIVATE ${OpenCL_LIBRARIES} ${OpenMP_CXX_LIBRARIES})

