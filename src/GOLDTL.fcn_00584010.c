// FUNCTION: GOLD 0x0057ba10
// SIZE: 186
// FUNCTION: GOLDTL 0x00584010
// SIZE: 186

extern char g_6a9288[];
extern char g_6a9274[];

int* __cdecl fcn_0041db70(int size, char* tag);
void __cdecl fcn_00580cf0(int);

#pragma optimize("y", off)
int* __cdecl fcn_00584010(void)
{
	int* p;
	char* fdest;
	int flen;

	p = fcn_0041db70(0x74, g_6a9288);
	fdest = (char*) p;
	if (p == 0) {
		fcn_00580cf0(0);
		return 0;
	}
	flen = 0x74;
	__asm {
		mov edi, fdest
		mov ebx, flen
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	p[5] = 0;
	p[6] = 0;
	p[7] = 0;
	p[8] = 0;
	p[0xc] = 0;
	p[0xd] = 0;
	p[0xe] = 0;
	p[0x10] = 0;
	p[0x11] = 0;
	p[0x1c] = 0;
	p[0] = 7;
	p[1] = 0x4f555452;
	p[2] = 5;
	p[3] = 0x3f27;
	p[4] = (int) g_6a9274;
	p[0xb] = -1;
	p[0x12] = 0xb;
	p[0x1a] = -9;
	return p;
}
#pragma optimize("", on)
