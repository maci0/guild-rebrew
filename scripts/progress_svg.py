"""Render the README graphic from `rebrew status --all-targets --json` on stdin."""

import argparse
import json
import sys
from collections import Counter
from datetime import UTC, datetime
from html import escape

MAP_COLORS = {
    "EXACT": ("#55dbac", "Exact C"),
    "RELOC": ("#39bdf8", "Reloc C"),
    "ASSEMBLY": ("#c3a7ff", "Assembly"),
    "LIBRARY": ("#bdc5cf", "Library"),
    "PROVEN": ("#ffc68b", "Proven only"),
    "NEAR_MATCHING": ("#e9a047", "Near match"),
    "SIZE_MISMATCH": ("#c16f45", "Size differs"),
    "PENDING": ("#394a59", "Pending"),
    "COMPILE_ERROR": ("#f16c85", "Compile error"),
}


def collect_map(report: dict) -> dict:
    """Use Rebrew's target selection, inventory and effective-verdict APIs."""
    from rebrew.config import load_config
    from rebrew.naming import external_vas, inside_annotated_vas, load_data, scope_to_target
    from rebrew.status import effective_status, load_verify_statuses

    result = {}
    for name, target in report["targets"].items():
        cfg = load_config(target=name)
        functions, existing, _ = load_data(cfg)
        libraries = external_vas(existing, cfg.external_libs)
        existing = scope_to_target(existing, cfg)
        pseudo = inside_annotated_vas(functions, existing)
        cache = load_verify_statuses(cfg)
        rows = []
        for va in sorted(set(existing) | ({f.va for f in functions} - pseudo)):
            info = existing.get(va, {})
            state = effective_status(info.get("status", "STUB"), cache.get(va))
            if va in libraries:
                state = "LIBRARY"
            elif state in ("EXACT", "RELOC") and info.get("source") == "naked":
                state = "ASSEMBLY"
            rows.append((va, state if state in MAP_COLORS else "PENDING"))
        counts = Counter(state for _, state in rows)
        matched = target["status"].get("EXACT", 0) + target["status"].get("RELOC", 0)
        if (
            len(rows) - counts["LIBRARY"] != target["functions"]["total"]
            or counts["LIBRARY"] != target["library_identified"]
            or counts["ASSEMBLY"] != target["naked_matched"]
            or counts["EXACT"] + counts["RELOC"] != matched - target["naked_matched"]
        ):
            raise ValueError(f"Function map and status report disagree for {name}; refresh status")
        result[name] = rows
    return result


def render_map(rows: dict, date: str) -> str:
    heights = {name: 56 + 5 * ((len(items) + 132) // 133) for name, items in rows.items()}
    height = 150 + sum(heights.values())
    parts = [
        '<svg xmlns="http://www.w3.org/2000/svg" width="715" '
        f'height="{height}" viewBox="0 0 715 {height}" role="img" '
        'aria-labelledby="title description">',
        '<title id="title">Address-ordered function map</title>',
        '<desc id="description">One block per catalogued function, ordered by address. '
        "Exact C, reloc C, assembly, library and unfinished verdicts have separate colors. "
        "Block area is a function count, not byte coverage.</desc>",
        f'<rect width="715" height="{height}" rx="16" fill="#101820"/>',
        '<g font-family="DejaVu Sans, sans-serif">',
        '<text x="24" y="32" font-size="18" fill="#f1f6fa">FUNCTION MAP</text>',
        f'<text x="691" y="32" text-anchor="end" font-size="12" fill="#aebdca">{escape(date)}</text>',
        '<text x="24" y="55" font-size="12" fill="#aebdca">One block per function · left to right, in address order</text>',
    ]
    y = 76
    for name, items in rows.items():
        parts.append(
            f'<text x="24" y="{y + 16}" font-size="15" fill="#f1f6fa">{escape(name)}</text>'
        )
        parts.append(
            f'<text x="691" y="{y + 16}" text-anchor="end" font-size="12" '
            f'fill="#aebdca">{len(items):,} blocks, including libraries</text>'
        )
        paths = {state: [] for state in MAP_COLORS}
        for index, (_, state) in enumerate(sorted(items)):
            x = 24 + index % 133 * 5
            cy = y + 30 + index // 133 * 5
            paths[state].append(f"M{x} {cy}h4v4h-4z")
        for state, commands in paths.items():
            if commands:
                parts.append(
                    f'<path fill="{MAP_COLORS[state][0]}" '
                    f'd="{"".join(commands)}" shape-rendering="crispEdges"/>'
                )
        y += heights[name]
    for index, (color, label) in enumerate(MAP_COLORS.values()):
        x = 24 + index % 5 * 133
        cy = y + index // 5 * 22
        parts.append(f'<rect x="{x}" y="{cy}" width="9" height="9" fill="{color}"/>')
        parts.append(
            f'<text x="{x + 15}" y="{cy + 9}" font-size="11" fill="#aebdca">{label}</text>'
        )
    parts.append(
        f'<text x="24" y="{y + 55}" font-size="11" fill="#aebdca">Library and PROVEN blocks do not count as C byte matches. Blocks do not measure code size.</text>'
    )
    parts.extend(["</g>", "</svg>"])
    return "\n".join(parts) + "\n"


def render(report: dict, date: str) -> str:
    targets = report["targets"]
    height = 126 + 156 * len(targets)
    parts = [
        '<svg xmlns="http://www.w3.org/2000/svg" width="715" '
        f'height="{height}" viewBox="0 0 715 {height}" role="img" '
        'aria-labelledby="title description">',
        '<title id="title">Guild reconstruction status</title>',
        '<desc id="description">Stored EXACT and RELOC function verdicts, with '
        "whole-function assembly matches separated from C source matches. "
        "Library functions and semantic PROVEN verdicts do not count as C matches. "
        "Client builds remain comparison scaffolds.</desc>",
        f'<rect width="715" height="{height}" rx="16" fill="#101820"/>',
        '<g font-family="DejaVu Sans, sans-serif">',
    ]

    def text(
        x: int, y: int, value: str, size: int = 13, color: str = "#aebdca", anchor: str = "start"
    ) -> None:
        parts.append(
            f'<text x="{x}" y="{y}" font-size="{size}" fill="{color}" '
            f'text-anchor="{anchor}">{escape(value)}</text>'
        )

    text(24, 33, "RECONSTRUCTION STATUS", 19, "#f1f6fa")
    text(691, 32, date, 12, anchor="end")
    text(24, 57, "Stored function verdicts · not whole-image completion")
    for index, (name, target) in enumerate(targets.items()):
        total = target["functions"]["total"]
        statuses = target["status"]
        assembly = target["naked_matched"]
        matched = statuses.get("EXACT", 0) + statuses.get("RELOC", 0)
        recovered = matched - assembly
        if not 0 <= assembly <= matched <= total:
            raise ValueError(f"Inconsistent function counts for {name}")
        percent = (1000 * recovered // total) / 10 if total else 0
        y = 80 + 156 * index
        parts.append(
            f'<rect x="24" y="{y}" width="667" height="144" '
            'rx="10" fill="#18242f" stroke="#2a3b49"/>'
        )
        text(40, y + 27, name, 16, "#f1f6fa")
        text(675, y + 36, f"{percent:.1f}%", 25, "#55dbac", "end")
        text(40, y + 49, f"{recovered:,} / {total:,} functions matched by C source")
        parts.append(f'<rect x="40" y="{y + 65}" width="635" height="12" fill="#394a59"/>')
        start = 40.0
        for count, color in ((recovered, "#55dbac"), (assembly, "#c3a7ff")):
            width = 635 * count / total if total else 0
            if width:
                parts.append(
                    f'<rect x="{start:.2f}" y="{y + 65}" '
                    f'width="{width:.2f}" height="12" fill="{color}"/>'
                )
            start += width
        text(
            40,
            y + 101,
            f"{assembly:,} assembly matches · {total - matched:,} functions still to match",
        )
        image = target.get("file", {})
        equal = bool(image.get("total_bytes")) and (
            image.get("matched_bytes") == image["total_bytes"]
        )
        label = (
            "Raw file equals reference"
            if equal
            else (
                "Raw file differs · comparison scaffold"
                if image.get("built")
                else "No built image compared"
            )
        )
        text(40, y + 124, label, 12, "#55dbac" if equal else "#ffc68b")

    y = 80 + 156 * len(targets)
    for x, color, label in (
        (24, "#55dbac", "C source match"),
        (247, "#c3a7ff", "Assembly match"),
        (470, "#394a59", "Still to match"),
    ):
        parts.append(f'<rect x="{x}" y="{y}" width="10" height="10" rx="2" fill="{color}"/>')
        text(x + 18, y + 10, label, 12)
    text(
        24,
        y + 32,
        "EXACT + RELOC only; libraries and PROVEN excluded. Inline assembly may remain.",
        11,
    )
    parts.extend(["</g>", "</svg>"])
    return "\n".join(parts) + "\n"


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--map", action="store_true", help="Render the address-ordered function map"
    )
    args = parser.parse_args()
    report = json.load(sys.stdin)
    date = datetime.now(UTC).date().isoformat()
    print(render_map(collect_map(report), date) if args.map else render(report, date), end="")
