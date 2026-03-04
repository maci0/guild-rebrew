cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# MSVC runtime library flags are selected by an abstraction
cmake_policy(SET CMP0091 NEW)

project(rebrew C)

include(CheckCSourceCompiles)
include(CMakeDependentOption)
include(CMakePushCheckState)
include("${CMAKE_CURRENT_LIST_DIR}/cmake/reccmp.cmake")

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# ---------------------------------------------------------------------------
# Options
# ---------------------------------------------------------------------------

option(ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
if (ENABLE_CLANG_TIDY)
  find_program(CLANG_TIDY_BIN NAMES "clang-tidy")
  set(CMAKE_C_CLANG_TIDY "${CLANG_TIDY_BIN}")
endif()

option(REBREW_WERROR "Treat warnings as errors" OFF)
option(REBREW_BUILD_SERVER "Build server.dll reconstruction" ON)
option(REBREW_BUILD_GOLD "Build Europa1400Gold.exe reconstruction" OFF)
option(REBREW_BUILD_GOLDTL "Build Europa1400Gold_TL.exe reconstruction" OFF)

# ---------------------------------------------------------------------------
# Architecture detection
# ---------------------------------------------------------------------------

math(EXPR bits "8 * ${CMAKE_SIZEOF_VOID_P}")
message(STATUS "Building ${bits}-bit Europa 1400 (rebrew)")
if (NOT bits EQUAL 32)
  message(WARNING "Only 32-bit executables are supported for decompilation matching")
endif()

# ---------------------------------------------------------------------------
# MSVC decompilation compiler detection
# ---------------------------------------------------------------------------

set(MSVC_FOR_DECOMP FALSE)
if (MSVC)
  # Visual C++ 6.0 -> cl version 12.x
  # Visual C++ 4.2 -> cl version 10.2.0
  if (CMAKE_C_COMPILER_VERSION VERSION_LESS "13.0")
    set(MSVC_FOR_DECOMP TRUE)
  endif()
endif()
message(STATUS "MSVC for decompilation: ${MSVC_FOR_DECOMP}")

# ---------------------------------------------------------------------------
# Warning helpers
# ---------------------------------------------------------------------------

function(add_c_warning WARNING)
  if(REBREW_WERROR)
    set(compiler_option "-Werror=${WARNING}")
  else()
    set(compiler_option "-W${WARNING}")
  endif()
  string(MAKE_C_IDENTIFIER "COMPILER_SUPPORTS${compiler_option}" varname)

  cmake_push_check_state(RESET)
  set(CMAKE_REQUIRED_FLAGS "${compiler_option} ")
  if(MSVC)
    string(APPEND CMAKE_REQUIRED_FLAGS "/WX")
  else()
    string(APPEND CMAKE_REQUIRED_FLAGS "-Werror")
  endif()
  check_c_source_compiles("int main(void) { return 0; }" ${varname})
  cmake_pop_check_state()

  if(${varname})
    add_compile_options(${compiler_option})
  endif()
endfunction()

add_c_warning(parentheses)

# ---------------------------------------------------------------------------
# server.dll target
# ---------------------------------------------------------------------------

if(REBREW_BUILD_SERVER)
  file(GLOB_RECURSE SERVER_SOURCES
    "src/server.dll/*.c"
  )

  list(FILTER SERVER_SOURCES INCLUDE REGEX "\\.c$")
  list(FILTER SERVER_SOURCES EXCLUDE REGEX "/crt/")
  list(FILTER SERVER_SOURCES EXCLUDE REGEX "/zlib/")

  if(NOT MSVC_FOR_DECOMP)
    set(_MSVC_ONLY_SOURCES
      "crt_memset.c"
      "crt_memmove.c"
      "crt_memmove2.c"
      "crt_strcmp.c"
      "crt_strcat.c"
    )
    foreach(_f IN LISTS _MSVC_ONLY_SOURCES)
      list(FILTER SERVER_SOURCES EXCLUDE REGEX "/${_f}$")
    endforeach()
  endif()

  set(ZLIB_SOURCES
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3/adler32.c"
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3/compress.c"
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3/crc32.c"
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3/deflate.c"
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3/gzio.c"
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3/infblock.c"
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3/infcodes.c"
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3/inffast.c"
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3/inflate.c"
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3/inftrees.c"
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3/infutil.c"
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3/trees.c"
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3/uncompr.c"
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3/zutil.c"
  )

  set(LINK_STUBS "${PROJECT_SOURCE_DIR}/src/link_stubs.c")

  add_library(server_dll SHARED ${SERVER_SOURCES} ${ZLIB_SOURCES} ${LINK_STUBS})

  target_include_directories(server_dll PRIVATE
    "${PROJECT_SOURCE_DIR}/src/server.dll"
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3"
  )

  target_link_libraries(server_dll PRIVATE
    "${PROJECT_SOURCE_DIR}/tools/MSVC600/VC98/Lib/KERNEL32.LIB"
    "${PROJECT_SOURCE_DIR}/tools/MSVC600/VC98/Lib/USER32.LIB"
    "${PROJECT_SOURCE_DIR}/tools/MSVC600/VC98/Lib/WS2_32.LIB"
    "${PROJECT_SOURCE_DIR}/tools/MSVC600/VC98/Lib/WINMM.LIB"
  )

  set_property(TARGET server_dll PROPERTY OUTPUT_NAME "server")
  set_property(TARGET server_dll PROPERTY PREFIX "")
  set_property(TARGET server_dll PROPERTY SUFFIX ".dll")

  target_sources(server_dll PRIVATE "${PROJECT_SOURCE_DIR}/src/server.dll/server.def")

  if(MSVC)
    foreach(_zsrc IN LISTS ZLIB_SOURCES)
      set_source_files_properties("${_zsrc}" PROPERTIES COMPILE_FLAGS "/O2")
    endforeach()
  endif()

  reccmp_add_target(server_dll ID SERVER)

  if (MSVC)
    target_compile_options(server_dll PRIVATE /W3)

    if (CMAKE_C_COMPILER_VERSION VERSION_GREATER_EQUAL "15")
      target_compile_definitions(server_dll PRIVATE "_CRT_SECURE_NO_WARNINGS")
    endif()
  endif()

  message(STATUS "server.dll: ${CMAKE_CURRENT_SOURCE_DIR}/src/server.dll (${SERVER_SOURCES_COUNT} source files)")
  list(LENGTH SERVER_SOURCES SERVER_SOURCES_COUNT)
  message(STATUS "server.dll: found ${SERVER_SOURCES_COUNT} source files")
endif()

# ---------------------------------------------------------------------------
# Europa1400Gold.exe target (future)
# ---------------------------------------------------------------------------

if(REBREW_BUILD_GOLD)
  file(GLOB_RECURSE GOLD_SOURCES
    "src/Europa1400Gold/*.c"
  )

  if(GOLD_SOURCES)
    add_executable(europa1400gold WIN32 ${GOLD_SOURCES})

    target_include_directories(europa1400gold PRIVATE
      "${PROJECT_SOURCE_DIR}/src/Europa1400Gold"
    )

    set_property(TARGET europa1400gold PROPERTY OUTPUT_NAME "Europa1400Gold")
    set_property(TARGET europa1400gold PROPERTY SUFFIX ".exe")

    reccmp_add_target(europa1400gold ID GOLD)
  else()
    message(STATUS "Europa1400Gold: no source files found in src/Europa1400Gold/ — skipping")
  endif()
endif()

# ---------------------------------------------------------------------------
# Europa1400Gold_TL.exe target (future)
# ---------------------------------------------------------------------------

if(REBREW_BUILD_GOLDTL)
  file(GLOB_RECURSE GOLDTL_SOURCES
    "src/Europa1400Gold_TL/*.c"
  )

  if(GOLDTL_SOURCES)
    add_executable(europa1400gold_tl WIN32 ${GOLDTL_SOURCES})

    target_include_directories(europa1400gold_tl PRIVATE
      "${PROJECT_SOURCE_DIR}/src/Europa1400Gold_TL"
    )

    set_property(TARGET europa1400gold_tl PROPERTY OUTPUT_NAME "Europa1400Gold_TL")
    set_property(TARGET europa1400gold_tl PROPERTY SUFFIX ".exe")

    reccmp_add_target(europa1400gold_tl ID GOLDTL)
  else()
    message(STATUS "Europa1400Gold_TL: no source files found in src/Europa1400Gold_TL/ — skipping")
  endif()
endif()

# ---------------------------------------------------------------------------
# MSVC for decompilation: match original compiler flags
# ---------------------------------------------------------------------------

if (MSVC_FOR_DECOMP)
  if(TARGET server_dll)
    set_property(TARGET server_dll PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  endif()

  set(CMAKE_C_FLAGS "/W3 /D \"WIN32\" /D \"_WINDOWS\" /D \"_WIN32_WINNT=0x0400\"")
  set(CMAKE_C_FLAGS_DEBUG "/Gm /Zi /Od /D \"_DEBUG\"")
  set(CMAKE_C_FLAGS_RELEASE "/D \"NDEBUG\"")
  set(CMAKE_C_FLAGS_RELWITHDEBINFO "/Zi /D \"NDEBUG\"")
  set(CMAKE_C_FLAGS_MINSIZEREL "/O1 /D \"NDEBUG\"")

  set(CMAKE_EXE_LINKER_FLAGS "/machine:I386")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "/incremental:yes /debug")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/incremental:no")
  set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/incremental:no /debug")
  set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "/incremental:no")

  set(CMAKE_STATIC_LINKER_FLAGS "/machine:I386")

  set(CMAKE_SHARED_LINKER_FLAGS "/machine:I386")
  set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "/incremental:yes /debug")
  set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "/incremental:no")
  set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "/incremental:no /debug")
  set(CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL "/incremental:no")

  if(TARGET server_dll)
    target_compile_options(server_dll PRIVATE /Z7)
    target_link_options(server_dll PRIVATE "/OPT:NOREF" "/debug")
  endif()
endif()

# ---------------------------------------------------------------------------
# Per-file CFLAGS from source annotations (MSVC decompilation builds only)
# ---------------------------------------------------------------------------
# Each .c file has a "// CFLAGS: ..." annotation that specifies the exact
# compiler flags needed to match the original binary. This function reads
# those annotations and applies them as per-file compile flags.

function(apply_annotation_cflags target)
  get_target_property(sources ${target} SOURCES)
  foreach(src IN LISTS sources)
    file(STRINGS "${src}" cflags_lines REGEX "^// CFLAGS:")
    if(cflags_lines)
      list(GET cflags_lines 0 cflags_line)
      string(REGEX REPLACE "^// CFLAGS: *" "" flags "${cflags_line}")
      string(REPLACE "/I\"references/" "/I\"${PROJECT_SOURCE_DIR}/references/" flags "${flags}")
      string(REPLACE "/I..\\\\..\\\\references\\\\" "/I\"${PROJECT_SOURCE_DIR}/references/" flags "${flags}")
      set_source_files_properties("${src}" PROPERTIES COMPILE_FLAGS "${flags}")
    else()
      # Default: GAME functions use /O2 /Gd (matches rebrew-project.toml)
      set_source_files_properties("${src}" PROPERTIES COMPILE_FLAGS "/O2 /Gd")
    endif()
  endforeach()
endfunction()

if(MSVC_FOR_DECOMP AND TARGET server_dll)
  apply_annotation_cflags(server_dll)
endif()

# ---------------------------------------------------------------------------
# clang-format target
# ---------------------------------------------------------------------------

find_program(CLANGFORMAT_BIN NAMES clang-format)
if(EXISTS "${CLANGFORMAT_BIN}")
  execute_process(COMMAND "${CLANGFORMAT_BIN}" --version
    OUTPUT_VARIABLE "CLANGFORMAT_VERSION_OUTPUT"
    RESULT_VARIABLE "CLANGFORMAT_RESULT"
  )
  if(CLANGFORMAT_RESULT EQUAL 0 AND CLANGFORMAT_VERSION_OUTPUT MATCHES "version ([0-9\\.]+)")
    set(CLANGFORMAT_VERSION "${CMAKE_MATCH_1}")
    set(CLANGFORMAT_VERSION_REQUIRED "17.0")
    message(DEBUG "Found clang-format version ${CLANGFORMAT_VERSION} (needs ${CLANGFORMAT_VERSION_REQUIRED})")
    if(CLANGFORMAT_VERSION VERSION_GREATER_EQUAL "${CLANGFORMAT_VERSION_REQUIRED}")
      file(GLOB_RECURSE rebrew_sources
        "${PROJECT_SOURCE_DIR}/src/*.c"
        "${PROJECT_SOURCE_DIR}/src/*.h"
      )
      string(REPLACE ";" "\n" rebrew_sources_lines "${rebrew_sources}")
      file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/rebrew_sources.txt" "${rebrew_sources_lines}\n")
      add_custom_target(clang-format ${CLANGFORMAT_BIN} -i "--files=${CMAKE_CURRENT_BINARY_DIR}/rebrew_sources.txt")
    endif()
  endif()
endif()

# ---------------------------------------------------------------------------
# reccmp configuration (generates reccmp-build.yml)
# ---------------------------------------------------------------------------

reccmp_configure()
