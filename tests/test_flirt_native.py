"""Qualified hosts keep the published python-flirt native module.

PEP 508 markers cannot tell musl or free-threaded CPython from the normal
builds, so a matching platform is not acceptance. The running interpreter's
SOABI has to be one of the four qualified tags before the module hash counts.
"""

from __future__ import annotations

import hashlib
import platform
import sys
import sysconfig
from importlib.metadata import distribution

import pytest

QUALIFIED_MODULES = {
    "cpython-315-x86_64-linux-gnu": (
        "flirt/flirt.cpython-315-x86_64-linux-gnu.so",
        "4bca0775a106b1e7ff0ed162ddcbe69872f0261ca90d942b73cbe59093f1467c",
    ),
    "cpython-315-aarch64-linux-gnu": (
        "flirt/flirt.cpython-315-aarch64-linux-gnu.so",
        "bd1513b80e2edc1a4dad3ab1e763d611ad5a302d1cf7fe3be99882e4fd680c83",
    ),
    "cpython-315-darwin": (
        "flirt/flirt.cpython-315-darwin.so",
        "ee3613fffb94d4366bb1124915ca8c81fbdabbc1fb5656003cabaf801fb32cd9",
    ),
    "cp315-win_amd64": (
        "flirt/flirt.cp315-win_amd64.pyd",
        "9a6591505745c72800fd41f332f652cfead413dee869b213b7ae98fb4d82724a",
    ),
}

_PLATFORM_LOOKALIKES = {
    ("linux", "x86_64"),
    ("linux", "aarch64"),
    ("darwin", "arm64"),
    ("win32", "AMD64"),
}


def test_qualified_flirt_module_hash() -> None:
    soabi = sysconfig.get_config_var("SOABI") or ""
    expected = QUALIFIED_MODULES.get(soabi)
    if expected is None:
        machine = platform.machine()
        if sys.platform == "win32" and machine.lower() == "amd64":
            machine = "AMD64"
        if sys.version_info[:2] == (3, 15) and (sys.platform, machine) in _PLATFORM_LOOKALIKES:
            pytest.fail(
                f"SOABI {soabi or '(missing)'} is not a qualified normal-GIL module; "
                "keep Rebrew's published source archive"
            )
        pytest.skip(
            "this interpreter has no qualified python-flirt wheel; "
            "Rebrew's published source archive remains the requirement"
        )
    relative, digest = expected
    files = distribution("python-flirt").files
    assert files is not None
    matches = [entry for entry in files if entry.as_posix().endswith(relative)]
    assert [entry.as_posix() for entry in matches] == [relative]
    found = hashlib.sha256(matches[0].locate().read_bytes()).hexdigest()
    assert found == digest
