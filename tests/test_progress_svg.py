"""Render the README progress map from synthetic states and read the SVG back.

Drives scripts/progress_svg.render() and readme_block() and asserts on the
markup they ship: each state's squares carry its brand class, library code is
an outline in the grid and a fill in the bar, every legend swatch has an edge,
the legend and the README alt text count every state, and both themes are in
the sheet.
"""

from __future__ import annotations

import importlib.util
import xml.etree.ElementTree as ET
from pathlib import Path
from types import ModuleType

NS = "{http://www.w3.org/2000/svg}"


def _root() -> Path:
    here = Path(__file__).resolve()
    for candidate in here.parents:
        if (candidate / "rebrew-project.toml").is_file():
            return candidate
    raise AssertionError("rebrew-project.toml not found above the test")


ROOT = _root()


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


def test_legend_names_and_counts_every_state_on_a_shared_fill() -> None:
    svg = _render(("exact", "size_mismatch", "stub", "stub", "compile_error"))
    labels = [t.text for t in svg.iter(f"{NS}text")]
    assert "stub 2 / size 1" in labels
    assert "error 1" in labels
    assert "no size" not in " ".join(label or "" for label in labels)


def test_every_legend_swatch_has_an_edge() -> None:
    svg = _render(("exact", "library", "unannotated"))
    swatches = [r for r in svg.iter(f"{NS}rect") if r.get("width") == "9.00"]
    assert [r.get("class") for r in swatches] == [
        "f-cell-exact edge",
        "o-control-line edge",
        "f-cell-unlit edge",
    ]
    style = svg.find(f"{NS}style")
    assert style is not None and style.text is not None
    assert ".edge{stroke:#82828a}" in style.text


def test_library_bar_segment_is_filled() -> None:
    svg = _render(("exact", "library"))
    bar = [r.get("class") for r in svg.iter(f"{NS}rect") if r.get("clip-path")]
    assert bar == ["f-surface-3", "f-cell-exact", "f-control-line"]


def test_readme_alt_carries_the_per_state_counts() -> None:
    block = _module().readme_block(715, [("server.dll", ("exact", "stub", "library"))])
    assert "server.dll 1 of 2 game functions (exact 1, stub 1, library 1)." in block


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
