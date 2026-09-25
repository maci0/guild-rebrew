extern unsigned char g_fb5760[][10];

// FUNCTION: GOLDTL 0x4c4450
// SIZE: 34

int __cdecl fcn_004c4450(int i)
{
	if (i >= 0 && i < 0x8000)
		return g_fb5760[i][0];
	return -1;
}
