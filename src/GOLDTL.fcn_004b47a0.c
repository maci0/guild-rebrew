extern char g_773d75;

int __cdecl fcn_0050d320(int, char);
int __cdecl fcn_0050b710(int, char);

// FUNCTION: GOLDTL 0x4b47a0
// SIZE: 50

int __cdecl fcn_004b47a0(int a, char* thr)
{
	return fcn_0050b710(fcn_0050d320(a, g_773d75), g_773d75) >= *(int*) (thr + 0x14);
}
