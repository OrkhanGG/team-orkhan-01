cmake_minimum_required(VERSION 3.24)

project(team-orkhan-01
    VERSION 0.1.0
    DESCRIPTION "wxWidgets desktop application"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(wxWidgets CONFIG REQUIRED)

add_executable(team-orkhan-01 WIN32
    src/App.cpp
    src/MainFrame.cpp
)

target_include_directories(team-orkhan-01
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(team-orkhan-01
    PRIVATE
        wx::core
        wx::base
)

if(MSVC)
    target_compile_options(team-orkhan-01 PRIVATE /W4 /permissive-)
    target_compile_definitions(team-orkhan-01 PRIVATE
        _CRT_SECURE_NO_WARNINGS
        wxUSE_RC_MANIFEST=1
    )
else()
    target_compile_options(team-orkhan-01 PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(team-orkhan-01 PROPERTIES
    OUTPUT_NAME "TeamOrkhan01"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

install(TARGETS team-orkhan-01 RUNTIME DESTINATION bin)
