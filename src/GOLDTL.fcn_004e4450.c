extern int g_772f3c;

void __cdecl fcn_00471af0(int k, int flag);

// FUNCTION: GOLD 0x004e2bd0
// FUNCTION: GOLDTL 0x004e4450
void __cdecl fcn_004e4450(int k, int flag)
{
	if (g_772f3c != 0) {
		*(float*) &flag = 0.0f;
	}
	fcn_00471af0(k, flag);
}
