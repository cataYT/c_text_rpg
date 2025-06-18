cmake_minimum_required(VERSION 3.15)
project(MyGameProject LANGUAGES C CXX)

# Recursively gather all .c files in src/ and subdirectories
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.c
)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/objs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/objs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/pdb)

# Compiler-specific settings
if(MSVC)
    # Use latest C and C++ standards available
    set(CMAKE_C_STANDARD 23)
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

    add_compile_options(
        /Zi                 # Debug info
        /EHsc               # Enable C++ exceptions (harmless for C)
        /nologo             # Suppress compiler banner
        /fsanitize=address  # Address sanitizer (VS 2019 16.9+)
        /Wall               # All warnings
        /WX                 # Treat warnings as errors
        /std:clatest        # Latest language standard (cl.exe-specific)
        /Qspectre           # Spectre mitigation
        /wd5045             # Disable spectre warning
        /wd4820             # Disable padding warning
    )
else()
    # GCC or Clang
    set(CMAKE_C_STANDARD 23)
    set(CMAKE_CXX_STANDARD 23)

    add_compile_options(
        -g
        -fsanitize=address
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -std=c23
        -fno-omit-frame-pointer
    )
    link_libraries(asan)
endif()

# Add executable
add_executable(main.exe ${SOURCES})

# PDB output settings for MSVC
if(MSVC)
    set_target_properties(main.exe PROPERTIES
        COMPILE_PDB_NAME main
        COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_PDB_OUTPUT_DIRECTORY}
    )
endif()