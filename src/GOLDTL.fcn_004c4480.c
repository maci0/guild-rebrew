extern unsigned char g_fb5760[][10];

// FUNCTION: GOLDTL 0x4c4480
// SIZE: 29

int __cdecl fcn_004c4480(int i)
{
	if (i >= 0 && i < 0x8000)
		return *(int*) &g_fb5760[i][6];
	return 0;
}
