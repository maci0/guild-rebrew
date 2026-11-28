


unsigned short __cdecl gm_RandomMod(int);
void __cdecl amt_FindOfficeSlotByKey(char, char*);
int __cdecl amt_GetRoleLevel(int);

/* ADDRESS: GOLDDE 0x004fc710 */
void __cdecl amt_CalcOfficeHolderAges(int n, int* dst, int* src)
{
	char buf[0x18];
	int t[15];
	int j;
	int i;

	t[0] = 0x18;
	t[1] = 0x27;
	t[2] = 0x33;
	t[3] = 0x3f;
	t[4] = 0x45;
	t[5] = 0x12;
	t[6] = 0x39;
	t[7] = 6;
	t[8] = 0xc;
	t[9] = 0x1e;
	t[10] = 0x4b;
	t[11] = 0x5e;
	t[12] = 0x58;
	t[13] = 0x51;
	t[14] = 0x2d;
	j = gm_RandomMod(15);
	for (i = 0; i < n; i++) {
		amt_FindOfficeSlotByKey((char) src[i], buf);
		dst[i] = t[j] - amt_GetRoleLevel((unsigned char) buf[8]) / 2;
		j = (j + 1) % 15;
	}
}
