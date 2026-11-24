# Unfinished reconstruction reviews

Use the GoldTL addresses below with `rebrew source findings` and review current
source and native code. See [current work](TODO.md) for priorities.

| GoldTL VA | Review question |
| --- | --- |
| 0x004cdda0 | Verify the caller contract. The earlier review mapped the passed buffer to `buf` and the final write to `arg2`. |
| 0x005cff20 | Native holder construction can run with `shown == 0` and `*a2 != 0`. Track the holder and shadow slots, read-before-write state and tail behavior. |
| 0x00515e10 | Verify the terminating NUL copy and caller return use. Provenance records a void-return correction on November 13, 2026. |
| 0x005a6e90 | Recheck the mode, comparison slot and loop conditions. |
| 0x00547770 | Check the floating-point threshold and intermediate precision apart from the integer operations. |
| 0x00524b50 | Trace the global counter, failure state and writes through callees. |
| 0x005e5a50 | Callee 0x00533a60 writes two IDs used by later gates. Verify both IDs and their uses across the whole body. |

The original scratch receipts were in a local archive removed on November 14,
2026. Use `git show 5e1cfc302:docs/HANDOFF.md` to look up their former paths.
[Provenance](provenance.md) records decisions and superseded candidates.
[Research history](goal-history.md#full-notebooks) lists the tracked notebooks.
