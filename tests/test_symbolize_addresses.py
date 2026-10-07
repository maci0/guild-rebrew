"""Regression check: --skip spans the function definition, not a call site."""
import runpy
import unittest
from pathlib import Path


SCRIPT = Path(__file__).resolve().parents[1] / "scripts/symbolize_addresses.py"

SOURCE = """int __cdecl f(void);
void g(void)
{
	if (f() == -1) {
		x = 1;
	}
}
int __cdecl f(void)
{
	if (y) {
		z = 2;
	}
	return 0;
}
"""


class BodySpanTest(unittest.TestCase):
    def test_skips_call_sites_and_covers_nested_blocks(self):
        body_span = runpy.run_path(str(SCRIPT))["body_span"]
        lo, hi = body_span(SOURCE, "_f")
        self.assertEqual(SOURCE[lo:hi + 1], SOURCE[SOURCE.index("f(void)\n{"):].rstrip("\n"))


if __name__ == "__main__":
    unittest.main()
