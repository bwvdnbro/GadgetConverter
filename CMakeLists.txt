cmake_minimum_required(VERSION 2.6)
project(GadgetConverter)

# The version number.
set(GADGETCONVERTER_VERSION_MAJOR 0)
set(GADGETCONVERTER_VERSION_MINOR 1)

# make warnings more strict
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wignored-qualifiers -Werror")

# write executables to a specific directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/rundir)

# include external libraries
find_package(HDF5 REQUIRED)
include_directories(${HDF5_INCLUDE_DIR})
link_directories(${HDF5_LIBRARY_DIRS})

add_subdirectory(src)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${PROJECT_SOURCE_DIR}/Doxyfile
                   ${PROJECT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc ALL
                      ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
                      WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
                      COMMENT "Generating API documentation with Doxygen"
                      VERBATIM
                     )
endif(DOXYGEN_FOUND)

