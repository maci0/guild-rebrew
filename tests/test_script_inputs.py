"""Linked manifests keep project, archive and placeholder attribution separate."""

import json
import runpy
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
publics = runpy.run_path(ROOT / "stubs/linked_manifest.py")["publics"]


def test_manifest_keeps_project_and_archive_origins() -> None:
    assert publics(
        " Address         Publics by Value              Rva+Base Lib:Object\n"
        " 0001:00000000 _stub 00401000 f symbol_stubs.c.obj\n"
        " 0001:00000010 _WinMain@16 00401010 f GOLD.main.c.obj\n"
        " 0002:00000000 _IID_IDirect3D8 00402000 d3dx8:init.obj\n"
        " 0002:00000010 __imp__ExitProcess@4 00402010 KERNEL32:KERNEL32.dll\n"
        " 0002:00000014 _common 00402014 <common>\n"
    ) == [
        ("_stub", "symbol_stubs.c.obj"),
        ("_WinMain@16", "GOLD.main.c.obj"),
        ("_IID_IDirect3D8", "d3dx8:init.obj"),
    ]


def test_manifest_counts_separate_abi_placeholders(tmp_path: Path, monkeypatch) -> None:
    map_path = tmp_path / "client.map"
    map_path.write_text(
        " Address         Publics by Value              Rva+Base Lib:Object\n"
        " 0001:00000000 _stub 00401000 f symbol_stubs.c.obj\n"
        " 0001:00000010 @variant@8 00401010 f abi_stubs.c.obj\n"
        " 0001:00000020 _WinMain@16 00401020 f GOLD.main.c.obj\n"
    )
    output = tmp_path / "symbols.json"
    monkeypatch.setattr("sys.argv", ["linked_manifest.py", str(map_path), str(output)])
    runpy.run_path(ROOT / "stubs/linked_manifest.py", run_name="__main__")
    document = json.loads(output.read_text())
    assert document["stub_symbol_count"] == 2
    assert document["stub_symbols"] == ["@variant@8", "_stub"]
    assert document["stub_objects"] == ["abi_stubs.c.obj", "symbol_stubs.c.obj"]
    assert document["checked_symbols"]["_WinMain@16"] == "GOLD.main.c.obj"
