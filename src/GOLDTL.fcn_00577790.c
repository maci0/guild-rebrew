extern char g_6a7e90[];

void* __cdecl fcn_00508e40(int);
void  __cdecl fcn_0051af00(void*, int, ...);
void  __cdecl fcn_00545d40(int, int, void*, int, int, void*);
void  __cdecl fcn_00546190(void*);

// FUNCTION: GOLDTL 0x577790
// SIZE: 186
// FUNCTION: GOLD 0x56f340
// SIZE: 186

void __cdecl fcn_00577790(void* a1)
{
	char buf[0x100];
	void* p1;
	void* p2;

	if (*(int*) ((char*) a1 + 0x70) != 0) {
		goto done;
	}
	p1 = fcn_00508e40(*(int*) ((char*) a1 + 0xac));
	p2 = fcn_00508e40(*(int*) ((char*) a1 + 0xb0));
	if (p1 != 0) {
		fcn_0051af00(buf, 0x4035);
		fcn_00545d40(*(int*) ((char*) a1 + 0xac), -1, buf, 1, 0x5fb, g_6a7e90);
	}
	if (p2 != 0) {
		fcn_0051af00(buf, 0x4036, *(unsigned short*) p1);
		fcn_00545d40(*(int*) ((char*) a1 + 0xb0), -1, buf, 1, 0x5fa, 0);
	}
done:
	fcn_00546190(a1);
}
