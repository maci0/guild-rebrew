#include <string.h>

extern char g_7f4ca0[];

char* __cdecl fcn_00508e40(int);
int __cdecl fcn_0064eeec(char*);
int __cdecl fcn_004ae130(int);
void __cdecl fcn_004c54c0(int, int, int, int);

// FUNCTION: GOLD 0x004b04a0
// SIZE: 320
// FUNCTION: GOLDTL 0x4b05e0
// SIZE: 320

int __cdecl fcn_004b05e0(int* a1, int a2, char* a3)
{
	char* e;
	int n;
	int i;

	if (a1 == 0 || a2 >= 8)
		return 0;
	e = fcn_00508e40(a1[a2 * 2 + 1]);
	if (e == 0)
		return 0;
	if (*a3 != '-')
		return 0;
	{
		int sign[2] = { -1, 1 };
		char names[2][6] = { "MINUS", "PLUS" };

		a3++;
		for (i = 0; i < 2; i++) {
			if (memcmp(a3, names[i], strlen(names[i])) == 0)
				break;
		}
		if (i >= 2)
			return 0;
		a3 += strlen(names[i]);
		if (*a3 != '_')
			return 0;
		a3++;
		n = fcn_0064eeec(a3) * sign[i] * 2;
	}
	for (i = 0; i < 768; i++) {
		if (fcn_004ae130(i) != 0
		    && (g_7f4ca0[i * 540 + 0x166] != 0 || g_7f4ca0[i * 540 + 0x169] != 0))
			fcn_004c54c0(*(int*) (e + 4), *(int*) (g_7f4ca0 + i * 540 + 4), n, 1);
	}
	return 1;
}
