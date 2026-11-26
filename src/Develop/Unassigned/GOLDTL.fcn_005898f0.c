extern int g_14b52fc;



void* __cdecl he_HasActiveAction0x99(int);
void __cdecl fcn_00526120(int, int);

int __cdecl fcn_005898f0(void* entry)
{
	void* match;

	match = he_HasActiveAction0x99(*(int*) ((char*) entry + 1));
	if (match != 0) {
		fcn_00526120(g_14b52fc, 0);
	}
	return match == 0;
}
