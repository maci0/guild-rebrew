// FUNCTION: GOLDTL 0x005816f0
// SIZE: 1839

extern char g_6a8774[];
extern char g_6a879c[];
extern char g_6a87b0[];
extern char g_6a87c4[];
extern char g_6a87d8[];
extern char g_6a87ec[];
extern char g_6a8800[];
extern char g_6a8814[];
extern char g_6a8828[];
extern char g_6a883c[];
extern char g_6a8850[];
extern char g_6a8864[];
extern char g_6a8878[];
extern char g_6a888c[];
extern char g_6a88a0[];
extern char g_6a88b4[];
extern char g_6a88c8[];
extern char g_6a88dc[];
extern char g_6a88f0[];
extern char g_6a8904[];
extern char g_6a8918[];
extern char g_6a892c[];
extern char g_6a8940[];
extern char g_6a8954[];
extern char g_6a8968[];
extern char g_6a897c[];
extern char g_6a8990[];
extern char g_6a89a4[];
extern char g_6a89b8[];
extern char g_6a89c8[];
extern char g_6a89dc[];

extern char g_6a8784[];
extern int g_774a00;
int __cdecl fcn_004c3100(char*, int);
int* __cdecl fcn_0041db70(int size, char* tag);
void __cdecl fcn_00580cf0(int*);
void __cdecl fcn_0057ecf0(void);
void __cdecl fcn_0057ed60(void);
void __cdecl fcn_0057edf0(void);
void __cdecl fcn_0057ee40(void);
void __cdecl fcn_0057ee60(void);
void __cdecl fcn_0057eea0(void);
void __cdecl fcn_0057eee0(void);
void __cdecl fcn_0057f090(void);
void __cdecl fcn_0057f100(void);
void __cdecl fcn_0057f130(void);
void __cdecl fcn_0057f180(void);
void __cdecl fcn_0057f1d0(void);
void __cdecl fcn_0057f220(void);
void __cdecl fcn_0057f2e0(void);
void __cdecl fcn_0057f310(void);
void __cdecl fcn_0057f3b0(void);
void __cdecl fcn_0057f3e0(void);

int* __cdecl fcn_005816f0(void)
{
	int* first;
	int* p;

	first = 0;
	p = fcn_0041db70(0x74, g_6a89dc);
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
	p[0x0] = 2;
	p[0x1] = 0x6e747232;
	p[0x2] = 0;
	p[0x3] = 0x3f53;
	p[0x4] = (int) g_6a89b8;
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
	p[0x1a] = 0x1837;
	p[0x1b] = 0;
	p[0x1c] = 0;
	first = p;
	p[0x1c] = (int) fcn_0041db70(0x74, g_6a89c8);
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
	p[0x0] = 2;
	p[0x1] = 0x63327341;
	p[0x2] = 1;
	p[0x3] = 0x3f55;
	p[0x4] = (int) g_6a8990;
	p[0x5] = 0x3f57;
	p[0x6] = (int) g_6a897c;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0x9] = 0x3f58;
	p[0xa] = (int) g_6a8968;
	p[0xb] = 0x429;
	p[0xc] = 0x8e;
	p[0xf] = (int) fcn_0057ecf0;
	p[0xd] = 0;
	p[0xe] = (int) fcn_0057f090;
	p[0x10] = 1;
	p[0x11] = 0x2148;
	p[0x12] = 0xa;
	p[0x1a] = 0x1837;
	p[0x1b] = 0;
	p[0x1c] = 0;
	p[0x1c] = (int) fcn_0041db70(0x74, g_6a89a4);
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
	p[0x0] = 2;
	p[0x1] = 0x63327342;
	p[0x2] = 1;
	p[0x3] = 0x3f59;
	p[0x4] = (int) g_6a8940;
	p[0x5] = 0x3f5b;
	p[0x6] = (int) g_6a892c;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0x9] = 0x3f5c;
	p[0xa] = (int) g_6a8918;
	p[0xb] = 0x429;
	p[0xc] = 0xd5;
	p[0xf] = (int) fcn_0057ed60;
	p[0xd] = (int) fcn_0057f100;
	p[0xe] = (int) fcn_0057f130;
	p[0x10] = 1;
	p[0x11] = 0x2148;
	p[0x12] = 0xb;
	p[0x1a] = 0x5837;
	p[0x1b] = 0;
	p[0x1c] = 0;
	p[0x1c] = (int) fcn_0041db70(0x74, g_6a8954);
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
	p[0x0] = 2;
	p[0x1] = 0x63327343;
	p[0x2] = 1;
	p[0x3] = 0x3f5d;
	p[0x4] = (int) g_6a88f0;
	p[0x5] = 0x3f5f;
	p[0x6] = (int) g_6a88dc;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0x9] = 0x3f60;
	p[0xa] = (int) g_6a88c8;
	p[0xb] = 0x429;
	p[0xc] = 0x8e;
	p[0xf] = (int) fcn_0057edf0;
	p[0xd] = 0;
	p[0xe] = (int) fcn_0057f180;
	p[0x10] = 1;
	p[0x11] = 0x2148;
	p[0x12] = 0xa;
	p[0x1a] = 0x5837;
	p[0x1b] = 0xe00;
	p[0x1c] = 0;
	p[0x1c] = (int) fcn_0041db70(0x74, g_6a8904);
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
	p[0x0] = 2;
	p[0x1] = 0x63327344;
	p[0x2] = 1;
	p[0x3] = 0x3f61;
	p[0x4] = (int) g_6a88a0;
	p[0x5] = 0x3f63;
	p[0x6] = (int) g_6a888c;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0x9] = 0x3f64;
	p[0xa] = (int) g_6a8878;
	p[0xb] = 0x429;
	p[0xc] = 0x8e;
	p[0xd] = 0;
	p[0xf] = (int) fcn_0057ee40;
	p[0xe] = (int) fcn_0057f1d0;
	p[0x10] = 1;
	p[0x11] = 0x2148;
	p[0x12] = 0xa;
	p[0x1a] = 0x5837;
	p[0x1b] = 0x1e00;
	p[0x1c] = 0;
	p[0x1c] = (int) fcn_0041db70(0x74, g_6a88b4);
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
	p[0x0] = 2;
	p[0x1] = 0x63327345;
	p[0x2] = 1;
	p[0x3] = 0x3f65;
	p[0x4] = (int) g_6a8850;
	p[0x5] = 0x3f67;
	p[0x6] = (int) g_6a883c;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0x9] = 0x3f68;
	p[0xa] = (int) g_6a8828;
	p[0xb] = 0x429;
	p[0xc] = 0x8e;
	p[0xf] = (int) fcn_0057ee60;
	p[0xd] = (int) fcn_0057f2e0;
	p[0xe] = (int) fcn_0057f220;
	p[0x10] = 1;
	p[0x11] = 0x2148;
	p[0x12] = 0xa;
	p[0x1a] = 0x5837;
	p[0x1b] = 0x1e00;
	p[0x1c] = 0;
	p[0x1c] = (int) fcn_0041db70(0x74, g_6a8864);
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
	p[0x0] = 2;
	p[0x1] = 0x63327346;
	p[0x2] = 1;
	p[0x3] = 0x3f69;
	p[0x4] = (int) g_6a8800;
	p[0x5] = 0x3f6b;
	p[0x6] = (int) g_6a87ec;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0x9] = 0x3f6c;
	p[0xa] = (int) g_6a87d8;
	p[0xb] = 0x429;
	p[0xc] = 0x8e;
	p[0xf] = (int) fcn_0057eea0;
	p[0xd] = (int) fcn_0057f3b0;
	p[0xe] = (int) fcn_0057f310;
	p[0x10] = 1;
	p[0x11] = 0x2148;
	p[0x12] = 0xa;
	p[0x1a] = 0x5837;
	p[0x1b] = 0x1e00;
	p[0x1c] = 0;
	p[0x1c] = (int) fcn_0041db70(0x74, g_6a8814);
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
	p[0x0] = 2;
	p[0x1] = 0x63327347;
	p[0x2] = 1;
	p[0x3] = 0x3f6d;
	p[0x4] = (int) g_6a87b0;
	p[0x5] = 0x3f6f;
	p[0x6] = (int) g_6a879c;
	p[0x7] = 0;
	p[0x8] = 0;
	p[0xb] = 0x429;
	p[0xc] = 0x8e;
	p[0xf] = (int) fcn_0057eee0;
	p[0xd] = 0;
	p[0xe] = (int) fcn_0057f3e0;
	p[0x10] = 1;
	p[0x11] = 0x429;
	p[0x12] = 0xa;
	p[0x1a] = 0x5837;
	p[0x1b] = 0x1e00;
	p[0x1c] = 0;
	p[0x1c] = (int) fcn_0041db70(0x74, g_6a87c4);
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
	p[0x0] = 2;
	p[0x1] = 0x75747232;
	p[0x2] = 3;
	p[0x3] = 0x3f70;
	p[0x4] = (int) g_6a8774;
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
	p[0x1a] = 0x5837;
	p[0x1b] = 0x1e00;
	p[0x1c] = 0;
	g_774a00 = fcn_004c3100(g_6a8784, 0);
	return first;
fail:
	fcn_00580cf0(first);
	return 0;
}
