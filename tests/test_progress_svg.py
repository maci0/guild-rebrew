"""The README must not count semantic or assembly verdicts as C recovery."""

import runpy
from pathlib import Path
from xml.etree import ElementTree

import pytest

render = runpy.run_path(Path(__file__).resolve().parents[1] / "scripts/progress_svg.py")["render"]
render_map = runpy.run_path(Path(__file__).resolve().parents[1] / "scripts/progress_svg.py")[
    "render_map"
]


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


def test_function_map_uses_address_order_and_distinct_verdicts() -> None:
    root = ElementTree.fromstring(
        render_map(
            {
                "game<&>.exe": [
                    (0x403000, "LIBRARY"),
                    (0x401000, "EXACT"),
                    (0x405000, "PROVEN"),
                    (0x402000, "ASSEMBLY"),
                    (0x404000, "PENDING"),
                ]
            },
            "2026-10-18",
        )
    )
    paths = root.findall(".//{http://www.w3.org/2000/svg}path")
    assert sum(p.attrib["d"].count("M") for p in paths) == 5
    assert len({p.attrib["fill"] for p in paths}) == 5
    assert paths[0].attrib["d"].startswith("M24 ")
    assert paths[1].attrib["d"].startswith("M29 ")
    text = " ".join(root.itertext())
    assert "game<&>.exe" in text
    assert "5 blocks, including libraries" in text
