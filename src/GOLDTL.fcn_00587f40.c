// GLOBAL: GOLDTL 0x662d40
extern float g_662d40[];
// FUNCTION: GOLD 0x0057f890
// SIZE: 73
// FUNCTION: GOLDTL 0x587f40
// SIZE: 73

void __cdecl fcn_00455140(int, void*, void*);

void __cdecl fcn_00587f40(char* obj)
{
	fcn_00455140(*(int*) (obj + 0x8c), (void*) g_662d40, obj + 0x24);
	fcn_00455140(*(int*) (obj + 0x8c), (void*) (g_662d40 + 8), obj + 0x44);
	fcn_00455140(*(int*) (obj + 0x8c), (void*) (g_662d40 + 4), obj + 0x34);
}
