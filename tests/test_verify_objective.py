"""Regression check for independent verifier input handling."""
import runpy
import subprocess
import sys
import unittest
from pathlib import Path


SCRIPT = Path(__file__).resolve().parents[1] / "scripts/verify_objective.py"


class VerifyObjectiveInputTest(unittest.TestCase):
    def test_rejects_unknown_flags_and_unbacked_rvas(self):
        result = subprocess.run(
            [sys.executable, str(SCRIPT), "--built", "unused.dll"],
            capture_output=True,
            text=True,
        )
        self.assertEqual(result.returncode, 2)
        self.assertIn("unrecognized arguments", result.stderr)

        rva2off = runpy.run_path(str(SCRIPT))["rva2off"]
        sections = {".data": (0x10002000, 0x1000, 0x400, 0x100)}
        self.assertEqual(rva2off(sections, 0x10000000, 0x2004), 0x404)
        with self.assertRaisesRegex(ValueError, "no file-backed section"):
            rva2off(sections, 0x10000000, 0x2100)


if __name__ == "__main__":
    unittest.main()
