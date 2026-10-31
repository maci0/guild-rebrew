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
option(REBREW_DEBUG_INFO "Emit /Z7 + /debug and PDB files. OFF = byte-identity build: original DLL has no debug directory" OFF)

if(REBREW_BUILD_GOLD OR REBREW_BUILD_GOLDTL)
  set(MSS32_ARCHIVE "${PROJECT_SOURCE_DIR}/references/mss-6.1c/mss32.lib")
  include("${PROJECT_SOURCE_DIR}/cmake/verify-mss32.cmake")
endif()

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


  # Order objects by original function VA and omit zlib files absent from
  # the original. The --first-va table supplies the
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
  # zlib optimization comes from the scoped metadata table. A source-wide
  # COMPILE_FLAGS "/O2" is appended for every target once that table uses
  # APPEND_STRING, so the files would compile as "/O2 /O2 /Gd".

  # Unified sources carry client-only branches guarded by target macros; the
  # server reference does not have the client's savegame compensation code.
  target_compile_definitions(server_dll PRIVATE REBREW_SERVER=1)

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
# Client comparison link helpers
# ---------------------------------------------------------------------------
# Vendored zlib members that game TUs call but that carry no target binding
# are the same references/zlib sources server.dll already compiles. The zlib
# sample program minigzip is omitted from these comparison scaffolds.

function(rebrew_append_client_zlib source_var)
  set(_sources ${${source_var}})
  set(_zlib_names
    adler32.c
    compress.c
    crc32.c
    deflate.c
    gzio.c
    infblock.c
    infcodes.c
    inffast.c
    inflate.c
    inftrees.c
    infutil.c
    trees.c
    uncompr.c
    zutil.c
  )
  foreach(_name IN LISTS _zlib_names)
    set(_path "${PROJECT_SOURCE_DIR}/references/zlib/${_name}")
    if(NOT _path IN_LIST _sources)
      list(APPEND _sources "${_path}")
    endif()
  endforeach()
  set(_unzip "${PROJECT_SOURCE_DIR}/references/minizip/unzip.c")
  if(NOT _unzip IN_LIST _sources)
    list(APPEND _sources "${_unzip}")
  endif()
  list(FILTER _sources EXCLUDE REGEX "/minigzip\\.c$")
  set(${source_var} ${_sources} PARENT_SCOPE)
endfunction()

# Scaffold selection for a measured LNK2005 pair. The omit list is a
# comparison-build choice: each dropped TU's external definitions are
# provided by another TU that stays on the link. It does not change
# metadata and it does not drop a TU that still has a unique symbol.
function(rebrew_apply_scaffold_omits source_var omit_file)
  set(_sources ${${source_var}})
  set(REBREW_SCAFFOLD_OMITS "")
  if(EXISTS "${omit_file}")
    include("${omit_file}")
  endif()
  foreach(_omit IN LISTS REBREW_SCAFFOLD_OMITS)
    if(NOT IS_ABSOLUTE "${_omit}")
      set(_omit "${PROJECT_SOURCE_DIR}/${_omit}")
    endif()
    list(REMOVE_ITEM _sources "${_omit}")
  endforeach()
  set(${source_var} ${_sources} PARENT_SCOPE)
endfunction()

function(rebrew_append_scaffold source_var scaffold_path)
  set(_sources ${${source_var}})
  if(EXISTS "${scaffold_path}")
    list(APPEND _sources "${scaffold_path}")
  endif()
  set(${source_var} ${_sources} PARENT_SCOPE)
endfunction()

# ---------------------------------------------------------------------------
# Europa1400Gold.exe comparison target
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
  rebrew_append_client_zlib(GOLD_SOURCES)
  rebrew_apply_scaffold_omits(GOLD_SOURCES
    "${PROJECT_SOURCE_DIR}/stubs/gold/omitted-sources.cmake")
  rebrew_append_scaffold(GOLD_SOURCES
    "${PROJECT_SOURCE_DIR}/stubs/gold/symbol_stubs.c")

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
# Europa1400Gold_TL.exe comparison target
# ---------------------------------------------------------------------------

if(REBREW_BUILD_GOLDTL)
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
  # zlib is compiled here and the archive's zlib members stay out of
  # d3dx8-includes.rsp; minizip's unzip.c comes from this helper too.
  rebrew_append_client_zlib(GOLDTL_SOURCES)
  rebrew_apply_scaffold_omits(GOLDTL_SOURCES
    "${PROJECT_SOURCE_DIR}/stubs/goldtl/omitted-sources.cmake")
  rebrew_append_scaffold(GOLDTL_SOURCES
    "${PROJECT_SOURCE_DIR}/stubs/goldtl/symbol_stubs.c")
  # Conflicting fastcall signatures need distinct C translation units.
  rebrew_append_scaffold(GOLDTL_SOURCES
    "${PROJECT_SOURCE_DIR}/stubs/goldtl/abi_stubs.c")
  # Zero-valued definitions for data symbols with a row but no owning TU yet.
  rebrew_append_scaffold(GOLDTL_SOURCES
    "${PROJECT_SOURCE_DIR}/stubs/goldtl/data_scaffold.c")
  # Fastcall band placeholders that complete the comparison link.
  rebrew_append_scaffold(GOLDTL_SOURCES
    "${PROJECT_SOURCE_DIR}/stubs/goldtl/link_scaffold.c")
  # Two shim definitions call GOLD-side symbols; the callee bodies belong to
  # the other client and are not part of this image, so the symbols come from
  # link_scaffold.c instead of dragging that target's closures in.


  # The reference carries zlib's minigzip functions at 0x462500-0x462930
  # (error, gz_uncompress, file_compress, file_uncompress, main), so the TL
  # scaffold compiles minigzip.c even though the helper omits it for the
  # other targets.
  list(APPEND GOLDTL_SOURCES "${PROJECT_SOURCE_DIR}/references/zlib/minigzip.c")

  # The XP image member uses the plain-C JPEG/PNG objects selected below.
  set(_GOLDTL_XP_D3DX "${PROJECT_SOURCE_DIR}/references/dxsdk8/lib/d3dx8-xpsp1.lib")
  if(NOT EXISTS "${_GOLDTL_XP_D3DX}")
    message(FATAL_ERROR "Provide the pristine XP SP1 D3DX8 archive at ${_GOLDTL_XP_D3DX} (SHA-256 c02e4fedf3e2e0964a1eed98ca02b28d68a0a7ac184594b04212216253bfbd9d)")
  endif()
  file(SHA256 "${_GOLDTL_XP_D3DX}" _GOLDTL_XP_D3DX_HASH)
  if(NOT _GOLDTL_XP_D3DX_HASH STREQUAL "c02e4fedf3e2e0964a1eed98ca02b28d68a0a7ac184594b04212216253bfbd9d")
    message(FATAL_ERROR "Unexpected XP SP1 D3DX8 archive SHA-256: ${_GOLDTL_XP_D3DX_HASH}")
  endif()
  find_program(_GOLDTL_LLVM_AR NAMES llvm-ar REQUIRED)
  set(_GOLDTL_XP_IMAGE "${CMAKE_CURRENT_BINARY_DIR}/xp-cd3dximage.obj")
  execute_process(COMMAND "${_GOLDTL_LLVM_AR}" p "${_GOLDTL_XP_D3DX}" "obj\\i386\\cd3dximage.obj"
    OUTPUT_FILE "${_GOLDTL_XP_IMAGE}" RESULT_VARIABLE _GOLDTL_XP_EXTRACT_RC)
  if(NOT _GOLDTL_XP_EXTRACT_RC EQUAL 0)
    message(FATAL_ERROR "Failed to extract XP SP1 cd3dximage.obj")
  endif()
  file(SHA256 "${_GOLDTL_XP_IMAGE}" _GOLDTL_XP_IMAGE_HASH)
  if(NOT _GOLDTL_XP_IMAGE_HASH STREQUAL "d0c91f1bf7550ae39709f738416a48710e75aba61749203d8c7b03d5a07fe592")
    message(FATAL_ERROR "Unexpected XP SP1 cd3dximage.obj SHA-256: ${_GOLDTL_XP_IMAGE_HASH}")
  endif()
  set(_GOLDTL_XP_JERROR "${CMAKE_CURRENT_BINARY_DIR}/xp-jerror.obj")
  execute_process(COMMAND "${_GOLDTL_LLVM_AR}" p "${_GOLDTL_XP_D3DX}" "obj\\i386\\jerror.obj"
    OUTPUT_FILE "${_GOLDTL_XP_JERROR}" RESULT_VARIABLE _GOLDTL_XP_EXTRACT_RC)
  if(NOT _GOLDTL_XP_EXTRACT_RC EQUAL 0)
    message(FATAL_ERROR "Failed to extract XP SP1 jerror.obj")
  endif()
  file(SHA256 "${_GOLDTL_XP_JERROR}" _GOLDTL_XP_JERROR_HASH)
  if(NOT _GOLDTL_XP_JERROR_HASH STREQUAL "e1203fbdc8cb43231d4952b24843030fdd4f332c51e858807bdaf6cbda0516ba")
    message(FATAL_ERROR "Unexpected XP SP1 jerror.obj SHA-256: ${_GOLDTL_XP_JERROR_HASH}")
  endif()
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${_GOLDTL_XP_D3DX}")
  list(APPEND GOLDTL_SOURCES "${_GOLDTL_XP_IMAGE}" "${_GOLDTL_XP_JERROR}")

  # The DX8 supplementary png/jpeg objects are prebuilt and carry no metadata
  # rows, so they need reference first VAs and must be ordered with the rest.
  file(GLOB GOLDTL_DX8_SUPP "${PROJECT_SOURCE_DIR}/references/dxsdk8/supp/*.obj")
  list(APPEND GOLDTL_SOURCES ${GOLDTL_DX8_SUPP})

  # Order objects by their original function VA so the linked image places every
  # body at the reference address. The vendored files are outside src/, so their
  # first-function VAs come from the metadata rows that name them.
  execute_process(
    COMMAND "${_REBREW_GOLDTL_BIN}" build order-sources ${GOLDTL_SOURCES}
      --target "Europa1400Gold_TL.exe" --module GOLDTL
      --first-va adler32.c=0x45d3f0
      --first-va crc32.c=0x45d600
      --first-va deflate.c=0x45da70
      --first-va gzio.c=0x45ee00
      --first-va infblock.c=0x45fc50
      --first-va infcodes.c=0x460a50
      --first-va inffast.c=0x4611b0
      --first-va inflate.c=0x461560
      --first-va inftrees.c=0x462200
      --first-va trees.c=0x462da0
      --first-va unzip.c=0x4645a0
      --first-va minigzip.c=0x462500
      --first-va xp-cd3dximage.obj=0x0061e196
      --first-va xp-jerror.obj=0x0062ecc6
      --first-va jcomapi.obj=0x0063e84b
      --first-va jdmarker.obj=0x0062d5df
      --first-va png.obj=0x0062fcce
      --first-va pngget.obj=0x0062f9df
      --first-va pngread.obj=0x0062d059
      --first-va pngrtran.obj=0x0062fd99
      --first-va pngrutil.obj=0x0063f638
      --first-va pngset.obj=0x00631aa6
      --first-va pngtrans.obj=0x00630bfa
      --first-va pngwrite.obj=0x0062f059
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    OUTPUT_VARIABLE GOLDTL_ORDERED
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE GOLDTL_ORDER_RC)
  if(NOT GOLDTL_ORDER_RC EQUAL 0)
    message(FATAL_ERROR "rebrew build order-sources failed for Europa1400Gold_TL.exe")
  endif()
  string(REPLACE "\n" ";" GOLDTL_SOURCES "${GOLDTL_ORDERED}")

  if(GOLDTL_SOURCES)
    add_executable(europa1400gold_tl WIN32 ${GOLDTL_SOURCES})

    # Move CTLFWR32 to the end: it sits before LIBCMT in the configured list and
    # its Util.Obj satisfies common CRT symbols for the C++ archive members,
    # which drags 14 imports the reference does not have.
    set(_GOLDTL_EXTERNAL_LIBS)
    set(_GOLDTL_CTL_LIBS)
    foreach(_lib IN LISTS REBREW_EXTERNAL_LIBS)
      if(_lib MATCHES "CTLFWR32")
        list(APPEND _GOLDTL_CTL_LIBS "${_lib}")
      else()
        list(APPEND _GOLDTL_EXTERNAL_LIBS "${_lib}")
      endif()
    endforeach()
    list(APPEND _GOLDTL_EXTERNAL_LIBS ${_GOLDTL_CTL_LIBS})
    target_link_libraries(europa1400gold_tl PRIVATE ${_GOLDTL_EXTERNAL_LIBS})
    # DirectX 8 import libraries the reference imports but the project does
    # not otherwise reference; vendored from the XP SP1 SDK (see
    # references/dxsdk8/VENDOR.md). Their import descriptors add DDRAW,
    # DINPUT8 and d3d8 entries to the import table when included.
    target_link_libraries(europa1400gold_tl PRIVATE
      "${PROJECT_SOURCE_DIR}/references/dxsdk8/lib/ddraw.lib"
      "${PROJECT_SOURCE_DIR}/references/dxsdk8/lib/dinput8.lib"
      "${PROJECT_SOURCE_DIR}/references/dxsdk8/lib/d3d8.lib")
    # Force the reference's import members; see layout/.../import-includes.rsp.
    target_link_options(europa1400gold_tl PRIVATE
      "@${PROJECT_SOURCE_DIR}/layout/Europa1400Gold_TL.exe/import-includes.rsp")
    # Pull the D3DX8 archive members the reference links. The list excludes the
    # members that cannot come in (amdmath.lib directive, unresolved D3DX
    # resource helpers, archive zlib colliding with the project zlib) and the
    # members whose imports the reference does not have.
    # The forced d3dx8 member list was removed on 2026-10-30: 13 of its members
    # do not appear in the reference image at all (btri, cassignment,
    # cd3dxstateblock, ceffect, cleanmesh, cparameter, cpass, createmesh,
    # ctechnique, cvalue, intersect, jdmaster, shapes), and forcing them added
    # ~190 KB of code the reference does not carry. Only loadutil.obj and
    # loadx.obj are present in the reference; they stay unlinked until their
    # CTLFWR32 globals resolve. The unused list is kept in
    # layout/Europa1400Gold_TL.exe/d3dx8-includes.rsp as evidence.
    target_include_directories(europa1400gold_tl PRIVATE
      "${PROJECT_SOURCE_DIR}/src"
    )

    # Data-only stubs cannot go through order-sources, and the CTL globals need
    # C++ mangled names, so compile that TU directly and link it with the
    # reference-present d3dx8 members after the archives. The member list lives in
    # stubs/goldtl/readd-members.cmake so the subset is reviewable in one place.
    set(_GOLDTL_CTL_STUB "${CMAKE_CURRENT_BINARY_DIR}/ctl_locale_stubs.obj")
    add_custom_command(
      OUTPUT "${_GOLDTL_CTL_STUB}"
      COMMAND "${_REBREW_GOLDTL_BIN}" build driver cl --
        /REBREW_TOOLCHAIN:msvc-6.0-sp5-pp /c /TP /MT
        "/Fo${_GOLDTL_CTL_STUB}"
        "${PROJECT_SOURCE_DIR}/stubs/goldtl/ctl_locale_stubs.cpp"
      DEPENDS "${PROJECT_SOURCE_DIR}/stubs/goldtl/ctl_locale_stubs.cpp"
      COMMENT "Compile the C++ CTL locale-global displacement (TL only)"
      VERBATIM)
    add_custom_target(goldtl_ctl_locale DEPENDS "${_GOLDTL_CTL_STUB}")
    add_dependencies(europa1400gold_tl goldtl_ctl_locale)
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
      "${PROJECT_SOURCE_DIR}/stubs/goldtl/readd-members.cmake")
    include("${PROJECT_SOURCE_DIR}/stubs/goldtl/readd-members.cmake")
    set(_GOLDTL_READD_OBJS "${_GOLDTL_CTL_STUB}")
    foreach(_member IN LISTS GOLDTL_READD_MEMBERS)
      list(APPEND _GOLDTL_READD_OBJS
        "${PROJECT_SOURCE_DIR}/.scratch/libs/d3dx8/${_member}")
    endforeach()
    target_link_libraries(europa1400gold_tl PRIVATE ${_GOLDTL_READD_OBJS})
    target_link_options(europa1400gold_tl PRIVATE
      "@${PROJECT_SOURCE_DIR}/stubs/goldtl/readd-symbols.rsp")


    # Resource section, TL only. The reference .rsrc holds RT_ICON ids 1 and 2
    # (32x32 and 16x16, 4bpp) under RT_GROUP_ICON id 101 in language 0x407.
    # Both images were extracted from original/Europa1400Gold_TL.exe; rc from
    # the msvc-6.0-sp5-pp image compiles them into a .res, and LINK builds the
    # .rsrc section from it.
    find_program(REBREW_DOCKER_BIN NAMES docker REQUIRED)
    set(_GOLDTL_RES_DIR "${CMAKE_CURRENT_BINARY_DIR}/goldtl-res")
    set(_GOLDTL_RES "${_GOLDTL_RES_DIR}/goldtl_app.res")
    add_custom_command(
      OUTPUT "${_GOLDTL_RES}"
      COMMAND "${CMAKE_COMMAND}" -E make_directory "${_GOLDTL_RES_DIR}"
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different
        "${PROJECT_SOURCE_DIR}/stubs/goldtl/res/goldtl_app.ico"
        "${PROJECT_SOURCE_DIR}/stubs/goldtl/res/goldtl_app.rc"
        "${_GOLDTL_RES_DIR}"
      COMMAND "${REBREW_DOCKER_BIN}" run --rm
        -v "${_GOLDTL_RES_DIR}:/work" -w /work
        --entrypoint wine "rebrew/msvc:6.0-sp5-pp-win32"
        /opt/msvc6.0-sp5-pp/Common/MSDev98/Bin/RC.EXE
        /fo goldtl_app.res goldtl_app.rc
      DEPENDS
        "${PROJECT_SOURCE_DIR}/stubs/goldtl/res/goldtl_app.ico"
        "${PROJECT_SOURCE_DIR}/stubs/goldtl/res/goldtl_app.rc"
      COMMENT "Compile Europa1400Gold_TL resources with rc (MSVC 6)"
      VERBATIM)
    add_custom_target(goldtl_resource DEPENDS "${_GOLDTL_RES}")
    add_dependencies(europa1400gold_tl goldtl_resource)
    target_link_libraries(europa1400gold_tl PRIVATE "${_GOLDTL_RES}")

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

# The pinned SDK must be the selected input at configure time and at each link.
foreach(_client europa1400gold europa1400gold_tl)
  if(TARGET ${_client})
    get_target_property(_client_libs ${_client} LINK_LIBRARIES)
    list(FIND _client_libs "${MSS32_ARCHIVE}" _mss32_lib_index)
    if(_mss32_lib_index EQUAL -1)
      message(FATAL_ERROR "${_client} must select the pinned Miles archive in rebrew-project.toml")
    endif()
    set_property(TARGET ${_client} APPEND PROPERTY LINK_DEPENDS
      "${MSS32_ARCHIVE}" "${PROJECT_SOURCE_DIR}/cmake/verify-mss32.cmake")
    add_custom_command(TARGET ${_client} PRE_LINK
      COMMAND "${CMAKE_COMMAND}" "-DMSS32_ARCHIVE=${MSS32_ARCHIVE}"
              -P "${PROJECT_SOURCE_DIR}/cmake/verify-mss32.cmake"
      VERBATIM)

    # Client compilation uses each target's measured profile and runtime.
    if(MSVC_FOR_DECOMP)
      if(_client STREQUAL "europa1400gold")
        set(_client_reference_target "Europa1400Gold.exe")
        set(_client_rebrew_bin "${_REBREW_GOLD_BIN}")
      else()
        set(_client_reference_target "Europa1400Gold_TL.exe")
        set(_client_rebrew_bin "${_REBREW_GOLDTL_BIN}")
      endif()
      execute_process(
        COMMAND "${_client_rebrew_bin}" binary pe --target "${_client_reference_target}" --json
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        RESULT_VARIABLE _client_timestamp_rc OUTPUT_VARIABLE _client_timestamps
        OUTPUT_STRIP_TRAILING_WHITESPACE)
      if(NOT _client_timestamp_rc EQUAL 0)
        message(FATAL_ERROR "Cannot read native ${_client_reference_target} build timestamp")
      endif()
      string(JSON _client_link_epoch GET "${_client_timestamps}" timestamp)
      string(JSON _client_reference GET "${_client_timestamps}" binary)
      if(NOT "${_client_link_epoch}" MATCHES "^[0-9]+$" OR _client_link_epoch GREATER 2147483647)
        message(FATAL_ERROR "Native Wine clock requires client timestamp in 0..2147483647")
      endif()
      string(REPLACE ";" "\\;" _client_reference "${_client_reference}")
      set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
        "${PROJECT_SOURCE_DIR}/rebrew-project.toml" "${_client_reference}")
      set_property(TARGET ${_client} PROPERTY RULE_LAUNCH_LINK
        "\"${CMAKE_COMMAND}\" -E env SOURCE_DATE_EPOCH=${_client_link_epoch}")
      target_include_directories(${_client} PRIVATE
        "${PROJECT_SOURCE_DIR}/src/Develop"
        "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3")
      target_compile_options(${_client} PRIVATE
        "/REBREW_TOOLCHAIN:msvc-6.0-sp5-pp")
      target_link_options(${_client} PRIVATE
        "/REBREW_TOOLCHAIN:msvc-6.0-sp5-pp"
        # shortcut: retain the game graph while WinMain is a stub; remove when its real references are restored.
        "/OPT:NOREF")
      if(_client STREQUAL "europa1400gold")
        set_property(TARGET ${_client} PROPERTY MSVC_RUNTIME_LIBRARY "")
        target_compile_options(${_client} PRIVATE "/ML")
      else()
        set_property(TARGET ${_client} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")
      endif()
      if(REBREW_ALLOW_NAKED)
        target_compile_definitions(${_client} PRIVATE REBREW_ALLOW_NAKED=1)
      endif()
      target_link_options(${_client} PRIVATE
        "/MAP:$<TARGET_FILE_DIR:${_client}>/$<TARGET_FILE_BASE_NAME:${_client}>.map")
    endif()
  endif()
endforeach()

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
function(rebrew_apply_cflags target_name cmake_target source_list suffix)
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
            --cmake-target "${cmake_target}"
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
    rebrew_apply_cflags("server.dll" server_dll SERVER_SOURCES "")
  endif()
  if(TARGET europa1400gold)
    rebrew_apply_cflags("Europa1400Gold.exe" europa1400gold GOLD_SOURCES "-gold")
  endif()
  if(TARGET europa1400gold_tl)
    rebrew_apply_cflags("Europa1400Gold_TL.exe" europa1400gold_tl GOLDTL_SOURCES "-goldtl")
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
