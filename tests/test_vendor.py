"""scripts/vendor.py: pristine + patches must reproduce the vendored trees exactly."""

import hashlib
import shutil
import subprocess
import sys
import unittest
import uuid
from pathlib import Path

SCRIPT = Path(__file__).resolve().parents[1] / "scripts/vendor.py"
ROOT = SCRIPT.parents[1]

PRISTINE = "int f(void)\n{\n    return 1;\n}\n"
PATCH = """reason: return 2

--- a/f.c
+++ b/f.c
@@ -1,4 +1,4 @@
 int f(void)
 {
-    return 1;
+    return 2;
 }
"""
MANIFEST = """name = "lib"
version = "1"
url = "https://example.invalid/lib-1.tar.gz"
sha256 = "00"
pristine = "lib-1"
checksums = "references/vendor/lib/pristine.sha256"
output = "lib"
files = ["f.c"]
patches = ["0001-two.patch"]
"""


def run(root: Path, mode: str, stage: Path | None = None) -> subprocess.CompletedProcess[str]:
    return subprocess.run(
        [
            sys.executable,
            "-I",
            str(SCRIPT),
            mode,
            "--root",
            str(root),
            "--stage",
            str(stage or root / "stage"),
        ],
        capture_output=True,
        text=True,
        check=False,
    )


class VendorTest(unittest.TestCase):
    def setUp(self) -> None:
        self.root = ROOT / ".scratch" / f"test-vendor-{uuid.uuid4().hex}"
        self.addCleanup(shutil.rmtree, self.root, ignore_errors=True)
        (self.root / "lib-1").mkdir(parents=True)
        (self.root / "lib-1/f.c").write_text(PRISTINE)
        vendor = self.root / "references/vendor/lib"
        vendor.mkdir(parents=True)
        (vendor / "vendor.toml").write_text(MANIFEST)
        (vendor / "0001-two.patch").write_text(PATCH)
        digest = hashlib.sha256(PRISTINE.encode()).hexdigest()
        (vendor / "pristine.sha256").write_text(f"{digest}  lib-1/f.c\n")
        self.assertEqual(run(self.root, "sync").returncode, 0)

    def test_sync_writes_patched_tree_and_check_passes(self) -> None:
        self.assertIn("return 2;", (self.root / "lib/f.c").read_text())
        result = run(self.root, "check")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("lib: 1 patches, check ok", result.stdout)

    def test_hand_edit_of_output_fails(self) -> None:
        (self.root / "lib/f.c").write_text(PRISTINE)
        result = run(self.root, "check")
        self.assertEqual(result.returncode, 1)
        self.assertIn("lib/f.c: differs from pristine + patches", result.stderr)

    def test_unlisted_output_file_fails(self) -> None:
        (self.root / "lib/g.c").write_text("")
        result = run(self.root, "check")
        self.assertEqual(result.returncode, 1)
        self.assertIn("lib/g.c: not in vendor.toml", result.stderr)

    def test_modified_pristine_fails(self) -> None:
        (self.root / "lib-1/f.c").write_text(PRISTINE.replace("1;", "3;"))
        result = run(self.root, "check")
        self.assertEqual(result.returncode, 1)
        self.assertIn("lib-1/f.c: sha256 differs", result.stderr)

    def test_unpinned_pristine_file_fails(self) -> None:
        (self.root / "lib-1/extra.c").write_text("")
        result = run(self.root, "check")
        self.assertEqual(result.returncode, 1)
        self.assertIn("lib-1/extra.c: not in references/vendor/lib/pristine.sha256", result.stderr)

    def test_patch_that_does_not_apply_fails(self) -> None:
        patch = self.root / "references/vendor/lib/0001-two.patch"
        patch.write_text(PATCH.replace("-    return 1;", "-    return 9;"))
        result = run(self.root, "check")
        self.assertEqual(result.returncode, 1)
        self.assertIn("0001-two.patch does not apply", result.stderr)

    def test_project_trees_match(self) -> None:
        result = run(ROOT, "check", self.root / "stage")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("zlib: 4 patches, check ok", result.stdout)


if __name__ == "__main__":
    unittest.main()
