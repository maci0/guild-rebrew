int __cdecl fcn_0064d41a(char*, char*, ...);
int __cdecl fcn_00478fc0(int a1, int a2, int a3, char* a4);

/* ADDRESS: GOLDTL 0x00479e40 */
int __cdecl fcn_00479e40(void* a1, void* a2, int a3, char* a4, int a5)
{
	char buf[0x80];
	char* entry;
	unsigned char saved;

	if (a4 == 0) {
		return 0;
	}
	if (a5 > *(unsigned short*) (a4 + 0x2a)) {
		fcn_0064d41a(buf, (char*) 0x67da68, a4 + 0xa);
		return 0;
	}
	entry = a4 + *(int*) (a4 + a5 * 4 + 0x45);
	saved = entry[0xd];
	entry[0xd] = 5;
	fcn_00478fc0((int) a1, (int) a2, a3, a4 + *(int*) (a4 + a5 * 4 + 0x45));
	entry[0xd] = saved;
	return 1;
}
