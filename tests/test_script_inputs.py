"""Retained recipes use canonical readers without changing allocation policy."""

import json
import runpy
from pathlib import Path

import pytest
from rebrew.config import ConfigWarning

ROOT = Path(__file__).resolve().parents[1]
load_items = runpy.run_path(ROOT / "scripts/gen_bss_layout.py")["load_items"]
publics = runpy.run_path(ROOT / "stubs/linked_manifest.py")["publics"]


def test_bss_reads_data_fragments_and_only_sized_server_rows(tmp_path: Path) -> None:
    (tmp_path / "rebrew-project.toml").write_text(
        '[targets."server.dll"]\nbinary = "server.dll"\nmodule = "SERVER"\n'
    )
    (tmp_path / "rebrew-data.toml").write_text(
        'format = 2\n["SERVER.0x10034610"]\nname = "first"\nsize = 4\n'
        '["GOLD.0x10034614"]\nname = "other_target"\nsize = 4\n'
        '["SERVER.0x10034618"]\nname = "unknown_extent"\n'
        '["SERVER.0x1003461c"]\nname = "g_before_old"\nsize = 4\n'
    )
    fragments = tmp_path / "rebrew-data.d"
    fragments.mkdir()
    (fragments / "test.toml").write_text(
        'format = 2\n["SERVER.0x10034614"]\nname = "second"\nsize = 4\ntype = "int"\n'
    )
    with pytest.warns(ConfigWarning, match="target binary not found"):
        rows = load_items(tmp_path)
    assert rows == [
        {"va": 0x10034610, "name": "first", "size": 4, "type": ""},
        {"va": 0x10034614, "name": "second", "size": 4, "type": "int"},
    ]


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
