"""The project gate must fail on reported drift and on lint warnings."""

import json
import re
import subprocess
import sys
from pathlib import Path

import pytest

GATE = Path(__file__).resolve().parents[1] / "scripts/gate.sh"


def _adapter(index: int, path: Path, *args: str) -> int:
    blocks = re.findall(r"<<'PYEOF'\n(.*?)\nPYEOF", GATE.read_text(), re.S)
    assert len(blocks) == 2
    return subprocess.run(
        [sys.executable, "-c", blocks[index], str(path), *args],
        capture_output=True,
        check=False,
    ).returncode


@pytest.mark.parametrize("failure", [None, "function", "baseline", "data", "file", "layout"])
def test_verification_rejects_drift(tmp_path: Path, failure: str | None) -> None:
    report = {
        "summary": {"passed": 3, "total": 3, "failed": 0},
        "data": {"matched": 1, "compared": 1, "mismatched": [], "missing": []},
        "whole_binary": {
            "match": True,
            **{
                k: {"match": True}
                for k in ("file", "sections", "exports", "imports", "rsrc", "headers", "layout")
            },
            "relocations": {"match": True, "missing": [], "added": []},
        },
    }
    if failure == "function":
        report["summary"]["failed"] = 1
    elif failure == "baseline":
        report["summary"]["passed"] = 1
    elif failure == "data":
        report["data"]["mismatched"] = ["drift"]
    elif failure == "file":
        report["whole_binary"]["file"]["match"] = False
        report["whole_binary"]["match"] = False
    elif failure == "layout":
        report["whole_binary"]["layout"]["match"] = False
    path = tmp_path / "report.json"
    path.write_text(json.dumps(report))
    assert _adapter(1, path, "2") == (0 if failure is None else 1)


@pytest.mark.parametrize("warnings", [0, 1])
def test_lint_warnings_are_fatal(tmp_path: Path, warnings: int) -> None:
    path = tmp_path / "lint.json"
    path.write_text(json.dumps({"passed": 3, "errors": 0, "warnings": warnings}))
    assert _adapter(0, path) == warnings
