#!/usr/bin/env python3
"""Write the README progress map, docs/progress.svg.

One square per discovered function, in address order, filled with the
relumea brand's verdict colours in light and dark. Matched is exact, reloc, or
proven. A function whose address falls in the
target's ``external_ranges`` is linked library code. It is drawn, and it is
left out of the matched/game fraction.

Regenerate after the coverage database changes:

    python3 scripts/progress_svg.py
"""

from __future__ import annotations

import json
import sqlite3
import tomllib
import xml.etree.ElementTree as ET
from pathlib import Path

# Brand tokens (light, dark), copied by hand from relumea.ai
# `src/system/tokens.css` on its feat/brand-refresh branch. Nothing checks for
# drift: change a value there first, then here. The SVG carries both themes
# and switches on the viewer's `prefers-color-scheme`.
TOKENS: dict[str, tuple[str, str]] = {
    "surface": ("#ffffff", "#131316"),
    "surface-3": ("#eef0f3", "#212126"),
    "border": ("#e7e8ec", "#28282e"),
    "control-line": ("#82828a", "#767681"),
    "text": ("#0a0a0b", "#ededef"),
    "text-muted": ("#55585f", "#a3a3ab"),
    "accent": ("#0f7a42", "#3fbf7a"),
    "cell-exact": ("#86d3a4", "#2f7a56"),
    "cell-reloc": ("#7fcbb8", "#31806f"),
    "cell-proven": ("#a9dcc1", "#3f7a63"),
    "cell-near": ("#e8cf86", "#8a6c2c"),
    "cell-stub": ("#c3c7cf", "#6a6a73"),
    "cell-fail": ("#e8a49c", "#a05c54"),
    "cell-unlit": ("#eff0f3", "#212124"),
}

# One brand verdict fill per state. The brand has no fill for SIZE_MISMATCH or
# MISSING_SIZE, so they share the stub and fail fills and the legend names both
# states on that key. Library code is not a verdict: it is drawn as an outline.
STATE_FILL: dict[str, str] = {
    "exact": "cell-exact",
    "reloc": "cell-reloc",
    "proven": "cell-proven",
    "near_matching": "cell-near",
    "size_mismatch": "cell-stub",
    "stub": "cell-stub",
    "compile_error": "cell-fail",
    "missing_size": "cell-fail",
    "library": "control-line",
    "unannotated": "cell-unlit",
}
OUTLINED: frozenset[str] = frozenset({"library"})

# Left to right on the summary bar: matched, then everything else, library
# and unattempted last so the bar reads as work done against work left.
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

# One legend key per fill; a key names every state it carries.
LEGEND: tuple[tuple[tuple[str, str], ...], ...] = (
    (("exact", "exact"),),
    (("reloc", "reloc"),),
    (("proven", "proven"),),
    (("near_matching", "near"),),
    (("stub", "stub"), ("size_mismatch", "size")),
    (("compile_error", "error"), ("missing_size", "no size")),
    (("library", "library"),),
    (("unannotated", "unattempted"),),
)

MATCHED: frozenset[str] = frozenset({"exact", "reloc", "proven"})

# Not functions. The coverage database stores these marker rows in the same
# table as functions.
_DATA_MARKERS: frozenset[str] = frozenset({"GLOBAL", "DATA", "VTABLE", "STRING"})

# Brand faces; an SVG loaded as an image cannot fetch fonts, so the stacks
# fall back to the platform sans and mono.
FONT_SANS = "Archivo, ui-sans-serif, system-ui, sans-serif"
FONT_MONO = "'JetBrains Mono', ui-monospace, monospace"
CARD_RADIUS = 14  # --radius-card
SWATCH_RADIUS = 3  # --radius-cell

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


def load_statuses(conn: sqlite3.Connection, target: str) -> dict[int, str]:
    rows = conn.execute(
        "SELECT va, status, markerType FROM functions WHERE target = ?",
        (target,),
    ).fetchall()
    found: dict[int, str] = {}
    for va, status, marker in rows:
        if marker in _DATA_MARKERS:
            continue
        if not isinstance(va, int):
            raise SystemExit(f"{target}: function va {va!r} is not an int")
        name = (status or "").strip()
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
    if key not in STATE_FILL:
        raise SystemExit(f"{target}: {va:#x} has unmapped status {status}")
    return key


def load_blocks(
    root: Path,
    conn: sqlite3.Connection,
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
    statuses = load_statuses(conn, target)
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
    counts = {key: 0 for key in STATE_FILL}
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
    placed: dict[str, list[tuple[int, int]]] = {key: [] for key in STATE_FILL}
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


def _path(squares: list[tuple[int, int]], outlined: bool) -> str:
    if outlined:  # a 1px stroke centred inside the cell keeps the same footprint
        side = CELL - 1
        return "".join(f"M{x + 0.5} {y + 0.5}h{side}v{side}h-{side}z" for x, y in squares)
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
        token: str,
        size: int,
        anchor: str = "start",
        weight: int = 400,
        mono: bool = False,
    ) -> None:
        face = " mono" if mono else ""
        self.lines.append(
            f'<text x="{x}" y="{y}" class="f-{token}{face}" '
            f'font-size="{size}" font-weight="{weight}" text-anchor="{anchor}">'
            f"{xml_text(content)}</text>"
        )

    def rect(
        self,
        x: float,
        y: float,
        w: float,
        h: float,
        css_class: str,
        rx: float = 0,
        extra: str = "",
    ) -> None:
        radius = f' rx="{rx}" ry="{rx}"' if rx else ""
        self.lines.append(
            f'<rect x="{x:.2f}" y="{y:.2f}" width="{w:.2f}" height="{h:.2f}" '
            f'class="{css_class}"{radius}{extra}/>'
        )


def state_class(state: str) -> str:
    """Filled cell, or an outline for a state that is not a verdict."""
    prefix = "o" if state in OUTLINED else "f"
    return f"{prefix}-{STATE_FILL[state]}"


def draw_target(
    svg: _Svg, name: str, states: tuple[str, ...], columns: int, bar_w: int, clip_id: str
) -> None:
    matched, game = game_matched(states)
    left = PAD
    right = PAD + bar_w
    svg.text(left, svg.y, name, "text", 15, weight=600, mono=True)
    fraction = f"{matched} / {game}"
    if game != len(states):
        fraction += " game"
    pct = percent(matched, game)
    svg.text(right, svg.y, pct, "accent", 14, anchor="end", weight=600, mono=True)
    svg.text(
        right - int(len(pct) * 8.4) - 12, svg.y, fraction, "text-muted", 13, anchor="end", mono=True
    )
    svg.y += 12

    svg.lines.append(
        f'<clipPath id="{clip_id}"><rect x="{left}" y="{svg.y}" width="{bar_w}" '
        f'height="{BAR_H}" rx="{BAR_H / 2}" ry="{BAR_H / 2}"/></clipPath>'
    )
    svg.rect(
        left,
        svg.y,
        bar_w,
        BAR_H,
        "f-surface-3",
        rx=BAR_H / 2,
        extra=f' clip-path="url(#{clip_id})"',
    )
    cursor = float(left)
    for state, span in segment_widths(counts_of(states), bar_w):
        if span <= 0:
            continue
        # A stroked outline inside the clipped bar reads as a hollow box, so
        # the bar fills library with the outline colour.
        svg.rect(
            cursor,
            svg.y,
            span,
            BAR_H,
            f"f-{STATE_FILL[state]}",
            extra=f' clip-path="url(#{clip_id})"',
        )
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
            f'<path class="{state_class(state)}" d="{_path(squares, state in OUTLINED)}" '
            'shape-rendering="crispEdges"/>'
        )
    if drawn != len(states):
        raise SystemExit(f"{name}: drew {drawn} blocks for {len(states)} functions")
    svg.y += grid_height(len(states), columns) + 22


def _legend_span(label: str) -> int:
    """Width of one legend key: swatch, gap, label, trailing space."""
    return 10 + 6 + int(len(label) * 6.8) + 12


def draw_legend(svg: _Svg, counts: dict[str, int], bar_w: int) -> None:
    """One key per fill, each label carrying its count, so the per-state
    numbers do not depend on telling the fills apart."""
    items: list[tuple[str, str]] = []
    for key in LEGEND:
        present = [(state, label) for state, label in key if counts[state]]
        if present:
            text = " / ".join(f"{label} {counts[state]}" for state, label in present)
            items.append((present[0][0], text))
    x = PAD
    baseline = svg.y + 4
    for state, label in items:
        needed = _legend_span(label)
        if x > PAD and x + needed > PAD + bar_w:
            x = PAD
            baseline += 18
        # Every swatch gets the control-line edge: the lightest fills are
        # under 3:1 against the card and would not show without it.
        svg.rect(x + 0.5, baseline - 8.5, 9, 9, f"{state_class(state)} edge", rx=SWATCH_RADIUS)
        svg.text(x + 16, baseline, label, "text-muted", 12)
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


def stylesheet() -> str:
    """Fill (`f-`) and outline (`o-`) classes per token, plus the swatch
    `edge` stroke, light then dark."""

    def rules(theme: int) -> str:
        tokens = "".join(
            f".f-{name}{{fill:{pair[theme]}}}.o-{name}{{fill:none;stroke:{pair[theme]}}}"
            for name, pair in TOKENS.items()
        )
        return f"{tokens}.edge{{stroke:{TOKENS['control-line'][theme]}}}"

    return (
        f"text{{font-family:{FONT_SANS}}}.mono{{font-family:{FONT_MONO}}}"
        f"{rules(0)}@media (prefers-color-scheme:dark){{{rules(1)}}}"
    )


def render(targets: list[tuple[str, tuple[str, ...]]]) -> str:
    columns = column_count(INNER)
    bar_w = grid_width(columns)
    width = PAD * 2 + bar_w
    svg = _Svg(width)
    svg.y = PAD + 12
    totals = {key: 0 for key in STATE_FILL}
    for name, states in targets:
        for state, count in counts_of(states).items():
            totals[state] += count
        draw_target(svg, name, states, columns, bar_w, f"bar-{len(svg.lines)}")
    draw_legend(svg, totals, bar_w)
    note = (
        "One block per discovered function, in address order. Matched is exact, reloc, or proven."
    )
    if totals["library"]:
        note += " Outlined blocks are linked library code and are not in the count."
    for line in wrap_caption(note, bar_w, 11):
        svg.text(PAD, svg.y, line, "text-muted", 11)
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
        f"<style>{stylesheet()}</style>\n"
        f'<rect width="{width}" height="{height}" rx="{CARD_RADIUS}" class="f-surface"/>\n'
        f'<rect x="0.5" y="0.5" width="{width - 1}" height="{height - 1}" rx="{CARD_RADIUS}" '
        'class="o-border"/>\n'
        f"{body}\n"
        "</svg>\n"
    )


def readme_block(svg_width: int, targets: list[tuple[str, tuple[str, ...]]]) -> str:
    bits: list[str] = []
    for name, states in targets:
        matched, game = game_matched(states)
        noun = "game functions" if game != len(states) else "functions"
        counts = counts_of(states)
        breakdown = ", ".join(
            f"{label} {counts[state]}" for key in LEGEND for state, label in key if counts[state]
        )
        bits.append(f"{name} {matched} of {game} {noun} ({breakdown})")
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
    db_path = root / str(db_dir) / "coverage.db"
    if not db_path.is_file():
        raise SystemExit(f"coverage database not found at {db_path}")
    conn = sqlite3.connect(f"file:{db_path}?mode=ro", uri=True)
    try:
        collected: list[tuple[str, tuple[str, ...]]] = []
        for name in names:
            table = targets_cfg[name]
            if not isinstance(table, dict):
                raise SystemExit(f"{name}: target table is not a table")
            inventory = table.get("inventory_file")
            if not isinstance(inventory, str) or not inventory:
                raise SystemExit(f"{name}: no inventory_file")
            states = load_blocks(
                root, conn, name, inventory, parse_ranges(table.get("external_ranges"), name)
            )
            collected.append((name, states))
        return collected
    finally:
        conn.close()


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
