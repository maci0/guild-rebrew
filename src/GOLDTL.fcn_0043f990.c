// FUNCTION: GOLDTL 0x43f990
// SIZE: 63

extern char g_6b5c60;

int __cdecl fcn_0043f7e0(char*, int, int);
void __cdecl fcn_0043bf20(char*);

int __cdecl fcn_0043f990(char* o, int a2, int idx)
{
	int r;

	o[idx * 64 + 0x7e24] = g_6b5c60;
	r = fcn_0043f7e0(o, a2, idx);
	if (r >= 0) {
		fcn_0043bf20(o);
	}
	return r;
}
