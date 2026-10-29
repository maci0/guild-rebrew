/* ADDRESS: GOLDTL 0x00431d70 */
void __cdecl fcn_00431d70(char* a1, char* a2, int idx, int a4, float* out)
{
	out[0] = *(float*) (*(char**) (*(char**) (a2 + 0x68) + 0x15c) + idx * 0xc0 + 0x2c) + *(float*) (a1 + 0x84);
	out[1] = *(float*) (*(char**) (*(char**) (a2 + 0x68) + 0x15c) + idx * 0xc0 + 0x30) + *(float*) (a1 + 0x88);
	out[2] = *(float*) (*(char**) (*(char**) (a2 + 0x68) + 0x15c) + idx * 0xc0 + 0x34) + *(float*) (a1 + 0x8c);
}
