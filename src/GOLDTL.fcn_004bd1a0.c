typedef struct {
	char pad0[0xd];
	unsigned char state;
	char padE[0x6];
	void* obj;
} fcn_004bd1a0_entry;
// SIZE 0x18

void __cdecl fcn_00442d50(void*, int);

/* ADDRESS: GOLD 0x004bcbe0 */
/* ADDRESS: GOLDTL 0x004bd1a0 */

void __cdecl fcn_004bd1a0(fcn_004bd1a0_entry* tab)
{
	int i;

	if (tab != 0) {
		for (i = 0; i < 64; i++) {
			if (tab[i].state != 0xff && tab[i].obj != 0)
				fcn_00442d50(tab[i].obj, 0);
		}
	}
}
