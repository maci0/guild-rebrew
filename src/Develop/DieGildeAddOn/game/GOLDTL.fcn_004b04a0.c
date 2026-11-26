#include <string.h>

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl atoi(char*);
int __cdecl gm_AccumulateTyped2(char*);
void __cdecl fcn_004c51a0(int, int, int, int);


/* ADDRESS: GOLDTL 0x004b04a0 */
int __cdecl fcn_004b04a0(int* entries, int index, char* text)
{
	int sign[2] = { -1, 1 };
	char names[2][6] = { "MINUS", "PLUS" };
	char* e;
	float f;
	int amount;
	int i;

	if (entries == 0 || index >= 8)
		return 0;
	e = gm_LookupEntityRecordById(entries[index * 2 + 1]);
	if (e == 0)
		return 0;
	if (*text != '-')
		return 0;
	text++;
	for (i = 0; i < 2; i++) {
		if (memcmp(text, names[i], strlen(names[i])) == 0)
			break;
	}
	if (i >= 2)
		return 0;
	text += strlen(names[i]);
	if (*text != '_')
		return 0;
	text++;
	f = atoi(text) * 0.01f;
	amount = (int) (gm_AccumulateTyped2(e) * f);
	if (sign[i] == -1)
		fcn_004c51a0(-1, *(int*) (e + 4), 0, amount);
	else
		fcn_004c51a0(*(int*) (e + 4), -1, 0, amount);
	return 1;
}
