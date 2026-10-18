"""The README must not count semantic or assembly verdicts as C recovery."""

import runpy
from pathlib import Path
from xml.etree import ElementTree

import pytest

render = runpy.run_path(Path(__file__).resolve().parents[1] / "scripts/progress_svg.py")["render"]


def test_progress_separates_assembly_and_semantic_verdicts() -> None:
    target = {
        "functions": {"total": 10},
        "status": {"EXACT": 4, "RELOC": 3, "PROVEN": 2, "STUB": 1},
        "naked_matched": 2,
        "file": {"built": "test.exe", "total_bytes": 100, "matched_bytes": 99},
    }
    report = {"targets": {"test<&>.exe": target}}
    root = ElementTree.fromstring(render(report, "2026-10-18"))
    text = " ".join(root.itertext())
    assert "test<&>.exe" in text
    assert "50.0%" in text
    assert "5 / 10 functions matched by C source" in text
    assert "2 assembly matches · 3 functions still to match" in text
    assert "Raw file differs · comparison scaffold" in text
    target["file"]["matched_bytes"] = 100
    assert "Raw file equals reference" in render(report, "2026-10-18")
    target["naked_matched"] = 8
    with pytest.raises(ValueError, match="Inconsistent function counts"):
        render(report, "2026-10-18")
