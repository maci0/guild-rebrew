"""Render README graphics from `rebrew status --all-targets --json` on stdin."""

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


def render(report: dict, date: str, *, data: bool = False) -> str:
    targets = report["targets"]
    height = 140 + 216 * len(targets)
    title = "Guild data verification" if data else "Guild reconstruction status"
    description = (
        "Three bars per target: verified initialized .data and .rdata bytes, verified "
        "catalogued data symbols including BSS, and EXACT symbols at their reference VA. "
        "Displacement, drift and unchecked or untracked data remain separate. "
        "Stored content verdicts do not establish storage ownership."
        if data
        else "Three bars per target: accounted virtual .text bytes "
        "including libraries and padding, C function matches excluding whole-function "
        "assembly and PROVEN verdicts, and existing raw-file bytes equal at original "
        "offsets. These are separate measures, not overall completion."
    )
    parts = [
        '<svg xmlns="http://www.w3.org/2000/svg" width="715" '
        f'height="{height}" viewBox="0 0 715 {height}" role="img" '
        'aria-labelledby="title description">',
        f'<title id="title">{title}</title>',
        f'<desc id="description">{description}</desc>',
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

    def bar(y: int, label: str, detail: str, count: int, total: int, color: str) -> None:
        if not 0 <= count <= total:
            raise ValueError(f"Inconsistent metric counts for {label}")
        percent = (1000 * count // total) / 10 if total else None
        text(40, y, f"{label} · {detail}", 12)
        text(675, y, f"{percent:.1f}%" if percent is not None else "N/A", 17, color, "end")
        parts.append(f'<rect x="40" y="{y + 9}" width="635" height="10" fill="#394a59"/>')
        if total and count:
            parts.append(
                f'<rect x="40" y="{y + 9}" width="{635 * count / total:.2f}" '
                f'height="10" fill="{color}"/>'
            )

    text(24, 33, "DATA VERIFICATION" if data else "RECONSTRUCTION METRICS", 19, "#f1f6fa")
    text(691, 32, date, 12, anchor="end")
    text(
        24,
        57,
        "Initialized bytes, data symbols and EXACT placement · separate measures"
        if data
        else "Code bytes, function counts and raw-file agreement · separate measures",
    )
    for index, (name, target) in enumerate(targets.items()):
        y = 80 + 216 * index
        parts.append(
            f'<rect x="24" y="{y}" width="667" height="204" '
            'rx="10" fill="#18242f" stroke="#2a3b49"/>'
        )
        text(40, y + 27, name, 16, "#f1f6fa")
        if data:
            metrics = target.get("data", {})
            total = metrics.get("total", 0)
            verified = metrics.get("verified", 0)
            exact = metrics.get("exact", 0)
            drift = metrics.get("drift", 0)
            displaced = metrics.get("displaced", 0)
            unchecked = metrics.get("unchecked", 0)
            byte_total = metrics.get("total_bytes", 0)
            byte_verified = metrics.get("verified_bytes", 0)
            buckets = metrics.get("bytes", {})
            if (
                not 0 <= exact <= verified <= total
                or not 0 <= displaced <= drift
                or unchecked < 0
                or verified + drift + unchecked != total
                or any(
                    buckets.get(k, 0) < 0 for k in ("verified", "drift", "unchecked", "untracked")
                )
                or sum(buckets.get(k, 0) for k in ("verified", "drift", "unchecked", "untracked"))
                != byte_total
                or buckets.get("verified", 0) != byte_verified
            ):
                raise ValueError(f"Inconsistent data accounting for {name}")
            bar(
                y + 51,
                "Initialized data bytes verified",
                f"{byte_verified:,} / {byte_total:,} bytes",
                byte_verified,
                byte_total,
                "#55dbac",
            )
            bar(
                y + 94,
                "Verified symbols (incl. BSS)",
                f"{verified:,} / {total:,} symbols",
                verified,
                total,
                "#39bdf8",
            )
            bar(
                y + 137,
                "EXACT symbols at reference VA",
                f"{exact:,} / {total:,} symbols",
                exact,
                total,
                "#c3a7ff",
            )
            text(
                40,
                y + 176,
                f"{displaced:,} displaced · {drift - displaced:,} other drift · {unchecked:,} unchecked symbols",
                11,
            )
            text(
                40,
                y + 192,
                f"Bytes: {buckets.get('drift', 0):,} drift · {buckets.get('unchecked', 0):,} unchecked · {buckets.get('untracked', 0):,} untracked",
                11,
            )
            continue
        total = target["functions"]["total"]
        statuses = target["status"]
        assembly = target["naked_matched"]
        matched = statuses.get("EXACT", 0) + statuses.get("RELOC", 0)
        recovered = matched - assembly
        if not 0 <= assembly <= matched <= total:
            raise ValueError(f"Inconsistent function counts for {name}")
        accounted = target["accounted_text_bytes"]
        text_total = target["total_text_bytes"]
        bar(
            y + 51,
            "Code accounting",
            f"{accounted:,} / {text_total:,} bytes",
            accounted,
            text_total,
            "#55dbac",
        )
        bar(
            y + 94,
            "C function matches",
            f"{recovered:,} / {total:,} functions",
            recovered,
            total,
            "#39bdf8",
        )
        image = target.get("file", {})
        file_total = image.get("total_bytes", 0)
        file_matched = image.get("matched_bytes", 0)
        detail = f"{file_matched:,} / {file_total:,} bytes" if file_total else "no image compared"
        bar(y + 137, "Raw file, original offsets", detail, file_matched, file_total, "#ffc68b")
        text(
            40,
            y + 176,
            f"{assembly:,} assembly matches · {total - matched:,} "
            f"function{'s' if total - matched != 1 else ''} still to match",
            11,
        )
        equal = bool(image.get("total_bytes")) and (
            image.get("matched_bytes") == image["total_bytes"]
        )
        label = (
            "Raw file equals reference"
            if equal
            else (
                "Raw file differs from reference"
                if image.get("built")
                else "No built image compared"
            )
        )
        text(40, y + 192, label, 11, "#55dbac" if equal else "#ffc68b")

    y = 80 + 216 * len(targets)
    text(
        24,
        y + 10,
        "Byte bar covers initialized .data + .rdata; excludes BSS and copied imports."
        if data
        else "Code accounting includes libraries and padding; C counts exclude whole-function assembly.",
        11,
    )
    text(
        24,
        y + 30,
        "Stored verdicts; symbols include BSS/views. Content checks do not establish storage ownership."
        if data
        else "Stored verdicts and existing images; not fresh verification. PROVEN is not a byte match.",
        11,
    )
    parts.extend(["</g>", "</svg>"])
    return "\n".join(parts) + "\n"


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument("--map", action="store_true", help="Render the address-ordered function map")
    mode.add_argument("--data", action="store_true", help="Render data verification and placement")
    args = parser.parse_args()
    report = json.load(sys.stdin)
    date = datetime.now(UTC).strftime("%Y-%m-%d %H:%M UTC")
    print(
        render_map(collect_map(report), date) if args.map else render(report, date, data=args.data),
        end="",
    )
