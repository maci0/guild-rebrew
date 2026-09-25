void* __cdecl fcn_0064e2f9(const char*, const char*);
int __cdecl fcn_0064e48f(void*, int, int);
int __cdecl fcn_0064ebe4(void*, int, int, void*);
int __cdecl fcn_0064e1fd(void*);

extern char g_6750e8[];

// FUNCTION: GOLDTL 0x4757d0
// SIZE: 84

int __cdecl fcn_004757d0(const char* name)
{
	unsigned char hdr[40];
	void* f;

	f = fcn_0064e2f9(name, g_6750e8);
	if (f != 0) {
		fcn_0064e48f(f, 14, 0);
		fcn_0064ebe4(hdr, 1, 40, f);
		fcn_0064e1fd(f);
		return *(unsigned short*) (hdr + 14);
	}
	return -1;
}
