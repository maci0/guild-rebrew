"""Render the README progress map from synthetic states and read the SVG back.

Drives scripts/progress_svg.render() and asserts on the markup it ships: each
state's squares carry its brand class, library code is an outline, the legend
names every state a shared fill carries, and both themes are in the sheet.
"""

from __future__ import annotations

import importlib.util
import xml.etree.ElementTree as ET
from pathlib import Path
from types import ModuleType

ROOT = Path(__file__).resolve().parents[1]
NS = "{http://www.w3.org/2000/svg}"


def _module() -> ModuleType:
    spec = importlib.util.spec_from_file_location(
        "progress_svg", ROOT / "scripts" / "progress_svg.py"
    )
    assert spec is not None and spec.loader is not None
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def _render(states: tuple[str, ...]) -> ET.Element:
    return ET.fromstring(_module().render([("server.dll", states)]))


def test_squares_carry_brand_classes() -> None:
    svg = _render(("exact", "size_mismatch", "stub", "library", "unannotated"))
    classes = {p.get("class") for p in svg.iter(f"{NS}path")}
    assert classes == {"f-cell-exact", "f-cell-stub", "o-control-line", "f-cell-unlit"}


def test_legend_names_every_state_on_a_shared_fill() -> None:
    svg = _render(("exact", "size_mismatch", "stub", "compile_error"))
    labels = [t.text for t in svg.iter(f"{NS}text")]
    assert "stub / size" in labels
    assert "error" in labels
    assert "no size" not in " ".join(label or "" for label in labels)


def test_stylesheet_carries_both_themes() -> None:
    style = _render(("exact",)).find(f"{NS}style")
    assert style is not None and style.text is not None
    light, _, dark = style.text.partition("@media (prefers-color-scheme:dark)")
    assert ".f-cell-exact{fill:#86d3a4}" in light
    assert ".f-cell-exact{fill:#2f7a56}" in dark


def test_library_is_left_out_of_the_fraction() -> None:
    svg = _render(("exact", "stub", "library", "library"))
    labels = [t.text for t in svg.iter(f"{NS}text")]
    assert "1 / 2 game" in labels
    assert "50.0%" in labels
