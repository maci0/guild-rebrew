// FUNCTION: GOLD 0x005dea0b
// SIZE: 45
// fcn_005dea0b — call [0x62de78] if set; 2 fcn_005deaf3 pairs.

void __cdecl fcn_005deaf3(void*, void*);

void __cdecl fcn_005dea0b(void)
{
	if (*(int*) 0x62de78 != 0) {
		((void (__stdcall*)()) *(void**) 0x62de78)();
	}
	fcn_005deaf3((void*) 0x5f1008, (void*) 0x5f1018);
	fcn_005deaf3((void*) 0x5f1000, (void*) 0x5f1004);
}
