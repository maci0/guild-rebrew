# CMake toolchain file for MSVC 6.0 via the rebrew docker image
#
# CL.EXE / LINK.EXE / LIB.EXE run inside rebrew/msvc:6.0-win32 (wine inside
# the image) through the tools/msvc6-wine-{cl,link,lib} wrappers; the host
# never calls the MSVC binaries directly.  The wrappers same-path mount the
# project root into the container, so absolute paths in the command line
# resolve identically inside it.
#
# Requirements: the docker image must be built first:
#   rebrew toolchain build msvc6     (or: rebrew toolchain pull msvc6)
#
# Usage:
#   cmake -B build --toolchain cmake/toolchain-msvc6-wine.cmake -DCMAKE_BUILD_TYPE=Release
#   cmake --build build -j8

cmake_minimum_required(VERSION 3.15)

# --- Target system ---
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86)

# --- Locate wrapper scripts ---
get_filename_component(_toolchain_dir "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
set(_tools_dir "${_toolchain_dir}/tools")

# --- Compiler / linker ---
set(CMAKE_C_COMPILER "${_tools_dir}/msvc6-wine-cl")
set(CMAKE_LINKER "${_tools_dir}/msvc6-wine-link")
set(CMAKE_AR "${_tools_dir}/msvc6-wine-lib")

# Tell CMake this is MSVC so if(MSVC) blocks activate
set(CMAKE_C_COMPILER_ID "MSVC" CACHE STRING "" FORCE)
set(CMAKE_C_COMPILER_VERSION "12.00.8804" CACHE STRING "" FORCE)
set(CMAKE_C_COMPILER_FORCED TRUE)

# Skip ABI / feature detection — Wine CL can't run CMake's probe executables
set(CMAKE_C_COMPILER_WORKS TRUE CACHE BOOL "" FORCE)

# 32-bit target
set(CMAKE_SIZEOF_VOID_P 4 CACHE STRING "" FORCE)

# --- Standard include / lib paths (set in wrapper, but also helpful here) ---
set(_msvc_root "${_tools_dir}/MSVC600/VC98")
set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES "${_msvc_root}/Include")

# --- MSVC-style output ---
set(CMAKE_C_OUTPUT_EXTENSION ".obj")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_SUFFIX ".lib")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_SUFFIX ".dll")
set(CMAKE_IMPORT_LIBRARY_PREFIX "")
set(CMAKE_IMPORT_LIBRARY_SUFFIX ".lib")
set(CMAKE_EXECUTABLE_SUFFIX ".exe")

# --- Prevent CMake from searching host paths ---
set(CMAKE_FIND_ROOT_PATH "${_msvc_root}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
