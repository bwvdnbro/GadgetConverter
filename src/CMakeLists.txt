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
    Reader.cpp
    Reader.hpp
    TypeMap.cpp
    TypeMap.hpp
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
