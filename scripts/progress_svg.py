"""Render the README graphic from `rebrew status --all-targets --json` on stdin."""

import json
import sys
from datetime import UTC, datetime
from html import escape


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
    print(render(json.load(sys.stdin), datetime.now(UTC).date().isoformat()), end="")
