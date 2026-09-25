// FUNCTION: GOLD 0x00425bc0
// SIZE: 284
// FUNCTION: GOLDTL 0x00421fe0
// SIZE: 284

extern int g_6b7d7c;
extern char* g_14cbbe4;
extern char g_14cbc20[];
extern int g_6b7d70;
extern int g_6b7e8c;
extern char* g_6b7e88;
extern char g_678e2c[];
extern char g_678df0[];
extern char g_14cbae0[];
int __cdecl fcn_0042a120(int* h, int a, int b, int c);
char* __cdecl fcn_0041db70(int size, char* tag);
int __cdecl fcn_0042a510(int h, char* slot);
long __cdecl fcn_0064e561(long* t);
void __cdecl fcn_0064d3eb(unsigned int seed);
int __cdecl fcn_0064d41a(char* buf, char* fmt, ...);

int __cdecl fcn_00421fe0(int id, int count, int a, int b, int c)
{
	int r;
	int i;
	int n;

	r = 0;
	if (g_6b7d7c != 0) {
		goto fail;
	}
	g_14cbbe4 = g_14cbc20;
	if (fcn_0042a120(&g_6b7d7c, a, b, c) != 0) {
		goto fail;
	}
	g_6b7d70 = id;
	if (id == 0) {
		g_6b7d70 = 0x1fffcc;
	}
	g_6b7e8c = count;
	g_6b7e88 = fcn_0041db70(count * 0x30, g_678e2c);
	if (g_6b7e88 != 0) {
		n = g_6b7e8c * 0x30;
		__asm {
			mov edi, g_6b7e88
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
		for (i = 0; i < g_6b7e8c; i++) {
			if (fcn_0042a510(g_6b7d7c, g_6b7e88 + i * 0x30) == -1) {
				r = -1;
			}
		}
		fcn_0064d3eb(fcn_0064e561(0));
		fcn_0064d41a(g_14cbae0, g_678df0, id);
		return r;
	}
fail:
	return -1;
}
