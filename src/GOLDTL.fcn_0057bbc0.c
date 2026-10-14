


int __cdecl fcn_00545580(int, void*, void*);
void __cdecl fcn_0057bcb0(void);
void __cdecl fcn_0057bd80(void);
void __cdecl fcn_0057c720(void);
void __cdecl fcn_0057c7b0(void);
void __cdecl fcn_0057c860(void);
void __cdecl fcn_0057c8d0(void);
void __cdecl fcn_0057c920(void);
void __cdecl fcn_0057cbc0(void);
void __cdecl fcn_0057cd50(void);
void __cdecl fcn_0057d0d0(void);
void __cdecl fcn_0057d950(void);
void __cdecl fcn_0057d9e0(void);
void __cdecl fcn_0057db20(void);
void __cdecl fcn_0057dba0(void);
int __cdecl fcn_00530ab0(int, char*, int, int, int);

int __cdecl fcn_0057bbc0(void)
{
	if (fcn_00545580(0x9d, (void*) fcn_0057bcb0, (void*) fcn_0057bd80) != 0 ||
	    fcn_00545580(0x9e, (void*) fcn_0057c720, (void*) fcn_0057c7b0) != 0 ||
	    fcn_00545580(0x9f, (void*) fcn_0057c860, (void*) fcn_0057c8d0) != 0 ||
	    fcn_00545580(0xa0, (void*) fcn_0057c920, (void*) fcn_0057cbc0) != 0 ||
	    fcn_00545580(0xa1, (void*) fcn_0057cd50, (void*) fcn_0057d0d0) != 0 ||
	    fcn_00545580(0xa3, (void*) fcn_0057d950, (void*) fcn_0057d9e0) != 0 ||
	    fcn_00545580(0xa4, (void*) fcn_0057db20, (void*) fcn_0057dba0) != 0) {
		return 1;
	}
	fcn_00530ab0(0xa1, 0, 0, 0x50f, -1);
	return 0;
}
