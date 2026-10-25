"""python-flirt override markers select one artifact per interpreter."""

from __future__ import annotations

import tomllib
from pathlib import Path

from packaging.markers import Marker
from packaging.requirements import Requirement

ROOT = Path(__file__).resolve().parents[1]
SDIST = "python_flirt-0.10.2%2Brelumea.1.tar.gz"

# CPython 3.15 on the four qualified tuples gets that platform's wheel.
# PyPy 3.15, CPython 3.16, and a CPython 3.15 platform outside those tuples
# get the maintained source archive. Musl and free-threading still match the
# CPython linux/x86_64 wheel marker; PEP 508 cannot exclude them.
CASES = (
    (
        {"implementation_name": "cpython", "python_version": "3.15", "sys_platform": "linux", "platform_machine": "x86_64"},
        "manylinux_2_28_x86_64.whl",
    ),
    (
        {"implementation_name": "cpython", "python_version": "3.15", "sys_platform": "linux", "platform_machine": "aarch64"},
        "manylinux_2_28_aarch64.whl",
    ),
    (
        {"implementation_name": "cpython", "python_version": "3.15", "sys_platform": "darwin", "platform_machine": "arm64"},
        "macosx_11_0_arm64.whl",
    ),
    (
        {"implementation_name": "cpython", "python_version": "3.15", "sys_platform": "win32", "platform_machine": "AMD64"},
        "win_amd64.whl",
    ),
    (
        {"implementation_name": "pypy", "python_version": "3.15", "sys_platform": "linux", "platform_machine": "x86_64"},
        SDIST,
    ),
    (
        {"implementation_name": "cpython", "python_version": "3.16", "sys_platform": "linux", "platform_machine": "x86_64"},
        SDIST,
    ),
    (
        {"implementation_name": "cpython", "python_version": "3.15", "sys_platform": "linux", "platform_machine": "ppc64le"},
        SDIST,
    ),
)


def _flirt_overrides(pyproject: Path | None = None) -> list[str]:
    path = ROOT / "pyproject.toml" if pyproject is None else pyproject
    project = tomllib.loads(path.read_text())
    return [
        item
        for item in project["tool"]["uv"]["override-dependencies"]
        if item.startswith("python-flirt ")
    ]


def assert_marker_matrix(pyproject: Path | None = None) -> None:
    overrides = _flirt_overrides(pyproject)
    assert overrides
    for environment, expected in CASES:
        chosen = [url for item in overrides if (url := _selected(item, environment))]
        assert len(chosen) == 1, (pyproject, environment, chosen)
        assert expected in chosen[0]
    text = "\n".join(overrides)
    assert "musl" not in text
    assert "free" not in text


def _selected(requirement: str, environment: dict[str, str]) -> str | None:
    parsed = Requirement(requirement)
    if parsed.marker is None or not parsed.marker.evaluate(environment):
        return None
    assert parsed.url is not None
    return parsed.url


def test_marker_matrix_selects_one_artifact() -> None:
    assert_marker_matrix()


def test_markers_do_not_claim_musl_or_free_threading() -> None:
    linux = {
        "implementation_name": "cpython",
        "python_version": "3.15",
        "sys_platform": "linux",
        "platform_machine": "x86_64",
    }
    chosen = [url for item in _flirt_overrides() if (url := _selected(item, linux))]
    assert len(chosen) == 1
    assert "manylinux_2_28_x86_64.whl" in chosen[0]
    assert Marker(
        "implementation_name == 'cpython' and python_version == '3.15' and sys_platform == 'linux' and platform_machine == 'x86_64'"
    ).evaluate(linux)
