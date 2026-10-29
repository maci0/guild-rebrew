/* Entity slot-walk arm: scans the 16-entry (stride 0x1c) block at entity+0x1a4
 * downwards for the first entry with a non-zero id at +0xc and owner != -1,
 * records that slot index and bails when none is found. The remainder
 * (0x5a5206-0x5a5439: per-slot setup and the 0x5a5430 exit) is not
 * transcribed yet. */
/* ADDRESS: GOLDTL 0x005a51c0 */
int __cdecl fcn_005a51c0(unsigned char* entity)
{
	int* p;
	int i;
	int slot;

	slot = 0;
	p = (int*) (entity + 0x1a4);
	for (i = 0xf; i >= 0; i--) {
		if (p[3] != 0 && p[0] != -1) {
			slot = i + 1;
			break;
		}
		p = (int*) ((char*) p - 0x1c);
	}
	if (slot <= 0) {
		return 0;
	}
	return 0;
}
