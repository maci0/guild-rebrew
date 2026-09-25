// FUNCTION: GOLDTL 0x005eaad0
// SIZE: 16

int __cdecl atexit(void (__cdecl*)(void));
void __cdecl fcn_005eaae0(void);

int __cdecl fcn_005eaad0(void)
{
	atexit(fcn_005eaae0);
	return 0;
}
