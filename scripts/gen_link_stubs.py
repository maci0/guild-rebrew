#!/usr/bin/env python3
"""Generate link_stubs.c from unresolved linker symbols.

Usage:
    # Build without link_stubs, capture linker errors, generate stubs:
    python scripts/gen_link_stubs.py

    # Or pipe linker output directly:
    cmake --build build -j8 2>&1 | python scripts/gen_link_stubs.py --from-stdin

The script:
1. Temporarily removes link_stubs.c from the CMake build
2. Builds to collect unresolved external symbols from MSVC linker
3. Parses extern declarations from source files for type info
4. Generates a new link_stubs.c with correct types and stub bodies

Special cases handled:
- gm_* forwarding wrappers (call the non-gm_ version)
- thread_proc (stdcall wrapper calling ServerMainThread)
- String literal globals (s_* with initializer)
- GetErrnoPointer (returns pointer to static errno)
- Conflicting extern types (first-seen wins, with warning)
"""

import argparse
import glob
import os
import re
import subprocess
import sys
import textwrap
from collections import OrderedDict
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parent.parent
SRC_DIR = PROJECT_ROOT / "src" / "server.dll"
LINK_STUBS_PATH = PROJECT_ROOT / "src" / "link_stubs.c"
CMAKELISTS_PATH = PROJECT_ROOT / "CMakeLists.txt"

# Symbols that need hand-written implementations (not auto-generable)
SPECIAL_FUNCTIONS = {
    "gm_AllocGebaeude": {
        "forward_to": "AllocGebaeude",
        "decl": "extern char* __cdecl AllocGebaeude(int, int);",
        "impl": textwrap.dedent("""\
            char* __cdecl gm_AllocGebaeude(int a, int b)
            {
            \treturn AllocGebaeude(a, b);
            }"""),
    },
    "gm_SubObjekt": {
        "forward_to": "SubObjekt",
        "decl": "extern int __cdecl SubObjekt(void*, unsigned int, int);",
        "impl": textwrap.dedent("""\
            int __cdecl gm_SubObjekt(void* a, unsigned int b, int c)
            {
            \treturn SubObjekt(a, b, c);
            }"""),
    },
    "gm_DeallocEntity": {
        "forward_to": "DeallocEntity",
        "decl": "extern void __cdecl DeallocEntity(unsigned int, int);",
        "impl": textwrap.dedent("""\
            void __cdecl gm_DeallocEntity(unsigned int a, int b)
            {
            \tDeallocEntity(a, b);
            }"""),
    },
    "gm_KannObjektHergestellt": {
        "forward_to": "KannObjektHergestellt",
        "decl": "extern int __cdecl KannObjektHergestellt(char*, int, int);",
        "impl": textwrap.dedent("""\
            int __cdecl gm_KannObjektHergestellt(char* a, int b, int c)
            {
            \treturn KannObjektHergestellt(a, b, c);
            }"""),
    },
    "thread_proc": {
        "decl": "extern int __cdecl ServerMainThread(void*);",
        "impl": textwrap.dedent("""\
            int __stdcall thread_proc(void* param)
            {
            \treturn ServerMainThread(param);
            }"""),
    },
    "GetErrnoPointer": {
        "impl": textwrap.dedent("""\
            static int stub_errno_val = 0;

            int* __cdecl GetErrnoPointer(void)
            {
            \treturn &stub_errno_val;
            }"""),
    },
}


def get_unresolved_symbols_from_build():
    """Build without link_stubs.c and return set of unresolved symbol names."""
    cmake_content = CMAKELISTS_PATH.read_text()

    # Temporarily remove link_stubs from CMake
    modified = cmake_content.replace(
        "add_library(server_dll SHARED ${SERVER_SOURCES} ${ZLIB_SOURCES} ${LINK_STUBS})",
        "add_library(server_dll SHARED ${SERVER_SOURCES} ${ZLIB_SOURCES})",
    )

    if modified == cmake_content:
        print("ERROR: Could not find link_stubs line in CMakeLists.txt", file=sys.stderr)
        sys.exit(1)

    CMAKELISTS_PATH.write_text(modified)
    try:
        result = subprocess.run(
            ["cmake", "--build", "build", "-j8"],
            capture_output=True,
            text=True,
            cwd=PROJECT_ROOT,
            timeout=300,
        )
        output = result.stdout + result.stderr
    finally:
        # Always restore
        CMAKELISTS_PATH.write_text(cmake_content)

    return parse_unresolved_symbols(output)


def parse_unresolved_symbols(linker_output):
    """Parse MSVC LNK2001/LNK2019 errors to extract unresolved symbol names."""
    symbols = set()
    for line in linker_output.splitlines():
        m = re.search(r"error LNK200[19]: unresolved external symbol (\S+)", line)
        if m:
            symbols.add(m.group(1))
    return symbols


def demangle_cdecl(mangled):
    """Strip MSVC cdecl name mangling: _name -> name, _name@N -> name."""
    name = mangled
    if name.startswith("_"):
        name = name[1:]
    # stdcall: _name@N
    name = re.sub(r"@\d+$", "", name)
    return name


def collect_extern_info(src_dir):
    """Parse extern declarations from all source files.

    Returns dict mapping symbol_name -> {
        'type': str (return type or var type),
        'is_func': bool,
        'calling_conv': str or None,
        'params': str or None (parameter list including parens),
        'full_decl': str (the raw extern line),
        'is_array': bool,
        'array_size': str or None,
    }
    """
    externs = {}  # symbol_name -> info dict

    for src_file in sorted(glob.glob(str(src_dir / "**" / "*.c"), recursive=True)):
        with open(src_file) as f:
            for line in f:
                line = line.strip()
                if not line.startswith("extern"):
                    continue
                line = re.sub(r"/\*.*?\*/", "", line).strip()
                line = line.rstrip("; ").strip()

                info = parse_extern_decl(line)
                if info and info["name"] not in externs:
                    externs[info["name"]] = info

    return externs


def parse_extern_decl(decl):
    """Parse a single extern declaration line into structured info."""
    rest = decl[len("extern") :].strip()

    # Function with calling convention: TYPE __cdecl NAME(PARAMS)
    m = re.match(
        r"(.*?)\b(__cdecl|__stdcall)\s+(\w+)\s*(\(.*)",
        rest,
    )
    if m:
        ret_type = m.group(1).strip()
        cc = m.group(2)
        name = m.group(3)
        params = m.group(4).rstrip(")")
        if params.endswith("("):
            params += ")"
        elif not params.endswith(")"):
            params += ")"
        return {
            "name": name,
            "type": ret_type,
            "is_func": True,
            "calling_conv": cc,
            "params": params,
            "full_decl": decl,
            "is_array": False,
            "array_size": None,
        }

    # Function without calling convention: TYPE NAME(PARAMS)
    # (e.g. "void func_1001a060(void)")
    m = re.match(r"(.*?)\b(\w+)\s*(\(.*)", rest)
    if m and "(" in m.group(3):
        ret_type = m.group(1).strip()
        name = m.group(2)
        params = m.group(3)
        if not params.endswith(")"):
            params += ")"
        # Skip if 'name' is a type keyword
        if name in ("int", "char", "void", "short", "float", "double", "unsigned", "struct"):
            pass
        else:
            return {
                "name": name,
                "type": ret_type,
                "is_func": True,
                "calling_conv": None,
                "params": params,
                "full_decl": decl,
                "is_array": False,
                "array_size": None,
            }

    # Variable with array: TYPE NAME[SIZE]
    m = re.match(r"(.*?)\b(\w+)\s*(\[.*?\])", rest)
    if m:
        var_type = m.group(1).strip()
        name = m.group(2)
        arr = m.group(3)
        if name not in ("int", "char", "void", "short", "float", "double", "unsigned", "struct"):
            # Extract array size
            size_m = re.search(r"\[(\d+)\]", arr)
            return {
                "name": name,
                "type": var_type,
                "is_func": False,
                "calling_conv": None,
                "params": None,
                "full_decl": decl,
                "is_array": True,
                "array_size": size_m.group(1) if size_m else "1",
            }

    # Simple variable: TYPE NAME
    m = re.match(r"(.*?)\b(\w+)\s*$", rest)
    if m:
        var_type = m.group(1).strip()
        name = m.group(2)
        if name not in ("int", "char", "void", "short", "float", "double", "unsigned", "struct"):
            return {
                "name": name,
                "type": var_type,
                "is_func": False,
                "calling_conv": None,
                "params": None,
                "full_decl": decl,
                "is_array": False,
                "array_size": None,
            }

    return None


def simplify_type_for_stub(type_str):
    """Simplify complex types (structs, typedefs) to basic C89 types for stubs.

    We can't use struct types or custom typedefs in link_stubs.c because
    those types aren't defined there. Map them to compatible basic types.
    """
    # Custom struct types -> basic types
    if re.match(r"struct\s+\w+\*", type_str):
        return "void*"
    if re.match(r"struct\s+\w+", type_str):
        return "int"

    # Named types we know about
    known_types = {
        "ENT": "int",
        "Record*": "int*",
        "SlotEntry": "int",
        "WORD*": "unsigned short*",
        "WORD": "unsigned short",
        "DWORD": "unsigned int",
        "LPVOID": "void*",
        "LPDWORD": "unsigned int*",
        "dispatch_fn": "int",
        "handler_func": "int",
        "undefined *": "void*",
        "undefined*": "void*",
        "uint": "unsigned int",
        "ushort": "unsigned short",
        "ushort*": "unsigned short*",
        "uint*": "unsigned int*",
        "ulong": "unsigned long",
        "ulong*": "unsigned long*",
        "uchar": "unsigned char",
        "uchar*": "unsigned char*",
    }
    for k, v in known_types.items():
        if type_str == k:
            return v

    # Catch-all: unknown single-word types that aren't C primitives
    c_primitives = {
        "int",
        "char",
        "short",
        "long",
        "float",
        "double",
        "void",
        "unsigned",
        "signed",
        "const",
    }
    base = type_str.rstrip("*").strip()
    tokens = base.split()
    if len(tokens) == 1 and tokens[0] not in c_primitives:
        if "*" in type_str:
            return "void*"
        return "int"

    return type_str


def ensure_param_names(params_str):
    """MSVC6 requires parameter names in definitions, not just types.

    Transforms '(int, char*, void*)' -> '(int a, char* b, void* c)'
    Leaves already-named params and '(void)' untouched.
    """
    inner = params_str.strip()
    if inner.startswith("("):
        inner = inner[1:]
    if inner.endswith(")"):
        inner = inner[:-1]
    inner = inner.strip()

    if not inner or inner == "void" or inner == "...":
        return params_str

    parts = []
    depth = 0
    current = ""
    for ch in inner:
        if ch == "(":
            depth += 1
            current += ch
        elif ch == ")":
            depth -= 1
            current += ch
        elif ch == "," and depth == 0:
            parts.append(current.strip())
            current = ""
        else:
            current += ch
    if current.strip():
        parts.append(current.strip())

    param_names = "abcdefghijklmnop"
    result_parts = []
    for i, part in enumerate(parts):
        if part == "...":
            result_parts.append(part)
            continue
        if part == "void" and len(parts) == 1:
            result_parts.append(part)
            continue

        tokens = part.split()
        has_name = False
        if len(tokens) >= 2:
            last = tokens[-1]
            if re.match(r"^[a-zA-Z_]\w*$", last) and last not in (
                "int",
                "char",
                "short",
                "long",
                "float",
                "double",
                "void",
                "unsigned",
                "signed",
                "const",
                "struct",
            ):
                has_name = True
            if last.startswith("*"):
                has_name = False
        if part.endswith("*"):
            has_name = False

        if not has_name:
            name = param_names[i] if i < len(param_names) else f"p{i}"
            result_parts.append(f"{part} {name}")
        else:
            result_parts.append(part)

    return "(" + ", ".join(result_parts) + ")"


def make_return_value(ret_type):
    """Generate appropriate return value for a stub function."""
    rt = ret_type.strip()
    if rt == "void":
        return None
    if "*" in rt:
        return "(void*) 0"
    if rt == "float":
        return "0.0f"
    if rt == "double":
        return "0.0"
    if rt in ("char", "short", "unsigned char", "unsigned short"):
        return "0"
    return "0"


def generate_link_stubs(unresolved_symbols, extern_info):
    """Generate the complete link_stubs.c content."""
    lines = []

    # Header
    lines.append("/* link_stubs.c - Stub definitions for unresolved external symbols.")
    lines.append(" * AUTO-GENERATED by scripts/gen_link_stubs.py")
    lines.append(" * These are NOT part of the rebrew matching pipeline - rebrew test")
    lines.append(" * compiles individual files and does not use this file.")
    lines.append(" *")
    lines.append(" * DO NOT edit manually. Regenerate with:")
    lines.append(" *   python scripts/gen_link_stubs.py")
    lines.append(" */")
    lines.append("")

    # Demangle all symbols and categorize
    demangled = {}
    for sym in unresolved_symbols:
        name = demangle_cdecl(sym)
        demangled[name] = sym

    # Categorize symbols
    globals_list = []
    functions_list = []
    string_globals = []
    special_list = []

    for name in sorted(demangled.keys()):
        if name in SPECIAL_FUNCTIONS:
            special_list.append(name)
            continue

        info = extern_info.get(name)

        if name.startswith("s_"):
            string_globals.append(name)
            continue

        if info and info["is_func"]:
            functions_list.append(name)
        elif info and not info["is_func"]:
            globals_list.append(name)
        else:
            # No extern info found - guess from naming conventions
            # func_*, FUN_*, sub_* are functions; everything else is a global
            if re.match(
                r"(func_|FUN_|sub_|cleanup_|check_|compute_|create_|find_|free_|get_|search_|setup_|locked_|rand_|crt_|debug_|log_|assert_|game_|stream_|mem_|write_|entity_|another_|compress_|classify|RecvGameSavegame|FreeCommandBuffer|FreeHeapBlockWithRuntimeLock|WriteFileBufferLocked|RandomBelow)",
                name,
            ):
                functions_list.append(name)
            else:
                globals_list.append(name)

    # --- Emit global variables ---
    lines.append("/* Global variable stubs */")
    for name in sorted(globals_list):
        info = extern_info.get(name)
        if info:
            var_type = simplify_type_for_stub(info["type"])
            if info["is_array"]:
                size = info["array_size"] or "1"
                lines.append(f"{var_type} {name}[{size}];")
            else:
                if name == "pfn_GetTickCount":
                    lines.append(f"{var_type} {name} = 0;")
                else:
                    lines.append(f"{var_type} {name};")
        else:
            # Fallback: int for unknown globals
            lines.append(f"int {name};")

    lines.append("")

    # --- Emit string literal globals ---
    if string_globals:
        lines.append("/* String literal globals */")
        for name in sorted(string_globals):
            info = extern_info.get(name)
            if info and info["is_array"]:
                size = info["array_size"] or "1"
                lines.append(f'char {name}[{size}] = "";')
            else:
                lines.append(f'char {name}[1] = "";')
        lines.append("")

    # --- Emit special functions (gm_ wrappers, thread_proc, GetErrnoPointer) ---
    if special_list:
        lines.append("/* Special forwarding stubs */")
        for name in sorted(special_list):
            spec = SPECIAL_FUNCTIONS[name]
            if "decl" in spec:
                lines.append(spec["decl"])
                lines.append("")
            lines.append(spec["impl"])
            lines.append("")

    # --- Emit function stubs ---
    lines.append("/* Function stubs */")
    for name in sorted(functions_list):
        info = extern_info.get(name)
        if info and info["is_func"]:
            ret_type = simplify_type_for_stub(info["type"])
            cc = info["calling_conv"] or "__cdecl"
            params = info["params"] if info["params"] else "(void)"

            params = re.sub(r"struct\s+\w+\*", "void*", params)
            # Simplify non-C89 types in parameters
            params = re.sub(r'\buint\b', 'unsigned int', params)
            params = re.sub(r'\bushort\b', 'unsigned short', params)
            params = re.sub(r'\bulong\b', 'unsigned long', params)
            params = re.sub(r'\buchar\b', 'unsigned char', params)
            params = ensure_param_names(params)

            ret_val = make_return_value(ret_type)
            if ret_val is None:
                lines.append(f"void {cc} {name}{params}")
                lines.append("{")
                lines.append("}")
            else:
                lines.append(f"{ret_type} {cc} {name}{params}")
                lines.append("{")
                lines.append(f"\treturn {ret_val};")
                lines.append("}")
        else:
            # No type info - default to int __cdecl name()
            lines.append(f"int __cdecl {name}(void)")
            lines.append("{")
            lines.append("\treturn 0;")
            lines.append("}")
        lines.append("")

    return "\n".join(lines) + "\n"


def main():
    parser = argparse.ArgumentParser(description="Generate link_stubs.c from unresolved symbols")
    parser.add_argument(
        "--from-stdin",
        action="store_true",
        help="Read linker output from stdin instead of building",
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Print generated content to stdout instead of writing file",
    )
    args = parser.parse_args()

    # Step 1: Get unresolved symbols
    if args.from_stdin:
        linker_output = sys.stdin.read()
        unresolved = parse_unresolved_symbols(linker_output)
    else:
        print("Building without link_stubs.c to find unresolved symbols...", file=sys.stderr)
        unresolved = get_unresolved_symbols_from_build()

    if not unresolved:
        print("No unresolved symbols found. Is the build configured correctly?", file=sys.stderr)
        sys.exit(1)

    print(f"Found {len(unresolved)} unresolved symbols", file=sys.stderr)

    # Step 2: Collect extern info from source files
    print("Parsing extern declarations from source files...", file=sys.stderr)
    extern_info = collect_extern_info(SRC_DIR)
    print(f"Found {len(extern_info)} unique extern declarations", file=sys.stderr)

    # Step 3: Generate
    content = generate_link_stubs(unresolved, extern_info)

    # Demangled symbol count
    demangled = set()
    for sym in unresolved:
        demangled.add(demangle_cdecl(sym))
    print(f"Generated stubs for {len(demangled)} unique symbols", file=sys.stderr)

    if args.dry_run:
        print(content)
    else:
        LINK_STUBS_PATH.write_text(content)
        print(f"Written to {LINK_STUBS_PATH}", file=sys.stderr)

    # Step 4: Verify by rebuilding
    if not args.dry_run and not args.from_stdin:
        print("Rebuilding with generated stubs...", file=sys.stderr)
        result = subprocess.run(
            ["cmake", "--build", "build", "-j8"],
            capture_output=True,
            text=True,
            cwd=PROJECT_ROOT,
            timeout=300,
        )
        if result.returncode == 0:
            print("Build successful!", file=sys.stderr)
        else:
            # Check for remaining unresolved
            remaining = parse_unresolved_symbols(result.stdout + result.stderr)
            if remaining:
                print(f"ERROR: {len(remaining)} symbols still unresolved:", file=sys.stderr)
                for s in sorted(remaining):
                    print(f"  {s}", file=sys.stderr)
                sys.exit(1)
            else:
                print("Build failed (not linker errors):", file=sys.stderr)
                # Print last 20 lines of output
                for line in (result.stdout + result.stderr).splitlines()[-20:]:
                    print(f"  {line}", file=sys.stderr)
                sys.exit(1)


if __name__ == "__main__":
    main()
