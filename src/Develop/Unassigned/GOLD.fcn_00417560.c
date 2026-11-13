extern int SonnenstrahlenAktiv;
extern int g_633444;

int __cdecl fcn_00411be0(char*);
char __cdecl fcn_004478e0(int, char);
void __cdecl d3_DestroyObject(void*);

/* ADDRESS: GOLD 0x00417560 */
void __cdecl fcn_00417560(void* a0)
{
	int found;
	int handle;

	found = -1;
	handle = *(int*) ((char*) a0 + 0x208);
	if (handle != *(int*) 0x5fb5b0) {
		handle = fcn_00411be0((char*) handle);
		fcn_004478e0(handle, 1);
		found = handle;
	}
	d3_DestroyObject(a0);
	SonnenstrahlenAktiv = 0;
	if (found != -1) {
		fcn_004478e0(g_633444, 1);
	}
}
