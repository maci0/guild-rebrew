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
  file(GLOB_RECURSE SERVER_SOURCES
    "src/server.dll/*.c"
  )

  list(FILTER SERVER_SOURCES INCLUDE REGEX "\\.c$")
  list(FILTER SERVER_SOURCES EXCLUDE REGEX "/crt/")
  list(FILTER SERVER_SOURCES EXCLUDE REGEX "/zlib/")
  # unknown/crc32.c is the reversed copy of zlib's crc32 (0x100011f0). It stays
  # in the tree for `rebrew test`, but linking it beside references/zlib-1.1.3/
  # crc32.c defines _crc32 twice.
  list(FILTER SERVER_SOURCES EXCLUDE REGEX "/unknown/crc32\\.c$")
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
  # The files kept below are NOT kept because their bodies are ours. Each one
  # exists to displace a specific LIBCMT object whose side effects the
  # reference does not have:
  #   sbh_globals/sbh_pool/sbh_aliases  displace sbheap.obj, which reaches
  #       IsBadWritePtr through __imp__IsBadWritePtr@8. A local IsBadWritePtr
  #       does not help: the function name is never referenced, only the
  #       indirect slot, which still resolves from KERNEL32.lib. crt_heap.c
  #       comes along because sbh_aliases.c calls its __sbh_heap_init body.
  #   mlock.c                            displaces mlock.obj (FatalAppExitA).
  #   amsg_exit.c                        keeps crt0msg.obj out. That object
  #       contributes the runtime-error message strings, which rdata_restore.c
  #       also supplies, so linking both overshoots .rdata by 0x320.
  #       Deleting them from the blob and letting the library provide them was
  #       tried and does not work: the original packs those strings into 0x2eb
  #       bytes, while the linker places crt0msg's 23 separate COMDATs with
  #       per-section padding into 0x32b. The content is then correct and
  #       unduplicated, but .rdata is 0x40 long and postlink still refuses it.
  #       Only the blob reproduces the original's tighter packing, so the blob
  #       keeps the strings and crt0msg.obj stays out of the link.
  #   crt_init.c                         NOT in this list and not compiled:
  #       LIBCMT's dllcrt0.obj already supplies __CRT_INIT, which dllmain.c
  #       calls. The reversed body stays in the tree for reference only.
  # Dropping any of these was tried and measured; each one regresses either the
  # import set or the .rdata size.
  list(FILTER SERVER_SOURCES EXCLUDE REGEX "/crt_region/")
  set(_CRT_REGION_KEEP
    "${PROJECT_SOURCE_DIR}/src/server.dll/crt_region/crt_imports.c"
    "${PROJECT_SOURCE_DIR}/src/server.dll/crt_region/data_restore.c"
    "${PROJECT_SOURCE_DIR}/src/server.dll/crt_region/data_globals.c"
    "${PROJECT_SOURCE_DIR}/src/server.dll/crt_region/rdata_restore.c"
    "${PROJECT_SOURCE_DIR}/src/server.dll/crt_region/dllmain.c"
    "${PROJECT_SOURCE_DIR}/src/server.dll/crt_region/initterm.c"
    "${PROJECT_SOURCE_DIR}/src/server.dll/crt_region/mlock.c"
    "${PROJECT_SOURCE_DIR}/src/server.dll/crt_region/sbh_globals.c"
    "${PROJECT_SOURCE_DIR}/src/server.dll/crt_region/sbh_pool.c"
    "${PROJECT_SOURCE_DIR}/src/server.dll/crt_region/sbh_aliases.c"
    "${PROJECT_SOURCE_DIR}/src/server.dll/crt_region/crt_heap.c"
    "${PROJECT_SOURCE_DIR}/src/server.dll/crt_region/amsg_exit.c"
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
      --first-va adler32.c=0x10001000
      --first-va crc32.c=0x100011f0
      --first-va deflate.c=0x10001330
      --first-va infblock.c=0x10003d20
      --first-va infcodes.c=0x10004b80
      --first-va inffast.c=0x10005390
      --first-va inflate.c=0x10005720
      --first-va inftrees.c=0x10005d00
      --first-va infutil.c=0x10006440
      --first-va trees.c=0x10006ec0
      --first-va trees2.c=0x10008800
      --first-va zutil.c=0x100092e0
      --exclude gzio.c
      --exclude compress.c --exclude uncompr.c
    OUTPUT_VARIABLE ORDERED_SOURCES
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE ORDER_RC)
  if(NOT ORDER_RC EQUAL 0)
    message(FATAL_ERROR "rebrew order-sources failed")
  endif()
  string(REPLACE "\n" ";" SERVER_SOURCES "${ORDERED_SOURCES}")

  # Link crt_imports.obj FIRST: its /include directives allocate IAT slots in
  # the original binary's exact import order. If any other object's code
  # references an import earlier, the linker gives that import an earlier slot
  # and the whole IAT layout shifts (kernel32 @ 0x24000 must stay exact).
  set(_CRT_IMPORTS "${PROJECT_SOURCE_DIR}/src/server.dll/crt_region/crt_imports.c")
  list(REMOVE_ITEM SERVER_SOURCES "${_CRT_IMPORTS}")
  list(INSERT SERVER_SOURCES 0 "${_CRT_IMPORTS}")

  # Link the .data gap TU next: it declares the raw .data bytes our game TUs
  # do not emit (original [0x3000:0xe000]), so the raw link's .data rsz reaches
  # 0xe000 and the section-derived header fields fall out of the link.
  set(_DATA_GAP "${PROJECT_SOURCE_DIR}/src/server.dll/crt_region/data_restore.c")
  list(REMOVE_ITEM SERVER_SOURCES "${_DATA_GAP}")
  list(INSERT SERVER_SOURCES 1 "${_DATA_GAP}")

  add_library(server_dll SHARED ${SERVER_SOURCES} ${LINK_STUBS})

  target_include_directories(server_dll PRIVATE
    "${PROJECT_SOURCE_DIR}/src/server.dll"
    "${PROJECT_SOURCE_DIR}/references/zlib-1.1.3"
  )

  # System import libs resolve inside the toolchain image via LIB
  # (Z:\opt\msvc6.0\VC98\Lib); WS2_32/WINMM are not in CMake's default set.
  # LIBCMT is the release static CRT the original binary links against: the
  # stock library from the toolchain image, resolved via LIB. The CRT is
  # linked, not reversed.
  #
  # It must stay stock. The build previously used a hand-stripped copy under
  # .scratch/ with 22 objects removed, which was both gitignored (so the build
  # was unreproducible on a fresh clone) and unnecessary. The objects that
  # actually have to lose the link are sbheap.obj, validate.obj and mlock.obj,
  # because they import IsBadWritePtr / FatalAppExitA and the original
  # server.dll has neither import. The crt_region files sbh_aliases.c,
  # sbh_pool.c and mlock.c define those symbols locally, so the linker never
  # pulls the LIBCMT versions and the import set matches the reference.
  #
  # Never patch a library to make the link work. Displace the offending object
  # with a local definition, as above, or change what references it. A doctored
  # .lib cannot be reproduced from a clean checkout and hides the very
  # duplication `rebrew lib-match` exists to catch; that check refuses to run
  # if the extracted copy differs from the toolchain image's.
  target_link_libraries(server_dll PRIVATE
    KERNEL32.lib
    USER32.lib
    WS2_32.lib
    WINMM.lib
    LIBCMT.lib
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

  if(REBREW_ALLOW_NAKED)
    target_compile_definitions(server_dll PRIVATE REBREW_ALLOW_NAKED=1)
    message(STATUS "server.dll: REBREW_ALLOW_NAKED=1 (naked+__asm fenced for byte-identical build)")
  endif()
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
    # /FORCE:MULTIPLE is still required for exactly two symbols. dllmain.c
    # calls _CRT_INIT, which the linker resolves from LIBCMT dllcrt0.obj, and
    # that object also defines ___app_type and __amsg_exit. The game overrides
    # both (amsg_exit.c is the reversed 0x1001ba71), so they collide. Dropping
    # the flag fails with LNK2005 on those two until dllcrt0.obj is replaced.
    # Every other duplicate has been resolved; the link is otherwise clean.
    if(REBREW_DEBUG_INFO)
      target_compile_options(server_dll PRIVATE /Z7)
      target_link_options(server_dll PRIVATE "/OPT:NOREF" "/debug" "/FORCE:MULTIPLE" "/NODEFAULTLIB:LIBCMTD" "/ENTRY:DllMain@12" "/INCLUDE:___ld12mul" "/INCLUDE:__except_handler3" "/INCLUDE:___dtold" "/INCLUDE:_wctomb" "/INCLUDE:__setmode_lk" "/INCLUDE:__strdup" "/INCLUDE:__NLG_Notify" "/INCLUDE:__ms_p5_mp_test_fdiv")
    else()
      target_link_options(server_dll PRIVATE "/OPT:NOREF" "/FORCE:MULTIPLE" "/NODEFAULTLIB:LIBCMTD" "/ENTRY:DllMain@12" "/INCLUDE:___ld12mul" "/INCLUDE:__except_handler3" "/INCLUDE:___dtold" "/INCLUDE:_wctomb" "/INCLUDE:__setmode_lk" "/INCLUDE:__strdup" "/INCLUDE:__NLG_Notify" "/INCLUDE:__ms_p5_mp_test_fdiv")
    endif()
    # Post-link (rebrew postlink --layout layout/server.dll): converge the
    # linked DLL onto the original's layout byte-for-byte, purely from the
    # committed text layout package.  imports: the MSVC6 linker's IAT slot
    # order is hash-driven and cannot be forced for all DLLs via /include,
    # so the slot order (and the .text operands pointing at the slots) is
    # rewritten to the reference's.  data: grows .data to 0xe000 (copying
    # the reference's bytes — the linker's .data COMDAT order is also
    # hash-driven), rewrites the remaining .text data operands / E8-E9
    # targets, and replaces .reloc.  pe-metadata: normalizes the DOS
    # stub/e_lfanew, TimeDateStamp, CheckSum, .data VirtualSize (BSS tail),
    # .reloc VA and SizeOfImage.  Content is untouched.
    # The section-geometry rules this depends on (raw-size rounding, the
    # .rdata prefix gate, the .data gap blob's sizing) are measured and
    # written up in docs/msvc6-link-layout.md.
    add_custom_command(TARGET server_dll POST_BUILD
      # Converge the linked DLL onto the original's layout WITHOUT needing the
      # original binary at build time: the text-only layout package
      # (layout/<target>/) from 'rebrew gen-layout' carries the reference as
      # plain-text metadata (no binary blobs), and 'rebrew postlink --layout'
      # reconstructs the reference from it.  Regenerate the package whenever
      # the original changes (rebrew gen-layout --target server.dll) and
      # commit it.
      COMMAND ${CMAKE_COMMAND} -E echo "Converging layout onto reference (rebrew postlink --layout)"
      COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:server_dll>" "${PROJECT_SOURCE_DIR}/.scratch/server.dll.prelayout"
      COMMAND rebrew postlink "$<TARGET_FILE:server_dll>"
              --layout "${PROJECT_SOURCE_DIR}/layout/server.dll"
      VERBATIM)
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
