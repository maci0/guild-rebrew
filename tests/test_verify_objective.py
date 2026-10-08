"""Regression check for independent verifier input handling."""
import runpy
import struct
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path


SCRIPT = Path(__file__).resolve().parents[1] / "scripts/verify_objective.py"


class VerifyObjectiveInputTest(unittest.TestCase):
    def test_accepts_identical_image_and_rejects_byte_or_length_drift(self):
        image = bytearray(0xA00)
        struct.pack_into("<I", image, 0x3C, 0x80)
        image[0x80:0x84] = b"PE\0\0"
        struct.pack_into("<H", image, 0x86, 4)
        struct.pack_into("<H", image, 0x94, 0xE0)
        opt = 0x98
        struct.pack_into("<I", image, opt + 16, 0x1000)
        struct.pack_into("<I", image, opt + 28, 0x10000000)
        struct.pack_into("<II", image, opt + 104, 0x24000, 40)
        for i, (name, rva, size) in enumerate((
            (b".text", 0x1000, 0x22846),
            (b".rdata", 0x24000, 0x200),
            (b".data", 0x25000, 0x200),
            (b".reloc", 0x26000, 0x200),
        )):
            offset = opt + 0xE0 + i * 40
            image[offset:offset + len(name)] = name
            struct.pack_into("<IIII", image, offset + 8, size, rva, 0x200, 0x200 + i * 0x200)
        struct.pack_into("<IIIII", image, 0x400, 0x24040, 0, 0, 0x241E0, 0x24040)
        for i in range(100):
            struct.pack_into("<I", image, 0x440 + i * 4, 0x80000001)
        image[0x5E0:0x5ED] = b"KERNEL32.dll\0"

        with tempfile.TemporaryDirectory() as directory:
            ref, built = Path(directory) / "ref.dll", Path(directory) / "built.dll"
            ref.write_bytes(image)
            changed = bytearray(image)
            changed[0x200] ^= 1
            for payload, expected in ((image, 0), (changed, 1), (image + b"\0", 1)):
                with self.subTest(expected=expected, size=len(payload)):
                    built.write_bytes(payload)
                    result = subprocess.run(
                        [sys.executable, str(SCRIPT), "--ref", str(ref), "--build", str(built)],
                        capture_output=True,
                        text=True,
                    )
                    self.assertEqual(result.returncode, expected, result.stdout + result.stderr)

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
