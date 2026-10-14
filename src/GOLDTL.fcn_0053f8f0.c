/* fcn_0053f8f0 — drop every entry of a second pointer table. */

void __cdecl fcn_004230e0(int);

/* ADDRESS: GOLDTL 0x0053f8f0 */
void __cdecl fcn_0053f8f0(void)
{
	int* entry;

	for (entry = (int*) 0x7e1d60; (int) entry < (int) 0x7e1f60; entry++) {
		if (*entry != 0) {
			fcn_004230e0(*entry);
		}
	}
}
