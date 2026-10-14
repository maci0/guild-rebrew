/* Owned (both targets) by src/GOLDTL.fcn_00549330.c. */
extern char g_7f4ca4[];




void* __cdecl fcn_00508e40(int);
void __cdecl fcn_004ae080(char*, char*, char**, int*);
int __cdecl fcn_0064eeec(char*);
int __cdecl fcn_004ae0f0(int);
int __cdecl fcn_004ae260(int);
void __cdecl fcn_0051af00(void*, int, ...);

/* The reference builds a frame (push ebp; mov ebp,esp; sub esp,0x20c) and
 * addresses the 0x200 scratch buffer off ebp; section 13 of
 * docs/msvc6-c-shapes.md. */
#pragma optimize("y", off)
int __cdecl fcn_004afa10(int a1, int a2, int a3, char* a4, int a5)
{
	char buf[0x200];
	char* e = 0;
	int v2 = 0;
	int n = 0x200;
	char* p = buf;
	char* q;
	int i;
	int r;
	int flag;

	/* The original's zero-fill is the 24-byte hand-written block-fill prelude
	 * (docs/msvc6-c-shapes.md section 11, docs/codegen-walls.md section 6b);
	 * no msvc6 C spelling emits it.  Reproduced as a block-fill with ordinary
	 * named operands. */
	__asm {
		mov edi, p
		mov ebx, n
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
	{
		int len;

		fcn_004ae080(a4, buf, &p, &len);
		if (len != 1) {
			return 0;
		}
		r = fcn_0064eeec(a4 + (int) p);
	}
	if (r < 0 || r > 2) {
		return 0;
	}
	flag = 1;
	if (r == 0) {
		flag = 0;
	} else {
		v2 = (r != 1);
	}
	if (a1 == 1) {
		e = (char*) fcn_00508e40(*(int*) ((char*) a2 + a3 * 8 + 4));
		if (e == 0 || *(unsigned char*) (e + 8) <= 0) {
			return 0;
		}
	} else {
		i = 0;
		q = g_7f4ca4;
		while ((int) q < (int) (g_7f4ca4 + 0x65400)) {
			if (fcn_004ae0f0(*(int*) q) != 0) {
				e = q - 4;
				if (flag == 0 || *(unsigned char*) (q + 5) == v2) {
					if (fcn_004ae260(i) != 0) {
						break;
					}
					e = 0;
				}
			}
			q += 0x21c;
			i++;
		}
		if (e == 0) {
			return 0;
		}
	}
	if (a1 == 0) {
		*(int*) ((char*) a2 + a3 * 8 + 4) = *(int*) ((char*) e + 4);
	}
	fcn_0051af00(a5, buf, *(unsigned short*) e);
	return 1;
}
