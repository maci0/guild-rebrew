cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

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
# Vendored libraries (docs/vendoring.md)
# ---------------------------------------------------------------------------

# references/zlib and references/minizip must equal their pinned pristine
# upstream plus references/vendor/<name>/*.patch; any drift stops configure.
if(EXISTS "${PROJECT_SOURCE_DIR}/.venv/bin/rebrew")
  set(_VENDOR_REBREW "${PROJECT_SOURCE_DIR}/.venv/bin/rebrew")
else()
  find_program(_VENDOR_REBREW rebrew REQUIRED)
endif()
file(GLOB_RECURSE _VENDOR_INPUTS CONFIGURE_DEPENDS
  "${PROJECT_SOURCE_DIR}/references/vendor/*"
  "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3/*"
  "${PROJECT_SOURCE_DIR}/references/zlib/*"
  "${PROJECT_SOURCE_DIR}/references/minizip/*")
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
  ${_VENDOR_INPUTS})
execute_process(
  COMMAND "${_VENDOR_REBREW}" library vendor
          references/vendor/zlib/vendor.toml references/vendor/minizip/vendor.toml
          --root "${PROJECT_SOURCE_DIR}"
  RESULT_VARIABLE _VENDOR_RC)
if(NOT _VENDOR_RC EQUAL 0)
  message(FATAL_ERROR "Vendored sources differ from pristine upstream + patches")
endif()

# ---------------------------------------------------------------------------
# server.dll target
# ---------------------------------------------------------------------------

if(REBREW_BUILD_SERVER)
  # CONFIGURE_DEPENDS makes the build system re-glob on every build. Without it
  # CMake expands the glob once at configure time, so renaming or adding a source
  # leaves build.make, objects1.rsp and link.txt pointing at a .obj that no
  # longer compiles. The build then fails with no obvious cause while
  # `rebrew build check` still reports clean, because that check compares flags
  # on the objects CMake already listed -- it cannot see an object that should
  # have left the list. Measured in round 1080: `rebrew source rename` renamed a .c,
  # split_link.sh died at exit 157, and the fix was a re-configure.
  #
  # Unified tree: game logic shared by all three binaries lives once in
  # src/ (target identities live in the metadata stores). The source list is
  # metadata-selected (rebrew build cmake-sources), not globbed: a GOLD/GOLDTL-only
  # TU linked into server.dll is a composition break (foreign bytes at best,
  # duplicate symbols at worst).
  if(EXISTS "${PROJECT_SOURCE_DIR}/.venv/bin/rebrew")
    set(_REBREW_SRC_BIN "${PROJECT_SOURCE_DIR}/.venv/bin/rebrew")
  else()
    find_program(_REBREW_SRC_BIN rebrew REQUIRED)
  endif()
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
               "${PROJECT_SOURCE_DIR}/rebrew-functions.toml")
  execute_process(
    COMMAND "${_REBREW_SRC_BIN}" build cmake-sources --target "server.dll"
            -o ${CMAKE_BINARY_DIR}/rebrew-sources-server.cmake
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE _REBREW_SOURCES_RC)
  if(NOT _REBREW_SOURCES_RC EQUAL 0)
    message(FATAL_ERROR "rebrew build cmake-sources failed for server.dll")
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
  # Pure CRT bodies and data live in LIBCMT, so nothing under crt_region is
  # compiled. amsg_exit.c in particular: /INCLUDE:__CRT_INIT@12 pulls
  # dllcrt0.obj for /ENTRY, which defines _amsg_exit itself (LNK2005 otherwise).
  list(FILTER SERVER_SOURCES EXCLUDE REGEX "/crt_region/")



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
    "${PROJECT_SOURCE_DIR}/references/zlib/adler32.c"
    "${PROJECT_SOURCE_DIR}/references/zlib/compress.c"
    "${PROJECT_SOURCE_DIR}/references/zlib/crc32.c"
    "${PROJECT_SOURCE_DIR}/references/zlib/deflate.c"
    "${PROJECT_SOURCE_DIR}/references/zlib/gzio.c"
    "${PROJECT_SOURCE_DIR}/references/zlib/infblock.c"
    "${PROJECT_SOURCE_DIR}/references/zlib/infcodes.c"
    "${PROJECT_SOURCE_DIR}/references/zlib/inffast.c"
    "${PROJECT_SOURCE_DIR}/references/zlib/inflate.c"
    "${PROJECT_SOURCE_DIR}/references/zlib/inftrees.c"
    "${PROJECT_SOURCE_DIR}/references/zlib/infutil.c"
    "${PROJECT_SOURCE_DIR}/references/zlib/trees.c"
    "${PROJECT_SOURCE_DIR}/references/zlib/uncompr.c"
    "${PROJECT_SOURCE_DIR}/references/zlib/zutil.c"
  )
  # minizip's unzip.c, vendored beside zlib (docs/vendoring.md); its rows are
  # outside src/, so cmake-sources does not list it.
  set(MINIZIP_SOURCES "${PROJECT_SOURCE_DIR}/references/minizip/unzip.c")


  # Order objects by original function VA (fixes reccmp "0 aligned"; drops
  # zlib files absent from the original). The --first-va table supplies the
  # vendored files' first-function VAs (pristine vendor C remains unchanged); the
  # --exclude list drops files absent from the original server.dll.
  execute_process(
    COMMAND "${_REBREW_SRC_BIN}" build order-sources ${SERVER_SOURCES} ${ZLIB_SOURCES} ${MINIZIP_SOURCES}
      --target server.dll --module SERVER
      --first-va adler32.c=0x10001000
      --first-va crc32.c=0x100011f0
      --first-va deflate.c=0x10001330
      --first-va infblock.c=0x10003d20
      --first-va infcodes.c=0x10004b80
      --first-va inffast.c=0x10005390
      --first-va inflate.c=0x10005720
      --first-va inftrees.c=0x10005d00
      --first-va infutil.c=0x10006440
      --first-va net.c=0x10006c80
      --first-va trees.c=0x10006ec0
      --first-va unzip.c=0x10008a50
      --first-va bss_head.c=0x10001000
      --first-va zutil.c=0x100092e0
      --first-va bss_head2.c=0x100092e1
      --first-va spiel_data.c=0x100156b0
      --first-va gzio.c=0x100036d0
      --exclude compress.c --exclude uncompr.c
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    OUTPUT_VARIABLE ORDERED_SOURCES
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE ORDER_RC)
  if(NOT ORDER_RC EQUAL 0)
    message(FATAL_ERROR "rebrew build order-sources failed")
  endif()
  string(REPLACE "\n" ";" SERVER_SOURCES "${ORDERED_SOURCES}")

  # The game's zero-initialized data sits in two generated objects (docs/msvc6-link-layout.md 5c):
  # bss_head.c is an ordinary object (its .bss precedes the CRT's); bss_late.c is a static library
  # listed after the stock archives, so LINK loads it after the CRT and its .bss follows theirs.
  list(FILTER SERVER_SOURCES EXCLUDE REGEX "/bss_late\\.c$")
  add_library(server_dll SHARED ${SERVER_SOURCES})
  add_library(bss_late STATIC "${PROJECT_SOURCE_DIR}/src/bss_layout/bss_late.c")

  target_include_directories(server_dll PRIVATE
    # Unified tree: src/Develop mirrors D:\Develop (game headers live at its
    # root); src/ holds rebrew scaffolding (generated bss_layout/, .def files).
    "${PROJECT_SOURCE_DIR}/src/Develop"
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3"
  )

  # Link unchanged stock archives in config order.
  target_link_libraries(server_dll PRIVATE ${REBREW_EXTERNAL_LIBS} bss_late)

  set_property(TARGET server_dll PROPERTY OUTPUT_NAME "server")
  set_property(TARGET server_dll PROPERTY PREFIX "")
  set_property(TARGET server_dll PROPERTY SUFFIX ".dll")

  if(MSVC_FOR_DECOMP)
    # Native LIB owns the export timestamp; native LINK owns the COFF timestamp.
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
      "${PROJECT_SOURCE_DIR}/rebrew-project.toml")
    execute_process(
      COMMAND "${_REBREW_SRC_BIN}" binary pe --target server.dll --json
      WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
      RESULT_VARIABLE _SERVER_TIMESTAMP_RC OUTPUT_VARIABLE _SERVER_TIMESTAMPS
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    if(NOT _SERVER_TIMESTAMP_RC EQUAL 0)
      message(FATAL_ERROR "Cannot read native server build timestamps")
    endif()
    string(JSON _SERVER_LINK_EPOCH GET "${_SERVER_TIMESTAMPS}" timestamp)
    string(JSON _SERVER_EXPORT_EPOCH GET "${_SERVER_TIMESTAMPS}" export_timestamp)
    string(JSON _SERVER_REFERENCE GET "${_SERVER_TIMESTAMPS}" binary)
    foreach(_epoch IN ITEMS _SERVER_LINK_EPOCH _SERVER_EXPORT_EPOCH)
      if(NOT "${${_epoch}}" MATCHES "^[0-9]+$" OR "${${_epoch}}" GREATER 2147483647)
        message(FATAL_ERROR "Native Wine clock requires ${_epoch} in 0..2147483647")
      endif()
    endforeach()
    string(REPLACE ";" "\\;" _SERVER_REFERENCE "${_SERVER_REFERENCE}")
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${_SERVER_REFERENCE}")
    set(_SERVER_EXPORT_DIR "${CMAKE_CURRENT_BINARY_DIR}/native-export")
    set(_SERVER_EXP "${_SERVER_EXPORT_DIR}/server.exp")
    set(_SERVER_ARCHIVE_COMMAND "${CMAKE_AR}")
    if (DEFINED REBREW_CMAKE_AR_COMMAND)
      set(_SERVER_ARCHIVE_COMMAND ${REBREW_CMAKE_AR_COMMAND})
    endif()
    add_custom_command(OUTPUT "${_SERVER_EXP}"
      BYPRODUCTS "${_SERVER_EXPORT_DIR}/server.lib"
      COMMAND "${CMAKE_COMMAND}" -E make_directory "${_SERVER_EXPORT_DIR}"
      COMMAND "${CMAKE_COMMAND}" -E env "SOURCE_DATE_EPOCH=${_SERVER_EXPORT_EPOCH}"
        ${_SERVER_ARCHIVE_COMMAND} /nologo /MACHINE:IX86
        "/DEF:${PROJECT_SOURCE_DIR}/src/server.def" "/OUT:${_SERVER_EXPORT_DIR}/server.lib"
      DEPENDS "${PROJECT_SOURCE_DIR}/src/server.def" "${_SERVER_REFERENCE}"
        "${PROJECT_SOURCE_DIR}/rebrew-project.toml"
      VERBATIM)
    set_source_files_properties("${_SERVER_EXP}" PROPERTIES GENERATED TRUE EXTERNAL_OBJECT TRUE)
    target_sources(server_dll PRIVATE "${_SERVER_EXP}")
    set_property(TARGET server_dll PROPERTY RULE_LAUNCH_LINK
      "\"${CMAKE_COMMAND}\" -E env SOURCE_DATE_EPOCH=${_SERVER_LINK_EPOCH} \"REBREW_TOOLCHAIN_OVERLAY_DIR=${PROJECT_SOURCE_DIR}/cmake/toolchain-overlays\"")
  else()
    target_sources(server_dll PRIVATE "${PROJECT_SOURCE_DIR}/src/server.def")
  endif()

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
    COMMAND "${_REBREW_GOLD_BIN}" build cmake-sources --target "Europa1400Gold.exe"
            -o ${CMAKE_BINARY_DIR}/rebrew-sources-gold.cmake
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE _REBREW_GOLD_RC)
  if(NOT _REBREW_GOLD_RC EQUAL 0)
    message(FATAL_ERROR "rebrew build cmake-sources failed for Europa1400Gold.exe")
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
  # No recovered SDK archive matches the reference's Miles 6.1c import hints.
  message(FATAL_ERROR
    "Gold TL linking is blocked: the original Miles 6.1c mss32.lib has not "
    "been verified. Do not substitute the 6.0 archive, OpenMiles, or the "
    "mislabeled 7.2g SDK. See references/mss-6.1c/README.md.")

  # Same rule as server.dll: marker-selected, never globbed.
  if(EXISTS "${PROJECT_SOURCE_DIR}/.venv/bin/rebrew")
    set(_REBREW_GOLDTL_BIN "${PROJECT_SOURCE_DIR}/.venv/bin/rebrew")
  else()
    find_program(_REBREW_GOLDTL_BIN rebrew REQUIRED)
  endif()
  execute_process(
    COMMAND "${_REBREW_GOLDTL_BIN}" build cmake-sources --target "Europa1400Gold_TL.exe"
            -o ${CMAKE_BINARY_DIR}/rebrew-sources-goldtl.cmake
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE _REBREW_GOLDTL_RC)
  if(NOT _REBREW_GOLDTL_RC EQUAL 0)
    message(FATAL_ERROR "rebrew build cmake-sources failed for Europa1400Gold_TL.exe")
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
    # bss_late too: compiled -MD it names MSVCRT as a default library, and LINK then resolves late CRT
    # references (such as the OLDNAMES alias targets) to MSVCRT.dll imports instead of LIBCMT members.
    set_property(TARGET server_dll bss_late PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
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
      "${PROJECT_SOURCE_DIR}/layout/server.dll/import-includes.rsp"
      "${PROJECT_SOURCE_DIR}/layout/server.dll/native-archive-includes.rsp"
      "${PROJECT_SOURCE_DIR}/layout/server.dll/game-includes.rsp")
    target_link_options(server_dll PRIVATE
      "/ORDER:@${PROJECT_SOURCE_DIR}/layout/server.dll/common-data-order.txt")
    # The order file places readonly COMDATs as well as COMMON data.
    # Retention anchors keep real readonly owners and native CRT/import placement.
    # The stock tcschr alias contributes native final-thunk alignment; no padding object.
    # The untouched stock reference leaves the PE checksum at LINK's default zero.
    # LINK uses Microsoft's runtime for import sorting; CL and stock archives stay SP5.
    target_link_options(server_dll PRIVATE
      "/REBREW_TOOLCHAIN:msvc-6.0-sp5-crt"
      "/OPT:REF" "/NODEFAULTLIB:LIBCMTD"
      "@${PROJECT_SOURCE_DIR}/layout/server.dll/import-includes.rsp"
      "@${PROJECT_SOURCE_DIR}/layout/server.dll/native-archive-includes.rsp"
      "@${PROJECT_SOURCE_DIR}/layout/server.dll/game-includes.rsp"
      "/MAP:${CMAKE_CURRENT_BINARY_DIR}/server.map")
    if(REBREW_DEBUG_INFO)
      target_compile_options(server_dll PRIVATE /Z7)
      target_link_options(server_dll PRIVATE /debug)
    endif()
  endif()
endif()

# Client links use the same header roots and explicit runtime as verification.
if(MSVC_FOR_DECOMP)
  foreach(_client europa1400gold europa1400gold_tl)
    if(TARGET ${_client})
      target_include_directories(${_client} PRIVATE
        "${PROJECT_SOURCE_DIR}/src/Develop"
        "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3")
      set_property(TARGET ${_client} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")
      if(REBREW_ALLOW_NAKED)
        target_compile_definitions(${_client} PRIVATE REBREW_ALLOW_NAKED=1)
      endif()
      target_link_options(${_client} PRIVATE
        "/MAP:${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_FILE_BASE_NAME:${_client}>.map")
    endif()
  endforeach()
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
# `rebrew build cmake-flags` resolves every source through the same chain the tools
# use and writes the table; this file only consumes it.  The metadata is a
# configure dependency, so editing it reconfigures the build instead of
# silently reusing baked COMPILE_FLAGS.
function(rebrew_apply_cflags target_name source_list suffix)
  if(EXISTS "${PROJECT_SOURCE_DIR}/.venv/bin/rebrew")
    set(REBREW_BIN "${PROJECT_SOURCE_DIR}/.venv/bin/rebrew")
  else()
    find_program(REBREW_BIN rebrew REQUIRED)
  endif()
  set(_rebrew_sources_txt "${CMAKE_BINARY_DIR}/rebrew-sources${suffix}.txt")
  set(_rebrew_cflags_cmake "${CMAKE_BINARY_DIR}/rebrew-cflags${suffix}.cmake")
  file(WRITE "${_rebrew_sources_txt}" "")
  foreach(_src IN LISTS ${source_list})
    if(NOT IS_ABSOLUTE "${_src}")
      set(_abs "${PROJECT_SOURCE_DIR}/${_src}")
    else()
      set(_abs "${_src}")
    endif()
    file(RELATIVE_PATH _rel "${PROJECT_SOURCE_DIR}" "${_abs}")
    file(APPEND "${_rebrew_sources_txt}" "${_rel}\n")
  endforeach()
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
               "${PROJECT_SOURCE_DIR}/rebrew-functions.toml")
  execute_process(
    COMMAND "${REBREW_BIN}" build cmake-flags
            --target "${target_name}"
            --sources-file "${_rebrew_sources_txt}"
            --output "${_rebrew_cflags_cmake}"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    RESULT_VARIABLE _rebrew_flags_rc)
  if(NOT _rebrew_flags_rc EQUAL 0)
    message(FATAL_ERROR
      "rebrew build cmake-flags failed (rc=${_rebrew_flags_rc}). It refuses a file "
      "whose functions resolve to different flags, because a translation unit "
      "compiles with one flag set; split the file or align the metadata.")
  endif()
  include("${_rebrew_cflags_cmake}")
  message(STATUS "rebrew: ${target_name} per-file CFLAGS resolved from metadata")
endfunction()

if(MSVC_FOR_DECOMP)
  if(TARGET server_dll)
    rebrew_apply_cflags("server.dll" SERVER_SOURCES "")
  endif()
  if(TARGET europa1400gold)
    rebrew_apply_cflags("Europa1400Gold.exe" GOLD_SOURCES "-gold")
  endif()
  if(TARGET europa1400gold_tl)
    rebrew_apply_cflags("Europa1400Gold_TL.exe" GOLDTL_SOURCES "-goldtl")
  endif()
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
    COMMAND "${_REBREW_SRC_BIN}" verify --whole-binary --built "$<TARGET_FILE:server_dll>" --json --target server.dll
    DEPENDS server_dll
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Verify raw server.dll against the reference"
    VERBATIM)
endif()
