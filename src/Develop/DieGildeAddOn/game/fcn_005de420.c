#include <string.h>

extern float g_6629d0;
extern float g_662a3c;
extern unsigned char g_773d75;
extern void* g_14a558c;

int __cdecl fcn_005015e0(int* out, int a, int b, int c);
int __cdecl fcn_005bdc30(int a, int* b, void* c, int d, int e);
int __cdecl fcn_00502cd0(int a, int b, ...);
int __cdecl fcn_00502850(void);
float __cdecl fcn_0042e450(void);
void __cdecl fcn_004c51f0(int a, int b, int c, int d, unsigned char e, int f);
void __cdecl fcn_0051af00(char* buf, int id, ...);
void __cdecl fcn_00545d40(int a, int b, char* buf, int c, int d, int e);
void __cdecl fcn_005dbe90(char* buf);

/* ADDRESS: GOLDTL 0x005de420 */
int __cdecl fcn_005de420(char* a0, char* a1)
{
	int one;
	int v12;
	int v10[0x14];
	char v14[0x200];
	char v13[0x800];
	char* base;
	int* rec;
	int* e;
	int* f;
	int v;

	one = 1;
	if (a0[2] == 6) {
		memset(v10, 0, 0x50);
		memset(&v10[7], -1, 0x20);
		v10[0] = one;
		v10[1] = -1;
		v10[4] = 6;
		v10[2] = 0xa0744300;
		v10[3] = one;
		v12 = fcn_005bdc30(one, v10, g_14a558c, 0, 0);
		if (v12 == 0)
			return 0;
	} else {
		fcn_005015e0(&v12, 0, 0, *(int*) (a1 + 4));
		if (v12 == 0)
			return 0;
	}

	rec = (int*) v12;
	base = (char*) ((int*) 0x7f4ca0
	    + (int) *(unsigned short*) ((char*) v12 + 0x27) * 135);
	e = (int*) fcn_00502cd0(*(int*) ((char*) rec + 0x5d), 2, 6, 0, 0x2a);
	if (e != 0) {
		fcn_00502cd0(*(int*) ((char*) e + 0x14), one, 5);	/* result unused */
		f = (int*) fcn_00502cd0(*(int*) ((char*) e + 0x14), one, 5);
		while (f != 0) {
			if (*(int*) ((char*) f + 0xe) > one) {
				v = (((int) ((fcn_0042e450() * g_6629d0 + g_662a3c)
				    * *(int*) ((char*) f + 0xe))) < one) ? one
				    : (int) ((fcn_0042e450() * g_6629d0 + g_662a3c)
				    * *(int*) ((char*) f + 0xe));
				fcn_004c51f0(-1, *(int*) ((char*) e + 2),
				    *(unsigned short*) f, v, g_773d75, 0);
			}
			f = (int*) fcn_00502850();
		}
	}

	if (base[2] == 6 || base[2] == 7) {
		fcn_0051af00(v13, 0x100c, v12);
		fcn_00545d40(*(int*) (base + 4), -1, v13, 0, 0x5fb, 0);
	}
	if (a0[2] == 6) {
		fcn_0051af00(v14, 0x109d,
		    *(unsigned short*) ((char*) v12 + 0x27), v12);
		fcn_0051af00(v13, 0xfe8, v14);
		fcn_005dbe90(v13);
	}
	*(int*) (a1 + 0x10) = one;
	return one;
}
