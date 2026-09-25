int __cdecl fcn_0048e0f0(int a1, char* p, int a3);
int __cdecl fcn_0048e230(int a1, char* p, int a3);
int __cdecl fcn_0048e360(int a1, char* p, int a3);
int __cdecl fcn_0048e4b0(int a1, char* p, int a3);

// FUNCTION: GOLDTL 0x48e050
// SIZE: 148
int __cdecl fcn_0048e050(int a1, char* p, int a3)
{
	switch (*(int*) (p + 0x10)) {
	case 0:
		return fcn_0048e0f0(a1, p, a3) ? 0x41 : 0;
	case 1:
		return fcn_0048e230(a1, p, a3) ? 0x41 : 0;
	case 2:
		return fcn_0048e360(a1, p, a3) ? 0x41 : 0;
	case 3:
		return fcn_0048e4b0(a1, p, a3) ? 0x41 : 0;
	}
	return 0;
}
