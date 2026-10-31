#include <string.h>

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_0064eeec(char*);
int __cdecl gm_AccumulateTyped2(char*);
void __cdecl fcn_004c51a0(int, int, int, int);


/* ADDRESS: GOLDTL 0x004b04a0 */
int __cdecl fcn_004b04a0(int* a1, int a2, char* a3)
{
	int sign[2] = { -1, 1 };
	char names[2][6] = { "MINUS", "PLUS" };
	char* e;
	float f;
	int amount;
	int i;

	if (a1 == 0 || a2 >= 8)
		return 0;
	e = gm_LookupEntityRecordById(a1[a2 * 2 + 1]);
	if (e == 0)
		return 0;
	if (*a3 != '-')
		return 0;
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
	f = fcn_0064eeec(a3) * 0.01f;
	amount = (int) (gm_AccumulateTyped2(e) * f);
	if (sign[i] == -1)
		fcn_004c51a0(-1, *(int*) (e + 4), 0, amount);
	else
		fcn_004c51a0(*(int*) (e + 4), -1, 0, amount);
	return 1;
}
