// FUNCTION: GOLDTL 0x00583760

extern char g_6a9010[];
extern char g_6a903c[];
extern char g_6a9050[];
extern char g_6a9064[];
extern char g_6a9078[];
extern char g_6a908c[];
extern char g_6a90a0[];
extern char g_6a90b4[];
extern char g_6a90c8[];
extern char g_6a90dc[];
extern char g_6a90f4[];
extern char g_6a9108[];
extern char g_6a911c[];
extern char g_6a9130[];
extern char g_6a9144[];
extern char g_6a915c[];
extern char g_6a9170[];
extern char g_6a9184[];
extern char g_6a919c[];
extern char g_6a91b0[];
extern char g_6a91c4[];
extern char g_6a91d8[];
extern char g_6a91ec[];
extern char g_6a9200[];
extern char g_6a9214[];
extern char g_6a9228[];
extern char g_6a923c[];
extern char g_6a924c[];
extern char g_6a9260[];

extern char g_6a9024[];
extern int g_774a0c;
extern int g_1040494;
int __cdecl fcn_004c3100(char*, int);
int* __cdecl m_AllocTracked(int size, char* tag);
void __cdecl fcn_00580cf0(int*);
void __cdecl fcn_0057fac0(void);
void __cdecl fcn_0057fb20(void);
void __cdecl fcn_0057fb60(void);
void __cdecl fcn_0057fdd0(void);
void __cdecl fcn_0057fe50(void);
void __cdecl fcn_0057fea0(void);
void __cdecl fcn_0057ff20(void);

int* __cdecl fcn_00583760(void)
{
	int* first;
	int* p;

	first = 0;
	p = m_AllocTracked(0x74, g_6a9260);
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
	p[0x0] = 5;
	p[0x1] = 0x6e747235;
	p[0x2] = 0;
	p[0x3] = 0x3fb5;
	p[0x4] = (int) g_6a923c;
	p[0x5] = 0;
	p[0x6] = 0;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0xb] = -1;
	p[0xc] = 0x8e;
	p[0xd] = (int) fcn_0057fdd0;
	p[0xe] = 0;
	p[0x10] = 0;
	p[0x11] = 0;
	p[0x12] = 0xb;
	p[0x1a] = 0x5f77;
	p[0x1b] = 0x1f70;
	p[0x1c] = 0;
	first = p;
	p[0x1c] = (int) m_AllocTracked(0x74, g_6a924c);
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
	p[0x0] = 5;
	p[0x1] = 0x63357331;
	p[0x2] = 1;
	p[0x3] = 0x3fb7;
	p[0x4] = (int) g_6a9214;
	p[0x5] = 0x3fb9;
	p[0x6] = (int) g_6a9200;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0x9] = 0x3fba;
	p[0xa] = (int) g_6a91ec;
	p[0xb] = 0x429;
	p[0xc] = 0x163;
	p[0xd] = 0;
	p[0xe] = 0;
	p[0x10] = 0x2c;
	p[0x11] = 0x1aa;
	p[0x12] = 0xb;
	p[0x1a] = 0x1877;
	p[0x1b] = 0x1f78;
	p[0x1c] = 0;
	p[0x1c] = (int) m_AllocTracked(0x74, g_6a9228);
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
	p[0x0] = 5;
	p[0x1] = 0x63357333;
	p[0x2] = 1;
	p[0x3] = 0x3fc5;
	p[0x4] = (int) g_6a91c4;
	p[0x5] = 0x3fc7;
	p[0x6] = (int) g_6a91b0;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0x9] = 0x3fc8;
	p[0xa] = (int) g_6a919c;
	p[0xb] = 0x429;
	p[0xc] = 0x8e;
	p[0xd] = 0;
	p[0xe] = 0;
	p[0x10] = 0xf;
	p[0x11] = 0x2148;
	p[0x12] = 0xa;
	p[0x1a] = 0x18f7;
	p[0x1b] = 0x1f78;
	p[0x1c] = 0;
	p[0x1c] = (int) m_AllocTracked(0x74, g_6a91d8);
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
	p[0x0] = 5;
	p[0x1] = 0x63357332;
	p[0x2] = 2;
	p[0x3] = 0x3fbb;
	p[0x4] = (int) g_6a9170;
	p[0x5] = 0x3fbe;
	p[0x6] = (int) g_6a915c;
	p[0x7] = 0x3fbd;
	p[0x8] = (int) g_6a9144;
	p[0x9] = 0x3fbf;
	p[0xa] = (int) g_6a9130;
	p[0xb] = 0x429;
	p[0xc] = 0xd5;
	p[0xe] = 0;
	p[0xd] = (int) fcn_0057fac0;
	p[0xf] = (int) fcn_0057fb20;
	p[0x10] = 0x17;
	p[0x11] = 0x58c;
	p[0x12] = 9;
	p[0x1a] = 0x1877;
	p[0x13] = 0x29;
	p[0x14] = 0;
	p[0x15] = 0;
	p[0x17] = 2;
	p[0x18] = (int) fcn_0057fb60;
	p[0x19] = (int) m_AllocTracked(0x58, g_6a9184);
	if (p[0x19] == 0) {
		goto fail;
	}
	if (g_1040494 == 800) {
		((float*) p[0x19])[0] = 140.0f;
		((float*) p[0x19])[1] = 170.0f;
		((float*) p[0x19])[2] = 250.0f;
		((float*) p[0x19])[3] = 290.0f;
		((float*) p[0x19])[4] = 450.0f;
		((float*) p[0x19])[5] = 290.0f;
		((float*) p[0x19])[6] = 600.0f;
		((float*) p[0x19])[7] = 305.0f;
	} else if (g_1040494 == 1024) {
		((float*) p[0x19])[0] = 250.0f;
		((float*) p[0x19])[1] = 255.0f;
		((float*) p[0x19])[2] = 400.0f;
		((float*) p[0x19])[3] = 400.0f;
		((float*) p[0x19])[4] = 600.0f;
		((float*) p[0x19])[5] = 450.0f;
		((float*) p[0x19])[6] = 710.0f;
		((float*) p[0x19])[7] = 390.0f;
	} else {
		((float*) p[0x19])[0] = 626.0f;
		((float*) p[0x19])[1] = 350.0f;
		((float*) p[0x19])[2] = 636.0f;
		((float*) p[0x19])[3] = 430.0f;
		((float*) p[0x19])[4] = 376.0f;
		((float*) p[0x19])[5] = 440.0f;
		((float*) p[0x19])[6] = 336.0f;
		((float*) p[0x19])[7] = 320.0f;
	}
	((float*) p[0x19])[8] = 35.0f;
	((float*) p[0x19])[9] = 177.0f;
	((float*) p[0x19])[10] = 106.0f;
	if (g_1040494 == 800) {
		((float*) p[0x19])[11] = 700.0f;
		((float*) p[0x19])[12] = 310.0f;
		((float*) p[0x19])[13] = 700.0f;
		((float*) p[0x19])[14] = 310.0f;
		((float*) p[0x19])[15] = 700.0f;
		((float*) p[0x19])[16] = 310.0f;
		((float*) p[0x19])[17] = 700.0f;
		((float*) p[0x19])[18] = 310.0f;
	} else if (g_1040494 == 1024) {
		((float*) p[0x19])[11] = 924.0f;
		((float*) p[0x19])[12] = 310.0f;
		((float*) p[0x19])[13] = 924.0f;
		((float*) p[0x19])[14] = 310.0f;
		((float*) p[0x19])[15] = 924.0f;
		((float*) p[0x19])[16] = 310.0f;
		((float*) p[0x19])[17] = 924.0f;
		((float*) p[0x19])[18] = 310.0f;
	} else {
		((float*) p[0x19])[11] = 560.0f;
		((float*) p[0x19])[12] = 420.0f;
		((float*) p[0x19])[13] = 710.0f;
		((float*) p[0x19])[14] = 370.0f;
		((float*) p[0x19])[15] = 860.0f;
		((float*) p[0x19])[16] = 320.0f;
		((float*) p[0x19])[17] = 1020.0f;
		((float*) p[0x19])[18] = 310.0f;
	}
	((float*) p[0x19])[19] = 0.0f;
	((float*) p[0x19])[20] = 7.0f;
	((float*) p[0x19])[21] = 21.0f;
	p[0x1c] = 0;
	p[0x1c] = (int) m_AllocTracked(0x74, g_6a91d8);
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
	p[0x0] = 5;
	p[0x1] = 0x63357332;
	p[0x2] = 2;
	p[0x3] = 0x3fc0;
	p[0x4] = (int) g_6a9108;
	p[0x5] = 0x3fc3;
	p[0x6] = (int) g_6a90f4;
	p[0x7] = 0x3fc2;
	p[0x8] = (int) g_6a90dc;
	p[0x9] = 0x3fc4;
	p[0xa] = (int) g_6a90c8;
	p[0xb] = 0x429;
	p[0xc] = 0xd5;
	p[0xe] = 0;
	p[0x10] = 0x14;
	p[0x11] = 0x2148;
	p[0x12] = 9;
	p[0x1a] = 0x1877;
	p[0x13] = 0x2d;
	p[0x14] = 0;
	p[0x15] = 0;
	p[0x1c] = 0;
	p[0x1c] = (int) m_AllocTracked(0x74, g_6a911c);
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
	p[0x0] = 5;
	p[0x1] = 0x63357334;
	p[0x2] = 1;
	p[0x3] = 0x3fc9;
	p[0x4] = (int) g_6a90a0;
	p[0x5] = 0x3fcb;
	p[0x6] = (int) g_6a908c;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0x9] = 0x3fcc;
	p[0xa] = (int) g_6a9078;
	p[0xb] = 0x429;
	p[0xc] = 0x163;
	p[0xd] = (int) fcn_0057fe50;
	p[0xe] = 0;
	p[0x10] = 0x2e;
	p[0x11] = 0x2148;
	p[0x12] = 0xa;
	p[0x1a] = 0x18f7;
	p[0x1b] = 0x3f78;
	p[0x1c] = 0;
	p[0x1c] = (int) m_AllocTracked(0x74, g_6a90b4);
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
	p[0x0] = 5;
	p[0x1] = 0x63357335;
	p[0x2] = 1;
	p[0x3] = 0x3fcd;
	p[0x4] = (int) g_6a9064;
	p[0x5] = 0x3fcf;
	p[0x6] = (int) g_6a9050;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0x9] = 0x3fd0;
	p[0xa] = (int) g_6a903c;
	p[0xb] = 0x429;
	p[0xc] = 0xd5;
	p[0xd] = (int) fcn_0057fea0;
	p[0xe] = 0;
	p[0x10] = 0x2f;
	p[0x11] = 0x2148;
	p[0x12] = 0xa;
	p[0x1a] = 0x18f7;
	p[0x1b] = 0xbf78;
	p[0x1c] = 0;
	p[0x1c] = (int) m_AllocTracked(0x74, g_6a90b4);
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
	p[0x0] = 6;
	p[0x1] = 0x63357336;
	p[0x2] = 1;
	p[0x3] = 0x3fd1;
	p[0x4] = (int) g_6a9010;
	p[0x5] = 0;
	p[0x6] = 0;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0xb] = 0x429;
	p[0xc] = 0x8e;
	p[0xd] = (int) fcn_0057ff20;
	p[0xe] = 0;
	p[0x10] = 0x30;
	p[0x11] = 0;
	p[0x12] = 0xb;
	p[0x1a] = 0x18f7;
	p[0x1b] = 0xbf78;
	p[0x1c] = 0;
	g_774a0c = fcn_004c3100(g_6a9024, 0);
	return first;
fail:
	fcn_00580cf0(first);
	return 0;
}
