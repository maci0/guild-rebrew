cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# MSVC runtime library flags are selected by an abstraction
cmake_policy(SET CMP0091 NEW)

project(rebrew C)

include(CheckCSourceCompiles)
include(CMakeDependentOption)
include(CMakePushCheckState)

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
option(REBREW_ALLOW_NAKED "Allow __declspec(naked)+__asm for byte-identical verification build (fenced #ifdef)" ON)
option(REBREW_DEBUG_INFO "Emit /Z7 + /debug (PDB for reccmp). OFF = byte-identity build: original DLL has no debug directory" OFF)

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
  # CONFIGURE_DEPENDS makes the build system re-glob on every build. Without it
  # CMake expands the glob once at configure time, so renaming or adding a source
  # leaves build.make, objects1.rsp and link.txt pointing at a .obj that no
  # longer compiles. The build then fails with no obvious cause while
  # `rebrew build-check` still reports clean, because that check compares flags
  # on the objects CMake already listed -- it cannot see an object that should
  # have left the list. Measured in round 1080: `rebrew rename` renamed a .c,
  # split_link.sh died at exit 157, and the fix was a re-configure.
  #
  # Unified tree: game logic shared by all three binaries lives once in
  # src/ (one // FUNCTION: marker per target). The source list is
  # marker-selected (rebrew cmake-sources), not globbed: a GOLD/GOLDTL-only
  # TU linked into server.dll is a composition break (foreign bytes at best,
  # duplicate symbols at worst).
  if(EXISTS "${PROJECT_SOURCE_DIR}/.venv/bin/rebrew")
    set(_REBREW_SRC_BIN "${PROJECT_SOURCE_DIR}/.venv/bin/rebrew")
  else()
    find_program(_REBREW_SRC_BIN rebrew REQUIRED)
  endif()
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
               "${PROJECT_SOURCE_DIR}/src/rebrew-functions.toml")
  execute_process(
    COMMAND "${_REBREW_SRC_BIN}" cmake-sources --target "server.dll"
            -o ${CMAKE_BINARY_DIR}/rebrew-sources-server.cmake
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE _REBREW_SOURCES_RC)
  if(NOT _REBREW_SOURCES_RC EQUAL 0)
    message(FATAL_ERROR "rebrew cmake-sources failed for server.dll")
  endif()
  include(${CMAKE_BINARY_DIR}/rebrew-sources-server.cmake)
  set(SERVER_SOURCES ${REBREW_SOURCES})

  list(FILTER SERVER_SOURCES INCLUDE REGEX "\\.c$")
  # A scratch file dropped in the tree (an agent's probe named _something.c) would
  # be swept up by the recursive glob and linked as an extra object, which moves
  # every symbol after it. This happened once. No tracked source has a leading
  # underscore, so excluding the prefix makes a stray probe harmless instead of
  # composition-breaking.
  list(FILTER SERVER_SOURCES EXCLUDE REGEX "/_[^/]*\\.c$")
  list(FILTER SERVER_SOURCES EXCLUDE REGEX "/crt/")
  list(FILTER SERVER_SOURCES EXCLUDE REGEX "/zlib/")
  # Pure CRT bodies live in LIBCMT. Keep only game/layout files under crt_region.
  #
  # All 68 annotated functions under crt_region/ were measured to be
  # byte-identical to stock LIBCMT (identical outside the library object's own
  # relocation slots). They are linked library code that was reversed by
  # mistake; none of it is reversing work to finish. Evidence and the exact
  # symbol/object for each: .scratch/libcmt_probe/SUMMARY.md, reproduce with
  # .scratch/libcmt_probe/cmp_libcmt.py. Note _initterm and _parse_cmdline are
  # static (COFF storage class 3) in the CRT, so they are absent from the
  # archive symbol index; a scan that only walks external symbols misses them.
  #
  # Stock LIBCMT supplies CRT code and readonly data; retain game data owners.
  list(FILTER SERVER_SOURCES EXCLUDE REGEX "/crt_region/")
  set(_CRT_REGION_KEEP
    "${PROJECT_SOURCE_DIR}/src/crt_region/crt_imports.c"
    "${PROJECT_SOURCE_DIR}/src/crt_region/game_float_constants.c"
    "${PROJECT_SOURCE_DIR}/src/crt_region/rdata_restore.c"
  )
  list(APPEND SERVER_SOURCES ${_CRT_REGION_KEEP})


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
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3/trees2.c"
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3/uncompr.c"
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3/zutil.c"
  )

  set(LINK_STUBS "${PROJECT_SOURCE_DIR}/src/link_stubs.c")

  # Order objects by original function VA (fixes reccmp "0 aligned"; drops
  # zlib files absent from the original). The --first-va table supplies the
  # zlib files' first-function VAs (they have no // FUNCTION: markers); the
  # --exclude list drops files absent from the original server.dll.
  execute_process(
    COMMAND rebrew order-sources ${SERVER_SOURCES} ${ZLIB_SOURCES}
      --marker SERVER
      --first-va adler32.c=0x10001000
      --first-va crc32.c=0x100011f0
      --first-va deflate.c=0x10001330
      --first-va infblock.c=0x10003d20
      --first-va infcodes.c=0x10004b80
      --first-va inffast.c=0x10005390
      --first-va inflate.c=0x10005720
      --first-va inftrees.c=0x10005d00
      --first-va infutil.c=0x10006440
      --first-va winsock_data.c=0x10006c80
      --first-va trees.c=0x10006ec0
      --first-va trees2.c=0x10008800
      --first-va zutil.c=0x100092e0
      --first-va spiel_data.c=0x100156b0
      --exclude gzio.c
      --exclude compress.c --exclude uncompr.c
    OUTPUT_VARIABLE ORDERED_SOURCES
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE ORDER_RC)
  if(NOT ORDER_RC EQUAL 0)
    message(FATAL_ERROR "rebrew order-sources failed")
  endif()
  string(REPLACE "\n" ";" SERVER_SOURCES "${ORDERED_SOURCES}")

  # Import retention directives precede the source-ordered game objects.
  # winsock_data.c and spiel_data.c use their owner TUs' --first-va above.
  set(_SERVER_DATA_PREFIX
    "${PROJECT_SOURCE_DIR}/src/crt_region/crt_imports.c"
  )
  list(REMOVE_ITEM SERVER_SOURCES ${_SERVER_DATA_PREFIX})
  list(PREPEND SERVER_SOURCES ${_SERVER_DATA_PREFIX})
  # These readonly strings precede the first game float-literal contribution.
  # Native ordering restores both reference addresses without moving code.
  set(_SERVER_RDATA_STRINGS "${PROJECT_SOURCE_DIR}/src/crt_region/rdata_restore.c")
  list(REMOVE_ITEM SERVER_SOURCES "${_SERVER_RDATA_STRINGS}")
  list(FIND SERVER_SOURCES
    "${PROJECT_SOURCE_DIR}/src/Develop/DieGildeAddOn/game/alchemistry_logic_c/ahm_ExAllocAlchemist.c"
    _SERVER_FIRST_FLOAT_OWNER)
  if(_SERVER_FIRST_FLOAT_OWNER LESS 0)
    message(FATAL_ERROR "Missing first server float-literal owner")
  endif()
  list(INSERT SERVER_SOURCES ${_SERVER_FIRST_FLOAT_OWNER} "${_SERVER_RDATA_STRINGS}")
  # These actual type tables precede the literal pools in the reference.
  set(_SERVER_RDATA_TYPES "${PROJECT_SOURCE_DIR}/src/Develop/DieGildeAddOn/game/type_adjustments.c")
  list(REMOVE_ITEM SERVER_SOURCES "${_SERVER_RDATA_TYPES}")
  list(FIND SERVER_SOURCES
    "${PROJECT_SOURCE_DIR}/src/Develop/DieGildeAddOn/game/alchemistry_logic_c/ahm_ExAllocAlchemist.c"
    _SERVER_FIRST_FLOAT_OWNER)
  list(INSERT SERVER_SOURCES ${_SERVER_FIRST_FLOAT_OWNER} "${_SERVER_RDATA_TYPES}")
  # Named readonly data precedes the first game double-one pool contribution.
  set(_SERVER_RDATA_CONSTANTS "${PROJECT_SOURCE_DIR}/src/crt_region/game_float_constants.c")
  list(REMOVE_ITEM SERVER_SOURCES "${_SERVER_RDATA_CONSTANTS}")
  list(FIND SERVER_SOURCES
    "${PROJECT_SOURCE_DIR}/src/Develop/DieGildeAddOn/game/spiel_c/gm_AllocSpieler.c"
    _SERVER_FIRST_DOUBLE_ONE_OWNER)
  if(_SERVER_FIRST_DOUBLE_ONE_OWNER LESS 0)
    message(FATAL_ERROR "Missing first server double-one pool owner")
  endif()
  list(INSERT SERVER_SOURCES ${_SERVER_FIRST_DOUBLE_ONE_OWNER} "${_SERVER_RDATA_CONSTANTS}")
  # The remaining data owner follows game objects, before stock CRT data.
  set(_SERVER_DATA_SUFFIX
    "${PROJECT_SOURCE_DIR}/src/link_stubs.c"
  )
  list(REMOVE_ITEM SERVER_SOURCES ${_SERVER_DATA_SUFFIX})
  list(APPEND SERVER_SOURCES ${_SERVER_DATA_SUFFIX})
  add_library(server_dll SHARED ${SERVER_SOURCES})

  target_include_directories(server_dll PRIVATE
    # Unified tree: src/Develop mirrors D:\Develop (game headers live at its
    # root); src/ holds rebrew scaffolding (link_stubs.c, .def files).
    "${PROJECT_SOURCE_DIR}/src/Develop"
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3"
  )

  # Link unchanged stock archives in config order.
  target_link_libraries(server_dll PRIVATE ${REBREW_EXTERNAL_LIBS})

  set_property(TARGET server_dll PROPERTY OUTPUT_NAME "server")
  set_property(TARGET server_dll PROPERTY PREFIX "")
  set_property(TARGET server_dll PROPERTY SUFFIX ".dll")

  target_sources(server_dll PRIVATE "${PROJECT_SOURCE_DIR}/src/server.def")

  # Plain VC6 SP5 preserves all game matches and supplies the matching stock CRT.
  # The server's x87 comparisons exclude the Processor Pack code generator.

  if(MSVC)
    foreach(_zsrc IN LISTS ZLIB_SOURCES)
      set_source_files_properties("${_zsrc}" PROPERTIES COMPILE_FLAGS "/O2")
    endforeach()
  endif()

  if (MSVC)
    target_compile_options(server_dll PRIVATE /W3)

    if (CMAKE_C_COMPILER_VERSION VERSION_GREATER_EQUAL "15")
      target_compile_definitions(server_dll PRIVATE "_CRT_SECURE_NO_WARNINGS")
    endif()
  endif()

  message(STATUS "server.dll: src/ (${SERVER_SOURCES_COUNT} source files)")
  list(LENGTH SERVER_SOURCES SERVER_SOURCES_COUNT)
  message(STATUS "server.dll: found ${SERVER_SOURCES_COUNT} source files")

  if(REBREW_ALLOW_NAKED)
    target_compile_definitions(server_dll PRIVATE REBREW_ALLOW_NAKED=1)
    message(STATUS "server.dll: REBREW_ALLOW_NAKED=1 (naked+__asm fenced for byte-identical build)")
  endif()
endif()

# ---------------------------------------------------------------------------
# Europa1400Gold.exe target (future)
# ---------------------------------------------------------------------------

if(REBREW_BUILD_GOLD)
  # Same rule as server.dll: marker-selected, never globbed. The shared tree
  # holds SERVER/GOLDTL TUs that must not link into the GOLD client.
  if(EXISTS "${PROJECT_SOURCE_DIR}/.venv/bin/rebrew")
    set(_REBREW_GOLD_BIN "${PROJECT_SOURCE_DIR}/.venv/bin/rebrew")
  else()
    find_program(_REBREW_GOLD_BIN rebrew REQUIRED)
  endif()
  execute_process(
    COMMAND "${_REBREW_GOLD_BIN}" cmake-sources --target "Europa1400Gold.exe"
            -o ${CMAKE_BINARY_DIR}/rebrew-sources-gold.cmake
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE _REBREW_GOLD_RC)
  if(NOT _REBREW_GOLD_RC EQUAL 0)
    message(FATAL_ERROR "rebrew cmake-sources failed for Europa1400Gold.exe")
  endif()
  include(${CMAKE_BINARY_DIR}/rebrew-sources-gold.cmake)
  set(GOLD_SOURCES ${REBREW_SOURCES})

  if(GOLD_SOURCES)
    add_executable(europa1400gold WIN32 ${GOLD_SOURCES})

    target_link_libraries(europa1400gold PRIVATE ${REBREW_EXTERNAL_LIBS})

    target_include_directories(europa1400gold PRIVATE
      "${PROJECT_SOURCE_DIR}/src"
    )

    set_property(TARGET europa1400gold PROPERTY OUTPUT_NAME "Europa1400Gold")
    set_property(TARGET europa1400gold PROPERTY SUFFIX ".exe")

  else()
    message(STATUS "Europa1400Gold: cmake-sources selected no TUs — skipping")
  endif()
endif()

# ---------------------------------------------------------------------------
# Europa1400Gold_TL.exe target (future)
# ---------------------------------------------------------------------------

if(REBREW_BUILD_GOLDTL)
  # Same rule as server.dll: marker-selected, never globbed.
  if(EXISTS "${PROJECT_SOURCE_DIR}/.venv/bin/rebrew")
    set(_REBREW_GOLDTL_BIN "${PROJECT_SOURCE_DIR}/.venv/bin/rebrew")
  else()
    find_program(_REBREW_GOLDTL_BIN rebrew REQUIRED)
  endif()
  execute_process(
    COMMAND "${_REBREW_GOLDTL_BIN}" cmake-sources --target "Europa1400Gold_TL.exe"
            -o ${CMAKE_BINARY_DIR}/rebrew-sources-goldtl.cmake
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE _REBREW_GOLDTL_RC)
  if(NOT _REBREW_GOLDTL_RC EQUAL 0)
    message(FATAL_ERROR "rebrew cmake-sources failed for Europa1400Gold_TL.exe")
  endif()
  include(${CMAKE_BINARY_DIR}/rebrew-sources-goldtl.cmake)
  set(GOLDTL_SOURCES ${REBREW_SOURCES})

  if(GOLDTL_SOURCES)
    add_executable(europa1400gold_tl WIN32 ${GOLDTL_SOURCES})

    target_link_libraries(europa1400gold_tl PRIVATE ${REBREW_EXTERNAL_LIBS})

    target_include_directories(europa1400gold_tl PRIVATE
      "${PROJECT_SOURCE_DIR}/src"
    )

    set_property(TARGET europa1400gold_tl PROPERTY OUTPUT_NAME "Europa1400Gold_TL")
    set_property(TARGET europa1400gold_tl PROPERTY SUFFIX ".exe")

  else()
    message(STATUS "Europa1400Gold_TL: cmake-sources selected no TUs — skipping")
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
    set_property(TARGET server_dll APPEND PROPERTY LINK_DEPENDS
      "${PROJECT_SOURCE_DIR}/layout/server.dll/common-data-order.txt"
      "${PROJECT_SOURCE_DIR}/layout/server.dll/native-archive-includes.rsp")
    target_link_options(server_dll PRIVATE
      "/ORDER:@${PROJECT_SOURCE_DIR}/layout/server.dll/common-data-order.txt")
    # Ordered archive anchors preserve native CRT member and import-thunk placement.
    # The stock tcschr alias contributes native final-thunk alignment; no padding object.
    # The reference stores a valid PE checksum; LINK computes it with /RELEASE.
    target_link_options(server_dll PRIVATE
      "/OPT:REF" "/RELEASE" "/NODEFAULTLIB:LIBCMTD" "/ENTRY:_DllMainCRTStartup@12"
      "@${PROJECT_SOURCE_DIR}/layout/server.dll/native-archive-includes.rsp"
      "/MAP:${CMAKE_CURRENT_BINARY_DIR}/server.map")
    if(REBREW_DEBUG_INFO)
      target_compile_options(server_dll PRIVATE /Z7)
      target_link_options(server_dll PRIVATE /debug)
    endif()
  endif()
endif()

# ---------------------------------------------------------------------------
# Per-file CFLAGS come from rebrew-functions.toml, not from the sources
# ---------------------------------------------------------------------------
# The flags a translation unit compiles with are the metadata's business: that
# is what `rebrew test`/`verify`/`match` resolve, and what the numbers in every
# file's notes were measured with.  Reading the `// CFLAGS:` annotation out of
# the .c instead means a file whose annotation disagreed with its metadata
# compiles something no tool ever measured: gm_AllocSpieler ran that way
# (annotation /O2 /Gd /Oa, metadata /Oa /Ow, every note measured on the
# metadata) and was 363 linked bytes behind its own notes.
#
# `rebrew cmake-flags` resolves every source through the same chain the tools
# use and writes the table; this file only consumes it.  The metadata is a
# configure dependency, so editing it reconfigures the build instead of
# silently reusing baked COMPILE_FLAGS.
if(MSVC_FOR_DECOMP AND TARGET server_dll)
  if(EXISTS "${PROJECT_SOURCE_DIR}/.venv/bin/rebrew")
    set(REBREW_BIN "${PROJECT_SOURCE_DIR}/.venv/bin/rebrew")
  else()
    find_program(REBREW_BIN rebrew REQUIRED)
  endif()
  set(_rebrew_sources_txt "${CMAKE_BINARY_DIR}/rebrew-sources.txt")
  set(_rebrew_cflags_cmake "${CMAKE_BINARY_DIR}/rebrew-cflags.cmake")
  file(WRITE "${_rebrew_sources_txt}" "")
  foreach(_src IN LISTS SERVER_SOURCES)
    if(NOT IS_ABSOLUTE "${_src}")
      set(_abs "${PROJECT_SOURCE_DIR}/${_src}")
    else()
      set(_abs "${_src}")
    endif()
    file(RELATIVE_PATH _rel "${PROJECT_SOURCE_DIR}" "${_abs}")
    file(APPEND "${_rebrew_sources_txt}" "${_rel}\n")
  endforeach()
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
               "${PROJECT_SOURCE_DIR}/src/rebrew-functions.toml")
  execute_process(
    COMMAND "${REBREW_BIN}" cmake-flags
            --sources-file "${_rebrew_sources_txt}"
            --output "${_rebrew_cflags_cmake}"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    RESULT_VARIABLE _rebrew_flags_rc)
  if(NOT _rebrew_flags_rc EQUAL 0)
    message(FATAL_ERROR
      "rebrew cmake-flags failed (rc=${_rebrew_flags_rc}). It refuses a file "
      "whose functions resolve to different flags, because a translation unit "
      "compiles with one flag set; split the file or align the metadata.")
  endif()
  include("${_rebrew_cflags_cmake}")
  message(STATUS "rebrew: per-file CFLAGS resolved from src/rebrew-functions.toml")
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
      file(GLOB_RECURSE rebrew_sources CONFIGURE_DEPENDS
        "${PROJECT_SOURCE_DIR}/src/*.c"
        "${PROJECT_SOURCE_DIR}/src/*.h"
      )
      string(REPLACE ";" "\n" rebrew_sources_lines "${rebrew_sources}")
      file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/rebrew_sources.txt" "${rebrew_sources_lines}\n")
      add_custom_target(clang-format ${CLANGFORMAT_BIN} -i "--files=${CMAKE_CURRENT_BINARY_DIR}/rebrew_sources.txt")
    endif()
  endif()
endif()

# The deliverable is the raw toolchain output; verification reports remaining differences.
if(MSVC_FOR_DECOMP AND TARGET server_dll)
  add_custom_target(final
    COMMAND rebrew verify --whole-binary --built "$<TARGET_FILE:server_dll>" --json
    DEPENDS server_dll
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Verify raw server.dll against the reference"
    VERBATIM)
endif()
