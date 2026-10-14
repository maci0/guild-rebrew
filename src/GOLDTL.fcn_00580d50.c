


extern char g_6a8428[];
extern char g_6a840c[];
extern char g_6a83f8[];
extern int g_7749f8[];

int* __cdecl m_alloc(int size, char* tag);
void __cdecl fcn_00580cf0(int);
int __cdecl fcn_004c3100(char*, int);

#pragma optimize("y", off)
int* __cdecl fcn_00580d50(void)
{
	int* p;
	char* fdest;
	int flen;

	p = m_alloc(0x74, g_6a8428);
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
	p[0] = 0;
	p[1] = 0x494e5452;
	p[2] = 4;
	p[3] = 0x3f24;
	p[4] = (int) g_6a83f8;
	p[5] = 0;
	p[6] = 0;
	p[7] = 0;
	p[8] = 0;
	p[0xb] = -1;
	p[0xc] = 0x8e;
	p[0xd] = 0;
	p[0xe] = 0;
	p[0x10] = 0;
	p[0x11] = 0;
	p[0x12] = 0xb;
	p[0x1a] = 0;
	p[0x1b] = 0;
	p[0x1c] = 0;
	(*(int*)g_7749f8) = fcn_004c3100(g_6a840c, 0);
	return p;
}
#pragma optimize("", on)
