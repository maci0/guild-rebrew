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


@pytest.mark.parametrize(
    "failure", [None, "function", "baseline", "data", "file", "layout", "unchecked", "missing-check"]
)
def test_verification_rejects_drift(tmp_path: Path, failure: str | None) -> None:
    report = {
        "functions_checked": True,
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
    elif failure == "unchecked":
        report["functions_checked"] = False
    elif failure == "missing-check":
        del report["functions_checked"]
    path = tmp_path / "report.json"
    path.write_text(json.dumps(report))
    assert _adapter(1, path, "2") == (0 if failure is None else 1)


@pytest.mark.parametrize("warnings", [0, 1])
def test_lint_warnings_are_fatal(tmp_path: Path, warnings: int) -> None:
    path = tmp_path / "lint.json"
    path.write_text(json.dumps({"passed": 3, "errors": 0, "warnings": warnings}))
    assert _adapter(0, path) == warnings


@pytest.mark.parametrize("wrong_server_pin", [None, "flags.make", "build.make", "link.txt"])
def test_toolchain_pins_are_scoped_to_the_generated_server(
    tmp_path: Path, wrong_server_pin: str | None
) -> None:
    (tmp_path / "CMakeLists.txt").write_text("/REBREW_TOOLCHAIN:msvc-6.0-sp5-pp\n")
    rules = tmp_path / "build/CMakeFiles/server_dll.dir"
    rules.mkdir(parents=True)
    for name in ("flags.make", "build.make", "link.txt"):
        profile = "msvc-6.0-sp5-pp" if name == wrong_server_pin else "msvc-6.0-sp5"
        (rules / name).write_text(f"/REBREW_TOOLCHAIN:{profile}\n")
    block = GATE.read_text().split('echo "== per-file toolchain pins"\n', 1)[1]
    block = block.split('echo "== deliverable vs reference, byte for byte"', 1)[0]
    result = subprocess.run(
        [
            "bash",
            "-c",
            'rc=0\nrebrew() { echo \'{"codegen":"plain"}\'; }\n' + block + '\nexit "$rc"',
        ],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=False,
    )
    assert result.returncode == (0 if wrong_server_pin is None else 1), result.stdout
