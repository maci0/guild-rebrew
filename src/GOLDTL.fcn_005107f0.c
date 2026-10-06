/* fcn_005107f0 — notify the helper while a global handle is live. */

void __cdecl fcn_00546b80(int);
void __cdecl fcn_004550b0(int, int);

// FUNCTION: GOLDTL 0x5107f0
void __cdecl fcn_005107f0(int a1)
{
	int handle;

	fcn_00546b80(a1);
	handle = *(int*) 0x773dd8;
	if (handle != 0) {
		fcn_004550b0(a1, handle);
	}
}
