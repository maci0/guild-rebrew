/* fcn_004e7390 — drop every entry of a pointer table. */

void __cdecl fcn_004e7310(int);

/* ADDRESS: GOLDTL 0x004e7390 */
void __cdecl fcn_004e7390(void)
{
	int* entry;

	for (entry = (int*) 0x14d0020; (int) entry < (int) 0x14d0c20; entry++) {
		if (*entry != 0) {
			fcn_004e7310(*entry);
		}
	}
}
