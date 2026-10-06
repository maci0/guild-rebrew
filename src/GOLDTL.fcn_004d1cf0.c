/* fcn_004d1cf0 — start the worker with the fixed queue geometry. */

void __cdecl fcn_004379a0(int, int, int, int, int);

// FUNCTION: GOLDTL 0x4d1cf0
void __cdecl fcn_004d1cf0(void)
{
	int handle;

	handle = *(int*) 0x67a370;
	*(int*) 0x772f08 = 0;
	fcn_004379a0(handle, 0, 0x100, 0x4d1ad0, 0);
}
