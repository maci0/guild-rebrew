extern int g_14b52fc;



void* __cdecl fcn_00577850(int);
void __cdecl fcn_00526120(int, int);

int __cdecl fcn_005898f0(void* entry)
{
	void* match;

	match = fcn_00577850(*(int*) ((char*) entry + 1));
	if (match != 0) {
		fcn_00526120(g_14b52fc, 0);
	}
	return match == 0;
}
