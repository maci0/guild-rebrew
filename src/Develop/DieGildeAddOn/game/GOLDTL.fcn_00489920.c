#include <string.h>

#pragma pack(push, 1)
typedef struct {
	int x00;
	unsigned short x04;
	int x06;
	int x0a;
} SIM_CLOCK_489920;
#pragma pack(pop)

int __cdecl gm_CanEvaluateMaster(char* e);
unsigned short __cdecl gm_RandomMod(int n);
char* __cdecl fcn_00502cd0(int a, int b, int c, ...);
char* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl fcn_00500bb0(SIM_CLOCK_489920* clock, int arg2, int arg3, int arg4);
void __cdecl fcn_004c5530(int msg);

/* ADDRESS: GOLDTL 0x00489920 */
void __cdecl fcn_00489920(char* e)
{
	char* o;
	char* q;
	char s[0xf8];

	if (gm_CanEvaluateMaster(e) == 0) {
		return;
	}
	if ((*(unsigned char*) (e + 0x1b4) & 1) == 0) {
		return;
	}
	o = *(char**) (e + 0x16c);
	q = fcn_00502cd0(*(int*) (o + 0x5d), 3, 6, 4, 0x1d, 3, *(unsigned short*) (o + 0x27));
	if (q == 0) {
		return;
	}
	do {
		if ((unsigned char) q[0x12] < (gm_RandomMod(0x20) & 0xffff) + 0x28) {
			memset(s, 0, sizeof(s));
			*(char*) (s + 4) = 0x10;
			*(int*) (s + 8) = *(int*) (*(unsigned short*) (o + 0x27) * 0x21c + 0x7f4ca4);
			*(int*) (s + 0xc) = *(int*) (o + 1);
			*(int*) (s + 0x28) = *(int*) 0x7f4c00;
			*(int*) (s + 0x2c) = *(int*) 0x7f4c04;
			*(int*) (s + 0x30) = *(int*) 0x7f4c08;
			*(unsigned short*) (s + 0x34) = *(unsigned short*) 0x7f4c0c;
			*(char*) (s + 0x36) = 1;
			fcn_00500bb0((SIM_CLOCK_489920*) (s + 0x28), 0, 0, 10);
			*(int*) (s + 0x58) = *(int*) (q + 2);
			*(int*) (s + 0x5c) = 100 - *(unsigned char*) (q + 0x12);
			*(int*) (s + 0x64) = 5;
			*(int*) (s + 0x84) = 0;
			fcn_004c5530((int) s);
		}
		q = gm_NextEntityQueryMatch();
	} while (q != 0);
}
