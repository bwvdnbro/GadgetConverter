################################################################################
# This file is part of GadgetConverter
# Copyright (C) 2016 Bert Vandenbroucke
#
# GadgetConverter is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# GadgetConverter is distributed in the hope that it will be useful,
# but WITOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with GadgetConverter. If not, see <http://www.gnu.org/licenses/>.
################################################################################

cmake_minimum_required(VERSION 2.6)
project(GadgetConverter)

# The version number.
set(GADGETCONVERTER_VERSION_MAJOR 0)
set(GADGETCONVERTER_VERSION_MINOR 1)

# make warnings more strict
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wignored-qualifiers -Werror")

# write executables to a specific directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/rundir)

include_directories(${PROJECT_BINARY_DIR}/src)

# include external libraries
find_package(HDF5 REQUIRED)
include_directories(${HDF5_INCLUDE_DIR})
link_directories(${HDF5_LIBRARY_DIRS})
# enable old HDF5 API
add_definitions(-DH5_USE_16_API)

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

