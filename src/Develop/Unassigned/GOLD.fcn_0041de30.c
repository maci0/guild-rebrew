/* Surface vtable slots: Lock at +0x64, Restore at +0x6c. */
typedef int (__stdcall* SurfLock)(void*, void*, unsigned int*, unsigned int, void*);
typedef int (__stdcall* SurfRestore)(void*);

/* Locks the surface, restoring it while Lock reports 0x887601c2 (surface
 * lost), publishes pitch and pixel depth, and returns the surface pointer
 * (0 on failure). The globals have no Gold data names yet. */
/* ADDRESS: GOLD 0x0041de30 */
void* __cdecl fcn_0041de30(void* surface, unsigned int flags)
{
	unsigned int desc[0x7c / 4];
	unsigned int bits;
	unsigned int pitch;
	int hr;

	desc[0] = 0x7c;
	flags |= 0x801;
	do {
		hr = ((SurfLock) (*(void***) surface)[0x64 / 4])(surface, 0, desc, flags, 0);
		if (hr == 0) {
			goto locked;
		}
	} while (hr == (int) 0x887601c2 && ((SurfRestore) (*(void***) surface)[0x6c / 4])(surface) == 0);
	return 0;
locked:
	bits = desc[0x54 / 4];
	pitch = desc[0x10 / 4];
	*(unsigned int*) 0x1464fb4 = bits;
	*(unsigned int*) 0x146357c = pitch;
	*(unsigned int*) 0x1463588 = pitch;
	*(unsigned int*) 0x14661a0 = pitch / *(unsigned int*) 0x1463568;
	*(unsigned int*) 0x1464fa0 = bits >> 3;
	return (void*) desc[0x24 / 4];
}
