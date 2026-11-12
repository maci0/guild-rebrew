"""The project gate must fail on reported drift and on lint warnings."""

import json
import os
import re
import shutil
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
    "failure",
    [None, "function", "baseline", "data", "file", "layout", "unchecked", "missing-check"],
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


@pytest.mark.parametrize("missing", ["flags.make", "build.make", "link.txt"])
def test_pin_check_rejects_missing_generated_input(tmp_path: Path, missing: str) -> None:
    rules = tmp_path / "build/CMakeFiles/server_dll.dir"
    rules.mkdir(parents=True)
    for name in ("flags.make", "build.make", "link.txt"):
        if name != missing:
            (rules / name).write_text("")
    block = GATE.read_text().split('echo "== per-file toolchain pins"\n', 1)[1]
    block = block.split('echo "== deliverable vs reference, byte for byte"', 1)[0]
    result = subprocess.run(
        ["bash", "-c", "set -uo pipefail\nrc=0\n" + block + '\nexit "$rc"'],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        check=False,
    )
    assert result.returncode == 1, result.stdout + result.stderr
    assert "no per-file toolchain pins" not in result.stdout


@pytest.mark.parametrize("failure", [None, "build", "verify-command", "verify-report", "pin-input"])
def test_gate_entry_point_propagates_failures(
    tmp_path: Path, monkeypatch, failure: str | None
) -> None:
    scripts = tmp_path / "scripts"
    scripts.mkdir()
    shutil.copyfile(GATE, scripts / "gate.sh")
    (scripts / "wine_load_check.sh").write_text("echo 'wine fixture OK'\n")
    (scripts / "verify_objective.py").write_text("print('objective fixture OK')\n")
    reference = tmp_path / "original/Server/server.dll"
    reference.parent.mkdir(parents=True)
    reference.write_bytes(b"fixture raw image")
    rules = tmp_path / "build/CMakeFiles/server_dll.dir"
    rules.mkdir(parents=True)
    for name in ("flags.make", "build.make", "link.txt"):
        if failure != "pin-input" or name != "flags.make":
            (rules / name).write_text("")
    reports = tmp_path / "reports"
    reports.mkdir()
    (reports / "lint.json").write_text(json.dumps({"passed": 3, "errors": 0, "warnings": 0}))
    (reports / "verify.json").write_text(
        json.dumps(
            {
                "functions_checked": True,
                "summary": {"passed": 316, "total": 316, "failed": int(failure == "verify-report")},
                "data": {"matched": 1, "compared": 1, "mismatched": [], "missing": []},
                "whole_binary": {
                    "match": True,
                    **{
                        name: {"match": True}
                        for name in (
                            "file",
                            "sections",
                            "exports",
                            "imports",
                            "rsrc",
                            "headers",
                            "layout",
                        )
                    },
                    "relocations": {"match": True, "missing": [], "added": []},
                },
            }
        )
    )
    commands = tmp_path / "bin"
    commands.mkdir()
    for name, body in {
        "rebrew": """case "$1 $2" in
'build check') exit 0 ;;
'lint --json') cat reports/lint.json ;;
'verify --no-cache') cat reports/verify.json; test "$FAIL_STAGE" != verify-command ;;
'toolchain detect') echo '{"codegen":"plain","aligned":true}' ;;
*) exit 99 ;;
esac""",
        # Recreate equal bytes even on failure, so cmp cannot hide a lost build status.
        "cmake": 'cp original/Server/server.dll build/server.dll\ntest "$FAIL_STAGE" != build',
        "docker": "exit 0",
    }.items():
        command = commands / name
        command.write_text("#!/bin/bash\n" + body + "\n")
        command.chmod(0o755)
    monkeypatch.setenv("PATH", str(commands) + os.pathsep + os.environ["PATH"])
    monkeypatch.setenv("FAIL_STAGE", failure or "")
    monkeypatch.setenv("BASELINE", "316")
    result = subprocess.run(
        ["bash", str(scripts / "gate.sh")],
        cwd=tmp_path,
        capture_output=True,
        text=True,
        timeout=60,
        check=False,
    )
    assert result.returncode == (0 if failure is None else 1), result.stdout + result.stderr
    assert (tmp_path / ".scratch/gate-verify.json").is_file()
    assert ("GATE: pass" if failure is None else "GATE: FAIL") in result.stdout
