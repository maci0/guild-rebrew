

extern int g_14abd70;

int __cdecl fcn_00525fb0(char*);
void __cdecl fcn_0052a0c0(char*, int);
void __cdecl fcn_005bdc30(int, void*, int, void*, int);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_0059cde0(void);
void __cdecl fcn_005305a0(void);

void __cdecl fcn_0059d020(char* a)
{
	if (fcn_00525fb0(a) == 0) {
		fcn_0052a0c0(a, 0);
		fcn_005bdc30(4, 0, g_14abd70, (void*) fcn_0059cde0, 0);
		fcn_0052a2d0();
		fcn_005305a0();
	}
}
