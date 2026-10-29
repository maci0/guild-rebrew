


extern char g_6a8e90[];
extern char g_6a8ea0[];
extern char g_6a8eb8[];
extern char g_6a8ecc[];
extern char g_6a8edc[];
extern char g_6a8ef0[];
extern char g_6a8f04[];
extern char g_6a8f18[];
extern char g_6a8f2c[];
extern char g_6a8f3c[];
extern char g_6a8f50[];
extern char g_6a8f64[];
extern char g_6a8f78[];
extern char g_6a8f8c[];
extern char g_6a8f9c[];
extern char g_6a8fb0[];
extern char g_6a8fc4[];
extern char g_6a8fd8[];
extern char g_6a8fe8[];
extern char g_6a8ffc[];
extern int g_774a08;

int* __cdecl m_alloc(int size, char* tag);
void __cdecl fcn_00580cf0(int*);
int __cdecl fcn_004c3100(char*, int);
void __cdecl fcn_0057f430(void);
void __cdecl fcn_0057f560(void);
void __cdecl fcn_0057f5d0(void);
void __cdecl fcn_0057f700(void);
void __cdecl fcn_0057f770(void);
void __cdecl fcn_0057f8b0(void);
void __cdecl fcn_0057f930(void);
void __cdecl fcn_0057fd60(void);

int* __cdecl fcn_00583330(void)
{
	int* first;
	int* p;

	first = 0;
	p = m_alloc(0x74, g_6a8ffc);
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
	p[0x0] = 3;
	p[0x1] = 0x6e747234;
	p[0x2] = 0;
	p[0x3] = 0x3fa2;
	p[0x4] = (int) g_6a8fd8;
	p[0x5] = 0;
	p[0x6] = 0;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0xb] = -1;
	p[0xc] = 0x8e;
	p[0xd] = (int) fcn_0057fd60;
	p[0xe] = 0;
	p[0x10] = 0;
	p[0x11] = 0;
	p[0x12] = 0xb;
	p[0x1a] = 0x5837;
	p[0x1b] = 0x1f70;
	p[0x1c] = 0;
	first = p;
	p[0x1c] = (int) m_alloc(0x74, g_6a8fe8);
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
	p[0x1] = 0x63347334;
	p[0x2] = 2;
	p[0x3] = 0x3fa4;
	p[0x4] = (int) g_6a8fb0;
	p[0x5] = 0x3fa7;
	p[0x6] = (int) g_6a8f9c;
	p[0x7] = 0x3fa6;
	p[0x8] = (int) g_6a8f8c;
	p[0x9] = 0x3fa8;
	p[0xa] = (int) g_6a8f78;
	p[0xb] = 0x429;
	p[0xc] = 0x8e;
	p[0xd] = (int) fcn_0057f930;
	p[0xf] = (int) fcn_0057f700;
	p[0xe] = (int) fcn_0057f5d0;
	p[0x10] = 1;
	p[0x11] = 0x2148;
	p[0x12] = 0xa;
	p[0x1a] = 0x5a37;
	p[0x1b] = 0x1f70;
	p[0x1c] = 0;
	p[0x1c] = (int) m_alloc(0x74, g_6a8fc4);
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
	p[0x1] = 0x63347332;
	p[0x2] = 2;
	p[0x3] = 0x3fa9;
	p[0x4] = (int) g_6a8f50;
	p[0x5] = 0x3fac;
	p[0x6] = (int) g_6a8f3c;
	p[0x7] = 0x3fab;
	p[0x8] = (int) g_6a8f2c;
	p[0x9] = 0x3fad;
	p[0xa] = (int) g_6a8f18;
	p[0xb] = 0x429;
	p[0xc] = 0x8e;
	p[0xd] = (int) fcn_0057f930;
	p[0xe] = (int) fcn_0057f430;
	p[0xf] = (int) fcn_0057f560;
	p[0x10] = 1;
	p[0x11] = 0x2148;
	p[0x12] = 0xa;
	p[0x1a] = 0x5b77;
	p[0x1b] = 0x1f70;
	p[0x1c] = 0;
	p[0x1c] = (int) m_alloc(0x74, g_6a8f64);
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
	p[0x1] = 0x63347335;
	p[0x2] = 2;
	p[0x3] = 0x3fae;
	p[0x4] = (int) g_6a8ef0;
	p[0x5] = 0x3fb1;
	p[0x6] = (int) g_6a8edc;
	p[0x7] = 0x3fb0;
	p[0x8] = (int) g_6a8ecc;
	p[0x9] = 0x3fb2;
	p[0xa] = (int) g_6a8eb8;
	p[0xb] = 0x429;
	p[0xc] = 0x8e;
	p[0xd] = (int) fcn_0057f930;
	p[0xf] = (int) fcn_0057f8b0;
	p[0xe] = (int) fcn_0057f770;
	p[0x10] = 1;
	p[0x11] = 0x2148;
	p[0x12] = 0xa;
	p[0x1a] = 0x5f77;
	p[0x1b] = 0x1f70;
	p[0x1c] = 0;
	p[0x1c] = (int) m_alloc(0x74, g_6a8f04);
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
	p[0x0] = 4;
	p[0x1] = 0x75747234;
	p[0x2] = 3;
	p[0x3] = 0x3fb3;
	p[0x4] = (int) g_6a8e90;
	p[0x5] = 0;
	p[0x6] = 0;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0xb] = -1;
	p[0xc] = 0x163;
	p[0xd] = 0;
	p[0xe] = 0;
	p[0x10] = 0;
	p[0x11] = 0;
	p[0x12] = 0xb;
	p[0x1a] = 0x1837;
	p[0x1b] = 0x1f70;
	p[0x1c] = 0;
	g_774a08 = fcn_004c3100(g_6a8ea0, 0);
	return first;
fail:
	fcn_00580cf0(first);
	return 0;
}
