#!/usr/bin/env python3
"""Write the README progress map, docs/progress.svg.

One square per discovered function, in address order, colored the way the
recoverage dashboard colors a match. The palette is the solid fills from
recoverage's potato view. Matched is exact, reloc, or proven: the same set
that view's progress bar counts. A function whose address falls in the
target's ``external_ranges`` is linked library code. It is drawn, and it is
left out of the matched/game fraction.

Regenerate after the coverage data changes:

    python3 scripts/progress_svg.py
"""

from __future__ import annotations

import json
import tomllib
import xml.etree.ElementTree as ET
from pathlib import Path

from rebrew.coverage_toml import CoverageTomlError, CoverageSnapshot, load_coverage_from

# Solid fills from recoverage potato.COLORS. size/error/no-size are the
# function statuses the dashboard folds into a neighbour; they stay distinct
# here so the legend can name them.
COLORS: dict[str, str] = {
    "exact": "#10b981",
    "reloc": "#0ea5e9",
    "proven": "#06b6d4",
    "near_matching": "#f59e0b",
    "size_mismatch": "#d97706",
    "stub": "#ef4444",
    "compile_error": "#e11d48",
    "missing_size": "#94a3b8",
    "library": "#C0C0D4",
    "unannotated": "#3F4958",
}

# Left to right on the summary bar: matched, then everything else, library
# and untouched last so the bar reads as work done against work left.
BAR_ORDER: tuple[str, ...] = (
    "exact",
    "reloc",
    "proven",
    "near_matching",
    "size_mismatch",
    "stub",
    "compile_error",
    "missing_size",
    "library",
    "unannotated",
)

LEGEND: tuple[tuple[str, str], ...] = (
    ("exact", "exact"),
    ("reloc", "reloc"),
    ("proven", "proven"),
    ("near_matching", "near"),
    ("size_mismatch", "size"),
    ("stub", "stub"),
    ("compile_error", "error"),
    ("missing_size", "no size"),
    ("library", "library"),
    ("unannotated", "untouched"),
)

MATCHED: frozenset[str] = frozenset({"exact", "reloc", "proven"})

# Not functions. The coverage database stores these marker rows in the same
# table as functions.
_DATA_MARKERS: frozenset[str] = frozenset({"GLOBAL", "DATA", "VTABLE", "STRING"})

BG = "#0f1216"
TRACK = "#1f2937"
TEXT = "#e7edf4"
MUTED = "#8b949e"
ACCENT = "#06b6d4"
BORDER = "#1c2a38"
FONT = "ui-sans-serif, system-ui, sans-serif"

CELL = 4
GAP = 1
PAD = 18
INNER = 680
BAR_H = 10
README_START = "<!-- progress:start -->"
README_END = "<!-- progress:end -->"


def project_root() -> Path:
    here = Path(__file__).resolve()
    for candidate in (here, *here.parents):
        if (candidate / "rebrew-project.toml").is_file():
            return candidate
    raise SystemExit("rebrew-project.toml not found above scripts/progress_svg.py")


def parse_ranges(raw_ranges: object, target: str) -> tuple[tuple[int, int], ...]:
    if raw_ranges is None:
        return ()
    if not isinstance(raw_ranges, list):
        raise SystemExit(f"{target}: external_ranges is not a list")
    parsed: list[tuple[int, int]] = []
    for raw in raw_ranges:
        if not isinstance(raw, str) or "-" not in raw:
            raise SystemExit(f"{target}: bad external range {raw!r}")
        lo_s, _, hi_s = raw.partition("-")
        try:
            lo, hi = int(lo_s, 16), int(hi_s, 16)
        except ValueError as exc:
            raise SystemExit(f"{target}: bad external range {raw!r}") from exc
        if hi < lo:
            raise SystemExit(f"{target}: external range {raw} is reversed")
        parsed.append((lo, hi))
    return tuple(parsed)


def in_ranges(va: int, ranges: tuple[tuple[int, int], ...]) -> bool:
    return any(lo <= va <= hi for lo, hi in ranges)


def load_statuses(snapshot: CoverageSnapshot, target: str) -> dict[int, str]:
    """Per-VA status, read from the target's coverage snapshot.

    The snapshot is rebrew's coverage-<target>.toml, parsed by rebrew itself,
    so this script and the dashboard read the same rows through the same
    reader. Its function rows are data rows too (GLOBAL/DATA/VTABLE/STRING
    markers); those are skipped here exactly as the SQL filter used to.
    """
    found: dict[int, str] = {}
    for fn in snapshot.functions:
        if fn.markerType in _DATA_MARKERS:
            continue
        va = fn.va
        if not isinstance(va, int):
            raise SystemExit(f"{target}: function va {va!r} is not an int")
        name = (fn.status or "").strip()
        if not name:
            raise SystemExit(f"{target}: function {va:#x} has an empty status")
        previous = found.get(va)
        if previous is not None and previous != name:
            raise SystemExit(f"{target}: function {va:#x} has statuses {previous} and {name}")
        found[va] = name
    return found


def block_state(status: str | None, library: bool, target: str, va: int) -> str:
    if library:
        return "library"
    if status is None:
        return "unannotated"
    key = status.lower()
    if key not in COLORS:
        raise SystemExit(f"{target}: {va:#x} has unmapped status {status}")
    return key


def load_blocks(
    root: Path,
    snapshot: CoverageSnapshot,
    target: str,
    inventory_file: str,
    ranges: tuple[tuple[int, int], ...],
) -> tuple[str, ...]:
    path = root / inventory_file
    if not path.is_file():
        raise SystemExit(f"{target}: inventory not found at {path}")
    payload = json.loads(path.read_text(encoding="utf-8"))
    if not isinstance(payload, list) or not payload:
        raise SystemExit(f"{target}: inventory {path} is empty")
    statuses = load_statuses(snapshot, target)
    seen: set[int] = set()
    ordered: list[tuple[int, str]] = []
    for entry in payload:
        if not isinstance(entry, dict) or not isinstance(entry.get("va"), int):
            raise SystemExit(f"{target}: inventory entry has no int va: {entry!r}")
        va = entry["va"]
        if va in seen:
            raise SystemExit(f"{target}: inventory lists {va:#x} twice")
        seen.add(va)
        ordered.append((va, block_state(statuses.get(va), in_ranges(va, ranges), target, va)))
    ordered.sort()
    return tuple(state for _, state in ordered)


def counts_of(states: tuple[str, ...]) -> dict[str, int]:
    counts = {key: 0 for key in COLORS}
    for state in states:
        counts[state] += 1
    return counts


def game_matched(states: tuple[str, ...]) -> tuple[int, int]:
    """Return (matched, game). Library blocks are in neither number."""
    matched = 0
    game = 0
    for state in states:
        if state == "library":
            continue
        game += 1
        if state in MATCHED:
            matched += 1
    return matched, game


def column_count(inner: int) -> int:
    return (inner + GAP) // (CELL + GAP)


def grid_width(columns: int) -> int:
    if columns < 1:
        raise SystemExit("progress map has no columns")
    return columns * CELL + (columns - 1) * GAP


def place_blocks(
    states: tuple[str, ...], columns: int, origin_x: int, origin_y: int
) -> dict[str, list[tuple[int, int]]]:
    """Top-left of each square, grouped by state. One square per function."""
    placed: dict[str, list[tuple[int, int]]] = {key: [] for key in COLORS}
    stride = CELL + GAP
    for index, state in enumerate(states):
        col = index % columns
        row = index // columns
        placed[state].append((origin_x + col * stride, origin_y + row * stride))
    return placed


def grid_height(n_blocks: int, columns: int) -> int:
    if n_blocks == 0:
        return 0
    rows = (n_blocks + columns - 1) // columns
    return rows * CELL + (rows - 1) * GAP


def segment_widths(counts: dict[str, int], width: int) -> list[tuple[str, float]]:
    total = sum(counts.values())
    if total == 0 or width <= 0:
        return []
    present = [state for state in BAR_ORDER if counts[state]]
    segments: list[tuple[str, float]] = []
    used = 0.0
    for index, state in enumerate(present):
        span = width - used if index == len(present) - 1 else counts[state] / total * width
        segments.append((state, span))
        used += span
    return segments


def xml_text(value: str) -> str:
    return (
        value.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;").replace('"', "&quot;")
    )


def percent(matched: int, game: int) -> str:
    if game == 0:
        return "0%"
    return f"{matched / game * 100:.1f}%"


def _path(squares: list[tuple[int, int]]) -> str:
    return "".join(f"M{x} {y}h{CELL}v{CELL}h-{CELL}z" for x, y in squares)


class _Svg:
    def __init__(self, width: int) -> None:
        self.width = width
        self.lines: list[str] = []
        self.y = PAD

    def text(
        self,
        x: int,
        y: int,
        content: str,
        fill: str,
        size: int,
        anchor: str = "start",
        weight: int = 400,
    ) -> None:
        self.lines.append(
            f'<text x="{x}" y="{y}" fill="{fill}" font-family="{FONT}" '
            f'font-size="{size}" font-weight="{weight}" text-anchor="{anchor}">'
            f"{xml_text(content)}</text>"
        )

    def rect(
        self,
        x: float,
        y: float,
        w: float,
        h: float,
        fill: str,
        rx: float = 0,
        stroke: str | None = None,
        extra: str = "",
    ) -> None:
        stroke_attr = f' stroke="{stroke}"' if stroke else ""
        radius = f' rx="{rx}" ry="{rx}"' if rx else ""
        self.lines.append(
            f'<rect x="{x:.2f}" y="{y:.2f}" width="{w:.2f}" height="{h:.2f}" '
            f'fill="{fill}"{radius}{stroke_attr}{extra}/>'
        )


def draw_target(
    svg: _Svg, name: str, states: tuple[str, ...], columns: int, bar_w: int, clip_id: str
) -> None:
    matched, game = game_matched(states)
    left = PAD
    right = PAD + bar_w
    svg.text(left, svg.y, name, TEXT, 15, weight=650)
    fraction = f"{matched} / {game}"
    if game != len(states):
        fraction += " game"
    pct = percent(matched, game)
    svg.text(right, svg.y, pct, ACCENT, 14, anchor="end", weight=650)
    svg.text(right - int(len(pct) * 8.4) - 12, svg.y, fraction, MUTED, 13, anchor="end")
    svg.y += 12

    svg.lines.append(
        f'<clipPath id="{clip_id}"><rect x="{left}" y="{svg.y}" width="{bar_w}" '
        f'height="{BAR_H}" rx="{BAR_H / 2}" ry="{BAR_H / 2}"/></clipPath>'
    )
    svg.rect(left, svg.y, bar_w, BAR_H, TRACK, rx=BAR_H / 2, extra=f' clip-path="url(#{clip_id})"')
    cursor = float(left)
    for state, span in segment_widths(counts_of(states), bar_w):
        if span <= 0:
            continue
        svg.rect(cursor, svg.y, span, BAR_H, COLORS[state], extra=f' clip-path="url(#{clip_id})"')
        cursor += span
    svg.y += BAR_H + 8

    origin_y = svg.y
    placed = place_blocks(states, columns, left, origin_y)
    drawn = 0
    for state in BAR_ORDER:
        squares = placed[state]
        drawn += len(squares)
        if not squares:
            continue
        svg.lines.append(
            f'<path fill="{COLORS[state]}" d="{_path(squares)}" shape-rendering="crispEdges"/>'
        )
    if drawn != len(states):
        raise SystemExit(f"{name}: drew {drawn} blocks for {len(states)} functions")
    svg.y += grid_height(len(states), columns) + 22


def _legend_span(label: str) -> int:
    """Width of one legend key: swatch, gap, label, trailing space."""
    return 10 + 6 + int(len(label) * 6.8) + 12


def draw_legend(svg: _Svg, counts: dict[str, int], bar_w: int) -> None:
    items = [(state, label) for state, label in LEGEND if counts[state]]
    x = PAD
    baseline = svg.y + 4
    for state, label in items:
        needed = _legend_span(label)
        if x > PAD and x + needed > PAD + bar_w:
            x = PAD
            baseline += 18
        svg.rect(x, baseline - 9, 10, 10, COLORS[state], rx=2)
        svg.text(x + 16, baseline, label, MUTED, 12)
        x += needed
    svg.y = baseline + 18


def wrap_caption(text: str, width: int, size: int) -> list[str]:
    """Greedy wrap. Character width is about 0.52em at `size`."""
    limit = max(24, int(width / (size * 0.52)))
    lines: list[str] = []
    current = ""
    for word in text.split():
        trial = word if not current else f"{current} {word}"
        if current and len(trial) > limit:
            lines.append(current)
            current = word
        else:
            current = trial
    if current:
        lines.append(current)
    return lines


def render(targets: list[tuple[str, tuple[str, ...]]]) -> str:
    columns = column_count(INNER)
    bar_w = grid_width(columns)
    width = PAD * 2 + bar_w
    svg = _Svg(width)
    svg.y = PAD + 12
    totals = {key: 0 for key in COLORS}
    for name, states in targets:
        for state, count in counts_of(states).items():
            totals[state] += count
        draw_target(svg, name, states, columns, bar_w, f"bar-{len(svg.lines)}")
    draw_legend(svg, totals, bar_w)
    note = (
        "One block per discovered function, in address order. Matched is exact, reloc, or proven."
    )
    if totals["library"]:
        note += " Silver blocks are linked library code and are not in the count."
    for line in wrap_caption(note, bar_w, 11):
        svg.text(PAD, svg.y, line, MUTED, 11)
        svg.y += 15
    height = svg.y + PAD - 15
    body = "\n".join(svg.lines)
    return (
        '<?xml version="1.0" encoding="UTF-8"?>\n'
        "<!-- generated by scripts/progress_svg.py; regenerate, do not edit -->\n"
        f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" '
        f'viewBox="0 0 {width} {height}" role="img">\n'
        "<title>Decompilation progress</title>\n"
        f"<desc>{xml_text(note)}</desc>\n"
        f'<rect width="{width}" height="{height}" rx="12" fill="{BG}"/>\n'
        f'<rect x="0.5" y="0.5" width="{width - 1}" height="{height - 1}" rx="12" '
        f'fill="none" stroke="{BORDER}"/>\n'
        f"{body}\n"
        "</svg>\n"
    )


def readme_block(svg_width: int, targets: list[tuple[str, tuple[str, ...]]]) -> str:
    bits: list[str] = []
    for name, states in targets:
        matched, game = game_matched(states)
        noun = "game functions" if game != len(states) else "functions"
        bits.append(f"{name} {matched} of {game} {noun}")
    alt = (
        "Decompilation progress. One block per discovered function, in address order. "
        + ". ".join(bits)
        + "."
    )
    return (
        f"{README_START}\n"
        '<p align="center">\n'
        f'  <img src="docs/progress.svg" width="{svg_width}" alt="{xml_text(alt)}">\n'
        "</p>\n"
        f"{README_END}"
    )


def write_readme(root: Path, block: str) -> None:
    path = root / "README.md"
    text = path.read_text(encoding="utf-8")
    start = text.find(README_START)
    end = text.find(README_END)
    if start == -1 or end == -1 or end < start:
        raise SystemExit("README.md is missing the progress:start / progress:end markers")
    end += len(README_END)
    path.write_text(text[:start] + block + text[end:], encoding="utf-8")


def svg_size(svg: str) -> tuple[int, int]:
    root = ET.fromstring(svg)
    width = root.get("width")
    height = root.get("height")
    if width is None or height is None:
        raise SystemExit("progress svg has no width or height")
    return int(width), int(height)


def collect(root: Path) -> list[tuple[str, tuple[str, ...]]]:
    with (root / "rebrew-project.toml").open("rb") as handle:
        config = tomllib.load(handle)
    project = config.get("project")
    targets_cfg = config.get("targets")
    if not isinstance(project, dict) or not isinstance(targets_cfg, dict):
        raise SystemExit("rebrew-project.toml has no project or targets table")
    default = project.get("default_target")
    db_dir = project.get("db_dir") or "db"
    if not isinstance(default, str) or default not in targets_cfg:
        raise SystemExit("default_target is missing from targets")
    names = [default, *[name for name in targets_cfg if name != default]]
    directory = root / str(db_dir)
    if not sorted(directory.glob("coverage-*.toml")):
        raise SystemExit(
            f"no coverage-<target>.toml found in {directory}; "
            "run 'rebrew build-db' to write it"
        )
    collected: list[tuple[str, tuple[str, ...]]] = []
    for name in names:
        table = targets_cfg[name]
        if not isinstance(table, dict):
            raise SystemExit(f"{name}: target table is not a table")
        inventory = table.get("inventory_file")
        if not isinstance(inventory, str) or not inventory:
            raise SystemExit(f"{name}: no inventory_file")
        try:
            snapshot = load_coverage_from(directory, name)
        except CoverageTomlError as exc:
            raise SystemExit(f"{name}: {exc}") from exc
        states = load_blocks(
            root, snapshot, name, inventory, parse_ranges(table.get("external_ranges"), name)
        )
        collected.append((name, states))
    return collected


def main() -> None:
    root = project_root()
    targets = collect(root)
    svg = render(targets)
    width, _height = svg_size(svg)
    out = root / "docs" / "progress.svg"
    out.write_text(svg, encoding="utf-8")
    write_readme(root, readme_block(width, targets))
    for name, states in targets:
        matched, game = game_matched(states)
        library = counts_of(states)["library"]
        print(f"{name}: {matched}/{game} game matched, {library} library, {len(states)} blocks")
    print(f"wrote {out.relative_to(root)}")


if __name__ == "__main__":
    main()
