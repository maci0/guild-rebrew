// FUNCTION: GOLDTL 0x00580e20
// SIZE: 2254

extern char g_6a8438[];
extern char g_6a8460[];
extern char g_6a8474[];
extern char g_6a8488[];
extern char g_6a849c[];
extern char g_6a84b0[];
extern char g_6a84c4[];
extern char g_6a84d8[];
extern char g_6a84ec[];
extern char g_6a8504[];
extern char g_6a8518[];
extern char g_6a852c[];
extern char g_6a8540[];
extern char g_6a8554[];
extern char g_6a8568[];
extern char g_6a857c[];
extern char g_6a8590[];
extern char g_6a85a4[];
extern char g_6a85b8[];
extern char g_6a85cc[];
extern char g_6a85e0[];
extern char g_6a85f0[];
extern char g_6a8604[];
extern char g_6a8618[];
extern char g_6a862c[];
extern char g_6a8640[];
extern char g_6a8650[];
extern char g_6a8664[];
extern char g_6a8678[];
extern char g_6a868c[];
extern char g_6a86a0[];
extern char g_6a86b0[];
extern char g_6a86c4[];
extern char g_6a86d8[];
extern char g_6a86ec[];
extern char g_6a8700[];
extern char g_6a8714[];
extern char g_6a8728[];
extern char g_6a873c[];
extern char g_6a874c[];
extern char g_6a8760[];

extern char g_6a8448[];
extern int g_7749fc;
int __cdecl fcn_004c3100(char*, int);
int* __cdecl fcn_0041db70(int size, char* tag);
void __cdecl fcn_00580cf0(int*);
void __cdecl fcn_0057ecf0(void);
void __cdecl fcn_0057ef30(void);
void __cdecl fcn_0057f030(void);

int* __cdecl fcn_00580e20(void)
{
	int* first;
	int* p;

	first = 0;
	p = fcn_0041db70(0x74, g_6a8760);
	if (p == 0) {
		goto fail;
	}
	{
		int flen;

		flen = 0x74;
		__asm {
			mov edi, p
			mov ebx, flen
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L0
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L0:
			add ecx, ebx
			rep stosb
		}
	}
	p[0x0] = 1;
	p[0x1] = 0x6e747231;
	p[0x2] = 0;
	p[0x3] = 0x3f2a;
	p[0x4] = (int) g_6a873c;
	p[0x5] = 0;
	p[0x6] = 0;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0xb] = -1;
	p[0xc] = 0x8e;
	p[0xf] = (int) fcn_0057ecf0;
	p[0xd] = 0;
	p[0xe] = 0;
	p[0x10] = 0;
	p[0x11] = 0;
	p[0x12] = 0xb;
	p[0x1a] = 0;
	p[0x1b] = 0;
	p[0x1c] = 0;
	first = p;
	p[0x1c] = (int) fcn_0041db70(0x74, g_6a874c);
	if (p[0x1c] == 0) {
		goto fail;
	}
	p = (int*) p[0x1c];
	{
		int flen;

		flen = 0x74;
		__asm {
			mov edi, p
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
	}
	p[0x0] = 1;
	p[0x1] = 0x63317341;
	p[0x2] = 1;
	p[0x3] = 0x3f2c;
	p[0x4] = (int) g_6a8714;
	p[0x5] = 0x3f2e;
	p[0x6] = (int) g_6a8700;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0x9] = 0x3f2f;
	p[0xa] = (int) g_6a86ec;
	p[0xb] = 0x429;
	p[0xc] = 0x163;
	p[0xf] = (int) fcn_0057ecf0;
	p[0xd] = 0;
	p[0xe] = 0;
	p[0x10] = 0x16;
	p[0x11] = 0;
	p[0x12] = 0xb;
	p[0x1a] = 0;
	p[0x1b] = 0;
	p[0x1c] = 0;
	p[0x1c] = (int) fcn_0041db70(0x74, g_6a8728);
	if (p[0x1c] == 0) {
		goto fail;
	}
	p = (int*) p[0x1c];
	{
		int flen;

		flen = 0x74;
		__asm {
			mov edi, p
			mov ebx, flen
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L2
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L2:
			add ecx, ebx
			rep stosb
		}
	}
	p[0x0] = 1;
	p[0x1] = 0x63317343;
	p[0x2] = 2;
	p[0x3] = 0x3f30;
	p[0x4] = (int) g_6a86c4;
	p[0x5] = 0x3f33;
	p[0x6] = (int) g_6a86b0;
	p[0x7] = 0x3f32;
	p[0x8] = (int) g_6a86a0;
	p[0x9] = 0x3f34;
	p[0xa] = (int) g_6a868c;
	p[0xb] = 0x429;
	p[0xc] = 0x8e;
	p[0xf] = (int) fcn_0057ecf0;
	p[0xd] = 0;
	p[0xe] = 0;
	p[0x10] = 6;
	p[0x11] = 0x2148;
	p[0x12] = 9;
	p[0x1a] = 1;
	p[0x1b] = 0;
	p[0x13] = 7;
	p[0x14] = 0;
	p[0x15] = 0;
	p[0x1c] = 0;
	p[0x1c] = (int) fcn_0041db70(0x74, g_6a86d8);
	if (p[0x1c] == 0) {
		goto fail;
	}
	p = (int*) p[0x1c];
	{
		int flen;

		flen = 0x74;
		__asm {
			mov edi, p
			mov ebx, flen
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L3
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L3:
			add ecx, ebx
			rep stosb
		}
	}
	p[0x0] = 1;
	p[0x1] = 0x63317344;
	p[0x2] = 2;
	p[0x3] = 0x3f35;
	p[0x4] = (int) g_6a8664;
	p[0x5] = 0x3f38;
	p[0x6] = (int) g_6a8650;
	p[0x7] = 0x3f37;
	p[0x8] = (int) g_6a8640;
	p[0x9] = 0x3f39;
	p[0xa] = (int) g_6a862c;
	p[0xb] = 0x429;
	p[0xc] = 0x8e;
	p[0xf] = (int) fcn_0057ecf0;
	p[0xd] = 0;
	p[0xe] = 0;
	p[0x10] = 8;
	p[0x11] = 0x2148;
	p[0x12] = 9;
	p[0x1a] = 3;
	p[0x1b] = 0;
	p[0x13] = 9;
	p[0x14] = 0;
	p[0x15] = 0;
	p[0x1c] = 0;
	p[0x1c] = (int) fcn_0041db70(0x74, g_6a8678);
	if (p[0x1c] == 0) {
		goto fail;
	}
	p = (int*) p[0x1c];
	{
		int flen;

		flen = 0x74;
		__asm {
			mov edi, p
			mov ebx, flen
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L4
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L4:
			add ecx, ebx
			rep stosb
		}
	}
	p[0x0] = 1;
	p[0x1] = 0x63317345;
	p[0x2] = 2;
	p[0x3] = 0x3f3a;
	p[0x4] = (int) g_6a8604;
	p[0x5] = 0x3f3d;
	p[0x6] = (int) g_6a85f0;
	p[0x7] = 0x3f3c;
	p[0x8] = (int) g_6a85e0;
	p[0x9] = 0x3f3e;
	p[0xa] = (int) g_6a85cc;
	p[0xb] = 0x429;
	p[0xc] = 0x8e;
	p[0xf] = (int) fcn_0057ecf0;
	p[0xd] = 0;
	p[0xe] = (int) fcn_0057ef30;
	p[0x10] = 1;
	p[0x11] = 0x2148;
	p[0x12] = 9;
	p[0x1a] = 7;
	p[0x1b] = 0;
	p[0x1c] = 0;
	p[0x1c] = (int) fcn_0041db70(0x74, g_6a8618);
	if (p[0x1c] == 0) {
		goto fail;
	}
	p = (int*) p[0x1c];
	{
		int flen;

		flen = 0x74;
		__asm {
			mov edi, p
			mov ebx, flen
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L5
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L5:
			add ecx, ebx
			rep stosb
		}
	}
	p[0x0] = 1;
	p[0x1] = 0x63317346;
	p[0x2] = 1;
	p[0x3] = 0x3f3f;
	p[0x4] = (int) g_6a85a4;
	p[0x5] = 0;
	p[0x6] = 0;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0xb] = 0x429;
	p[0xc] = 0x47;
	p[0xf] = (int) fcn_0057ecf0;
	p[0xd] = 0;
	p[0xe] = 0;
	p[0x10] = 3;
	p[0x11] = 0x47;
	p[0x12] = 0xb;
	p[0x1a] = 7;
	p[0x1b] = 0;
	p[0x1c] = 0;
	p[0x1c] = (int) fcn_0041db70(0x74, g_6a85b8);
	if (p[0x1c] == 0) {
		goto fail;
	}
	p = (int*) p[0x1c];
	{
		int flen;

		flen = 0x74;
		__asm {
			mov edi, p
			mov ebx, flen
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L6
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L6:
			add ecx, ebx
			rep stosb
		}
	}
	p[0x0] = 1;
	p[0x1] = 0x63317347;
	p[0x2] = 1;
	p[0x3] = 0x3f41;
	p[0x4] = (int) g_6a857c;
	p[0x5] = 0x3f43;
	p[0x6] = (int) g_6a8568;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0x9] = 0x3f44;
	p[0xa] = (int) g_6a8554;
	p[0xb] = 0x429;
	p[0xc] = 0x8e;
	p[0xf] = (int) fcn_0057ecf0;
	p[0xd] = 0;
	p[0xe] = 0;
	p[0x10] = 0xc;
	p[0x11] = 0x2148;
	p[0x12] = 0xa;
	p[0x1a] = 0x17;
	p[0x1b] = 0;
	p[0x1c] = 0;
	p[0x1c] = (int) fcn_0041db70(0x74, g_6a8590);
	if (p[0x1c] == 0) {
		goto fail;
	}
	p = (int*) p[0x1c];
	{
		int flen;

		flen = 0x74;
		__asm {
			mov edi, p
			mov ebx, flen
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L7
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L7:
			add ecx, ebx
			rep stosb
		}
	}
	p[0x0] = 1;
	p[0x1] = 0x63317348;
	p[0x2] = 1;
	p[0x3] = 0x3f45;
	p[0x4] = (int) g_6a852c;
	p[0x5] = 0x3f47;
	p[0x6] = (int) g_6a8518;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0x9] = 0x3f48;
	p[0xa] = (int) g_6a8504;
	p[0xb] = 0x429;
	p[0xc] = 0x8e;
	p[0xf] = (int) fcn_0057ecf0;
	p[0xd] = 0;
	p[0xe] = 0;
	p[0x10] = 0x13;
	p[0x11] = 0x2148;
	p[0x12] = 0xa;
	p[0x1a] = 0x817;
	p[0x1b] = 0;
	p[0x1c] = 0;
	p[0x1c] = (int) fcn_0041db70(0x74, g_6a8540);
	if (p[0x1c] == 0) {
		goto fail;
	}
	p = (int*) p[0x1c];
	{
		int flen;

		flen = 0x74;
		__asm {
			mov edi, p
			mov ebx, flen
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L8
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L8:
			add ecx, ebx
			rep stosb
		}
	}
	p[0x0] = 1;
	p[0x1] = 0x63317349;
	p[0x2] = 1;
	p[0x3] = 0x3f49;
	p[0x4] = (int) g_6a84d8;
	p[0x5] = 0x3f4b;
	p[0x6] = (int) g_6a84c4;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0x9] = 0x3f4c;
	p[0xa] = (int) g_6a84b0;
	p[0xb] = 0x429;
	p[0xc] = 0x8e;
	p[0xf] = (int) fcn_0057ecf0;
	p[0xd] = 0;
	p[0xe] = 0;
	p[0x10] = 0x14;
	p[0x11] = 0x2148;
	p[0x12] = 0xa;
	p[0x1a] = 0x1817;
	p[0x1b] = 0;
	p[0x1c] = 0;
	p[0x1c] = (int) fcn_0041db70(0x74, g_6a84ec);
	if (p[0x1c] == 0) {
		goto fail;
	}
	p = (int*) p[0x1c];
	{
		int flen;

		flen = 0x74;
		__asm {
			mov edi, p
			mov ebx, flen
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L9
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L9:
			add ecx, ebx
			rep stosb
		}
	}
	p[0x0] = 1;
	p[0x1] = 0x6331734a;
	p[0x2] = 1;
	p[0x3] = 0x3f4d;
	p[0x4] = (int) g_6a8488;
	p[0x5] = 0x3f4f;
	p[0x6] = (int) g_6a8474;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0x9] = 0x3f50;
	p[0xa] = (int) g_6a8460;
	p[0xb] = 0x429;
	p[0xc] = 0x163;
	p[0xf] = (int) fcn_0057ecf0;
	p[0xd] = 0;
	p[0xe] = (int) fcn_0057f030;
	p[0x10] = 0xd;
	p[0x11] = 0x2148;
	p[0x12] = 0xa;
	p[0x1a] = 0x1837;
	p[0x1b] = 0;
	p[0x1c] = 0;
	p[0x1c] = (int) fcn_0041db70(0x74, g_6a849c);
	if (p[0x1c] == 0) {
		goto fail;
	}
	p = (int*) p[0x1c];
	{
		int flen;

		flen = 0x74;
		__asm {
			mov edi, p
			mov ebx, flen
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L10
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L10:
			add ecx, ebx
			rep stosb
		}
	}
	p[0x0] = 1;
	p[0x1] = 0x75747231;
	p[0x2] = 3;
	p[0x3] = 0x3f51;
	p[0x4] = (int) g_6a8438;
	p[0x5] = 0;
	p[0x6] = 0;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0xb] = -1;
	p[0xc] = 0x163;
	p[0xf] = (int) fcn_0057ecf0;
	p[0xd] = 0;
	p[0xe] = 0;
	p[0x10] = 0;
	p[0x11] = 0;
	p[0x12] = 0xb;
	p[0x1a] = 0x1837;
	p[0x1b] = 0;
	p[0x1c] = 0;
	g_7749fc = fcn_004c3100(g_6a8448, 0);
	return first;
fail:
	fcn_00580cf0(first);
	return 0;
}
