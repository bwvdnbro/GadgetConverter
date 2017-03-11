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

configure_file(${PROJECT_SOURCE_DIR}/resources/names.txt
               ${PROJECT_BINARY_DIR}/resources/names.txt COPYONLY)
set(NAMEMAP_PATH ${PROJECT_BINARY_DIR}/resources/names.txt)
configure_file(${PROJECT_SOURCE_DIR}/resources/types.txt
               ${PROJECT_BINARY_DIR}/resources/types.txt COPYONLY)
set(TYPEMAP_PATH ${PROJECT_BINARY_DIR}/resources/types.txt)
configure_file(${PROJECT_SOURCE_DIR}/resources/type1_list.txt
               ${PROJECT_BINARY_DIR}/resources/type1_list.txt COPYONLY)
set(TYPE1LIST_PATH ${PROJECT_BINARY_DIR}/resources/type1_list.txt)
configure_file(${PROJECT_SOURCE_DIR}/src/Paths.hpp.in
               ${PROJECT_BINARY_DIR}/src/Paths.hpp @ONLY)

set(SOURCES
    Array.hpp
    Block.cpp
    Block.hpp
    CommandLineArguments.cpp
    CommandLineArguments.hpp
    Error.hpp
    Header.cpp
    Header.hpp
    main.cpp
    NameMap.cpp
    NameMap.hpp
    Paths.hpp.in
    Reader.cpp
    Reader.hpp
    TypeMap.cpp
    TypeMap.hpp
    Type1List.cpp
    Type1List.hpp
    Utils.hpp
    Writer.cpp
    Writer.hpp
   )

add_executable(GadgetConverter ${SOURCES})
target_link_libraries(GadgetConverter ${HDF5_LIBRARIES})

add_custom_command(TARGET GadgetConverter POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:GadgetConverter>/resources)
