"""Run the shipped loader checker with fake Wine and compiler commands."""

import os
import shutil
import subprocess
from pathlib import Path

import pytest

SCRIPT = Path(__file__).resolve().parents[1] / "scripts/wine_load_check.sh"


@pytest.fixture
def loader(tmp_path: Path):
    scripts = tmp_path / "scripts"
    scripts.mkdir()
    shutil.copyfile(SCRIPT, scripts / SCRIPT.name)
    (tmp_path / "server.dll").write_bytes(b"fixture")
    commands = tmp_path / "bin"
    commands.mkdir()
    environment = {
        **os.environ,
        "PATH": str(commands) + os.pathsep + os.environ["PATH"],
        "WINEPREFIX": str(tmp_path / "prefix"),
        "TMPDIR": str(tmp_path),
    }

    def command(name, body):
        path = commands / name
        path.write_text("#!/bin/bash\n" + body + "\n")
        path.chmod(0o755)

    command("i686-w64-mingw32-gcc", ': > "$2"; echo "$2" > compiler-output')
    command("wine", "echo 'Init resolved'; echo 'Exit resolved'")

    def run():
        return subprocess.run(
            ["bash", str(scripts / SCRIPT.name), "server.dll"],
            cwd=tmp_path,
            env=environment,
            capture_output=True,
            text=True,
            timeout=15,
        )

    return tmp_path, command, run


def test_wine_checker_confines_and_cleans_scratch(loader):
    root, _, run = loader
    result = run()
    assert result.returncode == 0, result.stdout + result.stderr
    output = Path((root / "compiler-output").read_text().strip())
    assert output.is_relative_to(root / ".scratch"), output
    assert not output.parent.exists()


def test_wine_checker_bounds_a_hung_load(loader):
    _, command, run = loader
    timeout = shutil.which("timeout")
    assert timeout
    command("wine", "sleep 30")
    # Keep production's timeout arguments under test while shortening the wait.
    command(
        "timeout",
        f'test "$1" = "--kill-after=5" && test "$2" = "60" || exit 99\nshift 2\nexec "{timeout}" --kill-after=0.1 0.1 "$@"',
    )
    try:
        result = run()
    except subprocess.TimeoutExpired:
        pytest.fail("Wine invocation has no effective timeout")
    assert result.returncode != 0
    assert "rc=124" in result.stdout, result.stdout + result.stderr


def test_wine_checker_stops_when_scratch_creation_fails(loader):
    root, command, run = loader
    command("mktemp", "exit 1")
    result = run()
    assert result.returncode != 0
    assert not (root / "compiler-output").exists()
